/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2015 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: task.c 1087 2015-02-03 01:04:34Z ertl-honda $
 */

/*
 *		�����������⥸�塼��
 */

#include "kernel_impl.h"
#include "wait.h"
#include "task.h"
#include "spin_lock.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_TEX_ENTER
#define LOG_TEX_ENTER(p_tcb, texptn)
#endif /* LOG_TEX_ENTER */

#ifndef LOG_TEX_LEAVE
#define LOG_TEX_LEAVE(p_tcb)
#endif /* LOG_TEX_LEAVE */

#ifdef TOPPERS_tskini

/*
 *  �����������⥸�塼��ν����
 */
void
initialize_task(void)
{
	uint_t	i, j;
	TCB		*p_tcb;
	PCB		*my_p_pcb;

	my_p_pcb = get_my_p_pcb();

	for (i = 0; i < tnum_tsk; i++) {
		j = INDEX_TSK(torder_table[i]);
		/* �������˳���դ��줿�������ν���� */
		if (tinib_table[j].iaffinity == ID_PRC(x_prc_index())) {
			p_tcb = p_tcb_table[j];
			p_tcb->p_tinib = &(tinib_table[j]);
			p_tcb->actque = false;
			p_tcb->actprc = TPRC_NONE;
			p_tcb->p_pcb = my_p_pcb;
			make_dormant(p_tcb);
			if ((p_tcb->p_tinib->tskatr & TA_ACT) != 0U) {
				(void) make_active(p_tcb);
			}
		}
	}
}

#endif /* TOPPERS_tskini */

/*
 *  �ӥåȥޥåץ������ؿ�
 *
 *  bitmap���1�ΥӥåȤ��⡤�ǤⲼ�̡ʱ��ˤΤ�Τ򥵡����������Υӥ�
 *  ���ֹ���֤����ӥå��ֹ�ϡ��ǲ��̥ӥåȤ�0�Ȥ��롥bitmap��0�����
 *  ���ƤϤʤ�ʤ������δؿ��Ǥϡ�bitmap��16�ӥåȤǤ��뤳�Ȥ��ꤷ��
 *  uint16_t���Ȥ��Ƥ��롥
 *
 *  �ӥåȥ�����̿�����ĥץ��å��Ǥϡ��ӥåȥ�����̿���Ȥ��褦��
 *  ��ľ����������Ψ���ɤ���礬���롥���Τ褦�ʾ��ˤϡ��������å�
 *  ��¸���ǥӥåȥ�����̿���Ȥä�bitmap_search���������
 *  OMIT_BITMAP_SEARCH��ޥ����������Ф褤���ޤ����ӥåȥ�����̿���
 *  �������������դʤɤ���ͳ��ͥ���٤ȥӥåȤȤ��б����ѹ�����������
 *  �ϡ�PRIMAP_BIT��ޥ����������Ф褤��
 *
 *  �ޤ����饤�֥���ffs������ʤ顤���Τ褦��������ƥ饤�֥��ؿ��� 
 *  �Ȥä�������Ψ���ɤ���ǽ���⤢��
 *		#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1U << (pri))
#endif /* PRIMAP_BIT */

#ifndef OMIT_BITMAP_SEARCH

static const unsigned char bitmap_search_table[] = { 0, 1, 0, 2, 0, 1, 0,
												3, 0, 1, 0, 2, 0, 1, 0 };

Inline uint_t
bitmap_search(uint16_t bitmap)
{
	uint_t	n = 0U;

	assert(bitmap != 0U);
	if ((bitmap & 0x00ffU) == 0U) {
		bitmap >>= 8;
		n += 8;
	}
	if ((bitmap & 0x0fU) == 0U) {
		bitmap >>= 4;
		n += 4;
	}
	return(n + bitmap_search_table[(bitmap & 0x0fU) - 1]);
}

#endif /* OMIT_BITMAP_SEARCH */

/*
 *  ͥ���٥ӥåȥޥåפ������Υ����å�
 */
Inline bool_t
primap_empty(PCB *p_pcb)
{
	return(p_pcb->ready_primap == 0U);
}

/*
 *  ͥ���٥ӥåȥޥåפΥ�����
 */
Inline uint_t
primap_search(PCB *p_pcb)
{
	return(bitmap_search(p_pcb->ready_primap));
}

/*
 *  ͥ���٥ӥåȥޥåפΥ��å�
 */
Inline void
primap_set(PCB *p_pcb, uint_t pri)
{
	p_pcb->ready_primap |= PRIMAP_BIT(pri);
}

/*
 *  ͥ���٥ӥåȥޥåפΥ��ꥢ
 */
Inline void
primap_clear(PCB *p_pcb, uint_t pri)
{
	p_pcb->ready_primap &= ~PRIMAP_BIT(pri);
}

/*
 *  �ǹ�ͥ���̥������Υ�����
 */
#ifdef TOPPERS_tsksched

TCB *
search_schedtsk(PCB *p_pcb)
{
	uint_t	schedpri;

	schedpri = primap_search(p_pcb);
	return((TCB *)((p_pcb->ready_queue)[schedpri].p_next));
}

#endif /* TOPPERS_tsksched */

/*
 *  �¹ԤǤ�����֤ؤΰܹ�
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ��¹ԤǤ��륿�������ʤ��ä����
 *  �ȡ�p_tcb��ͥ���٤��ǹ�ͥ���̤Υ�������ͥ���٤���⤤���Ǥ�
 *  �롥
 */
#ifdef TOPPERS_tskrun

bool_t
make_runnable(TCB *p_tcb)
{
	uint_t	pri = p_tcb->priority;
	PCB		*p_pcb;

	p_pcb = p_tcb->p_pcb;
	queue_insert_prev(&((p_pcb->ready_queue)[pri]), &(p_tcb->task_queue));
	primap_set(p_pcb, pri);

	if (p_pcb->p_schedtsk == (TCB *) NULL
		|| pri < p_pcb->p_schedtsk->priority) {
		p_pcb->p_schedtsk = p_tcb;
		return(p_pcb->dspflg);
	}
	return(false);
}

#endif /* TOPPERS_tskrun */

/*
 *  �¹ԤǤ�����֤���¾�ξ��֤ؤΰܹ�
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ�p_tcb���ǹ�ͥ���̤Υ�������
 *  ���ä����Ǥ��롥p_tcb��Ʊ��ͥ���٤Υ�������¾�ˤ�����ϡ�p_tcb
 *  �μ��Υ��������ǹ�ͥ���̤ˤʤ롥�����Ǥʤ����ϡ���ǥ����塼��
 *  ����������ɬ�פ����롥
 */
#ifdef TOPPERS_tsknrun

bool_t
make_non_runnable(TCB *p_tcb)
{
	uint_t	pri = p_tcb->priority;
	QUEUE	*p_queue = &((p_tcb->p_pcb->ready_queue)[pri]);
	PCB		*p_pcb = p_tcb->p_pcb;

	queue_delete(&(p_tcb->task_queue));
	if (queue_empty(p_queue)) {
		primap_clear(p_pcb,pri);
		if (p_pcb->p_schedtsk == p_tcb) {
			p_pcb->p_schedtsk = primap_empty(p_pcb) ? (TCB *) NULL : search_schedtsk(p_pcb);
			return(p_pcb->dspflg);
		}
	}
	else {
		if (p_pcb->p_schedtsk == p_tcb) {
			p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
			return(p_pcb->dspflg);
		}
	}
	return(false);
}

#endif /* TOPPERS_tsknrun */

/*
 *  �ٻ߾��֤ؤΰܹ�
 */
#ifdef TOPPERS_tskdmt

void
make_dormant(TCB *p_tcb)
{
	p_tcb->tstat = TS_DORMANT;
	p_tcb->priority = p_tcb->p_tinib->ipriority;
	p_tcb->wupque = false;
	p_tcb->enatex = false;
	p_tcb->texptn = 0U;
#if TTYPE_KLOCK != G_KLOCK
	p_tcb->pend_relwai = false;
	p_tcb->pend_chgpri = false;
#endif /* TTYPE_KLOCK != G_KLOCK */
	LOG_TSKSTAT(p_tcb);
}

#endif /* TOPPERS_tskdmt */

/*
 *  �ٻ߾��֤���¹ԤǤ�����֤ؤΰܹ�
 */
#ifdef TOPPERS_tskact

bool_t
make_active(TCB *p_tcb)
{
	activate_context(p_tcb);
	p_tcb->tstat = TS_RUNNABLE;
	LOG_TSKSTAT(p_tcb);
	return(make_runnable(p_tcb));
}

#endif /* TOPPERS_tskact */

/*
 *  ��������ͥ���٤��ѹ�
 *
 *  ���������¹ԤǤ�����֤ξ��ˤϡ���ǥ����塼����Ǥΰ��֤��ѹ���
 *  �롥���֥������Ȥ��Ԥ����塼������Ԥ����֤ˤʤäƤ�����ˤϡ���
 *  �����塼����Ǥΰ��֤��ѹ����롥
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ�(1) p_tcb���ǹ�ͥ���̤Υ���
 *  ���Ǥ��äơ�����ͥ���٤򲼤�����硤(2) p_tcb���ǹ�ͥ���̤Υ���
 *  ���ǤϤʤ����ѹ����ͥ���٤��ǹ�ͥ���̤Υ�������ͥ���٤���⤤
 *  ���Ǥ��롥(1)�ξ��ˤϡ���ǥ����塼�򥵡�������ɬ�פ����롥
 */
#ifdef TOPPERS_tskpri

bool_t
change_priority(TCB *p_tcb, uint_t newpri)
{
	uint_t	oldpri;
	PCB		*p_pcb;

	p_pcb = p_tcb->p_pcb;
	oldpri = p_tcb->priority;
	p_tcb->priority = newpri;

	if (TSTAT_RUNNABLE(p_tcb->tstat)) {
		/*
		 *  ���������¹ԤǤ�����֤ξ��
		 */
		queue_delete(&(p_tcb->task_queue));
		if (queue_empty(&((p_pcb->ready_queue)[oldpri]))) {
			primap_clear(p_pcb, oldpri);
		}
		queue_insert_prev(&((p_pcb->ready_queue)[newpri]), &(p_tcb->task_queue));
		primap_set(p_pcb, newpri);

		if (p_pcb->p_schedtsk == p_tcb) {
			if (newpri >= oldpri) {
				p_pcb->p_schedtsk = search_schedtsk(p_pcb);
				return(p_pcb->p_schedtsk != p_tcb && p_pcb->dspflg);
			}
		}
		else {
			if (newpri < p_pcb->p_schedtsk->priority) {
				p_pcb->p_schedtsk = p_tcb;
				return(p_pcb->dspflg);
			}
		}
	}
	else {
		if (TSTAT_WAIT_WOBJCB(p_tcb->tstat)) {
			/*
			 *  ����������Ʊ�����̿����֥������Ȥδ����֥�å��ζ�����
			 *  ʬ��WOBJCB�ˤ��Ԥ����塼�ˤĤʤ���Ƥ�����
			 */
			wobj_change_priority(p_tcb->p_wobjcb, p_tcb);
		}
	}
	return(false);
}

#endif /* TOPPERS_tskpri */

/*
 *  ��ǥ����塼�β�ž
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ��ǹ�ͥ���̤Υ���������������
 *  �塼�������˰�ư�������Ǥ��롥
 *
 */
#ifdef TOPPERS_tskrot

bool_t
rotate_ready_queue(uint_t pri, PCB *p_pcb)
{
	QUEUE	*p_queue = &((p_pcb->ready_queue)[pri]);
	QUEUE	*p_entry;

	if (!queue_empty(p_queue) && p_queue->p_next->p_next != p_queue) {
		p_entry = queue_delete_next(p_queue);
		queue_insert_prev(p_queue, p_entry);
		if (p_pcb->p_schedtsk == (TCB *) p_entry) {
			p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
			return(p_pcb->dspflg);
		}
	}
	return(false);
}

#endif /* TOPPERS_tskrot */

/*
 *  ͥ���̤�Ʊ��ͥ���٤Υ���������Ǻ����
 *
 *  ����ͥ���٤Υ�ǥ����塼�κǸ�������³���롥 
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ��ǹ�ͥ���̤Υ���������������
 *  �塼�������˰�ư�������Ǥ��롥
 */
#ifdef TOPPERS_tsklowprce

bool_t
set_lowest_precedence(TCB *p_tcb, PCB *p_pcb)
{
	uint_t	pri = p_tcb->priority;
	QUEUE	*p_queue = &((p_pcb->ready_queue)[pri]);

	queue_delete(&(p_tcb->task_queue));
	queue_insert_prev(p_queue, &(p_tcb->task_queue));

	if (p_pcb->p_schedtsk == p_tcb) {
		p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
		return(p_pcb->dspflg);
	}
	return(false);
}

#endif /* TOPPERS_tsklowprce */

/*
 *  �������㳰�����롼����θƽФ�
 *
 *  FMP�����ͥ�Ǥϡ��������㳰�����롼�������CPU��å����֤˰ܹԤ���
 *  ���ξ��֤��ᤵ���˥꥿���󤷤���硤�����ͥ뤬���ξ��֤��᤹��
 */
#ifdef TOPPERS_tsktex
#ifndef OMIT_CALL_TEXRTN

void
call_texrtn(PCB *my_p_pcb)
{
	TEXPTN	texptn;
	bool_t	saved_disdsp;
	TCB		*p_runtsk;

	saved_disdsp = my_p_pcb->disdsp;
	p_runtsk = my_p_pcb->p_runtsk;
	p_runtsk->enatex = false;
	do {
		texptn = p_runtsk->texptn;
		p_runtsk->texptn = 0U;
		/* ��������å��β��� */
		release_tsk_lock(my_p_pcb);
		t_unlock_cpu();

		LOG_TEX_ENTER(p_runtsk, texptn);
		(*((TEXRTN)(p_runtsk->p_tinib->texrtn)))(texptn,
												p_runtsk->p_tinib->exinf);
		LOG_TEX_LEAVE(p_runtsk);

		if (!t_sense_lock()) {
			t_lock_cpu();
		}
		/* ��������å��μ��� */
		my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
		if (!my_p_pcb->ipmflg) {
			t_set_ipm(TIPM_ENAALL);
			my_p_pcb->ipmflg = true;
		}
		my_p_pcb->disdsp = saved_disdsp;
		my_p_pcb->dspflg = !my_p_pcb->disdsp;
		p_runtsk->enatex = false;
		force_unlock_spin(my_p_pcb);
		if (p_runtsk != my_p_pcb->p_schedtsk && my_p_pcb->dspflg) {
			/* ��������å��β�����CPU��å��ϲ�����ʤ��� */
			release_tsk_lock(my_p_pcb);
			dispatch();
			/* ��������å��μ��� */
			my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
		}
	} while (p_runtsk->texptn != 0U);
	p_runtsk->enatex = true;
}

/*
 *  �ǥ����ѥå��㡼����Υ������㳰�����롼����θƤӽФ�
 *
 *  ��������å���������Ƥ��� call_texrtn() ��ƤӽФ��� 
 */
void
dispatch_call_texrtn(void)
{
	PCB		*my_p_pcb;

	/* ��������å��μ��� */
	my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
	call_texrtn(my_p_pcb);
	/* �ޥ����졼����󤵤�Ƥ����ǽ��������ΤǺƼ��� */
	my_p_pcb = get_my_p_pcb();
	/* ��������å��β��� */
	release_tsk_lock(my_p_pcb);
}


#endif /* OMIT_CALL_TEXRTN */

/*
 *  �������㳰�����롼����ε�ư
 */
#ifndef OMIT_CALLTEX

void
calltex(void)
{
	PCB *my_p_pcb;

	my_p_pcb = get_my_p_pcb();
	if (my_p_pcb->p_runtsk->enatex && my_p_pcb->p_runtsk->texptn != 0U
		&& my_p_pcb->ipmflg) {
		dispatch_call_texrtn();
	}
}

#endif /* OMIT_CALLTEX */
#endif /* TOPPERS_tsktex */

#ifdef TOPPERS_migrate_self

/*
 *  ����������ƥ����ȤǤμ����������Ф���ޥ����졼��������
 *
 *  CPU��å�����ư���Ȱ�ư��Υ�������å��μ���������ƥ�����
 *  ����¸�����Τ����󥿥�������ƥ����ȤΥ����å�����뤳�ȡ� 
 */
void
migrate_self(ID prcid)
{
	TCB		*p_tcb;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	f_p_pcb = get_my_p_pcb();
	p_tcb = f_p_pcb->p_runtsk;

	/* ��ư��Υץ��å���PCB����� */
	t_p_pcb = get_mp_p_pcb(prcid);

	if (TSTAT_RUNNABLE(p_tcb->tstat)) {
		/* ��ǥ������塼���鳰�� */
		make_non_runnable(p_tcb);
		/* pcb �ν񤭴��� */
		p_tcb->p_pcb = t_p_pcb;
		/* �ܹ���Υץ��å���make_runnable ����*/
		if (make_runnable(p_tcb)) {
			dispatch_request(t_p_pcb);
		}
	}
	else {
		/*
		 * CPU��å����ĥ�������å���������Ƥ��뤿��
		 * ¾�ξ��֤ˤϤʤ�ʤ�
		 */
		assert(0);
	}
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);

	/* �ǥ����ѥå��㡼�� */
	exit_and_dispatch();
	assert(0);
}

#endif /* TOPPERS_migrate_self */

#ifdef TOPPERS_exit_and_migrate_self

/*
 *  ����������ƥ����ȤǤμ����������Ф��륳��ƥ����Ȥ��˴���
 *  �ޥ����졼��������
 *
 *  CPU��å�����ư���Ȱ�ư��Υ�������å��μ��������Τ���
 *  �󥿥�������ƥ����ȤΥ����å�����뤳�ȡ� 
 */
void
exit_and_migrate_self(ID prcid)
{
	TCB		*p_tcb;
	PCB		*t_p_pcb;
	PCB		*f_p_pcb;

	f_p_pcb = get_my_p_pcb();
	p_tcb = f_p_pcb->p_runtsk;

	/* ��ư��Υץ��å���PCB����� */
	t_p_pcb = get_mp_p_pcb(prcid);

	(void) make_non_runnable(p_tcb);
	make_dormant(p_tcb);
	p_tcb->p_pcb = t_p_pcb;
	p_tcb->actque = false;
	p_tcb->actprc = TPRC_NONE;
	if (make_active(p_tcb)) {
		dispatch_request(t_p_pcb);
	}
	release_dual_tsk_lock(f_p_pcb, t_p_pcb);

	/* �ǥ����ѥå��㡼�� */
	exit_and_dispatch();
	assert(0);
}

#endif /* TOPPERS_exit_and_migrate_self */
