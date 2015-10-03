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
 *  @(#) $Id: interrupt.c 799 2011-04-08 08:47:37Z ertl-honda $
 */

/*
 *		����ߴ�����ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "interrupt.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_DIS_INT_ENTER
#define LOG_DIS_INT_ENTER(intno)
#endif /* LOG_DIS_INT_ENTER */

#ifndef LOG_DIS_INT_LEAVE
#define LOG_DIS_INT_LEAVE(ercd)
#endif /* LOG_DIS_INT_LEAVE */

#ifndef LOG_ENA_INT_ENTER
#define LOG_ENA_INT_ENTER(intno)
#endif /* LOG_ENA_INT_ENTER */

#ifndef LOG_ENA_INT_LEAVE
#define LOG_ENA_INT_LEAVE(ercd)
#endif /* LOG_ENA_INT_LEAVE */

#ifndef LOG_CHG_IPM_ENTER
#define LOG_CHG_IPM_ENTER(intpri)
#endif /* LOG_CHG_IPM_ENTER */

#ifndef LOG_CHG_IPM_LEAVE
#define LOG_CHG_IPM_LEAVE(ercd)
#endif /* LOG_CHG_IPM_LEAVE */

#ifndef LOG_GET_IPM_ENTER
#define LOG_GET_IPM_ENTER(p_intpri)
#endif /* LOG_GET_IPM_ENTER */

#ifndef LOG_GET_IPM_LEAVE
#define LOG_GET_IPM_LEAVE(ercd, intpri)
#endif /* LOG_GET_IPM_LEAVE */

/* 
 *  ����ߴ�����ǽ�ν����
 */
#ifdef TOPPERS_intini
#ifndef OMIT_INITIALIZE_INTERRUPT

void
initialize_interrupt(void)
{
	uint_t			i;
	const INHINIB	*p_inhinib;
	const INTINIB	*p_intinib;
    
	for (p_inhinib = inhinib_table, i = 0; i < tnum_inhno; p_inhinib++, i++) {
		if (p_inhinib->iaffinity == ID_PRC(x_prc_index())) {
			x_define_inh(p_inhinib->inhno, p_inhinib->int_entry, p_inhinib->affinity_mask);
		}
	}
    
	for (p_intinib = intinib_table, i = 0; i < tnum_intno; p_intinib++, i++) {
		if (p_intinib->iaffinity == ID_PRC(x_prc_index())) {
			x_config_int(p_intinib->intno, p_intinib->intatr, p_intinib->intpri, p_intinib->affinity_mask);
		}
	}
}

#endif /* OMIT_INITIALIZE_INTERRUPT */
#endif /* TOPPERS_intini */

/*
 *  ����ߤζػ�
 */
#ifdef TOPPERS_dis_int
#ifdef TOPPERS_SUPPORT_DIS_INT

ER
dis_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_DIS_INT_ENTER(intno);
	CHECK_TSKCTX();

	locked = t_sense_lock();
	if (!locked) {
		t_lock_cpu();
	}
	if (!VALID_INTNO_DISINT(ID_PRC(x_prc_index()), intno)) {
		ercd = E_PAR;
	}
	else if (t_disable_int(intno)) {
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}
	if (!locked) {
		t_unlock_cpu();
	}

  error_exit:
	LOG_DIS_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_DIS_INT */
#endif /* TOPPERS_dis_int */

/*
 *  ����ߤε���
 */
#ifdef TOPPERS_ena_int
#ifdef TOPPERS_SUPPORT_ENA_INT

ER
ena_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_ENA_INT_ENTER(intno);
	CHECK_TSKCTX();

	locked = t_sense_lock();
	if (!locked) {
		t_lock_cpu();
	}
	if (!VALID_INTNO_DISINT(ID_PRC(x_prc_index()), intno)) {
		ercd = E_PAR;
	}
	else if (t_enable_int(intno)) {
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}
	if (!locked) {
		t_unlock_cpu();
	}

  error_exit:
	LOG_ENA_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_ENA_INT */
#endif /* TOPPERS_ena_int */

/*
 *  �����ͥ���٥ޥ������ѹ�
 */
#ifdef TOPPERS_chg_ipm

ER
chg_ipm(PRI intpri)
{
	ER		ercd;
	PCB		*my_p_pcb;
	bool_t	dspreq = false;

	LOG_CHG_IPM_ENTER(intpri);
	CHECK_TSKCTX_UNL();
	CHECK_INTPRI_CHGIPM(intpri);

	t_lock_cpu();
	my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
	t_set_ipm(intpri);
	if (intpri == TIPM_ENAALL) {
		my_p_pcb->ipmflg = true;
		if (!(my_p_pcb->disdsp)) {
			my_p_pcb->dspflg = true;
			if (my_p_pcb->p_runtsk != my_p_pcb->p_schedtsk) {
				dspreq = true;
			}
		}
		/*
		 * �������㳰�����롼����ε�ư��郎����äƤ�����Ǥ⡤dspreq ��
		 * true�ξ��ϥǥ����ѥå���ͥ�褷�Ƽ¹Ԥ��뤿��ƤӽФ��ʤ���
		 * ���ξ�����IPM��-1�ʲ������ꤵ�줿���֤�sus_tsk()��ȯ�Ԥ�����Ͼ���
		 * �Ȥʤä�����������chg_ipm(TIPM_ENAALL) ��ƤӽФ�������ȯ�����롥
		 * dspreq �Υ����å��򤷤ʤ��ȡ����ꤵ�줿IPM���ץ��å��ֳ���ߤ�
		 * ͥ���٤��㤤���ϳ���ߤ���α����Ƥ��ꡤcall_texrtn()�����CPU��
		 * �å����������Ȥ��˳���ߤ�����ǥ����ѥå����뤬���ץ��å��ֳ�
		 * ���ߤ�ͥ���٤��⤤���ϡ�����ߤ�����դ��뤬����ߤνи��ǥǥ���
		 * �ѥå����ʤ������Τ��ᡤcall_texrtn()����ǳ���ߤ�����դ���������
		 * ���㳰�����롼�����¹Ԥ��Ƥ��ޤ��������񤤤��ץ��å��ֳ���ߤ�
		 * ͥ���٤ˤ��ۤʤäƤ��ޤ���
		 */
		if (my_p_pcb->p_runtsk->enatex && my_p_pcb->p_runtsk->texptn != 0U
			&& dspreq != true) {
			call_texrtn(my_p_pcb);
			/* �ޥ����졼����󤷤Ƥ����ǽ�������뤿��Ƽ��� */
			my_p_pcb = get_my_p_pcb();
		}
	}
	else {
		my_p_pcb->ipmflg = false;
		my_p_pcb->dspflg = false;
	}
	ercd = E_OK;
	release_tsk_lock(my_p_pcb);
	if (dspreq) {
		dispatch();
	}
	t_unlock_cpu();

  error_exit:
	LOG_CHG_IPM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_chg_ipm */

/*
 *  �����ͥ���٥ޥ����λ���
 */
#ifdef TOPPERS_get_ipm

ER
get_ipm(PRI *p_intpri)
{
	ER		ercd;

	LOG_GET_IPM_ENTER(p_intpri);
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*p_intpri = t_get_ipm();
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_GET_IPM_LEAVE(ercd, *p_intpri);
	return(ercd);
}

#endif /* TOPPERS_get_ipm */
