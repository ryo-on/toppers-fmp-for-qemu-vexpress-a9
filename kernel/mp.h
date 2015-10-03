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
 *  @(#) $Id: mp.h 905 2012-02-27 09:01:23Z ertl-honda $
 */

/*
 *		�ޥ���ץ��å������⥸�塼��
 *		���깽¤�����Ѥ��ޥ����������
 */

#ifndef TOPPERS_MP_H
#define TOPPERS_MP_H

#include <queue.h>
#include "task.h"
#include "alarm.h"
#include "cyclic.h"

/*
 *  �ץ��å�ID����ץ��å�INDEX�ؤ��Ѵ�
 */
#define INDEX_PRC(prcid)	((uint_t)((prcid) - TMIN_PRCID))

/*
 *  �ץ��å�INDEX����ץ��å�ID�ؤ��Ѵ�
 */
#define ID_PRC(prcindex)	((uint_t)((prcindex) + TMIN_PRCID))

/*
 *  ��ư���ν����
 */
extern void initialize_pcb(void);

/*
 *  �ץ��å��ֳ���ߥϥ�ɥ�
 */
extern void ipi_handler(void);

#ifndef OMIT_KER_REQ_ON_IPI
/*
 *  ��λ�����׵�ե饰
 */
extern bool_t ext_ker_reqflg;

/*
 *  ��λ�����׵�
 */
extern void ext_ker_request(void);
#endif /* OMIT_KER_REQ_ON_IPI */

#ifndef OMIT_BARRIER_SYNC
/*
 *  �ХꥢƱ��
 */
extern void barrier_sync(uint_t phase);
#endif  /* OMIT_BARRIER_SYNC */

/*
 *		�����������⥸�塼���Ϣ
 */

/*
 *  �ǥ����ѥå��׵�
 */
extern bool_t dispatch_request(PCB* p_pcb);

/*
 *  �󥿥�������ƥ������ѤΥ����å���Ϣ�Υǡ�����kernel_cfg.c��
 */
extern const SIZE _kernel_istksz_table[];

extern STK_T *const _kernel_istk_table[];

#ifdef TOPPERS_ISTKPT
extern STK_T *const _kernel_istkpt_table[];
#endif /* TOPPERS_ISTKPT */

/*
 *		��å��ط���ǽ
 */

#if TTYPE_KLOCK == G_KLOCK

/*
 *  ���㥤����ȥ�å�
 */

/*
 *  ���㥤����ȥ�å��ѤΥ�å��ѿ�
 */
extern LOCK giant_lock;

/*
 *  ���֥������ȥ���ȥ���֥�å������å��ѿ��μ��Ф�
 */
#define GET_OBJLOCK(p_wobjcb)   (giant_lock)

/*
 *		����������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ����ʥ���������ƥ����ȡ�
 */
Inline PCB*
t_acquire_tsk_lock_prcid(ID prcid)
{
	t_acquire_lock(&giant_lock);
	return(get_mp_p_pcb(prcid));
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *
 *  ��å������塤���������Υޥ����졼����������å�������ˡ�⤢�뤬��
 *  �����å��Υ����Ȥ�ͤ���ȡ������å������˰�Χ p_pcb ���������������
 *  Ψ���褤��Ƚ�Ǥ����� 
 */
Inline PCB*
t_acquire_tsk_lock_self(void)
{
	PCB *p_pcb;

	while(true) {
		t_acquire_lock(&giant_lock);
		/* �����������ޥ����졼�Ȥ��������θ����p_pcb���å�������˼��� */
		p_pcb = get_my_p_pcb();
		if (!TSTAT_RUNNABLE(p_pcb->p_runtsk->tstat)) { 
			/* RUNNABLE�Ǥʤ���� */
			x_release_lock(&giant_lock);
			t_unlock_cpu();
			t_lock_cpu();
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *  RUNNABLE�����å��ʤ�
 * 
 *  ���پ��֤��б����뤿�ᡤ���������ξ��֤��ѹ����ʤ������ƥॳ�����
 *  �������ƤӽФ��� 
 */
Inline PCB*
t_acquire_tsk_lock_self_without_runnable_check(void)
{
	PCB *p_pcb;

	t_acquire_lock(&giant_lock);
	/* �����������ޥ����졼�Ȥ��������θ����p_pcb���å�������˼��� */
	p_pcb = get_my_p_pcb();
	return(p_pcb);
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */ 
Inline PCB*
t_acquire_nested_tsk_lock_self(LOCK *p_objlock)
{
	return(get_my_p_pcb());
}

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 * 
 *  �оݥ��������ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�p_pcb��������롥  
 */ 
Inline  PCB*
t_acquire_tsk_lock(TCB *p_tcb)
{
	t_acquire_lock(&giant_lock);
	return(p_tcb->p_pcb);
}

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */
Inline PCB*
t_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock)
{
	return(p_tcb->p_pcb);
}

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 * 
 *  �оݥ��顼��ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  p_pcb��������롥
 */
Inline PCB*
t_acquire_tsk_lock_alm(ALMCB *p_almcb)
{
	t_acquire_lock(&giant_lock);
	return(p_almcb->p_pcb);
}

/*
 *  Ǥ�դμ����ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *  
 *  �оݼ����ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  p_pcb��������롥  
 */
Inline PCB*
t_acquire_tsk_lock_cyc(CYCCB *p_cyccb)
{
	t_acquire_lock(&giant_lock);
	return(p_cyccb->p_pcb);
}

/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 * 
 *  �оݥ��������ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�p_pcb��������롥    
 */  
Inline void
t_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
						PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	t_acquire_lock(&giant_lock);
	*pp_srcpcb = p_tcb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
}

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 * 
 *  �оݥ��顼��ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  p_pcb��������롥  
 */  
Inline void
t_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	t_acquire_lock(&giant_lock);
	*pp_srcpcb = p_almcb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
}

/*
 *  �����ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *  
 *  �оݼ����ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  p_pcb��������롥    
 */  
Inline void
t_acquire_dual_tsk_lock_cyc(CYCCB *p_cyccb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	t_acquire_lock(&giant_lock);
	*pp_srcpcb = p_cyccb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
}

/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */
Inline bool_t
t_acquire_nested_dual_tsk_lock(TCB *p_tcb, ID dstprcid, LOCK *p_objlock,
							   PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	*pp_srcpcb = p_tcb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
	return(false);
}

/*
 *		�󥿥�������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ������󥿥�������ƥ����ȡ�
 */
Inline PCB*
i_acquire_tsk_lock_prcid(ID prcid)
{
	i_acquire_lock(&giant_lock);
	return(get_mp_p_pcb(prcid));
}

/*
 *  ���ץ��å��Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 */ 
Inline PCB*
i_acquire_tsk_lock_self(void)
{
	i_acquire_lock(&giant_lock);
	return(get_my_p_pcb());
}

/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 *
 *  �оݥ��������ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  pp_pcb��������롥
 */
Inline PCB*
i_acquire_tsk_lock(TCB *p_tcb)
{
	i_acquire_lock(&giant_lock);
	return(p_tcb->p_pcb);
}

/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/2���ܡ�
 */
Inline PCB*
i_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock)
{
	return(p_tcb->p_pcb);
}

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ������󥿥�������ƥ����ȡ�
 *
 *  �оݥ��顼��ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  pp_pcb��������롥
 */
Inline PCB*
i_acquire_tsk_lock_alm(ALMCB *p_almcb)
{
	i_acquire_lock(&giant_lock);
	return(p_almcb->p_pcb);
}

/*
 *  2�ĤΥ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 *
 *  �оݥ��������ޥ����졼����󤹤��ǽ��������Τǡ���å�������ˡ�
 *  pp_srcpcb��������롥  
 */  
Inline void
i_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
						PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	i_acquire_lock(&giant_lock);
	*pp_srcpcb = p_tcb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
}

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *
 *  �оݥ��顼��ϥ�ɥ餬�ޥ����졼����󤹤��ǽ��������Τǡ���å���
 *  ����ˡ�pp_srcpcb��������롥  
 */  
Inline void
i_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	i_acquire_lock(&giant_lock);
	*pp_srcpcb = p_almcb->p_pcb;
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
}

/*
 *		����������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 *  ���֥������ȥ�å��μ����ʥ���������ƥ����ȡ�
 */
Inline void
t_acquire_obj_lock(LOCK *p_objlock)
{
	t_acquire_lock(&giant_lock);
}

/*
 *		�󥿥�������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��μ������󥿥�������ƥ����ȡ�
 */ 
Inline void
i_acquire_obj_lock(LOCK *p_objlock)
{
	t_acquire_lock(&giant_lock);
}

/*
 *		��������å������ؿ�
 */

/*
 *  ��������å��β����ʥ���������ƥ����ȡ�
 */ 
Inline void
release_tsk_lock(PCB *p_pcb)
{
	x_release_lock(&giant_lock);
}

/*
 *  ��������å��β�����2���ܡ�
 */ 
Inline void
release_nested_tsk_lock(PCB *p_pcb)
{
	
}

/*
 *  2�ĤΥ�������å��β���
 */ 
Inline void
release_dual_tsk_lock(PCB *p_srcpcb,  PCB *p_dstpcb)
{
	x_release_lock(&giant_lock);
}

/*
 *		���֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��β������󥿥�������ƥ����ȡ�
 */ 
Inline void
release_obj_lock(LOCK *p_objlock)
{
	x_release_lock(&giant_lock);
}

/*
 *		����¾�Υ�å��ؿ�
 */

/*
 *  �ץꥨ��ץ���󤷤ʤ����������Υ�������å��μ���
 */
Inline PCB*
acquire_tsk_lock_without_preemption_self(void)
{
	x_acquire_lock_without_preemption(&giant_lock);
	return(get_my_p_pcb());
} 
  
/*
 *  �ץꥨ��ץ���󤷤ʤ���������å��μ�����2���ܡ�
 */
Inline PCB*
acquire_nested_tsk_lock_without_preemption(TCB *p_tcb)
{
	return(p_tcb->p_pcb);
}

#else /* TTYPE_KLOCK != G_KLOCK */

#if TTYPE_KLOCK == P_KLOCK
#define GET_OBJLOCK(p_wobjcb)   (*((WOBJCB*)p_wobjcb)->p_wobjinib->p_obj_lock)
#else /* TTYPE_KLOCK == F_KLOCK */
#define GET_OBJLOCK(p_wobjcb)   (p_wobjcb->obj_lock)
#endif /* TTYPE_KLOCK == F_KLOCK */

/*
 *  �ץ��å���å��ʤ�����γ�٥�å�
 */

/*
 *		����������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ����ʥ���������ƥ����ȡ�
 */
extern PCB* t_acquire_tsk_lock_prcid(ID prcid);

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */ 
extern PCB* t_acquire_tsk_lock_self(void);

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *  RUNNABLE�����å��ʤ��� 
 */ 
extern PCB* t_acquire_tsk_lock_self_without_runnable_check(void);

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */ 
extern PCB* t_acquire_nested_tsk_lock_self(LOCK *p_objlock);

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */ 
extern PCB* t_acquire_tsk_lock(TCB *p_tcb);

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */ 
extern PCB* t_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock);

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ� 
 */
extern PCB* t_acquire_tsk_lock_alm(ALMCB *p_almcb);

/*
 *  Ǥ�դμ����ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ� 
 */
extern PCB* t_acquire_tsk_lock_cyc(CYCCB *p_cyccb);

/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */  
extern void t_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
									PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 */
extern bool_t t_acquire_nested_dual_tsk_lock(TCB *p_tcb, ID dstprcid, LOCK *p_objlock,
										 PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */  
extern void t_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
										PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *  �����ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */  
extern void t_acquire_dual_tsk_lock_cyc(CYCCB *p_cyccb, ID dstprcid, 
										PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *		�󥿥�������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ������󥿥�������ƥ����ȡ�
 */
extern PCB* i_acquire_tsk_lock_prcid(ID prcid);

/*
 *  ���ץ��å��Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 */ 
extern PCB* i_acquire_tsk_lock_self(void);

/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 */
extern PCB* i_acquire_tsk_lock(TCB *p_tcb);

/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/2���ܡ�
 */
extern PCB* i_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock);

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ������󥿥�������ƥ����ȡ� 
 */
extern PCB* i_acquire_tsk_lock_alm(ALMCB *p_almcb);

/*
 *  ��������2�ĤΥ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 */  
extern void i_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
									PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */  
extern void i_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
										PCB **pp_srcpcb, PCB **pp_dstpcb);

/*
 *		����������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 *  ���֥������ȥ�å��μ����ʥ���������ƥ����ȡ�
 */
extern void t_acquire_obj_lock(LOCK *p_objlock);

/*
 *  ���֥������ȥ�å��β����ʥ���������ƥ����ȡ�
 */
extern void t_release_obj_lock(LOCK *p_objlock);

/*
 *		�󥿥�������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��μ������󥿥�������ƥ����ȡ�
 */ 
extern void i_acquire_obj_lock(LOCK *p_objlock);

/*
 *		��������å������ؿ�
 */

/*
 *  ��������å��β���
 */ 
extern void release_tsk_lock(PCB *p_pcb);

/*
 *  ��������å��β�����2���ܡ�
 */ 
extern void release_nested_tsk_lock(PCB *p_pcb);

/*
 *  2�ĤΥ�������å��β����ʥ���������ƥ����ȡ�
 */ 
extern void release_dual_tsk_lock(PCB *p_srcpcb,  PCB *p_dstpcb);

/*
 *		���֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��β���
 */
extern void release_obj_lock(LOCK *p_objlock);

/*
 *		����¾�Υ�å��ؿ�
 */

/*
 *  �ץꥨ��ץ���󤷤ʤ����������Υ�������å��μ���
 */
extern PCB* acquire_tsk_lock_without_preemption_self(void);

/*
 *  �ץꥨ��ץ���󤷤ʤ���������å��μ�����2���ܡ�
 */
extern PCB* acquire_nested_tsk_lock_without_preemption(TCB *p_tcb);

/*
 *  �ץꥨ��ץ���󤷤ʤ���������2�ĤΥ�������å��μ����ʥ���������ƥ����ȡ�
 */
extern void acquire_dual_tsk_lock_without_preemption(TCB *p_tcb, ID dstprcid, 
										 PCB **pp_srcpcb, PCB **pp_dstpcb);
#endif /* TTYPE_KLOCK != G_KLOCK */

#endif /* TOPPERS_MP_H */
