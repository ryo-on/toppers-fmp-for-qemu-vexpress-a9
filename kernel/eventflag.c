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
 *  @(#) $Id: eventflag.c 684 2010-09-15 08:15:03Z ertl-honda $
 */

/*
 *		���٥�ȥե饰��ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "eventflag.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SET_FLG_ENTER
#define LOG_SET_FLG_ENTER(flgid, setptn)
#endif /* LOG_SET_FLG_ENTER */

#ifndef LOG_SET_FLG_LEAVE
#define LOG_SET_FLG_LEAVE(ercd)
#endif /* LOG_SET_FLG_LEAVE */

#ifndef LOG_ISET_FLG_ENTER
#define LOG_ISET_FLG_ENTER(flgid, setptn)
#endif /* LOG_ISET_FLG_ENTER */

#ifndef LOG_ISET_FLG_LEAVE
#define LOG_ISET_FLG_LEAVE(ercd)
#endif /* LOG_ISET_FLG_LEAVE */

#ifndef LOG_CLR_FLG_ENTER
#define LOG_CLR_FLG_ENTER(flgid, clrptn)
#endif /* LOG_CLR_FLG_ENTER */

#ifndef LOG_CLR_FLG_LEAVE
#define LOG_CLR_FLG_LEAVE(ercd)
#endif /* LOG_CLR_FLG_LEAVE */

#ifndef LOG_WAI_FLG_ENTER
#define LOG_WAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn)
#endif /* LOG_WAI_FLG_ENTER */

#ifndef LOG_WAI_FLG_LEAVE
#define LOG_WAI_FLG_LEAVE(ercd, flgptn)
#endif /* LOG_WAI_FLG_LEAVE */

#ifndef LOG_POL_FLG_ENTER
#define LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn)
#endif /* LOG_POL_FLG_ENTER */

#ifndef LOG_POL_FLG_LEAVE
#define LOG_POL_FLG_LEAVE(ercd, flgptn)
#endif /* LOG_POL_FLG_LEAVE */

#ifndef LOG_TWAI_FLG_ENTER
#define LOG_TWAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn, tmout)
#endif /* LOG_TWAI_FLG_ENTER */

#ifndef LOG_TWAI_FLG_LEAVE
#define LOG_TWAI_FLG_LEAVE(ercd, flgptn)
#endif /* LOG_TWAI_FLG_LEAVE */

#ifndef LOG_INI_FLG_ENTER
#define LOG_INI_FLG_ENTER(flgid)
#endif /* LOG_INI_FLG_ENTER */

#ifndef LOG_INI_FLG_LEAVE
#define LOG_INI_FLG_LEAVE(ercd)
#endif /* LOG_INI_FLG_LEAVE */

#ifndef LOG_REF_FLG_ENTER
#define LOG_REF_FLG_ENTER(flgid, pk_rflg)
#endif /* LOG_REF_FLG_ENTER */

#ifndef LOG_REF_FLG_LEAVE
#define LOG_REF_FLG_LEAVE(ercd, pk_rflg)
#endif /* LOG_REF_FLG_LEAVE */

/*
 *  ���٥�ȥե饰�ο�
 */
#define tnum_flg	((uint_t)(tmax_flgid - TMIN_FLGID + 1))

/*
 *  ���٥�ȥե饰ID���饤�٥�ȥե饰�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_FLG(flgid)	((uint_t)((flgid) - TMIN_FLGID))
#define get_flgcb(flgid)	(p_flgcb_table[INDEX_FLG(flgid)])

/*
 *  ���٥�ȥե饰��ǽ�ν����
 */
#ifdef TOPPERS_flgini

void
initialize_eventflag(void)
{
	uint_t	i;
	FLGCB	*p_flgcb;

	if (x_sense_mprc()) {
		for (i = 0; i < tnum_flg; i++) {
			p_flgcb = p_flgcb_table[i];
			queue_initialize(&(p_flgcb->wait_queue));
			p_flgcb->p_flginib = &(flginib_table[i]);
			p_flgcb->flgptn = p_flgcb->p_flginib->iflgptn;
#if TTYPE_KLOCK == F_KLOCK
			x_initialize_obj_lock(&(p_flgcb->obj_lock));
#endif /* TTYPE_KLOCK == F_KLOCK */
		}
	}
}

#endif /* TOPPERS_flgini */

/*
 *  ���٥�ȥե饰�Ԥ�������Υ����å�
 */
#ifdef TOPPERS_flgcnd

bool_t
check_flg_cond(FLGCB *p_flgcb, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	if ((wfmode & TWF_ORW) != 0U ? (p_flgcb->flgptn & waiptn) != 0U
									: (p_flgcb->flgptn & waiptn) == waiptn) {
		*p_flgptn = p_flgcb->flgptn;
		if ((p_flgcb->p_flginib->flgatr & TA_CLR) != 0U) {
			p_flgcb->flgptn = 0U;
		}
		return(true);
	}
	return(false);
}

#endif /* TOPPERS_flgcnd */

/*
 *  ���٥�ȥե饰�Υ��å�
 */
#ifdef TOPPERS_set_flg

ER
set_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*p_flgcb;
	QUEUE	*p_queue;
	TCB		*p_tcb;
	WINFO_FLG *p_winfo_flg;
	ER		ercd;
	bool_t	dspreq = false;
	PCB		*p_pcb;

	LOG_SET_FLG_ENTER(flgid, setptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	p_flgcb->flgptn |= setptn;
	p_queue = p_flgcb->wait_queue.p_next;
	while (p_queue != &(p_flgcb->wait_queue)) {
		p_tcb = (TCB *) p_queue;
		p_queue = p_queue->p_next;
		/* �ե饰�Υ��åȤ����˲������ɤˤǤ��ʤ����ᡤ��ȥ饤���ʤ� */
		p_pcb = acquire_nested_tsk_lock_without_preemption(p_tcb);
		p_winfo_flg = (WINFO_FLG *)(&(p_tcb->winfo_obj));
		if (check_flg_cond(p_flgcb, p_winfo_flg->waiptn,
							p_winfo_flg->wfmode, &(p_winfo_flg->flgptn))) {
			queue_delete(&(p_tcb->task_queue));
			if (wait_complete(p_tcb)) {
				if (dispatch_request(p_pcb)) {
					dspreq = true;
				}
			}
			if ((p_flgcb->p_flginib->flgatr & TA_CLR) != 0U) {
				release_nested_tsk_lock(p_pcb);
				break;
			}
		}
		release_nested_tsk_lock(p_pcb);
	}
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_SET_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_set_flg */

/*
 *  ���٥�ȥե饰�Υ��åȡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iset_flg

ER
iset_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*p_flgcb;
	QUEUE	*p_queue;
	TCB		*p_tcb;
	WINFO_FLG *p_winfo_flg;
	ER		ercd;
	PCB		*p_pcb;

	LOG_ISET_FLG_ENTER(flgid, setptn);
	CHECK_INTCTX_UNL();
	CHECK_FLGID(flgid);
	p_flgcb = get_flgcb(flgid);

	i_lock_cpu();
	i_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	p_flgcb->flgptn |= setptn;
	p_queue = p_flgcb->wait_queue.p_next;
	while (p_queue != &(p_flgcb->wait_queue)) {
		p_tcb = (TCB *) p_queue;
		/* �ե饰�Υ��åȤ����˲������ɤˤǤ��ʤ����ᡤ��ȥ饤���ʤ� */
		p_pcb = acquire_nested_tsk_lock_without_preemption(p_tcb);
		p_queue = p_queue->p_next;
		p_winfo_flg = (WINFO_FLG *)(&(p_tcb->winfo_obj));
		if (check_flg_cond(p_flgcb, p_winfo_flg->waiptn,
							p_winfo_flg->wfmode, &(p_winfo_flg->flgptn))) {
			queue_delete(&(p_tcb->task_queue));
			if (wait_complete(p_tcb)) {
				if (dispatch_request(p_pcb)){
					(get_my_p_pcb())->reqflg = true;
				}
			}
			if ((p_flgcb->p_flginib->flgatr & TA_CLR) != 0U) {
				release_nested_tsk_lock(p_pcb);
				break;
			}
		}
		release_nested_tsk_lock(p_pcb);
	}
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	i_unlock_cpu();

  error_exit:
	LOG_ISET_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iset_flg */

/*
 *  ���٥�ȥե饰�Υ��ꥢ
 */
#ifdef TOPPERS_clr_flg

ER
clr_flg(ID flgid, FLGPTN clrptn)
{
	FLGCB	*p_flgcb;
	ER		ercd;

	LOG_CLR_FLG_ENTER(flgid, clrptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	p_flgcb->flgptn &= clrptn; 
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	t_unlock_cpu();

  error_exit:
	LOG_CLR_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_clr_flg */

/*
 *  ���٥�ȥե饰�Ԥ�
 */
#ifdef TOPPERS_wai_flg

ER
wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*p_flgcb;
	WINFO_FLG *p_winfo_flg;
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

	LOG_WAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0U);
	CHECK_PAR(wfmode == TWF_ORW || wfmode == TWF_ANDW);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	if ((p_flgcb->p_flginib->flgatr & TA_WMUL) == 0U
					&& !queue_empty(&(p_flgcb->wait_queue))) {
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		ercd = E_ILUSE;
	}
	else if (check_flg_cond(p_flgcb, waiptn, wfmode, p_flgptn)) {
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_flgcb))) == NULL){
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_winfo_flg = (WINFO_FLG *)(&(p_runtsk->winfo_obj));
		p_winfo_flg->waiptn = waiptn;
		p_winfo_flg->wfmode = wfmode;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_FLG);
		wobj_make_wait((WOBJCB *) p_flgcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		dispatch();
		/* �ͤλ��Ȥ����ʤΤǥ�å���ɬ�פʤ� */
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_flgptn = p_winfo_flg->flgptn;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_WAI_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* TOPPERS_wai_flg */

/*
 *  ���٥�ȥե饰�Ԥ��ʥݡ���󥰡�
 */
#ifdef TOPPERS_pol_flg

ER
pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*p_flgcb;
	ER		ercd;

	LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0U);
	CHECK_PAR(wfmode == TWF_ORW || wfmode == TWF_ANDW);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	if ((p_flgcb->p_flginib->flgatr & TA_WMUL) == 0U
					&& !queue_empty(&(p_flgcb->wait_queue))) {
		ercd = E_ILUSE;
	}
	else if (check_flg_cond(p_flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	t_unlock_cpu();

  error_exit:
	LOG_POL_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* TOPPERS_pol_flg */

/*
 *  ���٥�ȥե饰�Ԥ��ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_twai_flg

ER
twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout)
{
	FLGCB	*p_flgcb;
	WINFO_FLG *p_winfo_flg;
	ER		ercd;
	PCB		*my_p_pcb;
	TCB		*p_runtsk;

	LOG_TWAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn, tmout);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0U);
	CHECK_PAR(wfmode == TWF_ORW || wfmode == TWF_ANDW);
	CHECK_TMOUT(tmout);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	if ((p_flgcb->p_flginib->flgatr & TA_WMUL) == 0U
					&& !queue_empty(&(p_flgcb->wait_queue))) {
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		ercd = E_ILUSE;
	}
	else if (check_flg_cond(p_flgcb, waiptn, wfmode, p_flgptn)) {
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		ercd = E_TMOUT;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_flgcb))) == NULL){
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_winfo_flg = (WINFO_FLG *)(&(p_runtsk->winfo_obj));
		p_winfo_flg->waiptn = waiptn;
		p_winfo_flg->wfmode = wfmode;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_FLG);
		wobj_make_wait_tmout((WOBJCB *) p_flgcb, tmout, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_flgcb));
		dispatch();
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_flgptn = p_winfo_flg->flgptn;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TWAI_FLG_LEAVE(ercd, *p_flgptn);
	return(ercd);
}

#endif /* TOPPERS_twai_flg */

/*
 *  ���٥�ȥե饰�κƽ����
 */
#ifdef TOPPERS_ini_flg

ER
ini_flg(ID flgid)
{
	FLGCB	*p_flgcb;
	ER		ercd;
	bool_t	dspreq;

	LOG_INI_FLG_ENTER(flgid);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	dspreq = init_wait_queue(&(p_flgcb->wait_queue));
	p_flgcb->flgptn = p_flgcb->p_flginib->iflgptn;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_INI_FLG_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_flg */

/*
 *  ���٥�ȥե饰�ξ��ֻ���
 */
#ifdef TOPPERS_ref_flg

ER
ref_flg(ID flgid, T_RFLG *pk_rflg)
{
	FLGCB	*p_flgcb;
	ER		ercd;

	LOG_REF_FLG_ENTER(flgid, pk_rflg);
	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	p_flgcb = get_flgcb(flgid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_flgcb));
	pk_rflg->wtskid = wait_tskid(&(p_flgcb->wait_queue));
	pk_rflg->flgptn = p_flgcb->flgptn;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_flgcb));
	t_unlock_cpu();

  error_exit:
	LOG_REF_FLG_LEAVE(ercd, pk_rflg);
	return(ercd);
}

#endif /* TOPPERS_ref_flg */
