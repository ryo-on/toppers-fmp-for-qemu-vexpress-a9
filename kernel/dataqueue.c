/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: dataqueue.c 792 2011-03-10 14:18:33Z ertl-honda $
 */

/*
 *		�ǡ������塼��ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "dataqueue.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SND_DTQ_ENTER
#define LOG_SND_DTQ_ENTER(dtqid, data)
#endif /* LOG_SND_DTQ_ENTER */

#ifndef LOG_SND_DTQ_LEAVE
#define LOG_SND_DTQ_LEAVE(ercd)
#endif /* LOG_SND_DTQ_LEAVE */

#ifndef LOG_PSND_DTQ_ENTER
#define LOG_PSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_PSND_DTQ_ENTER */

#ifndef LOG_PSND_DTQ_LEAVE
#define LOG_PSND_DTQ_LEAVE(ercd)
#endif /* LOG_PSND_DTQ_LEAVE */

#ifndef LOG_IPSND_DTQ_ENTER
#define LOG_IPSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_IPSND_DTQ_ENTER */

#ifndef LOG_IPSND_DTQ_LEAVE
#define LOG_IPSND_DTQ_LEAVE(ercd)
#endif /* LOG_IPSND_DTQ_LEAVE */

#ifndef LOG_TSND_DTQ_ENTER
#define LOG_TSND_DTQ_ENTER(dtqid, data, tmout)
#endif /* LOG_TSND_DTQ_ENTER */

#ifndef LOG_TSND_DTQ_LEAVE
#define LOG_TSND_DTQ_LEAVE(ercd)
#endif /* LOG_TSND_DTQ_LEAVE */

#ifndef LOG_FSND_DTQ_ENTER
#define LOG_FSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_FSND_DTQ_ENTER */

#ifndef LOG_FSND_DTQ_LEAVE
#define LOG_FSND_DTQ_LEAVE(ercd)
#endif /* LOG_FSND_DTQ_LEAVE */

#ifndef LOG_IFSND_DTQ_ENTER
#define LOG_IFSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_IFSND_DTQ_ENTER */

#ifndef LOG_IFSND_DTQ_LEAVE
#define LOG_IFSND_DTQ_LEAVE(ercd)
#endif /* LOG_IFSND_DTQ_LEAVE */

#ifndef LOG_RCV_DTQ_ENTER
#define LOG_RCV_DTQ_ENTER(dtqid, p_data)
#endif /* LOG_RCV_DTQ_ENTER */

#ifndef LOG_RCV_DTQ_LEAVE
#define LOG_RCV_DTQ_LEAVE(ercd, data)
#endif /* LOG_RCV_DTQ_LEAVE */

#ifndef LOG_PRCV_DTQ_ENTER
#define LOG_PRCV_DTQ_ENTER(dtqid, p_data)
#endif /* LOG_PRCV_DTQ_ENTER */

#ifndef LOG_PRCV_DTQ_LEAVE
#define LOG_PRCV_DTQ_LEAVE(ercd, data)
#endif /* LOG_PRCV_DTQ_LEAVE */

#ifndef LOG_TRCV_DTQ_ENTER
#define LOG_TRCV_DTQ_ENTER(dtqid, p_data, tmout)
#endif /* LOG_TRCV_DTQ_ENTER */

#ifndef LOG_TRCV_DTQ_LEAVE
#define LOG_TRCV_DTQ_LEAVE(ercd, data)
#endif /* LOG_TRCV_DTQ_LEAVE */

#ifndef LOG_INI_DTQ_ENTER
#define LOG_INI_DTQ_ENTER(dtqid)
#endif /* LOG_INI_DTQ_ENTER */

#ifndef LOG_INI_DTQ_LEAVE
#define LOG_INI_DTQ_LEAVE(ercd)
#endif /* LOG_INI_DTQ_LEAVE */

#ifndef LOG_REF_DTQ_ENTER
#define LOG_REF_DTQ_ENTER(dtqid, pk_rdtq)
#endif /* LOG_REF_DTQ_ENTER */

#ifndef LOG_REF_DTQ_LEAVE
#define LOG_REF_DTQ_LEAVE(ercd, pk_rdtq)
#endif /* LOG_REF_DTQ_LEAVE */

/*
 *  �ǡ������塼�ο�
 */
#define tnum_dtq	((uint_t)(tmax_dtqid - TMIN_DTQID + 1))

/*
 *  �ǡ������塼ID����ǡ������塼�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_DTQ(dtqid)	((uint_t)((dtqid) - TMIN_DTQID))
#define get_dtqcb(dtqid)	(p_dtqcb_table[INDEX_DTQ(dtqid)])

/*
 *  �ǡ������塼��ǽ�ν����
 */
#ifdef TOPPERS_dtqini

void
initialize_dataqueue(void)
{
	uint_t	i;
	DTQCB	*p_dtqcb;

	if (x_sense_mprc()) {
		for (i = 0; i < tnum_dtq; i++) {
			p_dtqcb = p_dtqcb_table[i];
			queue_initialize(&(p_dtqcb->swait_queue));
			p_dtqcb->p_dtqinib = &(dtqinib_table[i]);
			queue_initialize(&(p_dtqcb->rwait_queue));
			p_dtqcb->count = 0U;
			p_dtqcb->head = 0U;
			p_dtqcb->tail = 0U;
#if TTYPE_KLOCK == F_KLOCK
			x_initialize_obj_lock(&(p_dtqcb->obj_lock));
#endif /* TTYPE_KLOCK == F_KLOCK */
		}
	}
}

#endif /* TOPPERS_dtqini */

/*
 *  �ǡ������塼�����ΰ�ؤΥǡ����γ�Ǽ
 */
#ifdef TOPPERS_dtqenq

void
enqueue_data(DTQCB *p_dtqcb, intptr_t data)
{
	(p_dtqcb->p_dtqinib->p_dtqmb + p_dtqcb->tail)->data = data;
	p_dtqcb->count++;
	p_dtqcb->tail++;
	if (p_dtqcb->tail >= p_dtqcb->p_dtqinib->dtqcnt) {
		p_dtqcb->tail = 0U;
	}
}

#endif /* TOPPERS_dtqenq */

/*
 *  �ǡ������塼�����ΰ�ؤΥǡ����ζ�����Ǽ
 */
#ifdef TOPPERS_dtqfenq

void
force_enqueue_data(DTQCB *p_dtqcb, intptr_t data)
{
	(p_dtqcb->p_dtqinib->p_dtqmb + p_dtqcb->tail)->data = data;
	p_dtqcb->tail++;
	if (p_dtqcb->tail >= p_dtqcb->p_dtqinib->dtqcnt) {
		p_dtqcb->tail = 0U;
	}
	if (p_dtqcb->count < p_dtqcb->p_dtqinib->dtqcnt) {
		p_dtqcb->count++;
	}
	else {
		p_dtqcb->head = p_dtqcb->tail;
	}
}

#endif /* TOPPERS_dtqfenq */

/*
 *  �ǡ������塼�����ΰ褫��Υǡ����μ�Ф�
 */
#ifdef TOPPERS_dtqdeq

void
dequeue_data(DTQCB *p_dtqcb, intptr_t *p_data)
{
	*p_data = (p_dtqcb->p_dtqinib->p_dtqmb + p_dtqcb->head)->data;
	p_dtqcb->count--;
	p_dtqcb->head++;
	if (p_dtqcb->head >= p_dtqcb->p_dtqinib->dtqcnt) {
		p_dtqcb->head = 0U;
	}
}

#endif /* TOPPERS_dtqdeq */

/*
 *  �ǡ������塼�ؤ�����
 */
#ifdef TOPPERS_snd_dtq

ER
snd_dtq(ID dtqid, intptr_t data)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_SND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_dtqcb->count < p_dtqcb->p_dtqinib->dtqcnt) {
		enqueue_data(p_dtqcb, data);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->winfo_obj.dtq.data = data;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SDTQ);
		wobj_make_wait((WOBJCB *) p_dtqcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_SND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_snd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡�
 */
#ifdef TOPPERS_psnd_dtq

ER
psnd_dtq(ID dtqid, intptr_t data)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_PSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ��� */
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		ercd = E_OK;
	}
	else if (p_dtqcb->count < p_dtqcb->p_dtqinib->dtqcnt) {
		enqueue_data(p_dtqcb, data);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_PSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_psnd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥݡ���󥰡��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_ipsnd_dtq

ER
ipsnd_dtq(ID dtqid, intptr_t data)
{
	DTQCB	*p_dtqcb;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_IPSND_DTQ_ENTER(dtqid, data);
	CHECK_INTCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	i_lock_cpu();

  retry:
	i_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb = i_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			if (dispatch_request(p_pcb)) {
				(get_my_p_pcb())->reqflg = true;
			}
		}
		release_nested_tsk_lock(p_pcb);
		i_unlock_cpu();
		ercd = E_OK;
	}
	else if (p_dtqcb->count < p_dtqcb->p_dtqinib->dtqcnt) {
		enqueue_data(p_dtqcb, data);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	i_unlock_cpu();

  error_exit:
	LOG_IPSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ipsnd_dtq */

/*
 *  �ǡ������塼�ؤ������ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_tsnd_dtq

ER
tsnd_dtq(ID dtqid, intptr_t data, TMO tmout)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_TSND_DTQ_ENTER(dtqid, data, tmout);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	CHECK_TMOUT(tmout);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_dtqcb->count < p_dtqcb->p_dtqinib->dtqcnt) {
		enqueue_data(p_dtqcb, data);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_TMOUT;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->winfo_obj.dtq.data = data;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SDTQ);
		wobj_make_wait_tmout((WOBJCB *) p_dtqcb, tmout, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_TSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_tsnd_dtq */

/*
 *  �ǡ������塼�ؤζ�������
 */
#ifdef TOPPERS_fsnd_dtq

ER
fsnd_dtq(ID dtqid, intptr_t data)
{
	DTQCB	*p_dtqcb;
	ER		ercd;
	bool_t	dspreq = false;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_FSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);
	CHECK_ILUSE(p_dtqcb->p_dtqinib->dtqcnt > 0U);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb =t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
	}
	else {
		force_enqueue_data(p_dtqcb, data);
	}
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	if (dspreq) {
		dispatch();
	}
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_FSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_fsnd_dtq */

/*
 *  �ǡ������塼�ؤζ����������󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_ifsnd_dtq

ER
ifsnd_dtq(ID dtqid, intptr_t data)
{
	DTQCB	*p_dtqcb;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_IFSND_DTQ_ENTER(dtqid, data);
	CHECK_INTCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);
	CHECK_ILUSE(p_dtqcb->p_dtqinib->dtqcnt > 0U);

	i_lock_cpu();

  retry:
	i_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/*
	 * ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���
	 */
	if (!queue_empty(&(p_dtqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_dtqcb->rwait_queue.p_next);
		if ((p_pcb = i_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.dtq.data = data;
		if (wait_complete(p_tcb)) {
			if (dispatch_request(p_pcb)){
				(get_my_p_pcb())->reqflg = true;
			}
		}
		release_nested_tsk_lock(p_pcb);
		i_unlock_cpu();
	}
	else {
		force_enqueue_data(p_dtqcb, data);
	}
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	i_unlock_cpu();

  error_exit:
	LOG_IFSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ifsnd_dtq */

/*
 *  �ǡ������塼����μ���
 */
#ifdef TOPPERS_rcv_dtq

ER
rcv_dtq(ID dtqid, intptr_t *p_data)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_RCV_DTQ_ENTER(dtqid, p_data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	if (!queue_empty(&(p_dtqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_dtqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_dtqcb->count > 0U) {
			dequeue_data(p_dtqcb, p_data);
			enqueue_data(p_dtqcb, p_tcb->winfo_obj.dtq.data);
		}
		else {
			*p_data = p_tcb->winfo_obj.dtq.data;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_dtqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_data(p_dtqcb, p_data);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_OK;
	}
	else {
		/* �Хåե��������������Ԥ��������ʤ� */
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RDTQ);
		make_wait(p_runtsk);
		queue_insert_prev(&(p_dtqcb->rwait_queue), &(p_runtsk->task_queue));
		p_runtsk->p_wobjcb = (WOBJCB*)p_dtqcb;
		LOG_TSKSTAT(p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		dispatch();
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_data = p_runtsk->winfo_obj.dtq.data;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_RCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* TOPPERS_rcv_dtq */

/*
 *  �ǡ������塼����μ����ʥݡ���󥰡�
 */
#ifdef TOPPERS_prcv_dtq

ER
prcv_dtq(ID dtqid, intptr_t *p_data)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_PRCV_DTQ_ENTER(dtqid, p_data);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ��� */
	if (!queue_empty(&(p_dtqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_dtqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_dtqcb->count > 0U) {
			dequeue_data(p_dtqcb, p_data);
			enqueue_data(p_dtqcb, p_tcb->winfo_obj.dtq.data);
		}
		else {
			*p_data = p_tcb->winfo_obj.dtq.data;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		ercd = E_OK;
	}
	else if (p_dtqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_data(p_dtqcb, p_data);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_PRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* TOPPERS_prcv_dtq */

/*
 *  �ǡ������塼����μ����ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_trcv_dtq

ER
trcv_dtq(ID dtqid, intptr_t *p_data, TMO tmout)
{
	DTQCB	*p_dtqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_TRCV_DTQ_ENTER(dtqid, p_data, tmout);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	CHECK_TMOUT(tmout);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_dtqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_dtqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_dtqcb->count > 0U) {
			dequeue_data(p_dtqcb, p_data);
			enqueue_data(p_dtqcb, p_tcb->winfo_obj.dtq.data);
		}
		else {
			*p_data = p_tcb->winfo_obj.dtq.data;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_dtqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_data(p_dtqcb, p_data);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_OK;
	}   /* �Хåե��������������Ԥ��������ʤ� */
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		ercd = E_TMOUT;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_dtqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RDTQ);
		make_wait_tmout(tmout, my_p_pcb);
		queue_insert_prev(&(p_dtqcb->rwait_queue), &(p_runtsk->task_queue));
		p_runtsk->p_wobjcb = (WOBJCB*)p_dtqcb;
		LOG_TSKSTAT(p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_dtqcb));
		dispatch();
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_data = p_runtsk->winfo_obj.dtq.data;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* TOPPERS_trcv_dtq */

/*
 *  �ǡ������塼�κƽ����
 */
#ifdef TOPPERS_ini_dtq

ER
ini_dtq(ID dtqid)
{
	DTQCB	*p_dtqcb;
	ER		ercd;
	bool_t	dspreq;

	LOG_INI_DTQ_ENTER(dtqid);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	dspreq = init_wait_queue(&(p_dtqcb->swait_queue));
	if (init_wait_queue(&(p_dtqcb->rwait_queue))){
		dspreq = true;
	}
	p_dtqcb->count = 0U;
	p_dtqcb->head = 0U;
	p_dtqcb->tail = 0U;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_INI_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_dtq */

/*
 *  �ǡ������塼�ξ��ֻ���
 */
#ifdef TOPPERS_ref_dtq

ER
ref_dtq(ID dtqid, T_RDTQ *pk_rdtq)
{
	DTQCB	*p_dtqcb;
	ER		ercd;

	LOG_REF_DTQ_ENTER(dtqid, pk_rdtq);
	CHECK_TSKCTX_UNL();
	CHECK_DTQID(dtqid);
	p_dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_dtqcb));
	pk_rdtq->stskid = wait_tskid(&(p_dtqcb->swait_queue));
	pk_rdtq->rtskid = wait_tskid(&(p_dtqcb->rwait_queue));
	pk_rdtq->sdtqcnt = p_dtqcb->count;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_dtqcb));
	t_unlock_cpu();

  error_exit:
	LOG_REF_DTQ_LEAVE(ercd, pk_rdtq);
	return(ercd);
}

#endif /* TOPPERS_ref_dtq */
