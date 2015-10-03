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
 *  @(#) $Id: task_sync.c 905 2012-02-27 09:01:23Z ertl-honda $
 */

/*
 *		��������°Ʊ����ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SLP_TSK_ENTER
#define LOG_SLP_TSK_ENTER()
#endif /* LOG_SLP_TSK_ENTER */

#ifndef LOG_SLP_TSK_LEAVE
#define LOG_SLP_TSK_LEAVE(ercd)
#endif /* LOG_SLP_TSK_LEAVE */

#ifndef LOG_TSLP_TSK_ENTER
#define LOG_TSLP_TSK_ENTER(tmout)
#endif /* LOG_TSLP_TSK_ENTER */

#ifndef LOG_TSLP_TSK_LEAVE
#define LOG_TSLP_TSK_LEAVE(ercd)
#endif /* LOG_TSLP_TSK_LEAVE */

#ifndef LOG_WUP_TSK_ENTER
#define LOG_WUP_TSK_ENTER(tskid)
#endif /* LOG_WUP_TSK_ENTER */

#ifndef LOG_WUP_TSK_LEAVE
#define LOG_WUP_TSK_LEAVE(ercd)
#endif /* LOG_WUP_TSK_LEAVE */

#ifndef LOG_IWUP_TSK_ENTER
#define LOG_IWUP_TSK_ENTER(tskid)
#endif /* LOG_IWUP_TSK_ENTER */

#ifndef LOG_IWUP_TSK_LEAVE
#define LOG_IWUP_TSK_LEAVE(ercd)
#endif /* LOG_IWUP_TSK_LEAVE */

#ifndef LOG_CAN_WUP_ENTER
#define LOG_CAN_WUP_ENTER(tskid)
#endif /* LOG_CAN_WUP_ENTER */

#ifndef LOG_CAN_WUP_LEAVE
#define LOG_CAN_WUP_LEAVE(ercd)
#endif /* LOG_CAN_WUP_LEAVE */

#ifndef LOG_REL_WAI_ENTER
#define LOG_REL_WAI_ENTER(tskid)
#endif /* LOG_REL_WAI_ENTER */

#ifndef LOG_REL_WAI_LEAVE
#define LOG_REL_WAI_LEAVE(ercd)
#endif /* LOG_REL_WAI_LEAVE */

#ifndef LOG_IREL_WAI_ENTER
#define LOG_IREL_WAI_ENTER(tskid)
#endif /* LOG_IREL_WAI_ENTER */

#ifndef LOG_IREL_WAI_LEAVE
#define LOG_IREL_WAI_LEAVE(ercd)
#endif /* LOG_IREL_WAI_LEAVE */

#ifndef LOG_SUS_TSK_ENTER
#define LOG_SUS_TSK_ENTER(tskid)
#endif /* LOG_SUS_TSK_ENTER */

#ifndef LOG_SUS_TSK_LEAVE
#define LOG_SUS_TSK_LEAVE(ercd)
#endif /* LOG_SUS_TSK_LEAVE */

#ifndef LOG_RSM_TSK_ENTER
#define LOG_RSM_TSK_ENTER(tskid)
#endif /* LOG_RSM_TSK_ENTER */

#ifndef LOG_RSM_TSK_LEAVE
#define LOG_RSM_TSK_LEAVE(ercd)
#endif /* LOG_RSM_TSK_LEAVE */

#ifndef LOG_DLY_TSK_ENTER
#define LOG_DLY_TSK_ENTER(dlytim)
#endif /* LOG_DLY_TSK_ENTER */

#ifndef LOG_DLY_TSK_LEAVE
#define LOG_DLY_TSK_LEAVE(ercd)
#endif /* LOG_DLY_TSK_LEAVE */

/*
 *  �����Ԥ�
 */
#ifdef TOPPERS_slp_tsk

ER
slp_tsk(void)
{
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	
	LOG_SLP_TSK_ENTER();
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

	my_p_pcb = t_acquire_tsk_lock_self();
	p_runtsk = my_p_pcb->p_runtsk;
	if (p_runtsk->wupque) {
		p_runtsk->wupque = false;
		release_tsk_lock(my_p_pcb);
		ercd = E_OK;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SLP);
		make_wait(p_runtsk);
		LOG_TSKSTAT(p_runtsk);
		release_tsk_lock(my_p_pcb);
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_SLP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_slp_tsk */

/*
 *  �����Ԥ��ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_tslp_tsk

ER
tslp_tsk(TMO tmout)
{
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

	LOG_TSLP_TSK_ENTER(tmout);
	CHECK_TSKCTX_UNL();
	CHECK_TMOUT(tmout);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

	my_p_pcb = t_acquire_tsk_lock_self();
	p_runtsk = my_p_pcb->p_runtsk;
	if (p_runtsk->wupque) {
		p_runtsk->wupque = false;
		release_tsk_lock(my_p_pcb);
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		release_tsk_lock(my_p_pcb);
		ercd = E_TMOUT;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SLP);
		make_wait_tmout(tmout, my_p_pcb);
		LOG_TSKSTAT(p_runtsk);
		release_tsk_lock(my_p_pcb);
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_TSLP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_tslp_tsk */

/*
 *  �������ε���
 */
#ifdef TOPPERS_wup_tsk

ER
wup_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_WUP_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_WAIT_SLP(p_tcb->tstat)) {
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->wupque)) {
		p_tcb->wupque = true;
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
	LOG_WUP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_wup_tsk */

/*
 *  �������ε������󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iwup_tsk

ER
iwup_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	PCB		*p_pcb;

	LOG_IWUP_TSK_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	i_lock_cpu();
	p_pcb = i_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_WAIT_SLP(p_tcb->tstat)) {
		if (wait_complete(p_tcb)) {
			if (dispatch_request(p_pcb)) {
				(get_my_p_pcb())->reqflg = true;
			}
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->wupque)) {
		p_tcb->wupque = true;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	release_tsk_lock(p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_IWUP_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iwup_tsk */

/*
 *  �����������׵�Υ���󥻥�
 */
#ifdef TOPPERS_can_wup

ER_UINT
can_wup(ID tskid)
{
	TCB		*p_tcb;
	ER_UINT	ercd;
	PCB		*p_pcb;

	LOG_CAN_WUP_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		ercd = p_tcb->wupque ? 1 : 0;
		p_tcb->wupque = false;
	}
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_CAN_WUP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_can_wup */

/*
 *  �Ԥ����֤ζ������
 */
#ifdef TOPPERS_rel_wai

ER
rel_wai(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_REL_WAI_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (!TSTAT_WAITING(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
#if TTYPE_KLOCK == G_KLOCK
		if (wait_release(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
#else /* TTYPE_KLOCK != G_KLOCK */
		if (!TSTAT_WAIT_WOBJ(p_tcb->tstat)) {
			/* ���֥��������Ԥ��Ǥʤ���� */
			dspreq = wait_release(p_tcb);
		}
		else {
			/*
			 * ���֥��������Ԥ��ξ��
			 * �ǥåɥ�å�����Τ��ᡤ��å��������ľ�� 
			 */
			WOBJCB *p_wobjcb = p_tcb->p_wobjcb;
			p_tcb->pend_relwai = true;
			release_tsk_lock(p_pcb);

			/*
			 * ���餿���
			 *   ���֥������ȥ�å� -> ��������å�
			 * �ν�ǥ�å������ 
			 */
			TEST_G_LABEL("_test_rel_wai");
		  retry:
			t_acquire_obj_lock(&GET_OBJLOCK(p_wobjcb));
			if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_wobjcb))) == NULL){
				goto retry;
			}

			/* �������ξ��֤��Ѳ����Ƥ��ʤ��������å� */
			if (!(p_tcb->pend_relwai)) {
				/* ����¾�βս���Ԥ�����������ʤ��줿 */
				release_nested_tsk_lock(p_pcb);
				release_obj_lock(&GET_OBJLOCK(p_wobjcb));
				t_unlock_cpu();
				ercd = E_OBJ;
				goto error_exit;
			}
			p_tcb->pend_relwai = false;
			dspreq = wait_release(p_tcb);
			release_obj_lock(&GET_OBJLOCK(p_wobjcb));
		}
		if (dspreq) {
			dspreq = dispatch_request(p_pcb);
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
	LOG_REL_WAI_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rel_wai */

/*
 *  �Ԥ����֤ζ���������󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_irel_wai

ER
irel_wai(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_IREL_WAI_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	i_lock_cpu();
#if TTYPE_KLOCK != G_KLOCK
  retry:
#endif /* TTYPE_KLOCK != G_KLOCK */
	p_pcb = i_acquire_tsk_lock(p_tcb);
	if (!TSTAT_WAITING(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
#if TTYPE_KLOCK == G_KLOCK
		dspreq = wait_release(p_tcb);
#else /* TTYPE_KLOCK != G_KLOCK */
		if (!TSTAT_WAIT_WOBJ(p_tcb->tstat)) {
			/* ���֥��������Ԥ��Ǥʤ���� */
			dspreq = wait_release(p_tcb);
		}
		else {
			/*
			 * ���֥��������Ԥ��ξ��
			 * �ǥåɥ�å�����Τ��ᡤ��å��������ľ�� 
			 */
			WOBJCB *p_wobjcb = p_tcb->p_wobjcb;
			p_tcb->pend_relwai = true;
			release_tsk_lock(p_pcb);
			/*
			 * ���餿���
			 *   ���֥������ȥ�å� -> ��������å�
			 * �ν�ǥ�å������ 
			 */
			TEST_G_LABEL("_test_irel_wai");
			t_acquire_obj_lock(&GET_OBJLOCK(p_wobjcb));
			if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_wobjcb))) == NULL){
				goto retry;
			}

			/* �������ξ��֤��Ѳ����Ƥ��ʤ��������å� */
			if (!(p_tcb->pend_relwai)) {
				/* ����¾�βս���Ԥ�����������ʤ��줿 */
				release_nested_tsk_lock(p_pcb);
				release_obj_lock(&GET_OBJLOCK(p_wobjcb));
				t_unlock_cpu();
				ercd = E_OBJ;
				goto error_exit;
			}
			p_tcb->pend_relwai = false;
			dspreq = wait_release(p_tcb);
			release_obj_lock(&GET_OBJLOCK(p_wobjcb));
		}
#endif /* TTYPE_KLOCK != G_KLOCK */
		if (dspreq){
			if (dispatch_request(p_pcb)) {
				(get_my_p_pcb())->reqflg = true;
			}
		}
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	i_unlock_cpu();

  error_exit:
	LOG_IREL_WAI_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_irel_wai */

/*
 *  �����Ԥ����֤ؤΰܹ�
 * 
 *  �����������оݤǤʤ��������Υץ��å����ǥ����ѥå��ػ���Ǥ�
 *  ȯ�Ԥ��롥
 *  �����������оݤξ��ϡ�¾��sus_tsk�ȥ졼���󥰤���ȡ�E_QOVR ���֤뤳
 *  �Ȥ����롥
 */
#ifdef TOPPERS_sus_tsk

ER
sus_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;
	PCB		*my_p_pcb;

	LOG_SUS_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	my_p_pcb = get_my_p_pcb();
	if (p_tcb == my_p_pcb->p_runtsk && !(my_p_pcb->dspflg)) {
		/* ��ʬ���ǥ����ѥå��ػ߾��֤�sus_tsk��ȯ�Ԥ���ȥ��顼 */
		ercd = E_CTX;
	}
	else if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(p_tcb->tstat)) {
		/*
		 *  �¹ԤǤ�����֤��鶯���Ԥ����֤ؤ�����
		 */
		p_tcb->tstat = TS_SUSPENDED;
		LOG_TSKSTAT(p_tcb);
		if (make_non_runnable(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		ercd = E_OK;
	}
	else if (TSTAT_SUSPENDED(p_tcb->tstat)) {
		ercd = E_QOVR;
	}
	else {
		/*
		 *  �Ԥ����֤�������Ԥ����֤ؤ�����
		 */
		p_tcb->tstat |= TS_SUSPENDED;
		LOG_TSKSTAT(p_tcb);
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_SUS_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_sus_tsk */

/*
 *  �����Ԥ����֤���κƳ�
 */
#ifdef TOPPERS_rsm_tsk

ER
rsm_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_RSM_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	t_lock_cpu();
	p_pcb = t_acquire_tsk_lock(p_tcb);
	if (!TSTAT_SUSPENDED(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (!TSTAT_WAITING(p_tcb->tstat)) {
		/*
		 *  �����Ԥ����֤���¹ԤǤ�����֤ؤ�����
		 */
		p_tcb->tstat = TS_RUNNABLE;
		LOG_TSKSTAT(p_tcb);
		if (make_runnable(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		ercd = E_OK;
	}
	else {
		/*
		 *  ����Ԥ����֤����Ԥ����֤ؤ�����
		 */
		p_tcb->tstat &= ~TS_SUSPENDED;
		LOG_TSKSTAT(p_tcb);
		ercd = E_OK;
	}
	release_tsk_lock(p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_RSM_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rsm_tsk */

/*
 *  �����������ٱ�
 */
#ifdef TOPPERS_dly_tsk

ER
dly_tsk(RELTIM dlytim)
{
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;
	
	LOG_DLY_TSK_ENTER(dlytim);
	CHECK_TSKCTX_UNL();
	CHECK_PAR(dlytim <= TMAX_RELTIM);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

	my_p_pcb = t_acquire_tsk_lock_self();
	p_runtsk = my_p_pcb->p_runtsk;
	p_runtsk->tstat = (TS_WAITING | TS_WAIT_DLY);
	(void) make_non_runnable(p_runtsk);
	tmevtb_enqueue(my_p_pcb->p_tevtcb, &(p_runtsk->tmevtb), dlytim, (CBACK) wait_tmout_ok, (void *) p_runtsk);
	LOG_TSKSTAT(p_runtsk);
	release_tsk_lock(my_p_pcb);
	dispatch();
	ercd = p_runtsk->wercd;
	t_unlock_cpu();

  error_exit:
	LOG_DLY_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_dly_tsk */
