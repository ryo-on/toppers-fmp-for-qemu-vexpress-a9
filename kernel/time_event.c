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
 *  @(#) $Id: time_event.c 661 2010-07-29 10:10:12Z ertl-honda $
 */

/*
 *		�����।�٥�ȴ����⥸�塼��
 */

#include "kernel_impl.h"
#include "check.h"
#include "time_event.h"
#include "task.h"
#include "mp.h"

/*
 *  �����।�٥�ȥҡ������ޥ���
 */
#define	PARENT(index)		((index) >> 1)		/* �ƥΡ��ɤ���� */
#define	LCHILD(index)		((index) << 1)		/* ���λҥΡ��ɤ���� */
#define	TMEVT_NODE(p_tevtcb, index)	((p_tevtcb->p_tmevt_heap)[(index) - 1])

/*
 *  ���٥��ȯ��������ӥޥ���
 *
 *  ���٥��ȯ������ϡ�min_time����������ͤ���Ӥ��롥���ʤ����
 *  min_time��Ǿ��͡ʺǤ�ᤤ����ˡ�mit_time-1�������͡ʺǤ�󤤻����
 *  �󤤻���ˤȤߤʤ�����Ӥ��롥
 */
#define	EVTTIM_LT(p_tevtcb, t1, t2) (((t1) - p_tevtcb->min_time) < ((t2) - p_tevtcb->min_time))
#define	EVTTIM_LE(p_tevtcb, t1, t2) (((t1) - p_tevtcb->min_time) <= ((t2) - p_tevtcb->min_time))

#ifdef TOPPERS_tmeini

/*
 *  �����ޥ⥸�塼��ν����
 */
void
initialize_tmevt(void)
{
	PCB		*my_p_pcb;
	TEVTCB	*my_p_tevtcb;

	my_p_pcb = get_my_p_pcb();

	/*
	 *  PCB�ؤΥ��å�
	 */
#ifdef TOPPERS_SYSTIM_LOCAL
	/* �����륿���ޤξ�� */
	my_p_pcb->p_tevtcb = p_tevtcb_table[x_prc_index()];
	my_p_pcb->p_tevtcb->p_tmevt_heap = p_tmevt_heap_table[x_prc_index()];
#else /* TOPPERS_SYSTIM_GLOBAL */
	/* �����Х륿���ޤξ�� */
	my_p_pcb->p_tevtcb = &tevtcb;
	my_p_pcb->p_tevtcb->p_tmevt_heap = tmevt_heap;

	if (TOPPERS_SYSTIM_PRCID != ID_PRC(x_prc_index())) {
		return;
	}
#endif /* TOPPERS_SYSTIM_GLOBAL */

	my_p_tevtcb = my_p_pcb->p_tevtcb;

	my_p_tevtcb->min_time = 0U;
	my_p_tevtcb->current_time = 0U;
	my_p_tevtcb->next_time = my_p_tevtcb->current_time + TIC_NUME / TIC_DENO;
#if TIC_DENO != 1U
	my_p_tevtcb->next_subtime = TIC_NUME % TIC_DENO;
#endif /* TIC_DENO != 1U */
	my_p_tevtcb->last_index = 0U;
}

#endif /* TOPPERS_tmeini */

/*
 *  �����।�٥�Ȥ��������֤�������õ��
 *
 *  ����time��ȯ�����륿���।�٥�Ȥ���������Ρ��ɤ�����뤿��ˡ�
 *  �ҡ��פξ�˸����äƶ��Ρ��ɤ��ư�����롥��ư���ζ��Ρ��ɤΰ��֤�
 *  index���Ϥ��ȡ���ư��ζ��Ρ��ɤΰ��֡ʤ��ʤ���������֡ˤ��֤���
 */
#ifdef TOPPERS_tmeup

uint_t
tmevt_up(TEVTCB *p_tevtcb, uint_t index, EVTTIM time)
{
	uint_t	parent;

	while (index > 1) {
		/*
		 *  �ƥΡ��ɤΥ��٥��ȯ������������ᤤ�ʤޤ���Ʊ����
		 *  �ʤ�С�index ���������֤ʤΤǥ롼�פ�ȴ���롥
		 */
		parent = PARENT(index);
		if (EVTTIM_LE(p_tevtcb, TMEVT_NODE(p_tevtcb, parent).time, time)) {
			break;
		}

		/*
		 *  �ƥΡ��ɤ� index �ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(p_tevtcb, index) = TMEVT_NODE(p_tevtcb, parent);
		TMEVT_NODE(p_tevtcb, index).p_tmevtb->index = index;

		/*
		 *  index ��ƥΡ��ɤΰ��֤˹�����
		 */
		index = parent;
	}
	return(index);
}

#endif /* TOPPERS_tmeup */

/*
 *  �����।�٥�Ȥ��������֤򲼸�����õ��
 *
 *  ����time��ȯ�����륿���।�٥�Ȥ���������Ρ��ɤ�����뤿��ˡ�
 *  �ҡ��פβ��˸����äƶ��Ρ��ɤ��ư�����롥��ư���ζ��Ρ��ɤΰ��֤� 
 *  index���Ϥ��ȡ���ư��ζ��Ρ��ɤΰ��֡ʤ��ʤ���������֡ˤ��֤���
 */
#ifdef TOPPERS_tmedown

uint_t
tmevt_down(TEVTCB *p_tevtcb, uint_t index, EVTTIM time)
{
	uint_t	child;

	while ((child = LCHILD(index)) <= p_tevtcb->last_index) {
		/*
		 *  �����λҥΡ��ɤΥ��٥��ȯ���������Ӥ����ᤤ����
		 *  �ҥΡ��ɤΰ��֤� child �����ꤹ�롥�ʲ��λҥΡ���
		 *  �ϡ����������Ф줿���λҥΡ��ɤΤ��ȡ�
		 */
		if (child + 1 <= p_tevtcb->last_index
						&& EVTTIM_LT(p_tevtcb,
									 TMEVT_NODE(p_tevtcb, child + 1).time,
									 TMEVT_NODE(p_tevtcb, child).time)) {
			child = child + 1;
		}

		/*
		 *  �ҥΡ��ɤΥ��٥��ȯ������������٤��ʤޤ���Ʊ����
		 *  �ʤ�С�index ���������֤ʤΤǥ롼�פ�ȴ���롥
		 */
		if (EVTTIM_LE(p_tevtcb, time, TMEVT_NODE(p_tevtcb, child).time)) {
			break;
		}

		/*
		 *  �ҥΡ��ɤ� index �ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(p_tevtcb, index) = TMEVT_NODE(p_tevtcb, child);
		TMEVT_NODE(p_tevtcb, index).p_tmevtb->index = index;

		/*
		 *  index ��ҥΡ��ɤΰ��֤˹�����
		 */
		index = child;
	}
	return(index);
}

#endif /* TOPPERS_tmedown */

/*
 *  �����।�٥�ȥҡ��פؤ���Ͽ
 *
 *  p_tmevtb�ǻ��ꤷ�������।�٥�ȥ֥�å���time�ǻ��ꤷ�����֤���
 *  ���˥��٥�Ȥ�ȯ������褦�ˡ������।�٥�ȥҡ��פ���Ͽ���롥
 */
#ifdef TOPPERS_tmeins

void
tmevtb_insert(TEVTCB *p_tevtcb, TMEVTB *p_tmevtb, EVTTIM time)
{
	uint_t	index;

	/*
	 *  last_index �򥤥󥯥���Ȥ��������������������֤�õ����
	 */
	index = tmevt_up(p_tevtcb, ++(p_tevtcb->last_index), time);

	/*
	 *  �����।�٥�Ȥ� index �ΰ��֤��������롥
	 */ 
	TMEVT_NODE(p_tevtcb, index).time = time;
	TMEVT_NODE(p_tevtcb, index).p_tmevtb = p_tmevtb;
	p_tmevtb->index = index;
}

#endif /* TOPPERS_tmeins */

/*
 *  �����।�٥�ȥҡ��פ���κ��
 */
#ifdef TOPPERS_tmedel

RELTIM
tmevtb_delete(TEVTCB *p_tevtcb, TMEVTB *p_tmevtb)
{
	uint_t	index = p_tmevtb->index;
	uint_t	parent;
	EVTTIM	event_time = TMEVT_NODE(p_tevtcb, p_tevtcb->last_index).time;
	EVTTIM	time;
	RELTIM	left_time;

	/*
	 *  �����।�٥�ȤޤǤλĤ���֤�׻�
	 *  tmevt_leftim()�Ȥϰۤʤ��礭����(current_time�Ȥκ�ʬ)�˴ݤ�롥 
	 */
	time = TMEVT_NODE(p_tevtcb, p_tmevtb->index).time;
	left_time = (RELTIM)(time - p_tevtcb->current_time);

	/*
	 *  ����ˤ�꥿���।�٥�ȥҡ��פ����ˤʤ���ϲ��⤷�ʤ���
	 */
	if (--(p_tevtcb->last_index) == 0) {
		return(left_time);
	}

	/*
	 *  ��������Ρ��ɤΰ��֤˺Ǹ�ΥΡ��ɡ�last_index+1�ΰ��֤ΥΡ��ɡ�
	 *  ���������������Ŭ�ڤʰ��֤ذ�ư�����롥�ºݤˤϡ��Ǹ�ΥΡ���
	 *  ��ºݤ���������ΤǤϤʤ�����������Ρ��ɤΰ��֤����Ρ��ɤˤ�
	 *  ��Τǡ��Ǹ�ΥΡ��ɤ��������٤����֤ظ����ƶ��Ρ��ɤ��ư����
	 *  �롥
	 *  �Ǹ�ΥΡ��ɤΥ��٥��ȯ�����郎����������Ρ��ɤοƥΡ��ɤΥ�
	 *  �٥��ȯ�����������ξ��ˤϡ���˸����ä��������֤�õ������
	 *  ���Ǥʤ����ˤϡ����˸����ä�õ����
	 */
	if (index > 1 && EVTTIM_LT(p_tevtcb, event_time,
								TMEVT_NODE(p_tevtcb, parent = PARENT(index)).time)) {
		/*
		 *  �ƥΡ��ɤ�index�ΰ��֤˰�ư�����롥
		 */
		TMEVT_NODE(p_tevtcb, index) = TMEVT_NODE(p_tevtcb, parent);
		TMEVT_NODE(p_tevtcb, index).p_tmevtb->index = index;

		/*
		 *  ��������Ρ��ɤοƥΡ��ɤ����˸����ä��������֤�õ����
		 */
		index = tmevt_up(p_tevtcb, parent, event_time);
	}
	else {
		/*
		 *  ��������Ρ��ɤ��鲼�˸����ä��������֤�õ����
		 */
		index = tmevt_down(p_tevtcb, index, event_time);
	}

	/*
	 *  �Ǹ�ΥΡ��ɤ�index�ΰ��֤��������롥
	 */ 
	TMEVT_NODE(p_tevtcb, index) = TMEVT_NODE(p_tevtcb, (p_tevtcb->last_index) + 1);
	TMEVT_NODE(p_tevtcb, index).p_tmevtb->index = index;

	return(left_time);
}

#endif /* TOPPERS_tmedel */

/*
 *  �����।�٥�ȥҡ��פ���Ƭ�ΥΡ��ɤκ��
 */
Inline void
tmevtb_delete_top(TEVTCB* p_tevtcb)
{
	uint_t	index;
	EVTTIM	event_time = TMEVT_NODE(p_tevtcb, p_tevtcb->last_index).time;

	/*
	 *  ����ˤ�꥿���।�٥�ȥҡ��פ����ˤʤ���ϲ��⤷�ʤ���
	 */
	if (--(p_tevtcb->last_index) == 0) {
		return;
	}

	/*
	 *  �롼�ȥΡ��ɤ˺Ǹ�ΥΡ��ɡ�last_index + 1 �ΰ��֤ΥΡ��ɡˤ�
	 *  �������������Ŭ�ڤʰ��֤ذ�ư�����롥�ºݤˤϡ��Ǹ�ΥΡ��ɤ�
	 *  �ºݤ���������ΤǤϤʤ����롼�ȥΡ��ɤ����Ρ��ɤˤʤ�Τǡ���
	 *  ��ΥΡ��ɤ��������٤����֤ظ����ƶ��Ρ��ɤ��ư�����롥
	 */
	index = tmevt_down(p_tevtcb, 1, event_time);

	/*
	 *  �Ǹ�ΥΡ��ɤ�index�ΰ��֤��������롥
	 */ 
	TMEVT_NODE(p_tevtcb, index) = TMEVT_NODE(p_tevtcb, p_tevtcb->last_index + 1);
	TMEVT_NODE(p_tevtcb, index).p_tmevtb->index = index;
}

/*
 *  �����।�٥�ȤޤǤλĤ���֤η׻�
 */
#ifdef TOPPERS_tmeltim

RELTIM
tmevt_lefttim(TEVTCB *p_tevtcb, TMEVTB *p_tmevtb)
{
	EVTTIM	time;

	time = TMEVT_NODE(p_tevtcb, p_tmevtb->index).time;
	if (EVTTIM_LE(p_tevtcb, time, p_tevtcb->next_time)) {
		/*
		 *  ���Υ�����ƥ��å��ǽ����������ˤ�0���֤���
		 */
		return(0U);
	}
	else {
		return((RELTIM)(time - base_time(p_tevtcb)));
	}
}

#endif /* TOPPERS_tmeltim */

/*
 *  ������ƥ��å��ζ���
 */
#ifdef TOPPERS_sigtim

void
signal_time(void)
{
	TMEVTB	*p_tmevtb;
	PCB		*my_p_pcb;
	TEVTCB	*my_p_tevtcb;

	assert(sense_context());
	assert(!i_sense_lock());

	i_lock_cpu();
	my_p_pcb = i_acquire_tsk_lock_self();

	my_p_tevtcb = my_p_pcb->p_tevtcb;

	/*
	 *  current_time�򹹿����롥
	 */
	my_p_tevtcb->current_time = my_p_tevtcb->next_time;

	/*
	 *  next_time��next_subtime�򹹿����롥
	 */
#if TIC_DENO == 1U
	my_p_tevtcb->next_time = my_p_tevtcb->current_time + TIC_NUME;
#else /* TIC_DENO == 1U */
	my_p_tevtcb->next_subtime += TIC_NUME % TIC_DENO;
	my_p_tevtcb->next_time = my_p_tevtcb->current_time + TIC_NUME / TIC_DENO;
	if (my_p_tevtcb->next_subtime >= TIC_DENO) {
		my_p_tevtcb->next_subtime -= TIC_DENO;
		my_p_tevtcb->next_time += 1U;
	}
#endif /* TIC_DENO == 1U */

	/*
	 *  curent_time��ꥤ�٥��ȯ��������ᤤ�ʤޤ���Ʊ���˥����।�٥�
	 *  �Ȥ򡤥����।�٥�ȥҡ��פ���������������Хå��ؿ���Ƥӽ�
	 *  ����
	 */
	while ((my_p_tevtcb->last_index) > 0 && EVTTIM_LE(my_p_tevtcb, TMEVT_NODE(my_p_tevtcb, 1).time, my_p_tevtcb->current_time)) {
		p_tmevtb = TMEVT_NODE(my_p_tevtcb, 1).p_tmevtb;
		tmevtb_delete_top(my_p_tevtcb);
		(*(p_tmevtb->callback))(p_tmevtb->arg);
	}

	/*
	 *  min_time�򹹿����롥
	 */
	my_p_tevtcb->min_time = my_p_tevtcb->current_time;

	release_tsk_lock(my_p_pcb);
	i_unlock_cpu();
}

#endif /* TOPPERS_sigtim */


#ifdef TOPPERS_get_my_current_time

/*
 *  syslog�ǻ��Ѥ��뤿������
 */
ulong_t
get_my_current_time(void){
	PCB		*my_p_pcb;

	my_p_pcb = get_my_p_pcb();

	return my_p_pcb->p_tevtcb->current_time;
}

#endif /* TOPPERS_get_my_current_time */
