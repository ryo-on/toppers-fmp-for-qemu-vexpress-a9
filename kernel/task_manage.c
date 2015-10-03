/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: task_manage.c 905 2012-02-27 09:01:23Z ertl-honda $
 */

/*
 *		������������ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "spin_lock.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_MIG_TSK_ENTER
#define LOG_MIG_TSK_ENTER(tskid, prcid)
#endif  /* LOG_MIG_TSK_ENTER */

#ifndef LOG_MIG_TSK_LEAVE
#define LOG_MIG_TSK_LEAVE(ercd)
#endif  /* LOG_MIG_TSK_LEAVE */

#ifndef LOG_ACT_TSK_ENTER
#define LOG_ACT_TSK_ENTER(tskid)
#endif /* LOG_ACT_TSK_ENTER */

#ifndef LOG_ACT_TSK_LEAVE
#define LOG_ACT_TSK_LEAVE(ercd)
#endif /* LOG_ACT_TSK_LEAVE */

#ifndef LOG_IACT_TSK_ENTER
#define LOG_IACT_TSK_ENTER(tskid)
#endif /* LOG_IACT_TSK_ENTER */

#ifndef LOG_IACT_TSK_LEAVE
#define LOG_IACT_TSK_LEAVE(ercd)
#endif /* LOG_IACT_TSK_LEAVE */

#ifndef LOG_MACT_TSK_ENTER
#define LOG_MACT_TSK_ENTER(tskid, prcid)
#endif /* LOG_MACT_TSK_ENTER */

#ifndef LOG_MACT_TSK_LEAVE
#define LOG_MACT_TSK_LEAVE(ercd)
#endif /* LOG_MACT_TSK_LEAVE */

#ifndef LOG_IMACT_TSK_ENTER
#define LOG_IMACT_TSK_ENTER(tskid, prcid)
#endif /* LOG_IMACT_TSK_ENTER */

#ifndef LOG_IMACT_TSK_LEAVE
#define LOG_IMACT_TSK_LEAVE(ercd)
#endif /* LOG_IMACT_TSK_LEAVE */

#ifndef LOG_CAN_ACT_ENTER
#define LOG_CAN_ACT_ENTER(tskid)
#endif /* LOG_CAN_ACT_ENTER */

#ifndef LOG_CAN_ACT_LEAVE
#define LOG_CAN_ACT_LEAVE(ercd)
#endif /* LOG_CAN_ACT_LEAVE */

#ifndef LOG_EXT_TSK_ENTER
#define LOG_EXT_TSK_ENTER()
#endif /* LOG_EXT_TSK_ENTER */

#ifndef LOG_EXT_TSK_LEAVE
#define LOG_EXT_TSK_LEAVE(ercd)
#endif /* LOG_EXT_TSK_LEAVE */

#ifndef LOG_TER_TSK_ENTER
#define LOG_TER_TSK_ENTER(tskid)
#endif /* LOG_TER_TSK_ENTER */

#ifndef LOG_TER_TSK_LEAVE
#define LOG_TER_TSK_LEAVE(ercd)
#endif /* LOG_TER_TSK_LEAVE */

#ifndef LOG_CHG_PRI_ENTER
#define LOG_CHG_PRI_ENTER(tskid, tskpri)
#endif /* LOG_CHG_PRI_ENTER */

#ifndef LOG_CHG_PRI_LEAVE
#define LOG_CHG_PRI_LEAVE(ercd)
#endif /* LOG_CHG_PRI_LEAVE */

#ifndef LOG_GET_PRI_ENTER
#define LOG_GET_PRI_ENTER(tskid, p_tskpri)
#endif /* LOG_GET_PRI_ENTER */

#ifndef LOG_GET_PRI_LEAVE
#define LOG_GET_PRI_LEAVE(ercd, tskpri)
#endif /* LOG_GET_PRI_LEAVE */

#ifndef LOG_GET_INF_ENTER
#define LOG_GET_INF_ENTER(p_exinf)
#endif /* LOG_GET_INF_ENTER */

#ifndef LOG_GET_INF_LEAVE
#define LOG_GET_INF_LEAVE(ercd, exinf)
#endif /* LOG_GET_INF_LEAVE */

/*
 *  ���ץ��å���¾�Υ�������ư������
 */
#ifdef TOPPERS_mig_tsk

ER
mig_tsk(ID tskid, ID prcid)
{
	TCB		*p_tcb;
	ER		ercd = E_OK;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;
	bool_t	dspreq = false;
	PCB		*my_p_pcb;
#ifdef TOPPERS_SYSTIM_LOCAL
	EVTTIM	left_time;
#endif /* TOPPERS_SYSTIM_LOCAL */

	LOG_MIG_TSK_ENTER(tskid, prcid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_PRCID_INI(prcid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	prcid = (prcid == TPRC_INI)? p_tcb->p_tinib->iaffinity : prcid;
	T_CHECK_MIG(p_tcb->p_tinib->affinity_mask, prcid);

	/* ���߳���դ����Ƥ���ץ��å��Ȱ�ư��Υץ��å��Υ�������å������ */
	t_acquire_dual_tsk_lock(p_tcb, prcid, &f_p_pcb, &t_p_pcb);
	my_p_pcb = get_my_p_pcb();
	if (f_p_pcb != my_p_pcb) {
		/*
		 * ����������Ʊ���ץ��å��˳���դ����Ƥ��륿�����Ǥʤ���
		 * �Х��顼�� mig_tsk ��ƤӽФ����������������ƥॳ����ƽФ��塤
		 * �ޥ����졼�Ȥ��줿���ˤ⡤�����ǥ��顼�Ȥʤ�
		 */
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(p_tcb->tstat)){
		/* �¹Բ�ǽ���� */
		if(p_tcb == my_p_pcb->p_runtsk) {
			/* �����������Ф���ȯ�� */
			if (!(my_p_pcb->dspflg)) {
				/* �ǥ����ѥå��ػ���ʤ饨�顼 */
				ercd = E_CTX;
			}
			else if (t_p_pcb == my_p_pcb) {
				/* Ʊ��ץ��å������ */
				/* ͥ���̤�Ʊ��ͥ���٤Υ���������Ǻ���Ȥ��� */
				dspreq = set_lowest_precedence(p_tcb, my_p_pcb);
				ercd = E_OK; 
			}
			else {
				/* �ޥ����졼������׵����� */
				LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
				dispatch_and_migrate(prcid);
				/* ��������äƤ�����ˤϥ�å��ϲ�������Ƥ��� */
				ercd = E_OK;
				t_unlock_cpu();
				goto error_exit;
			}
		} 
		else {
			/* ¾�������ξ�� */
			if (t_p_pcb == my_p_pcb) {
				/* Ʊ��ץ��å������ */
				/* 
				 *  ͥ���̤�Ʊ��ͥ���٤Υ���������Ǻ���Ȥ��롥
				 *  �оݤΥ������Ϻǹ�ͥ���̤Υ������Ǥʤ����ᡤ��
				 *  �����ڤ��ؤ���ȯ�����ʤ�
				 */
				(void)set_lowest_precedence(p_tcb, my_p_pcb);
				ercd = E_OK; 
			}
			else {
				/* �ۤʤ�ץ��å������ */
				/* ��ǥ������塼���鳰�� */
				make_non_runnable(p_tcb);
				/* pcb �ν񤭴��� */
				p_tcb->p_pcb = t_p_pcb;
				LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
				/* �ܹ���Υץ��å���make_runnable ����*/
				if (make_runnable(p_tcb)) {
					dispatch_request(t_p_pcb);
				}
				ercd = E_OK;
			}
		}
	}
	else if (TSTAT_DORMANT(p_tcb->tstat)) {
		/* �ٻ߾��� */
		LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
		p_tcb->p_pcb = t_p_pcb;
		ercd = E_OK;
	}
	else {
		/* �Ԥ����� */
		if ((p_tcb->tmevtb).callback == NULL) {
			/* �����Ԥ��Ǥʤ���� */
			LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
			p_tcb->p_pcb = t_p_pcb;
			ercd = E_OK;
		}
		else {
			/*
			 * �����Ԥ��ξ�� �����Х륿�������� �ʤ�ɬ�פʤ�
			 */
#ifdef TOPPERS_SYSTIM_LOCAL
			/* ���塼������ */
			left_time = tmevtb_dequeue(f_p_pcb->p_tevtcb, &(p_tcb->tmevtb));
			LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
			/* ��ư��Υץ��å��Υ��塼������ */
			tmevtb_insert(t_p_pcb->p_tevtcb, &(p_tcb->tmevtb), base_time(t_p_pcb->p_tevtcb) + left_time);
#else  /* TOPPERS_SYSTIM_GLOBAL */
			LOG_TSKMIG(p_tcb, my_p_pcb->prcid, prcid);
#endif /* TOPPERS_SYSTIM_GLOBAL */
			p_tcb->p_pcb = t_p_pcb;
			ercd = E_OK;
		}
	}
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_MIG_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_mig_tsk */

/*
 *  �������ε�ư
 */
#ifdef TOPPERS_act_tsk

ER
act_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_ACT_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		if (make_active(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_tsk_lock(p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_ACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_act_tsk */

/*
 *  �������ε�ư���󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iact_tsk

ER
iact_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_IACT_TSK_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	i_lock_cpu();
	p_pcb = i_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		if (make_active(p_tcb)) {
			if (dispatch_request(p_pcb)) {
				p_pcb->reqflg = true;
			}
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_tsk_lock(p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_IACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iact_tsk */

/*
 *  �ץ��å�����Υ������ε�ư
 */
#ifdef TOPPERS_mact_tsk

ER
mact_tsk(ID tskid, ID prcid)
{
	TCB		*p_tcb;
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;
	bool_t	dspreq = false;

	LOG_MACT_TSK_ENTER(tskid, prcid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_PRCID_INI(prcid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	prcid = (prcid == TPRC_INI)? p_tcb->p_tinib->iaffinity : prcid;
	T_CHECK_MIG(p_tcb->p_tinib->affinity_mask, prcid);

	/* ���߳���դ����Ƥ���ץ��å��Ȱ�ư��Υץ��å��Υ�������å������ */
	t_acquire_dual_tsk_lock(p_tcb, prcid, &f_p_pcb, &t_p_pcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		LOG_TSKMIG(p_tcb, f_p_pcb->prcid, prcid);
		p_tcb->p_pcb = t_p_pcb;
		if (make_active(p_tcb)) {
			dspreq = dispatch_request(t_p_pcb);
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		p_tcb->actprc = prcid;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_MACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_mact_tsk */

/*
 *  �ץ��å�����Υ������ε�ư���󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_imact_tsk

ER
imact_tsk(ID tskid, ID prcid)
{
	TCB		*p_tcb;
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	LOG_IMACT_TSK_ENTER(tskid, prcid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	CHECK_PRCID_INI(prcid);
	p_tcb = get_tcb(tskid);
	prcid = (prcid == TPRC_INI)? p_tcb->p_tinib->iaffinity : prcid;
	CHECK_MIG(p_tcb->p_tinib->affinity_mask, prcid);

	i_lock_cpu();
	/* ���߳���դ����Ƥ���ץ��å��Ȱ�ư��Υץ��å��Υ�������å������ */
	i_acquire_dual_tsk_lock(p_tcb, prcid, &f_p_pcb, &t_p_pcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		LOG_TSKMIG(p_tcb, f_p_pcb->prcid, prcid);
		p_tcb->p_pcb = t_p_pcb;
		if (make_active(p_tcb)) {
			if (dispatch_request(t_p_pcb)) {
				t_p_pcb->reqflg = true;
			}
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		p_tcb->actprc = prcid;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_IMACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_imact_tsk */

/*
 *  ��������ư�׵�Υ���󥻥�
 */
#ifdef TOPPERS_can_act

ER_UINT
can_act(ID tskid)
{
	TCB		*p_tcb;
	ER_UINT	ercd;
	PCB		*p_pcb;

	LOG_CAN_ACT_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	ercd = p_tcb->actque ? 1 : 0;
	p_tcb->actque = false;
	p_tcb->actprc = TPRC_NONE;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_CAN_ACT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_can_act */

/*
 *  ���������ν�λ
 */
#ifdef TOPPERS_ext_tsk

#if TTYPE_KLOCK == G_KLOCK

ER
ext_tsk(void)
{
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

	LOG_EXT_TSK_ENTER();
	CHECK_TSKCTX();

	/*
	 *  CPU��å����֤�ext_tsk���ƤФ줿���ϡ���å��������˳���ߤ����
	 *  ���ʤ�.
	 *  ��å��������˳���ߤ���Ĥ��ʤ��Τϡ� ���پ��֤ξ��˥�å������
	 *  �Ǥ��ʤ��ä����˳���ߤ���Ĥ���ȡ�����ߤ����ꥵ���ڥ�ɾ��֤�
	 *  �ʤäƤ��ޤ�����Ǥ��롥
	 *  �ǥ����ѥå��ػߤ�����ͥ���٥ޥ�����������֤Ǥʤ����β��پ��֤�
	 *  ���ϡ�����ߤ����äƤ����ߤνи��ǥǥ����ѥå���˹Ԥ�������ä�
	 *  ���뤿������ʤ���
	 */
	if (t_sense_lock()) {
		my_p_pcb = acquire_tsk_lock_without_preemption_self();
	}
	else {
		t_lock_cpu();
		my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
	}

	p_runtsk = my_p_pcb->p_runtsk;
	if (my_p_pcb->disdsp) {
		/*
		 *  �ǥ����ѥå��ػ߾��֤�ext_tsk���ƤФ줿�����б����ơ��ǥ����ѥ�
		 *  �����ľ��֤ˤ��Ƥ��饿������λ���롥
		 */
		my_p_pcb->disdsp = false;
	}
	if (!my_p_pcb->ipmflg) {
	/*
	 *  �����ͥ���٥ޥ�����IPM�ˤ�TIPM_ENAALL�ʳ��ξ��֤�ext_tsk���ƤФ�
	 *  �������б����ơ�IPM��TIPM_ENAALL�ˤ��Ƥ��饿������λ���롥
	 */
		t_set_ipm(TIPM_ENAALL);
		my_p_pcb->ipmflg = true;
	}
	my_p_pcb->dspflg = true;
	/*
	 *  ���ԥ��å���������Ƥ�����ϡ����ԥ��å���������
	 */
	force_unlock_spin(my_p_pcb);

	/* �Ƶ�ư���Υޥ����졼�����ʤ� */
	if ((p_runtsk->actprc == TPRC_NONE) || (p_runtsk->actprc == my_p_pcb->prcid)) {
		(void) make_non_runnable(p_runtsk);
		make_dormant(p_runtsk);
		if (p_runtsk->actque) {
			p_runtsk->actque = false;
			p_runtsk->actprc = TPRC_NONE;
			(void) make_active(p_runtsk);
		}
		release_tsk_lock(my_p_pcb);
		exit_and_dispatch();
		ercd = E_SYS;
	}
	else {
		/* ���ߥ���ƥ����Ȥ�ΤƤƥޥ����졼����� */
		exit_and_migrate(p_runtsk->actprc);
		ercd = E_SYS;
	}

  error_exit:
	LOG_EXT_TSK_LEAVE(ercd);
	return(ercd);
}

#else /* TTYPE_KLOCK != G_KLOCK */


ER
ext_tsk(void)
{
	ER		ercd;
	PCB		*t_p_pcb;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	bool_t	locked;

	LOG_EXT_TSK_ENTER();
	CHECK_TSKCTX();

	/*
	 *  CPU��å����֤�ext_tsk���ƤФ줿���ϡ���å��������˳���ߤ����
	 *  ���ʤ�.
	 *  ��å��������˳���ߤ���Ĥ��ʤ��Τϡ� ���پ��֤ξ��˥�å������
	 *  �Ǥ��ʤ��ä����˳���ߤ���Ĥ���ȡ�����ߤ����ꥵ���ڥ�ɾ��֤�
	 *  �ʤäƤ��ޤ�����Ǥ��롥 
	 */
	locked = t_sense_lock();
  retry:
	if (locked) {
		my_p_pcb = acquire_tsk_lock_without_preemption_self();
	}
	else {
		t_lock_cpu();
		my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
	}

	p_runtsk = my_p_pcb->p_runtsk;

	/* �Ƶ�ư���Υޥ����졼�����ʤ� */
	if ((p_runtsk->actprc == TPRC_NONE) || (p_runtsk->actprc == my_p_pcb->prcid)) {
		/*
		 *  �ǥ����ѥå��ػ߾��֤�ext_tsk���ƤФ줿�����б����ơ��ǥ����ѥ�
		 *  �����ľ��֤ˤ��Ƥ��饿������λ���롥
		 */
		my_p_pcb->disdsp = false;
		/*
		 *  �����ͥ���٥ޥ�����IPM�ˤ�TIPM_ENAALL�ʳ��ξ��֤�ext_tsk���ƤФ�
		 *  �������б����ơ�IPM��TIPM_ENAALL�ˤ��Ƥ��饿������λ���롥
		 */
		t_set_ipm(TIPM_ENAALL);
		my_p_pcb->ipmflg = true;
		my_p_pcb->dspflg = true;
		/*
		 *  ���ԥ��å���������Ƥ�����ϡ����ԥ��å���������
		 */
		force_unlock_spin(my_p_pcb);

		(void) make_non_runnable(p_runtsk);
		make_dormant(p_runtsk);
		if (p_runtsk->actque) {
			p_runtsk->actque = false;
			p_runtsk->actprc = TPRC_NONE;
			(void) make_active(p_runtsk);
		}
		release_tsk_lock(my_p_pcb);
		exit_and_dispatch();
		ercd = E_SYS;
	}
	else {
		/* ��ư��Υץ��å���PCB����� */
		t_p_pcb = get_mp_p_pcb(p_runtsk->actprc);
		/* ��ö��������å���Υ�� */
		release_tsk_lock(my_p_pcb);

		/*
		 * ���߳���դ����Ƥ���ץ��å��Ȱ�ư��Υץ��å��Υ�����
		 * ��å������
		 */
		if (locked) {
			acquire_dual_tsk_lock_without_preemption(p_runtsk, p_runtsk->actprc, &my_p_pcb, &t_p_pcb);
		}
		else {
			t_acquire_dual_tsk_lock(p_runtsk, p_runtsk->actprc, &my_p_pcb, &t_p_pcb);
		}
		/*
		 * �ޥ����졼�������Υץ��å����ѹ����줿���ϥ�ȥ饤
		 */
		if (p_runtsk->actprc != t_p_pcb->prcid) {
			release_dual_tsk_lock(p_runtsk->p_pcb, t_p_pcb);
			goto retry;
		}

		/*
		 *  �����ǳƥ����ͥ���֤��ѹ�����Τϡ��ǥ����ѥå��ػ߾��֤ȳ��
		 *  ��ͥ���٥ޥ�����������֤Ǥʤ����֤ˤ����پ��֤ξ��ˡ��ƥ�
		 *  ���ͥ���֤��ѹ����Ƥ��顤��å������ؿ��ǳ���ߤ���Ĥ��Ƴ��
		 *  �ߤ�����ȡ�����ߤ���Υ꥿������˥ǥ����ѥå��㤬�ƤФ�Ƥ�
		 *  �ޤ����ٻ߾��֤Ȥʤ뤿��Ǥ��롥 
		 */
		my_p_pcb->disdsp = false;
		t_set_ipm(TIPM_ENAALL);
		my_p_pcb->ipmflg = true;
		my_p_pcb->dspflg = true;
		force_unlock_spin(my_p_pcb);

		/* ���ߥ���ƥ����Ȥ�ΤƤƥޥ����졼����� */
		exit_and_migrate(p_runtsk->actprc);
		ercd = E_SYS;
	}

  error_exit:
	LOG_EXT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TTYPE_KLOCK != G_KLOCK */

#endif /* TOPPERS_ext_tsk */

/*
 *  �������ζ�����λ
 */
#ifdef TOPPERS_ter_tsk

#if TTYPE_KLOCK == G_KLOCK
ER
ter_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;
	PCB		*my_p_pcb;

	LOG_TER_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock(p_tcb);
	my_p_pcb = get_my_p_pcb();
	/* ������������ꤹ��ȥ��顼 */
	if ((p_tcb) == my_p_pcb->p_runtsk) {
		ercd = E_ILUSE;
	}
	/* �ۤʤ�ץ��å��˳���դ����Ƥ��륿�����ʤ饨�顼�Ȥ��� */
	else if (p_pcb != my_p_pcb) {
		ercd = E_OBJ;
	}
	else if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		if (TSTAT_RUNNABLE(p_tcb->tstat)) {
			/*
			 * �оݥ�������¾�ץ��å���Υ���������RUNNABLE�ξ�硤
			 * RUN���֤β�ǽ�������뤿�ᡤ�ǥ����ѥå��׵��Ф�ɬ�פ����뤬��
			 * �ܥ����ƥॳ�����Ʊ���ץ��å��˳���դ����Ƥ��륿�����Τ�
			 * ��ȯ�Բ�ǽ�Ǥ���Τǡ��ǥ����ѥå��׵��Ф�ɬ�פϤʤ��� 
			 */
			(void)make_non_runnable(p_tcb);
		}
		else if (TSTAT_WAITING(p_tcb->tstat)) {
			wait_dequeue_wobj(p_tcb);
			wait_dequeue_tmevtb(p_tcb);
		}
		make_dormant(p_tcb);
		if (p_tcb->actque) {
			p_tcb->actque = false;
			/*
			 * �ޥ����졼������׵᤬���塼���󥰤��Ƥ�����ϡ�
			 * �ޥ����졼����������Ԥ��� 
			 */
			if ((p_tcb->actprc != TPRC_NONE) && (p_tcb->actprc != my_p_pcb->prcid)) {
				p_tcb->p_pcb = get_mp_p_pcb(p_tcb->actprc);
			}
			p_tcb->actprc = TPRC_NONE;
			if (make_active(p_tcb)) {
				dspreq = dispatch_request(p_tcb->p_pcb);
			}
		}
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_TER_TSK_LEAVE(ercd);
	return(ercd);
}

#else /* TTYPE_KLOCK != G_KLOCK */

ER
ter_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd = E_OK;
	bool_t	dspreq = false;
	PCB		*f_p_pcb;
	PCB		*t_p_pcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;

	LOG_TER_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	t_lock_cpu();
  retry:
	p_pcb = t_acquire_tsk_lock(p_tcb);
	my_p_pcb = get_my_p_pcb();
	/* ������������ꤹ��ȥ��顼 */
	if ((p_tcb) == my_p_pcb->p_runtsk) {
		ercd = E_ILUSE;
		release_tsk_lock(p_pcb);
	}
	/* �ۤʤ�ץ��å��˳���դ����Ƥ��륿�����ʤ饨�顼�Ȥ��� */
	else if (p_pcb != my_p_pcb) {
		ercd = E_OBJ;
		release_tsk_lock(p_pcb);
	}
	else if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
		release_tsk_lock(p_pcb);
	}
	else {
		if (!(TSTAT_WAITING(p_tcb->tstat) && TSTAT_WAIT_WOBJ(p_tcb->tstat))) {
			/* ���֥��������Ԥ��ʳ��ξ��֤ξ�� */
			if ((p_tcb->actprc == TPRC_NONE) || (p_tcb->actprc == p_pcb->prcid)) {
				/* �Ƶ�ư���Υޥ����졼�����ʤ� */
				if (TSTAT_RUNNABLE(p_tcb->tstat)) {
					/*
					 * �оݥ�������¾�ץ��å���Υ���������RUNNABLE�ξ�硤
					 * RUN���֤β�ǽ�������뤿�ᡤ�ǥ����ѥå��׵��Ф�ɬ�פ����뤬��
					 * �ܥ����ƥॳ�����Ʊ���ץ��å��˳���դ����Ƥ��륿�����Τ�
					 * ��ȯ�Բ�ǽ�Ǥ���Τǡ��ǥ����ѥå��׵��Ф�ɬ�פϤʤ��� 
					 */
					(void)make_non_runnable(p_tcb);
				}
				else if (TSTAT_WAITING(p_tcb->tstat)) {
					/* ���֥��������Ԥ��ʳ����Ԥ����֤ξ�� */
					wait_dequeue_tmevtb(p_tcb);
				}
				make_dormant(p_tcb);
				if (p_tcb->actque) {
					p_tcb->actque = false;
					p_tcb->actprc = TPRC_NONE;
					if (make_active(p_tcb)) {
						dspreq = dispatch_request(p_pcb);
					}
				}
				release_tsk_lock(p_pcb);
				if (dspreq) {
					dispatch();
				}
			}
			else {
				/* ��ư�׵ᥭ�塼���󥰤��� & ¾�ץ��å��˥ޥ����졼����󤢤� */
				/* ��ư��Υץ��å���PCB����� */
				t_p_pcb = get_mp_p_pcb(p_tcb->actprc);
				/* ��ö��������å���Υ�� */
				release_tsk_lock(p_pcb);

				/*
				 * ���߳���դ����Ƥ���ץ��å��Ȱ�ư��Υץ��å��Υ�����
				 * ��å������
				 */
				t_acquire_dual_tsk_lock(p_tcb, p_tcb->actprc, &p_pcb, &t_p_pcb);

				/*
				 *  �ޥ����졼�������Υץ��å����ѹ����줿���ϥ�ȥ饤
				 *  �оݥ������ȼ�����������°����ץ��å����ۤʤ����
				 *  ��ȥ饤���롥
				 */
				if ((p_tcb->actprc != t_p_pcb->prcid) || (p_pcb != my_p_pcb)) {
					release_dual_tsk_lock(p_pcb, t_p_pcb);
					goto retry;
				}
				if (TSTAT_RUNNABLE(p_tcb->tstat)) {
					/*
					 * �оݥ�������¾�ץ��å���Υ���������RUNNABLE�ξ�硤
					 * RUN���֤β�ǽ�������뤿�ᡤ�ǥ����ѥå��׵��Ф�ɬ�פ����뤬��
					 * �ܥ����ƥॳ�����Ʊ���ץ��å��˳���դ����Ƥ��륿�����Τ�
					 * ��ȯ�Բ�ǽ�Ǥ���Τǡ��ǥ����ѥå��׵��Ф�ɬ�פϤʤ��� 
					 */
					(void)make_non_runnable(p_tcb);
				}
				else if (TSTAT_WAITING(p_tcb->tstat)) {
					/* ���֥��������Ԥ��ʳ����Ԥ����֤ξ�� */
					wait_dequeue_tmevtb(p_tcb);
				}
				make_dormant(p_tcb);
				p_tcb->actque = false;
				p_tcb->actprc = TPRC_NONE;
				f_p_pcb = p_pcb;
				p_tcb->p_pcb = t_p_pcb;
				if (make_active(p_tcb)) {
					/*
					 * ���߽�°����ץ��å���Ʊ���ץ��å��˥ޥ����졼
					 * ����󤹤���Ϥ�������ʤ����ᡤdispatch_request()
					 * ����ͤϥ����å����ʤ��� 
					 */ 
					(void)dispatch_request(t_p_pcb);
				}
				release_dual_tsk_lock(f_p_pcb, t_p_pcb);
			}
		}
		else {
			/* ���֥��������Ԥ����֤ξ�� */
			if ((p_tcb->actprc == TPRC_NONE) || (p_tcb->actprc == p_pcb->prcid)) {
				/* �Ƶ�ư���Υޥ����졼�����ʤ� */
				/*
				 * �ǥåɥ�å�����Τ��ᡤ��å��������ľ�� 
				 */
				WOBJCB *p_wobjcb = p_tcb->p_wobjcb;
				release_tsk_lock(p_pcb);
				/*
				 * ���餿���
				 *   ���֥������ȥ�å� -> ��������å�
				 * �ν�ǥ�å������ 
				 */
				TEST_G_LABEL("_test_ter_tsk_01");
				t_acquire_obj_lock(&GET_OBJLOCK(p_wobjcb));
				if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_wobjcb))) == NULL){
					goto retry;
				}
				/*
				 * ���֥��������Ԥ����ְʳ��ʤ������ۤʤ륪�֥������Ȥ��Ф����Ԥ�
				 * �ˤʤäƤ��ʤ��������å���
				 */
				if ((TSTAT_WAITING(p_tcb->tstat) && !TSTAT_WAIT_WOBJ(p_tcb->tstat))
					|| p_wobjcb != p_tcb->p_wobjcb) {
					release_nested_tsk_lock(p_pcb);
					release_obj_lock(&GET_OBJLOCK(p_wobjcb));
					goto retry;
				}
				wait_dequeue_wobj(p_tcb);
				wait_dequeue_tmevtb(p_tcb);
				release_obj_lock(&GET_OBJLOCK(p_wobjcb));
				make_dormant(p_tcb);
				if (p_tcb->actque) {
					p_tcb->actque = false;
					p_tcb->actprc = TPRC_NONE;
					if (make_active(p_tcb)) {
						dspreq = dispatch_request(p_pcb);
					}
				}
				release_tsk_lock(p_pcb);
				if (dspreq) {
					dispatch();
				}
			}
			else {
				/* ��ư�׵ᥭ�塼���󥰤��� & ¾�ץ��å��ؤΥޥ����졼����� */
				/* ��ư��Υץ��å���PCB����� */
				t_p_pcb = get_mp_p_pcb(p_tcb->actprc);
				/*
				 * �ǥåɥ�å�����Τ��ᡤ��å��������ľ�� 
				 */
				WOBJCB *p_wobjcb = p_tcb->p_wobjcb;
				release_tsk_lock(p_pcb);

				/*
				 * ���餿���
				 *   ���֥������ȥ�å� -> ��������å�
				 * �ν�ǥ�å������ 
				 */
				TEST_G_LABEL("_test_ter_tsk_02"); 
				t_acquire_obj_lock(&GET_OBJLOCK(p_wobjcb));
				if (t_acquire_nested_dual_tsk_lock(p_tcb, p_tcb->actprc, &GET_OBJLOCK(p_wobjcb),
												   &p_pcb, &t_p_pcb)) {
					goto retry;
				}
				/*
				 * �ۤʤ륪�֥������Ȥ��Ф����Ԥ��ʤ��������֥��������Ԥ����ְʳ���
				 * �ˤʤäƤ��ʤ����ۤʤ�ץ��å��ؤΥޥ����졼������оݥ�����
				 * ���ޥ����졼�Ȥ��Ƥ���ʤ��ȥ饤��
				 */
				if ((p_wobjcb != p_tcb->p_wobjcb) ||
					(TSTAT_WAITING(p_tcb->tstat) && !TSTAT_WAIT_WOBJ(p_tcb->tstat)) ||
					(get_mp_p_pcb(p_tcb->actprc) != t_p_pcb) ||
					(p_pcb != my_p_pcb)) {
					release_dual_tsk_lock(p_pcb, t_p_pcb);
					release_obj_lock(&GET_OBJLOCK(p_wobjcb));
					goto retry;
				}
				wait_dequeue_wobj(p_tcb);
				wait_dequeue_tmevtb(p_tcb);
				release_obj_lock(&GET_OBJLOCK(p_wobjcb));
				make_dormant(p_tcb);
				p_tcb->actque = false;
				p_tcb->actprc = TPRC_NONE;
				f_p_pcb = p_pcb;
				p_tcb->p_pcb = t_p_pcb;
				if (make_active(p_tcb)) {
					/*
					 * ���߽�°����ץ��å���Ʊ���ץ��å��˥ޥ����졼
					 * ����󤹤���Ϥ�������ʤ����ᡤdispatch_request()
					 * ����ͤϥ����å����ʤ��� 
					 */
					(void)dispatch_request(t_p_pcb);
				}
				release_dual_tsk_lock(f_p_pcb, t_p_pcb);
			}
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TER_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TTYPE_KLOCK != G_KLOCK */

#endif /* TOPPERS_ter_tsk */

/*
 *  �������Υ١���ͥ���٤��ѹ�
 */
#ifdef TOPPERS_chg_pri

ER
chg_pri(ID tskid, PRI tskpri)
{
	TCB		*p_tcb;
	uint_t	newpri;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_CHG_PRI_ENTER(tskid, tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_TPRI_INI(tskpri);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	newpri = (tskpri == TPRI_INI) ? p_tcb->p_tinib->ipriority
										: INT_PRIORITY(tskpri);
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
#if TTYPE_KLOCK == G_KLOCK
		if (change_priority(p_tcb, newpri)) {
			dspreq = dispatch_request(p_pcb);
		}
#else /* TTYPE_KLOCK != G_KLOCK */
		if (!(TSTAT_WAITING(p_tcb->tstat) && TSTAT_WAIT_WOBJ(p_tcb->tstat))) {
			/* ���֥��������Ԥ��ʳ��ξ��֤ξ�� */
			if (change_priority(p_tcb, newpri)) {
				dspreq = dispatch_request(p_pcb);
			}
		}
		else {
			/*
			 * ���֥��������Ԥ��ξ��
			 * �ǥåɥ�å�����Τ��ᡤ��å��������ľ�� 
			 */
			WOBJCB *p_wobjcb = p_tcb->p_wobjcb;
			p_tcb->pend_chgpri = true;
			p_tcb->pend_newpri = newpri;
			release_tsk_lock(p_pcb);

			/*
			 * ���餿���
			 *   ���֥������ȥ�å� -> ��������å�
			 * �ν�ǥ�å������ 
			 */
			TEST_G_LABEL("_test_chg_pri");
		  retry:
			t_acquire_obj_lock(&GET_OBJLOCK(p_wobjcb));
			if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_wobjcb))) == NULL){
				goto retry;
			}

			/* �������ξ��֤��Ѳ����Ƥ��ʤ��������å� */
			if (!(p_tcb->pend_chgpri)) {
				/* ����¾�βս��ͥ�����ѹ��������ʤ��줿 */
				release_nested_tsk_lock(p_pcb);
				release_obj_lock(&GET_OBJLOCK(p_wobjcb));
				t_unlock_cpu();
				ercd = E_OK;
				goto error_exit;
			}

			p_tcb->priority = p_tcb->pend_newpri;
			p_tcb->pend_chgpri = false;
			change_priority(p_tcb, newpri);
			release_obj_lock(&GET_OBJLOCK(p_wobjcb));
		}
#endif /* TTYPE_KLOCK != G_KLOCK */
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_CHG_PRI_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_chg_pri */

/*
 *  ������ͥ���٤λ���
 */
#ifdef TOPPERS_get_pri

ER
get_pri(ID tskid, PRI *p_tskpri)
{
	TCB		*p_tcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_GET_PRI_ENTER(tskid, p_tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		*p_tskpri = EXT_TSKPRI(p_tcb->priority);
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_GET_PRI_LEAVE(ercd, *p_tskpri);
	return(ercd);
}

#endif /* TOPPERS_get_pri */

/*
 *  ���������γ�ĥ����λ���
 */
#ifdef TOPPERS_get_inf

ER
get_inf(intptr_t *p_exinf)
{
	ER		ercd;
	PCB		*my_p_pcb;

	LOG_GET_INF_ENTER(p_exinf);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
	*p_exinf = my_p_pcb->p_runtsk->p_tinib->exinf;
	ercd = E_OK;
	release_tsk_lock(my_p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_GET_INF_LEAVE(ercd, *p_exinf);
	return(ercd);
}

#endif /* TOPPERS_get_inf */
