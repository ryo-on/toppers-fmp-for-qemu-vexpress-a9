/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2008-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: mp.c 905 2012-02-27 09:01:23Z ertl-honda $
 */

/*
 *		�ޥ���ץ��å������⥸�塼��
 */
#include "kernel_impl.h"
#include "mp.h"
#include "target_ipi.h"

#ifdef TOPPERS_mpini

#if TTYPE_KLOCK == G_KLOCK
/*
 *  ���㥤����ȥ�å�
 */
LOCK giant_lock;
#endif /* TTYPE_KLOCK == G_KLOCK */

#ifndef OMIT_KER_REQ_ON_IPI
/*
 *  ��λ�����׵�ե饰
 */
bool_t ext_ker_reqflg;
#endif /* OMIT_KER_REQ_ON_IPI */

/*
 *  �ޥ���ץ��å������⥸�塼��ν����
 */
void
initialize_pcb(void)
{
	uint_t	i;
	PCB *my_p_pcb = get_my_p_pcb();

	/*
	 *  PCB ��prcid ������
	 */
	my_p_pcb->prcid = ID_PRC(x_prc_index());

#if TTYPE_KLOCK == G_KLOCK
	/*
	 *  ���㥤����ȥ�å��ν����(�ޥ����ץ��å��Τ�)
	 */
	if (x_sense_mprc()) {
		x_initialize_giant_lock(&giant_lock);
	}
#else /* TTYPE_KLOCK != G_KLOCK */
	/*
	 *  ��������å��ν����
	 */
	x_initialize_tsk_lock(&(my_p_pcb->tsk_lock));

	/*
	 *  1���ܤμ�����Υ�å��ν����
	 */
	my_p_pcb->p_firstlock = NULL;

	/*
	 *  2���ܤμ�����Υ�å�
	 */
	my_p_pcb->p_secondlock = NULL;
#endif /* TTYPE_KLOCK != G_KLOCK */

#if TTYPE_KLOCK == P_KLOCK
	/*
	 *  ���֥������ȥ�å��ν����
	 */
	x_initialize_obj_lock(&(my_p_pcb->obj_lock));
#endif /* TTYPE_KLOCK == P_KLOCK */

	/*
	 *  �����������ط��ν����
	 */
	my_p_pcb->p_runtsk = my_p_pcb->p_schedtsk = NULL;
	my_p_pcb->reqflg = false;
	my_p_pcb->ipmflg = true;
	my_p_pcb->disdsp = false;
	my_p_pcb->dspflg = true;

	for (i = 0; i < TNUM_TPRI; i++) {
		queue_initialize(&(my_p_pcb->ready_queue[i]));
	}

	my_p_pcb->ready_primap = 0U;

	my_p_pcb->locspnid = 0U;

#ifndef OMIT_KER_REQ_ON_IPI
	if (x_sense_mprc()) {
		ext_ker_reqflg = false;
	}
#endif /*  OMIT_KER_REQ_ON_IPI */
}

#endif /* TOPPERS_mpini */

#ifdef TOPPERS_ipi_handler

/*
 *  �ץ��å��ֳ���ߥϥ�ɥ�
 */
void
ipi_handler(void)
{
	PCB *my_p_pcb = get_my_p_pcb();

	target_ipi_clear();

#ifndef OMIT_KER_REQ_ON_IPI
	/*
	 *  ��λ�����׵������å�
	 */
	if (ext_ker_reqflg) {
		ext_ker();
	}
#endif /* OMIT_KER_REQ_ON_IPI */

	my_p_pcb->reqflg = true;
}

#endif /* TOPPERS_ipi_handler */

#ifdef TOPPERS_disp_req

/*
 *  �ǥ����ѥå��׵�
 *  �оݤ�¾�ץ��å��ξ��ϥץ��å��ֳ����ߤ�ȯ�Ԥ���
 *  ToDo  : ¾�ץ��å��ξ������Ƥ֤褦���ѹ��Ǥ��ʤ���
 */
bool_t
dispatch_request(PCB* p_pcb)
{
	if (p_pcb == get_my_p_pcb()) {
		return(true);
	}
	else {
		target_ipi_raise(p_pcb->prcid);
		return(false);
	}
}

#endif /* TOPPERS_disp_req */

#ifdef TOPPERS_ext_ker_req

#ifndef OMIT_KER_REQ_ON_IPI

/*
 *  ��λ�����׵�
 */
void
ext_ker_request(void)
{
	ID prcid;

	/* ���Ǥ��׵᤬�ФƤ���Х꥿���� */
	if (ext_ker_reqflg) {
		return;
	}

	ext_ker_reqflg = true;

	for(prcid = 1; prcid <= TNUM_PRCID; prcid++){
		if (prcid != ID_PRC(x_prc_index())) {
			target_ipi_raise(prcid);
		}
	}
}

#endif /* OMIT_KER_REQ_ON_IPI */

#endif /* TOPPERS_ext_ker_req */

#ifndef OMIT_BARRIER_SYNC

/*
 *  �ХꥢƱ�����ѿ�
 */
static volatile uint_t prc_init[TNUM_PRCID];
static volatile uint_t sys_start;

/*
 *  �ХꥢƱ��
 */
void
barrier_sync(uint_t phase)
{
	volatile uint_t i, j;
	volatile uint_t flag;

	prc_init[x_prc_index()] = phase;

	if (x_sense_mprc()) {
		do{
			flag = 0;
			for(i = 0; i < TNUM_PRCID; i++){
				if(prc_init[i] == phase){
					flag++;
				}
			}
			for(j = 0; j < 100; j++);
		}while (flag < TNUM_PRCID);
		sys_start = phase;
	}
	else {
		while(sys_start != phase) {
			for(j = 0; j < 100; j++);
		}
	}
}

#endif  /* OMIT_BARRIER_SYNC */

#if TTYPE_KLOCK != G_KLOCK

/*
 *  �ץ��å���å��ʤ�����γ�٥�å��Υ�å������������ؿ�
 */

/*
 *		����������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ����ʥ���������ƥ����ȡ�
 */
PCB*
t_acquire_tsk_lock_prcid(ID prcid)
{
	PCB *p_pcb;

	p_pcb = get_mp_p_pcb(prcid);
 	t_acquire_lock(&(p_pcb->tsk_lock));
	return(p_pcb);
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *
 *  t_acquire_lock()�ǳ���ߤ���Ĥ��뤿�ᡤ�ޥ����졼���������å���ɬ��
 *  �Ȥʤ롥
 * 
 *  TSTAT_RUNNABLE()��false�ξ��˳���ߤ���Ĥ���Τϡ�����ߤ�����դ���
 *  ���Ȥˤ�ꡤ�ǥ����ѥå���ȯ�������뤿��Ǥ��롥����ߤ���Ĥ��ʤ��ȡ�
 *  �Ƥӥ�å���1��Ǽ���������硤TSTAT_RUNNABLE()��false�Ȥʤꡤ̵
 *  �¤˥롼�פ��롥
 */
PCB*
t_acquire_tsk_lock_self(void)
{
	TCB *my_p_tcb;
	PCB *my_p_pcb;

	while(true) {
		my_p_pcb = get_my_p_pcb();
		my_p_tcb = my_p_pcb->p_runtsk;
		TEST_G_LABEL("_test_t_acquire_tsk_lock_self"); 
		t_acquire_lock(&(my_p_pcb->tsk_lock));
		if (!TSTAT_RUNNABLE(my_p_tcb->tstat)) { 
			/* RUNNABLE�Ǥʤ���� */
			x_release_lock(&(my_p_pcb->tsk_lock));
			t_unlock_cpu();
			t_lock_cpu();
		} else if (my_p_pcb != my_p_tcb->p_pcb) {
			/* �����������ޥ����졼�Ȥ������ */
			x_release_lock(&(my_p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(my_p_pcb);
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *  RUNNABLE�����å��ʤ�
 * 
 *  ���پ��֤��б����뤿�ᡤ���������ξ��֤��ѹ����ʤ������ƥॳ�����
 *  �������ƤӽФ���
 *
 *  t_acquire_lock()�ǳ���ߤ���Ĥ��뤿�ᡤ�ޥ����졼���������å���ɬ��
 *  �Ȥʤ롥  
 */
PCB*
t_acquire_tsk_lock_self_without_runnable_check(void)
{
	TCB *my_p_tcb;
	PCB *my_p_pcb;

	while(true) {
		my_p_pcb = get_my_p_pcb();
		my_p_tcb = my_p_pcb->p_runtsk;
		t_acquire_lock(&(my_p_pcb->tsk_lock));
		if (my_p_pcb != my_p_tcb->p_pcb) {
			/* �����������ޥ����졼�Ȥ������ */
			x_release_lock(&(my_p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(my_p_pcb);
}

/*
 *  ���ץ��å��Υ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 *  
 *  TSTAT_RUNNABLE()��false�ξ��˳���ߤ���Ĥ���Τϡ�����ߤ�����դ�
 *  �뤳�Ȥˤ�ꡤ�ǥ����ѥå���ȯ�������뤿��Ǥ��롥����ߤ���Ĥ��ʤ�
 *  �ȡ��Ƥӥ�å���1��Ǽ���������硤TSTAT_RUNNABLE()��false�Ȥʤꡤ̵
 *  �¤˥롼�פ��롥
 * 
 *  t_acquire_nested_lock()��ǳ���ߤ���Ĥ�����̡�����ߤ����ꡤ�ޥ�����
 *  �������ȯ�������ǽ�������뤬�����ξ��ϡ�t_acquire_nested_lock()��
 *  true���֤롥���Τ��ᡤ��å�������Υޥ����졼���������å���ɬ����
 *  �Ϥʤ��ʥޥ����졼����󤷤Ƥ����retry����ˡ�
 *
 *  t_acquire_nested_lock()��false���֤äƤ������ϡ���������Ǽ¹Ԥ����
 *  ���å����Ѥ�뤳�Ȥ��ʤ����ᡤp_pcb�������ͭ���Ǥ��롥
 */
PCB*
t_acquire_nested_tsk_lock_self(LOCK *p_objlock)
{
	PCB *my_p_pcb;

	my_p_pcb = get_my_p_pcb();
	my_p_pcb->p_firstlock = p_objlock;
	TEST_G_LABEL("_test_t_acquire_nested_tsk_lock_self"); 
	if (t_acquire_nested_lock(&(my_p_pcb->tsk_lock))) {
		return(NULL);
	}
	my_p_pcb->p_firstlock = NULL;
	if (!TSTAT_RUNNABLE(my_p_pcb->p_runtsk->tstat)){
		x_release_lock(&(my_p_pcb->tsk_lock));
		x_release_lock(p_objlock);
		t_unlock_cpu();
		t_lock_cpu();
		return(NULL);
	}
	return(my_p_pcb);
}

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 *
 */
PCB*
t_acquire_tsk_lock(TCB *p_tcb)
{
	PCB *p_pcb;

	while(true) {
		p_pcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_tsk_lock"); 
		t_acquire_lock(&(p_pcb->tsk_lock));
		if (p_pcb != p_tcb->p_pcb) {
			/* �оݥ��������ޥ����졼�Ȥ������ */
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  Ǥ�ե������ʼ���������ޤ�ˤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 * 
 *  t_acquire_nested_lock()��ǳ���ߤ���Ĥ�����̡�����ߤ����ꡤ����
 *  �������ޥ����졼����󤬤����ǽ�������뤬�����ξ��ϡ�
 *  t_acquire_nested_lock()��true���֤롥
 *
 *  t_acquire_nested_lock()��false���֤äƤ������ϡ���������Ǽ�������
 *  ��¹Ԥ���ץ��å����Ѥ�뤳�Ȥ��ʤ����ᡤmy_p_pcb�������ͭ���Ǥ��롥
 */
PCB*
t_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock)
{
	PCB *my_p_pcb;
	PCB *p_pcb;
 
	while(true) {
		my_p_pcb = get_my_p_pcb();
		my_p_pcb->p_firstlock = p_objlock;
		p_pcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_nested_tsk_lock"); 
		if (t_acquire_nested_lock(&(p_pcb->tsk_lock))) {
			p_pcb = NULL;
			break;
		}
		my_p_pcb->p_firstlock = NULL;
		if (p_pcb != p_tcb->p_pcb) {
			/* �оݥ��������ޥ����졼�Ȥ������ */
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */
PCB*
t_acquire_tsk_lock_alm(ALMCB *p_almcb)
{
	PCB *p_pcb;

	while(true){
		p_pcb = p_almcb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_tsk_lock_alm"); 
		t_acquire_lock(&(p_pcb->tsk_lock));
		if (p_pcb != p_almcb->p_pcb) {
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  Ǥ�դμ����ϥ�ɥ�Υ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */
PCB*
t_acquire_tsk_lock_cyc(CYCCB *p_cyccb)
{
	PCB *p_pcb;

	while(true){
		p_pcb = p_cyccb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_tsk_lock_cyc");
		t_acquire_lock(&(p_pcb->tsk_lock));
		if (p_pcb != p_cyccb->p_pcb) {
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}


/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 * 
 *  t_acquire_nested_lock()��ǳ���ߤ���Ĥ�����̡�����ߤ����ꡤ�ޥ�����
 *  �������ȯ�������ǽ�������뤬�����ξ��ϡ�t_acquire_nested_lock()��
 *  true���֤롥
 *
 *  t_acquire_nested_lock()��false���֤äƤ������ϡ���������Ǽ¹Ԥ����
 *  ���å����Ѥ�뤳�Ȥ��ʤ����ᡤmy_p_pcb�������ͭ���Ǥ��롥
 */
void 
t_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
						PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_dual_tsk_lock");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_dstpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_dstpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				/* 2���ܤΥ�å��������Ǥ������ */
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_tcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
				} else {
					break;
				}
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_srcpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_tcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
				} else {
					break;
				}
			}
		}
		else {
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			if (*pp_srcpcb != p_tcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				break;
			}
		}
	}
}

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */
void
t_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_almcb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_dual_tsk_lock_alm");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_dstpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_dstpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				/* 2���ܤΥ�å��������Ǥ������ */
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_almcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
				} else {
					break;
				}
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_srcpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_almcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
				} else {
					break;
				}
			}
		}
		else {
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			if (*pp_srcpcb != p_almcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				break;
			}
		}
	}
}

/*
 *  �����ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */
void
t_acquire_dual_tsk_lock_cyc(CYCCB *p_cyccb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_cyccb->p_pcb;
		TEST_G_LABEL("_test_t_acquire_dual_tsk_lock_cyc");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_dstpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_dstpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				/* 2���ܤΥ�å��������Ǥ������ */
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_cyccb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
				} else {
					break;
				}
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 1���ܤΥ�å������ */
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_srcpcb)->tsk_lock);
			if (!t_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_cyccb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
				} else {
					break;
				}
			}
		}
		else {
			t_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			if (*pp_srcpcb != p_cyccb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				break;
			}
		}
	}
}

/*
 *  ��������2�ĤΥ�������å��μ����ʥ���������ƥ�����/2���ܡ�
 *
 *  t_acquire_nested_lock()��ǳ���ߤ���Ĥ�����̡�����ߤ����ꡤ�ޥ�����
 *  �������ȯ�������ǽ�������뤬�����ξ��ϡ�t_acquire_nested_lock()��
 *  true���֤롥
 *
 *  t_acquire_nested_lock()��false���֤äƤ������ϡ���������Ǽ¹Ԥ����
 *  ���å����Ѥ�뤳�Ȥ��ʤ����ᡤmy_p_pcb�������ͭ���Ǥ��롥
 *
 *  �ܴؿ��ϸ�����ter_tsk()����Τ߸ƤӽФ���롥ter_tsk()��ȯ���оݤ�����
 *  ������Ʊ���ץ��å��˽�°���Ƥ��륿�����˸¤��롥���Τ��ᡤ2���ܤ�
 *  ��å��������˳���ߤ������оݤΥ��������ޥ����졼�����ȯ��������硤
 *  �оݥ��������ޥ����졼����󤷤����Υ����å��롼�����ã�������ˡ�
 *  t_acquire_nested_lock()���p_firstlock == NULL �˳�������false�ǥ꥿��
 *  �󤷤Ƥ��롥���ʤ���������Ǥ��оݥ��������ޥ����졼����󤷤����Υ�
 *  ���å��롼�����ɬ�פʤ������ʤ��ʤ��顤���塤�����ѹ�����¾��API����
 *  �ؿ���Ȥ���ǽ�������뤿�ᡤ �����å��롼�����Ĥ��Ƥ�����
 */
bool_t 
t_acquire_nested_dual_tsk_lock(TCB *p_tcb, ID dstprcid, LOCK *p_objlock,
							   PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;
	bool_t result = true;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_tcb->p_pcb;
		my_p_pcb = get_my_p_pcb();
		my_p_pcb->p_firstlock = p_objlock;
		TEST_G_LABEL("_test_t_acquire_nested_dual_tsk_lock");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 2���ܤΥ�å������ */
			if (t_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				break;
			}
			my_p_pcb->p_secondlock = &((*pp_dstpcb)->tsk_lock);
			/* 3���ܤΥ�å������ */
			if (t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				break;
			}
			my_p_pcb->p_secondlock = NULL;
			my_p_pcb->p_firstlock = NULL;
			if (*pp_srcpcb != p_tcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
				x_release_lock(&((*pp_dstpcb)->tsk_lock));
			} else {
				result = false;
				break;
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 2���ܤΥ�å������ */
			if (t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				break;
			}
			my_p_pcb->p_secondlock = &((*pp_srcpcb)->tsk_lock);
			/* 3���ܤΥ�å������ */
			if (t_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				break;
			}
			my_p_pcb->p_secondlock = NULL;
			my_p_pcb->p_firstlock = NULL;
			if (*pp_srcpcb != p_tcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_dstpcb)->tsk_lock));
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			}else {
				result = false;
				break;
			}
		} else {
			/* 2���ܤΥ�å������ */
			if (t_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				break;
			}
			my_p_pcb->p_firstlock = NULL;
			if (*pp_srcpcb != p_tcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				result = false;
				break;
			}
		}
	}
	return result;
}

/*
 *		�󥿥�������ƥ������ѤΥ�������å������ؿ�
 */

/*
 *  Ǥ�եץ��å��Υ�������å��μ������󥿥�������ƥ����ȡ�
 */
PCB*
i_acquire_tsk_lock_prcid(ID prcid)
{
	PCB *p_pcb;

	p_pcb = get_mp_p_pcb(prcid);
	i_acquire_lock(&(p_pcb->tsk_lock));
	return(get_mp_p_pcb(prcid));
}

/*
 *  ���ץ��å��Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 *
 *  �ޥ����졼����󤹤뤳�ȤϤʤ����ᡤ����������ƥ����ȤǼ»ܤ��Ƥ���
 *  �ޥ����졼���������å���ɬ�פʤ���  
 */ 
PCB*
i_acquire_tsk_lock_self(void)
{
	PCB *my_p_pcb;

	my_p_pcb = get_my_p_pcb();
	i_acquire_lock(&(my_p_pcb->tsk_lock));
	return(get_my_p_pcb());
}


/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 *
 */
PCB*
i_acquire_tsk_lock(TCB *p_tcb) 
{
	PCB *p_pcb;

	while(true) {
		p_pcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_i_acquire_tsk_lock");
		i_acquire_lock(&(p_pcb->tsk_lock));
		if (p_pcb != p_tcb->p_pcb) {
			/* �оݥ��������ޥ����졼�Ȥ������ */
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  Ǥ�ե������Υ�������å��μ������󥿥�������ƥ�����/2���ܡ�
 */
PCB*
i_acquire_nested_tsk_lock(TCB *p_tcb, LOCK *p_objlock)
{
	PCB* my_p_pcb;
	PCB* p_pcb;

	while(true) {
		my_p_pcb = get_my_p_pcb();
		my_p_pcb->p_firstlock = p_objlock;
		p_pcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_i_acquire_nested_tsk_lock");
		if (i_acquire_nested_lock(&(p_pcb->tsk_lock))) {
			p_pcb = NULL;
			break;
		}
		my_p_pcb->p_firstlock = NULL;
		if (p_pcb != p_tcb->p_pcb) {
			/* �оݥ��������ޥ����졼�Ȥ������ */
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  Ǥ�դΥ��顼��ϥ�ɥ�Υ�������å��μ������󥿥�������ƥ����ȡ�
 */
PCB*
i_acquire_tsk_lock_alm(ALMCB *p_almcb)
{
	PCB *p_pcb;

	while(true){
		p_pcb = p_almcb->p_pcb;
		TEST_G_LABEL("_test_i_acquire_tsk_lock_alm");
		i_acquire_lock(&(p_pcb->tsk_lock));
		if (p_pcb != p_almcb->p_pcb) {
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  2�ĤΥ�������å��μ������󥿥�������ƥ�����/1���ܡ�
 */
void 
i_acquire_dual_tsk_lock(TCB *p_tcb, ID dstprcid, 
                                    PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_i_acquire_dual_tsk_lock");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 1���ܤΥ�å������ */
			i_acquire_lock(&((*pp_dstpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_dstpcb)->tsk_lock);
			if (!i_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				/* 2���ܤΥ�å��������Ǥ������ */
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_tcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
				} else {
					break;
				}
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 1���ܤΥ�å������ */
			i_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_srcpcb)->tsk_lock);
			if (!i_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_tcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
				} else {
					break;
				}
			}
		}
		else {
			i_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			if (*pp_srcpcb != p_tcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				break;
			}
		}
	}
}

/*
 *  ���顼��ϥ�ɥ��2�ĤΥ�������å��μ����ʥ���������ƥ�����/1���ܡ�
 */
void
i_acquire_dual_tsk_lock_alm(ALMCB *p_almcb, ID dstprcid, 
							PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	PCB* my_p_pcb;

	*pp_dstpcb = get_mp_p_pcb(dstprcid);

	while(true) {
		*pp_srcpcb = p_almcb->p_pcb;
		TEST_G_LABEL("_test_i_acquire_dual_tsk_lock_alm");
		if ((*pp_srcpcb)->prcid > dstprcid) {
			/* 1���ܤΥ�å������ */
			i_acquire_lock(&((*pp_dstpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_dstpcb)->tsk_lock);
			if (!i_acquire_nested_lock(&((*pp_srcpcb)->tsk_lock))) {
				/* 2���ܤΥ�å��������Ǥ������ */
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_almcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
				} else {
					break;
				}
			}
		} else if ((*pp_srcpcb)->prcid < dstprcid) {
			/* 1���ܤΥ�å������ */
			i_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			my_p_pcb = get_my_p_pcb();
			my_p_pcb->p_firstlock = &((*pp_srcpcb)->tsk_lock);
			if (!i_acquire_nested_lock(&((*pp_dstpcb)->tsk_lock))) {
				my_p_pcb->p_firstlock = NULL;
				if (*pp_srcpcb != p_almcb->p_pcb) {
					/* �оݥ��������ޥ����졼�Ȥ������ */
					x_release_lock(&((*pp_dstpcb)->tsk_lock));
					x_release_lock(&((*pp_srcpcb)->tsk_lock));
				} else {
					break;
				}
			}
		}
		else {
			i_acquire_lock(&((*pp_srcpcb)->tsk_lock));
			if (*pp_srcpcb != p_almcb->p_pcb) {
				/* �оݥ��������ޥ����졼�Ȥ������ */
				x_release_lock(&((*pp_srcpcb)->tsk_lock));
			} else {
				return;
			}
		}
	}
}

/*
 *		����������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 *  ���֥������ȥ�å��μ����ʥ���������ƥ����ȡ�
 */
void
t_acquire_obj_lock(LOCK *p_objlock) 
{ 
	t_acquire_lock(p_objlock);
}

/*
 *		�󥿥�������ƥ������ѤΥ��֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��μ������󥿥�������ƥ����ȡ�
 */
void 
i_acquire_obj_lock(LOCK *p_objlock) 
{ 
	i_acquire_lock(p_objlock);
}

/*
 *		��������å������ؿ�
 */

/*
 *  ��������å��β����ʥ���������ƥ����ȡ�
 */ 
void
release_tsk_lock(PCB *p_pcb)
{
	x_release_lock(&(p_pcb->tsk_lock));
}

/*
 *  ��������å��β�����2���ܡ�
 */ 
void
release_nested_tsk_lock(PCB *p_pcb)
{
	x_release_lock(&(p_pcb->tsk_lock));
}

/*
 *  2�ĤΥ�������å��β���
 */ 
void
release_dual_tsk_lock(PCB *p_srcpcb,  PCB *p_dstpcb)
{
	x_release_lock(&(p_srcpcb->tsk_lock));
	x_release_lock(&(p_dstpcb->tsk_lock));
}

/*
 *		���֥������ȥ�å������ؿ�
 */

/*
 * ���֥������ȥ�å��β������󥿥�������ƥ����ȡ�
 */ 
void
release_obj_lock(LOCK *p_objlock)
{
	x_release_lock(p_objlock);
}

/*
 *		����¾�Υ�å��ؿ�
 */

/*
 *  �ץꥨ��ץ���󤷤ʤ����������Υ�������å��μ���
 */
PCB* 
acquire_tsk_lock_without_preemption_self(void)
{
	PCB *my_p_pcb;

	my_p_pcb = get_my_p_pcb();
	x_acquire_lock_without_preemption(&(my_p_pcb->tsk_lock));

	return(my_p_pcb);
}

/*
 *  �ץꥨ��ץ���󤷤ʤ���������å��μ�����2���ܡ�
 */
PCB*
acquire_nested_tsk_lock_without_preemption(TCB *p_tcb)
{
	PCB *p_pcb;

	while(true) {
		p_pcb = p_tcb->p_pcb;
		TEST_G_LABEL("_test_acquire_nested_tsk_lock_without_preemption");
		x_acquire_lock_without_preemption(&(p_pcb->tsk_lock));
		if (p_pcb != p_tcb->p_pcb) {
			/* �оݥ��������ޥ����졼�Ȥ������ */
			x_release_lock(&(p_pcb->tsk_lock));
		} else {
			break;
		}
	}
	return(p_pcb);
}

/*
 *  �ץꥨ��ץ���󤷤ʤ���������2�ĤΥ�������å��μ����ʥ���������ƥ����ȡ�
 */
void 
acquire_dual_tsk_lock_without_preemption(TCB *p_tcb, ID dstprcid, 
										 PCB **pp_srcpcb, PCB **pp_dstpcb)
{
	*pp_dstpcb = get_mp_p_pcb(dstprcid);
	*pp_srcpcb = p_tcb->p_pcb;

	if ((*pp_srcpcb)->prcid > dstprcid) {
		/* 1���ܤΥ�å������ */
		x_acquire_lock_without_preemption(&((*pp_dstpcb)->tsk_lock));
		/* 2���ܤΥ�å������ */
		x_acquire_lock_without_preemption(&((*pp_srcpcb)->tsk_lock));
	} else if ((*pp_srcpcb)->prcid < dstprcid) {
		/* 1���ܤΥ�å������ */
		x_acquire_lock_without_preemption(&((*pp_srcpcb)->tsk_lock));
		/* 2���ܤΥ�å������ */
		x_acquire_lock_without_preemption(&((*pp_dstpcb)->tsk_lock));
	}
	else {
		x_acquire_lock_without_preemption(&((*pp_srcpcb)->tsk_lock));
	}
}

#endif /* TTYPE_KLOCK != G_KLOCK */
