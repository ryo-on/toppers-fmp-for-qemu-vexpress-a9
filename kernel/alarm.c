/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: alarm.c 721 2010-10-14 02:53:19Z ertl-honda $
 */

/*
 *		���顼��ϥ�ɥ鵡ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "alarm.h"
#include "mp.h"
#include "spin_lock.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_ALM_ENTER
#define LOG_ALM_ENTER(p_almcb)
#endif /* LOG_ALM_ENTER */

#ifndef LOG_ALM_LEAVE
#define LOG_ALM_LEAVE(p_almcb)
#endif /* LOG_ALM_LEAVE */

#ifndef LOG_STA_ALM_ENTER
#define LOG_STA_ALM_ENTER(almid, almtim)
#endif /* LOG_STA_ALM_ENTER */

#ifndef LOG_STA_ALM_LEAVE
#define LOG_STA_ALM_LEAVE(ercd)
#endif /* LOG_STA_ALM_LEAVE */

#ifndef LOG_MSTA_ALM_ENTER
#define LOG_MSTA_ALM_ENTER(almid, almtim, prcid)
#endif /* LOG_STA_ALM_ENTER */

#ifndef LOG_MSTA_ALM_LEAVE
#define LOG_MSTA_ALM_LEAVE(ercd)
#endif /* LOG_STA_ALM_LEAVE */

#ifndef LOG_ALMMIG
#define LOG_ALMMIG(p_almcb, src_id, dest_id)
#endif /* LOG_ALMMIG */

#ifndef LOG_ISTA_ALM_ENTER
#define LOG_ISTA_ALM_ENTER(almid, almtim)
#endif /* LOG_ISTA_ALM_ENTER */

#ifndef LOG_ISTA_ALM_LEAVE
#define LOG_ISTA_ALM_LEAVE(ercd)
#endif /* LOG_ISTA_ALM_LEAVE */

#ifndef LOG_IMSTA_ALM_ENTER
#define LOG_IMSTA_ALM_ENTER(almid, almtim, prcid)
#endif /* LOG_ISTA_ALM_ENTER */

#ifndef LOG_IMSTA_ALM_LEAVE
#define LOG_IMSTA_ALM_LEAVE(ercd)
#endif /* LOG_ISTA_ALM_LEAVE */

#ifndef LOG_STP_ALM_ENTER
#define LOG_STP_ALM_ENTER(almid)
#endif /* LOG_STP_ALM_ENTER */

#ifndef LOG_STP_ALM_LEAVE
#define LOG_STP_ALM_LEAVE(ercd)
#endif /* LOG_STP_ALM_LEAVE */

#ifndef LOG_ISTP_ALM_ENTER
#define LOG_ISTP_ALM_ENTER(almid)
#endif /* LOG_ISTP_ALM_ENTER */

#ifndef LOG_ISTP_ALM_LEAVE
#define LOG_ISTP_ALM_LEAVE(ercd)
#endif /* LOG_ISTP_ALM_LEAVE */

#ifndef LOG_REF_ALM_ENTER
#define LOG_REF_ALM_ENTER(almid, pk_ralm)
#endif /* LOG_REF_ALM_ENTER */

#ifndef LOG_REF_ALM_LEAVE
#define LOG_REF_ALM_LEAVE(ercd, pk_ralm)
#endif /* LOG_REF_ALM_LEAVE */

/*
 *  ���顼��ϥ�ɥ�ο�
 */
#define tnum_alm	((uint_t)(tmax_almid - TMIN_ALMID + 1))

/*
 *  ���顼��ϥ�ɥ�ID���饢�顼��ϥ�ɥ�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_ALM(almid)	((uint_t)((almid) - TMIN_ALMID))
#define get_almcb(almid)	(p_almcb_table[INDEX_ALM(almid)])

/*
 *  ���顼��ϥ�ɥ鵡ǽ�ν����
 */
#ifdef TOPPERS_almini

void
initialize_alarm(void)
{
	uint_t	i;
	ALMCB	*p_almcb;
	PCB 	*p_pcb;

#ifdef TOPPERS_SYSTIM_GLOBAL
	if (!x_sense_mprc()) {
		return;
	}
	p_pcb = get_mp_p_pcb(TOPPERS_SYSTIM_PRCID);
#else  /* TOPPERS_SYSTIM_LOCAL */
	p_pcb = get_my_p_pcb();
#endif /* TOPPERS_SYSTIM_GLOBAL */

	for (i = 0; i < tnum_alm; i++) {
#ifdef TOPPERS_SYSTIM_LOCAL
		/* �������˳���դ��줿���顼��ϥ�ɥ�ν���� */
		if(alminib_table[i].iaffinity == ID_PRC(x_prc_index())){
#endif /* TOPPERS_SYSTIM_LOCAL */
			p_almcb = p_almcb_table[i];
			p_almcb->p_alminib = &alminib_table[i];
			p_almcb->almsta = false;
			p_almcb->p_pcb = p_pcb;
#ifdef TOPPERS_SYSTIM_LOCAL
		}
#endif /* TOPPERS_SYSTIM_LOCAL */
	}
}

#endif /* TOPPERS_almini */

/*
 *  ���顼��ϥ�ɥ��ư���
 */
#ifdef TOPPERS_sta_alm

ER
sta_alm(ID almid, RELTIM almtim)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_STA_ALM_ENTER(almid, almtim);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	CHECK_PAR(almtim <= TMAX_RELTIM);
	p_almcb = get_almcb(almid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_alm(p_almcb);
	if (p_almcb->almsta) {
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	else {
		p_almcb->almsta = true;
	}
	tmevtb_enqueue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb), almtim,
								(CBACK) call_almhdr, (void *) p_almcb);
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_STA_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_sta_alm */

/*
 *  ���顼��ϥ�ɥ��ư���
 */
#ifdef TOPPERS_msta_alm

#ifdef TOPPERS_SYSTIM_LOCAL

ER
msta_alm(ID almid, RELTIM almtim, ID prcid)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	LOG_MSTA_ALM_ENTER(almid, almtim, prcid);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	CHECK_PAR(almtim <= TMAX_RELTIM);
	CHECK_PRCID_INI(prcid);
	p_almcb = get_almcb(almid);
	prcid = (prcid == TPRC_INI)? p_almcb->p_alminib->iaffinity : prcid;
	CHECK_MIG(p_almcb->p_alminib->affinity_mask, prcid);

	t_lock_cpu();
	t_acquire_dual_tsk_lock_alm(p_almcb, prcid, &f_p_pcb, &t_p_pcb);
	if (p_almcb->almsta) {
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	else {
		p_almcb->almsta = true;
	}
	LOG_ALMMIG(p_almcb, f_p_pcb->prcid, prcid);
	/* ��ư��� pcb ����Ͽ */
	p_almcb->p_pcb = t_p_pcb;
	tmevtb_enqueue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb), almtim,
								(CBACK) call_almhdr, (void *) p_almcb);
	ercd = E_OK;
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_MSTA_ALM_LEAVE(ercd);
	return(ercd);
}

#else /* TOPPERS_SYSTIM_GLOBAL */

ER
msta_alm(ID almid, RELTIM almtim, ID prcid)
{
	ER		ercd = E_NOSPT;

	LOG_MSTA_ALM_ENTER(almid, almtim, prcid);
	LOG_MSTA_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SYSTIM_GLOBAL */

#endif /* TOPPERS_msta_alm */

/*
 *  ���顼��ϥ�ɥ��ư��ϡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_ista_alm

ER
ista_alm(ID almid, RELTIM almtim)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_ISTA_ALM_ENTER(almid, almtim);
	CHECK_INTCTX_UNL();
	CHECK_ALMID(almid);
	CHECK_PAR(almtim <= TMAX_RELTIM);
	p_almcb = get_almcb(almid);

	i_lock_cpu();
	p_pcb = i_acquire_tsk_lock_alm(p_almcb);
	if (p_almcb->almsta) {
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	else {
		p_almcb->almsta = true;
	}
	tmevtb_enqueue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb), almtim,
								(CBACK) call_almhdr, (void *) p_almcb);
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_ISTA_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ista_alm */

/*
 *  ���顼��ϥ�ɥ��ư��ϡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_imsta_alm

#ifdef TOPPERS_SYSTIM_LOCAL

ER
imsta_alm(ID almid, RELTIM almtim, ID prcid)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	LOG_IMSTA_ALM_ENTER(almid, almtim, prcid);
	CHECK_INTCTX_UNL();
	CHECK_ALMID(almid);
	CHECK_PAR(almtim <= TMAX_RELTIM);
	CHECK_PRCID_INI(prcid);
	p_almcb = get_almcb(almid);
	prcid = (prcid == TPRC_INI)? p_almcb->p_alminib->iaffinity : prcid;
	CHECK_MIG(p_almcb->p_alminib->affinity_mask, prcid);

	i_lock_cpu();
	i_acquire_dual_tsk_lock_alm(p_almcb, prcid, &f_p_pcb, &t_p_pcb);
	if (p_almcb->almsta) {
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	else {
		p_almcb->almsta = true;
	}

	LOG_ALMMIG(p_almcb, f_p_pcb->prcid, prcid);
	/* ��ư��� pcb ����Ͽ */
	p_almcb->p_pcb = t_p_pcb;
	tmevtb_enqueue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb), almtim,
								(CBACK) call_almhdr, (void *) p_almcb);
	ercd = E_OK;
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_IMSTA_ALM_LEAVE(ercd);
	return(ercd);
}

#else /* TOPPERS_SYSTIM_GLOBAL */

ER
imsta_alm(ID almid, RELTIM almtim, ID prcid)
{
	ER		ercd = E_NOSPT;

	LOG_IMSTA_ALM_ENTER(almid, almtim, prcid);
	LOG_IMSTA_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SYSTIM_GLOBAL */

#endif /* TOPPERS_imsta_alm */

/*
 *  ���顼��ϥ�ɥ��ư�����
 */
#ifdef TOPPERS_stp_alm

ER
stp_alm(ID almid)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_STP_ALM_ENTER(almid);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	p_almcb = get_almcb(almid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_alm(p_almcb);
	if (p_almcb->almsta) {
		p_almcb->almsta = false;
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_STP_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_stp_alm */

/*
 *  ���顼��ϥ�ɥ��ư����ߡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_istp_alm

ER
istp_alm(ID almid)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_ISTP_ALM_ENTER(almid);
	CHECK_INTCTX_UNL();
	CHECK_ALMID(almid);
	p_almcb = get_almcb(almid);

	i_lock_cpu();
	p_pcb = i_acquire_tsk_lock_alm(p_almcb);
	if (p_almcb->almsta) {
		p_almcb->almsta = false;
		tmevtb_dequeue(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}	
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_ISTP_ALM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_istp_alm */

/*
 *  ���顼��ϥ�ɥ�ξ��ֻ���
 */
#ifdef TOPPERS_ref_alm

ER
ref_alm(ID almid, T_RALM *pk_ralm)
{
	ALMCB	*p_almcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_REF_ALM_ENTER(almid, pk_ralm);
	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	p_almcb = get_almcb(almid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_alm(p_almcb);
	if (p_almcb->almsta) {
		pk_ralm->almstat = TALM_STA;
		pk_ralm->lefttim = tmevt_lefttim(p_almcb->p_pcb->p_tevtcb, &(p_almcb->tmevtb));
	}
	else {
		pk_ralm->almstat = TALM_STP;
	}
	pk_ralm->prcid = p_almcb->p_pcb->prcid;
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_REF_ALM_LEAVE(ercd, pk_ralm);
	return(ercd);
}

#endif /* TOPPERS_ref_alm */

/*
 *  ���顼��ϥ�ɥ鵯ư�롼����
 */
#ifdef TOPPERS_almcal

void
call_almhdr(ALMCB *p_almcb)
{
	PRI		saved_ipm;
	PCB		*my_p_pcb;

	/*
	 *  ���顼��ϥ�ɥ����߾��֤ˤ��롥
	 */
	p_almcb->almsta = false;

	/*
	 *  ���顼��ϥ�ɥ��CPU��å�������֤ǸƤӽФ���
	 */
	saved_ipm = i_get_ipm();
	release_tsk_lock(p_almcb->p_pcb);
	i_unlock_cpu();

	LOG_ALM_ENTER(p_almcb);
	(*((ALMHDR)(p_almcb->p_alminib->almhdr)))(p_almcb->p_alminib->exinf);
	LOG_ALM_LEAVE(p_almcb);

	if (!i_sense_lock()) {
		i_lock_cpu();
	}
	my_p_pcb = i_acquire_tsk_lock_self();

	i_set_ipm(saved_ipm);
	force_unlock_spin(my_p_pcb);
}

#endif /* TOPPERS_almcal */
