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
 *  @(#) $Id: cyclic.c 721 2010-10-14 02:53:19Z ertl-honda $
 */

/*
 *		�����ϥ�ɥ鵡ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "cyclic.h"
#include "mp.h"
#include "spin_lock.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_CYC_ENTER
#define LOG_CYC_ENTER(p_cyccb)
#endif /* LOG_CYC_ENTER */

#ifndef LOG_CYC_LEAVE
#define LOG_CYC_LEAVE(p_cyccb)
#endif /* LOG_CYC_LEAVE */

#ifndef LOG_STA_CYC_ENTER
#define LOG_STA_CYC_ENTER(cycid)
#endif /* LOG_STA_CYC_ENTER */

#ifndef LOG_STA_CYC_LEAVE
#define LOG_STA_CYC_LEAVE(ercd)
#endif /* LOG_STA_CYC_LEAVE */

#ifndef LOG_MSTA_CYC_ENTER
#define LOG_MSTA_CYC_ENTER(cycid, prcid)
#endif /* LOG_MSTA_CYC_ENTER */

#ifndef LOG_MSTA_CYC_LEAVE
#define LOG_MSTA_CYC_LEAVE(ercd)
#endif /* LOG_MSTA_CYC_LEAVE */

#ifndef LOG_CYCMIG
#define LOG_CYCMIG(p_cyccb, src_id, dest_id)
#endif /* LOG_CYCMIG */

#ifndef LOG_STP_CYC_ENTER
#define LOG_STP_CYC_ENTER(cycid)
#endif /* LOG_STP_CYC_ENTER */

#ifndef LOG_STP_CYC_LEAVE
#define LOG_STP_CYC_LEAVE(ercd)
#endif /* LOG_STP_CYC_LEAVE */

#ifndef LOG_REF_CYC_ENTER
#define LOG_REF_CYC_ENTER(cycid, pk_rcyc)
#endif /* LOG_REF_CYC_ENTER */

#ifndef LOG_REF_CYC_LEAVE
#define LOG_REF_CYC_LEAVE(ercd, pk_rcyc)
#endif /* LOG_REF_CYC_LEAVE */

/*
 *  �����ϥ�ɥ�ο�
 */
#define tnum_cyc	((uint_t)(tmax_cycid - TMIN_CYCID + 1))

/*
 *  �����ϥ�ɥ�ID��������ϥ�ɥ�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_CYC(cycid)	((uint_t)((cycid) - TMIN_CYCID))
#define get_cyccb(cycid)	(p_cyccb_table[INDEX_CYC(cycid)])

/*
 *  �����ϥ�ɥ鵯ư�Τ���Υ����।�٥�ȥ֥�å�����Ͽ
 */
Inline void
tmevtb_enqueue_cyc(CYCCB *p_cyccb, EVTTIM evttim)
{
	tmevtb_enqueue_evttim(p_cyccb->p_pcb->p_tevtcb, &(p_cyccb->tmevtb), evttim,
								(CBACK) call_cychdr, (void *) p_cyccb);
	p_cyccb->evttim = evttim;
}

/*
 *  �����ϥ�ɥ鵡ǽ�ν����
 */
#ifdef TOPPERS_cycini

void
initialize_cyclic(void)
{
	uint_t	i;
	CYCCB	*p_cyccb;
	PCB		*p_pcb;

#ifdef TOPPERS_SYSTIM_GLOBAL
	if (!x_sense_mprc()) {
		return;
	}
	p_pcb = get_mp_p_pcb(TOPPERS_SYSTIM_PRCID);
#else  /* TOPPERS_SYSTIM_LOCAL */
	p_pcb = get_my_p_pcb();
#endif /* TOPPERS_SYSTIM_GLOBAL */

	for (i = 0; i < tnum_cyc; i++) {
#ifdef TOPPERS_SYSTIM_LOCAL
		/* �������˳���դ��줿�����ϥ�ɥ�ν���� */
		if(cycinib_table[i].iaffinity == ID_PRC(x_prc_index())){
#endif /* TOPPERS_SYSTIM_LOCAL */
			p_cyccb = p_cyccb_table[i];
			p_cyccb->p_cycinib = &(cycinib_table[i]);
			p_cyccb->p_pcb = p_pcb;
			if ((p_cyccb->p_cycinib->cycatr & TA_STA) != 0U) {
				p_cyccb->cycsta = true;
				tmevtb_enqueue_cyc(p_cyccb, (EVTTIM)(p_cyccb->p_cycinib->cycphs));
			}
			else {
				p_cyccb->cycsta = false;
			}
#ifdef TOPPERS_SYSTIM_LOCAL
		}
#endif /* TOPPERS_SYSTIM_LOCAL */
	}
}

#endif /* TOPPERS_cycini */

/*
 *  �����ϥ�ɥ��ư���
 */
#ifdef TOPPERS_sta_cyc

ER
sta_cyc(ID cycid)
{
	CYCCB	*p_cyccb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_STA_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	p_cyccb = get_cyccb(cycid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_cyc(p_cyccb);
	if (p_cyccb->cycsta) {
		tmevtb_dequeue(p_cyccb->p_pcb->p_tevtcb, &(p_cyccb->tmevtb));
	}
	else {
		p_cyccb->cycsta = true;
	}
	tmevtb_enqueue_cyc(p_cyccb, base_time(p_cyccb->p_pcb->p_tevtcb) + p_cyccb->p_cycinib->cycphs);
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_STA_CYC_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_sta_cyc */


/*
 *  �����ϥ�ɥ��ư���
 */
#ifdef TOPPERS_msta_cyc

#ifdef TOPPERS_SYSTIM_LOCAL

ER
msta_cyc(ID cycid, ID prcid)
{
	CYCCB	*p_cyccb;
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	LOG_MSTA_CYC_ENTER(cycid, prcid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	CHECK_PRCID_INI(prcid);
	p_cyccb = get_cyccb(cycid);
	prcid = (prcid == TPRC_INI)? p_cyccb->p_cycinib->iaffinity : prcid;
	CHECK_MIG(p_cyccb->p_cycinib->affinity_mask, prcid);

	t_lock_cpu();
	t_acquire_dual_tsk_lock_cyc(p_cyccb, prcid, &f_p_pcb, &t_p_pcb);
	if (p_cyccb->cycsta) {
		tmevtb_dequeue(p_cyccb->p_pcb->p_tevtcb, &(p_cyccb->tmevtb));
	}
	else {
		p_cyccb->cycsta = true;
	}

	LOG_CYCMIG(p_cyccb, f_p_pcb->prcid, prcid);
	/* ��ư��� pcb ����Ͽ */
	p_cyccb->p_pcb = t_p_pcb;

	tmevtb_enqueue_cyc(p_cyccb, base_time(t_p_pcb->p_tevtcb) + p_cyccb->p_cycinib->cycphs);
	ercd = E_OK;
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_MSTA_CYC_LEAVE(ercd);
	return(ercd);
}

#else  /* TOPPERS_SYSTIM_GLOBAL */

ER
msta_cyc(ID cycid, ID prcid)
{
	ER		ercd = E_NOSPT;

	LOG_MSTA_CYC_ENTER(cycid, prcid);
	LOG_MSTA_CYC_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SYSTIM_GLOBAL */

#endif /* TOPPERS_msta_cyc */


/*
 *  �����ϥ�ɥ��ư�����
 */
#ifdef TOPPERS_stp_cyc

ER
stp_cyc(ID cycid)
{
	CYCCB	*p_cyccb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_STP_CYC_ENTER(cycid);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	p_cyccb = get_cyccb(cycid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_cyc(p_cyccb);
	if (p_cyccb->cycsta) {
		p_cyccb->cycsta = false;
		tmevtb_dequeue(p_cyccb->p_pcb->p_tevtcb, &(p_cyccb->tmevtb));
	}
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_STP_CYC_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_stp_cyc */

/*
 *  �����ϥ�ɥ�ξ��ֻ���
 */
#ifdef TOPPERS_ref_cyc

ER
ref_cyc(ID cycid, T_RCYC *pk_rcyc)
{
	CYCCB	*p_cyccb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_REF_CYC_ENTER(cycid, pk_rcyc);
	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	p_cyccb = get_cyccb(cycid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock_cyc(p_cyccb);
	if (p_cyccb->cycsta) {
		pk_rcyc->cycstat = TCYC_STA;
		pk_rcyc->lefttim = tmevt_lefttim(p_cyccb->p_pcb->p_tevtcb, &(p_cyccb->tmevtb));
	}
	else {
		pk_rcyc->cycstat = TCYC_STP;
	}
	pk_rcyc->prcid = p_cyccb->p_pcb->prcid;
	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_REF_CYC_LEAVE(ercd, pk_rcyc);
	return(ercd);
}

#endif /* TOPPERS_ref_cyc */

/*
 *  �����ϥ�ɥ鵯ư�롼����
 */
#ifdef TOPPERS_cyccal

void
call_cychdr(CYCCB *p_cyccb)
{
	PRI		saved_ipm;
	PCB		*my_p_pcb;

	/*
	 *  ����ε�ư�Τ���Υ����।�٥�ȥ֥�å�����Ͽ���롥
	 *
	 *  Ʊ��������ƥ��å��Ǽ����ϥ�ɥ����ٵ�ư���٤����ˤϡ�����
	 *  �ؿ�����signal_time����ä���ˡ����٤��δؿ����ƤФ�뤳�Ȥˤ�
	 *  �롥
	 */
	tmevtb_enqueue_cyc(p_cyccb, p_cyccb->evttim + p_cyccb->p_cycinib->cyctim);

	/*
	 *  �����ϥ�ɥ��CPU��å�������֤ǸƤӽФ���
	 */
	saved_ipm = i_get_ipm();
	release_tsk_lock(p_cyccb->p_pcb);
	i_unlock_cpu();

	LOG_CYC_ENTER(p_cyccb);
	(*((CYCHDR)(p_cyccb->p_cycinib->cychdr)))(p_cyccb->p_cycinib->exinf);
	LOG_CYC_LEAVE(p_cyccb);

	if (!i_sense_lock()) {
		i_lock_cpu();
	}

	my_p_pcb = i_acquire_tsk_lock_self();

	i_set_ipm(saved_ipm);
	force_unlock_spin(my_p_pcb);
}

#endif /* TOPPERS_cyccal */
