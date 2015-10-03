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
 *  @(#) $Id: pridataq.c 654 2010-07-25 14:17:01Z ertl-honda $
 */

/*
 *		ͥ���٥ǡ������塼��ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "pridataq.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_SND_PDQ_ENTER
#define LOG_SND_PDQ_ENTER(pdqid, data, datapri)
#endif /* LOG_SND_PDQ_ENTER */

#ifndef LOG_SND_PDQ_LEAVE
#define LOG_SND_PDQ_LEAVE(ercd)
#endif /* LOG_SND_PDQ_LEAVE */

#ifndef LOG_PSND_PDQ_ENTER
#define LOG_PSND_PDQ_ENTER(pdqid, data, datapri)
#endif /* LOG_PSND_PDQ_ENTER */

#ifndef LOG_PSND_PDQ_LEAVE
#define LOG_PSND_PDQ_LEAVE(ercd)
#endif /* LOG_PSND_PDQ_LEAVE */

#ifndef LOG_IPSND_PDQ_ENTER
#define LOG_IPSND_PDQ_ENTER(pdqid, data, datapri)
#endif /* LOG_IPSND_PDQ_ENTER */

#ifndef LOG_IPSND_PDQ_LEAVE
#define LOG_IPSND_PDQ_LEAVE(ercd)
#endif /* LOG_IPSND_PDQ_LEAVE */

#ifndef LOG_TSND_PDQ_ENTER
#define LOG_TSND_PDQ_ENTER(pdqid, data, datapri, tmout)
#endif /* LOG_TSND_PDQ_ENTER */

#ifndef LOG_TSND_PDQ_LEAVE
#define LOG_TSND_PDQ_LEAVE(ercd)
#endif /* LOG_TSND_PDQ_LEAVE */

#ifndef LOG_RCV_PDQ_ENTER
#define LOG_RCV_PDQ_ENTER(pdqid, p_data, p_datapri)
#endif /* LOG_RCV_PDQ_ENTER */

#ifndef LOG_RCV_PDQ_LEAVE
#define LOG_RCV_PDQ_LEAVE(ercd, data, datapri)
#endif /* LOG_RCV_PDQ_LEAVE */

#ifndef LOG_PRCV_PDQ_ENTER
#define LOG_PRCV_PDQ_ENTER(pdqid, p_data, p_datapri)
#endif /* LOG_PRCV_PDQ_ENTER */

#ifndef LOG_PRCV_PDQ_LEAVE
#define LOG_PRCV_PDQ_LEAVE(ercd, data, datapri)
#endif /* LOG_PRCV_PDQ_LEAVE */

#ifndef LOG_TRCV_PDQ_ENTER
#define LOG_TRCV_PDQ_ENTER(pdqid, p_data, p_datapri, tmout)
#endif /* LOG_TRCV_PDQ_ENTER */

#ifndef LOG_TRCV_PDQ_LEAVE
#define LOG_TRCV_PDQ_LEAVE(ercd, data, datapri)
#endif /* LOG_TRCV_PDQ_LEAVE */

#ifndef LOG_INI_PDQ_ENTER
#define LOG_INI_PDQ_ENTER(pdqid)
#endif /* LOG_INI_PDQ_ENTER */

#ifndef LOG_INI_PDQ_LEAVE
#define LOG_INI_PDQ_LEAVE(ercd)
#endif /* LOG_INI_PDQ_LEAVE */

#ifndef LOG_REF_PDQ_ENTER
#define LOG_REF_PDQ_ENTER(pdqid, pk_rpdq)
#endif /* LOG_REF_PDQ_ENTER */

#ifndef LOG_REF_PDQ_LEAVE
#define LOG_REF_PDQ_LEAVE(ercd, pk_rpdq)
#endif /* LOG_REF_PDQ_LEAVE */

/*
 *  ͥ���٥ǡ������塼�ο�
 */
#define tnum_pdq	((uint_t)(tmax_pdqid - TMIN_PDQID + 1))

/*
 *  ͥ���٥ǡ������塼ID����ͥ���٥ǡ������塼�����֥�å�����Ф���
 *  ��Υޥ���
 */
#define INDEX_PDQ(pdqid)	((uint_t)((pdqid) - TMIN_PDQID))
#define get_pdqcb(pdqid)	(p_pdqcb_table[INDEX_PDQ(pdqid)])

/*
 *  ͥ���٥ǡ������塼��ǽ�ν����
 */
#ifdef TOPPERS_pdqini

void
initialize_pridataq(void)
{
	uint_t	i;
	PDQCB	*p_pdqcb;

	if (x_sense_mprc()) {
		for (i = 0; i < tnum_pdq; i++) {
			p_pdqcb = p_pdqcb_table[i];
			queue_initialize(&(p_pdqcb->swait_queue));
			p_pdqcb->p_pdqinib = &(pdqinib_table[i]);
			queue_initialize(&(p_pdqcb->rwait_queue));
			p_pdqcb->count = 0U;
			p_pdqcb->p_head = NULL;
			p_pdqcb->unused = 0U;
			p_pdqcb->p_freelist = NULL;
#if TTYPE_KLOCK == F_KLOCK
			x_initialize_obj_lock(&(p_pdqcb->obj_lock));
#endif /* TTYPE_KLOCK == F_KLOCK */
		}
	}
}

#endif /* TOPPERS_pdqini */

/*
 *  ͥ���٥ǡ������塼�����ΰ�ؤΥǡ����γ�Ǽ
 */
#ifdef TOPPERS_pdqenq

void
enqueue_pridata(PDQCB *p_pdqcb, intptr_t data, PRI datapri)
{
	PDQMB	*p_pdqmb;
	PDQMB	**pp_prev_next, *p_next;

	if (p_pdqcb->p_freelist != NULL) {
		p_pdqmb = p_pdqcb->p_freelist;
		p_pdqcb->p_freelist = p_pdqmb->p_next;
	}
	else {
		p_pdqmb = p_pdqcb->p_pdqinib->p_pdqmb + p_pdqcb->unused;
		p_pdqcb->unused++;
	}

	p_pdqmb->data = data;
	p_pdqmb->datapri = datapri;

	pp_prev_next = &(p_pdqcb->p_head);
	while ((p_next = *pp_prev_next) != NULL) {
		if (p_next->datapri > datapri) {
			break;
		}
		pp_prev_next = &(p_next->p_next);
	}
	p_pdqmb->p_next = p_next;
	*pp_prev_next = p_pdqmb;
	p_pdqcb->count++;
}

#endif /* TOPPERS_pdqenq */

/*
 *  ͥ���٥ǡ������塼�����ΰ褫��Υǡ����μ�Ф�
 */
#ifdef TOPPERS_pdqdeq

void
dequeue_pridata(PDQCB *p_pdqcb, intptr_t *p_data, PRI *p_datapri)
{
	PDQMB	*p_pdqmb;

	p_pdqmb = p_pdqcb->p_head;
	p_pdqcb->p_head = p_pdqmb->p_next;
	p_pdqcb->count--;

	*p_data = p_pdqmb->data;
	*p_datapri = p_pdqmb->datapri;

	p_pdqmb->p_next = p_pdqcb->p_freelist;
	p_pdqcb->p_freelist = p_pdqmb;
}

#endif /* TOPPERS_pdqdeq */

/*
 *  ͥ���٥ǡ������塼�ؤ�����
 */
#ifdef TOPPERS_snd_pdq

ER
snd_pdq(ID pdqid, intptr_t data, PRI datapri)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_SND_PDQ_ENTER(pdqid, data, datapri);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);
	CHECK_PAR(TMIN_DPRI <= datapri && datapri <= p_pdqcb->p_pdqinib->maxdpri);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (!queue_empty(&(p_pdqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_pdqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.pdq.data = data;
		p_tcb->winfo_obj.pdq.datapri = datapri;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_pdqcb->count < p_pdqcb->p_pdqinib->pdqcnt) {
		enqueue_pridata(p_pdqcb, data, datapri);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_OK;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->winfo_obj.pdq.data = data;
		p_runtsk->winfo_obj.pdq.datapri = datapri;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SPDQ);
		wobj_make_wait((WOBJCB *) p_pdqcb, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_SND_PDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_snd_pdq */

/*
 *  ͥ���٥ǡ������塼�ؤ������ʥݡ���󥰡�
 */
#ifdef TOPPERS_psnd_pdq

ER
psnd_pdq(ID pdqid, intptr_t data, PRI datapri)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_PSND_PDQ_ENTER(pdqid, data, datapri);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);
	CHECK_PAR(TMIN_DPRI <= datapri && datapri <= p_pdqcb->p_pdqinib->maxdpri);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_pdqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_pdqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.pdq.data = data;
		p_tcb->winfo_obj.pdq.datapri = datapri;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		ercd = E_OK;
	}
	else if (p_pdqcb->count < p_pdqcb->p_pdqinib->pdqcnt) {
		enqueue_pridata(p_pdqcb, data, datapri);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_PSND_PDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_psnd_pdq */

/*
 *  ͥ���٥ǡ������塼�ؤ������ʥݡ���󥰡��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_ipsnd_pdq

ER
ipsnd_pdq(ID pdqid, intptr_t data, PRI datapri)
{
	PDQCB	*p_pdqcb;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_IPSND_PDQ_ENTER(pdqid, data, datapri);
	CHECK_INTCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);
	CHECK_PAR(TMIN_DPRI <= datapri && datapri <= p_pdqcb->p_pdqinib->maxdpri);

	i_lock_cpu();
  retry:
	i_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ���*/
	if (!queue_empty(&(p_pdqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_pdqcb->rwait_queue.p_next);
		if ((p_pcb = i_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.pdq.data = data;
		p_tcb->winfo_obj.pdq.datapri = datapri;
		if (wait_complete(p_tcb)) {
			if (dispatch_request(p_pcb)) {
				(get_my_p_pcb())->reqflg = true;
			}
		}
		release_nested_tsk_lock(p_pcb);
		i_unlock_cpu();
		ercd = E_OK;
	}
	else if (p_pdqcb->count < p_pdqcb->p_pdqinib->pdqcnt) {
		enqueue_pridata(p_pdqcb, data, datapri);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_pdqcb));
	i_unlock_cpu();

  error_exit:
	LOG_IPSND_PDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ipsnd_pdq */

/*
 *  ͥ���٥ǡ������塼�ؤ������ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_tsnd_pdq

ER
tsnd_pdq(ID pdqid, intptr_t data, PRI datapri, TMO tmout)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_TSND_PDQ_ENTER(pdqid, data, datapri, tmout);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	CHECK_TMOUT(tmout);
	p_pdqcb = get_pdqcb(pdqid);
	CHECK_PAR(TMIN_DPRI <= datapri && datapri <= p_pdqcb->p_pdqinib->maxdpri);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (!queue_empty(&(p_pdqcb->rwait_queue))) {
		p_tcb = (TCB *)(p_pdqcb->rwait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		p_tcb->winfo_obj.pdq.data = data;
		p_tcb->winfo_obj.pdq.datapri = datapri;
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_pdqcb->count < p_pdqcb->p_pdqinib->pdqcnt) {
		enqueue_pridata(p_pdqcb, data, datapri);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_OK;
	}   /* �Хåե����ե뤫�ļ����Ԥ��������ʤ� */
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_TMOUT;
	}
	else {
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->winfo_obj.pdq.data = data;
		p_runtsk->winfo_obj.pdq.datapri = datapri;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SPDQ);
		wobj_make_wait_tmout((WOBJCB *) p_pdqcb, tmout, p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		dispatch();
		ercd = p_runtsk->wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_TSND_PDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_tsnd_pdq */

/*
 *  ͥ���٥ǡ������塼����μ���
 */
#ifdef TOPPERS_rcv_pdq

ER
rcv_pdq(ID pdqid, intptr_t *p_data, PRI *p_datapri)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_RCV_PDQ_ENTER(pdqid, p_data, p_datapri);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ� */
	if (!queue_empty(&(p_pdqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_pdqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL){
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_pdqcb->count > 0U) {
			dequeue_pridata(p_pdqcb, p_data, p_datapri);
			enqueue_pridata(p_pdqcb, p_tcb->winfo_obj.pdq.data, p_tcb->winfo_obj.pdq.datapri);
		}
		else {
			*p_data = p_tcb->winfo_obj.pdq.data;
			*p_datapri = p_tcb->winfo_obj.pdq.datapri;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_pdqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_pridata(p_pdqcb, p_data, p_datapri);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_OK;
	}
	else {
		/* �Хåե��������������Ԥ��������ʤ� */
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RPDQ);
		make_wait(p_runtsk);
		queue_insert_prev(&(p_pdqcb->rwait_queue), &(p_runtsk->task_queue));
		p_runtsk->p_wobjcb = (WOBJCB*)p_pdqcb;
		LOG_TSKSTAT(p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		dispatch();
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_data = p_runtsk->winfo_obj.pdq.data;
			*p_datapri = p_runtsk->winfo_obj.pdq.datapri;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_RCV_PDQ_LEAVE(ercd, *p_data, *p_datapri);
	return(ercd);
}

#endif /* TOPPERS_rcv_pdq */

/*
 *  ͥ���٥ǡ������塼����μ����ʥݡ���󥰡�
 */
#ifdef TOPPERS_prcv_pdq

ER
prcv_pdq(ID pdqid, intptr_t *p_data, PRI *p_datapri)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*p_pcb;

	LOG_PRCV_PDQ_ENTER(pdqid, p_data, p_datapri);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));	
	/* ���δ֤Ϸ����֤��¹Ԥ���뤿�ᡤ���˲������ɤǤʤ���Фʤ�ʤ� */
	if (!queue_empty(&(p_pdqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_pdqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_pdqcb->count > 0U) {
			dequeue_pridata(p_pdqcb, p_data, p_datapri);
			enqueue_pridata(p_pdqcb, p_tcb->winfo_obj.pdq.data, p_tcb->winfo_obj.pdq.datapri);
		}
		else {
			*p_data = p_tcb->winfo_obj.pdq.data;
			*p_datapri = p_tcb->winfo_obj.pdq.datapri;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		ercd = E_OK;
	}
	else if (p_pdqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_pridata(p_pdqcb, p_data, p_datapri);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	release_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_PRCV_PDQ_LEAVE(ercd, *p_data, *p_datapri);
	return(ercd);
}

#endif /* TOPPERS_prcv_pdq */

/*
 *  ͥ���٥ǡ������塼����μ����ʥ����ॢ���Ȥ����
 */
#ifdef TOPPERS_trcv_pdq

ER
trcv_pdq(ID pdqid, intptr_t *p_data, PRI *p_datapri, TMO tmout)
{
	PDQCB	*p_pdqcb;
	bool_t	dspreq = false;
	ER		ercd;
	TCB		*p_tcb;
	PCB		*my_p_pcb;
	PCB		*p_pcb;
	TCB		*p_runtsk;

	LOG_TRCV_PDQ_ENTER(pdqid, p_data, p_datapri, tmout);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	CHECK_TMOUT(tmout);
	p_pdqcb = get_pdqcb(pdqid);

	t_lock_cpu();
	my_p_pcb = get_my_p_pcb();
	T_CHECK_DISPATCH(my_p_pcb);

  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (!queue_empty(&(p_pdqcb->swait_queue))) {
		/* �����Ԥ����������� */
		p_tcb = (TCB *)(p_pdqcb->swait_queue.p_next);
		if ((p_pcb = t_acquire_nested_tsk_lock(p_tcb, &GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		queue_delete((QUEUE *) p_tcb);
		if (p_pdqcb->count > 0U) {
			dequeue_pridata(p_pdqcb, p_data, p_datapri);
			enqueue_pridata(p_pdqcb, p_tcb->winfo_obj.pdq.data, p_tcb->winfo_obj.pdq.datapri);
		}
		else {
			*p_data = p_tcb->winfo_obj.pdq.data;
			*p_datapri = p_tcb->winfo_obj.pdq.datapri;
		}
		if (wait_complete(p_tcb)) {
			dspreq = dispatch_request(p_pcb);
		}
		release_nested_tsk_lock(p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (p_pdqcb->count > 0U) {
		/* �Хåե��˥ǡ��������ꡤ�����Ԥ��������ʤ� */
		dequeue_pridata(p_pdqcb, p_data, p_datapri);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_OK;
	}   /* �Хåե��������������Ԥ��������ʤ� */
	else if (tmout == TMO_POL) {
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		ercd = E_TMOUT;
	}
	else {
		/* �Хåե��������������Ԥ��������ʤ� */
		if ((my_p_pcb = t_acquire_nested_tsk_lock_self(&GET_OBJLOCK(p_pdqcb))) == NULL) {
			goto retry;
		}
		p_runtsk = my_p_pcb->p_runtsk;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RPDQ);
		make_wait_tmout(tmout, my_p_pcb);
		queue_insert_prev(&(p_pdqcb->rwait_queue), &(p_runtsk->task_queue));
		p_runtsk->p_wobjcb = (WOBJCB*)p_pdqcb;
		LOG_TSKSTAT(p_runtsk);
		release_nested_tsk_lock(my_p_pcb);
		release_obj_lock(&GET_OBJLOCK(p_pdqcb));
		dispatch();
		ercd = p_runtsk->wercd;
		if (ercd == E_OK) {
			*p_data = p_runtsk->winfo_obj.pdq.data;
			*p_datapri = p_runtsk->winfo_obj.pdq.datapri;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TRCV_PDQ_LEAVE(ercd, *p_data, *p_datapri);
	return(ercd);
}

#endif /* TOPPERS_trcv_pdq */

/*
 *  ͥ���٥ǡ������塼�κƽ����
 */
#ifdef TOPPERS_ini_pdq

ER
ini_pdq(ID pdqid)
{
	PDQCB	*p_pdqcb;
	ER		ercd;
	bool_t	dspreq;

	LOG_INI_PDQ_ENTER(pdqid);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	dspreq = init_wait_queue(&(p_pdqcb->swait_queue));
	if (init_wait_queue(&(p_pdqcb->rwait_queue))) {
		dspreq = true;
	}
	p_pdqcb->count = 0U;
	p_pdqcb->p_head = NULL;
	p_pdqcb->unused = 0U;
	p_pdqcb->p_freelist = NULL;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_pdqcb));
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_INI_PDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_pdq */

/*
 *  ͥ���٥ǡ������塼�ξ��ֻ���
 */
#ifdef TOPPERS_ref_pdq

ER
ref_pdq(ID pdqid, T_RPDQ *pk_rpdq)
{
	PDQCB	*p_pdqcb;
	ER		ercd;

	LOG_REF_PDQ_ENTER(pdqid, pk_rpdq);
	CHECK_TSKCTX_UNL();
	CHECK_PDQID(pdqid);
	p_pdqcb = get_pdqcb(pdqid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_pdqcb));
	pk_rpdq->stskid = wait_tskid(&(p_pdqcb->swait_queue));
	pk_rpdq->rtskid = wait_tskid(&(p_pdqcb->rwait_queue));
	pk_rpdq->spdqcnt = p_pdqcb->count;
	ercd = E_OK;
	release_obj_lock(&GET_OBJLOCK(p_pdqcb));
	t_unlock_cpu();

  error_exit:
	LOG_REF_PDQ_LEAVE(ercd, pk_rpdq);
	return(ercd);
}

#endif /* TOPPERS_ref_pdq */
