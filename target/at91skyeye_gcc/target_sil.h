/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_sil.h 881 2011-12-31 14:06:52Z ertl-honda $
 */

/*
 *  sil.h�Υ��åװ�¸����AT91SKYEYE�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�sil.h����Ƭ�ǥ��󥯥롼�ɤ���롥¾�Υե�
 *  ���뤫���ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥󥯥롼
 *  �ɤ������ˡ�t_stddef.h�����󥯥롼�ɤ����Τǡ������˰�¸���Ƥ�
 *  �褤��
 */

#ifndef TOPPERS_TARGET_SIL_H
#define TOPPERS_TARGET_SIL_H

/*
 *  ���åפΥ���ǥ�����
 */
#define SIL_ENDIAN_LITTLE             /* ��ȥ륨��ǥ����� */

/*
 *  ARM�Ƕ��̤����
 */
#include "core_sil.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ץ��å�ID�ϡ��ɥ������Υ��ɥ쥹
 */
#define TOPPERS_PRC_ID_ADDR 0xFFFFFFE0

/*
 *  �ץ��å�ID�μ���
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	/*
	 * ��Ŭ����ͭ���ˤ��뤿�ᡤsil�ǤϸƤӽФ��Ƥ��ʤ�
	 */
	*p_prcid = (*((uint32_t *)TOPPERS_PRC_ID_ADDR) + 1); 
}

/*
 *  �����ƥ।�󥿥ե������쥤�䡼�ǻ��Ѥ��� Mutex �� ID
 */
#define TOPPERS_SIL_LOC_MUTEX_ID  10

/*
 *  Mutex�ѥϡ��ɥ�����
 */
#define TOPPERS_MUTEX_ID_REG      (0xFFFFFF00)
#define TOPPERS_MUTEX_CNT_REG     (0xFFFFFF04)

/*
 *  SIL_LOC_SPN()����������ץ��å��δ�����target_config.c��
 */
extern uint32_t TOPPERS_spn_var;

/*
 *  ���ԥ��å��μ�����sil�����ѤǤ��ʤ��Τ�ľ�ܥ���������
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint32_t irq_fiq_mask;
	ID       prcid;

  retry:
	/* ������ߥ�å����֤�*/
	irq_fiq_mask = TOPPERS_disint();

	/* ���ԥ��å��μ��� */
	*((volatile unsigned int *)TOPPERS_MUTEX_ID_REG) = TOPPERS_SIL_LOC_MUTEX_ID;

	if (*((volatile unsigned int *)TOPPERS_MUTEX_CNT_REG) != 1) {
		/* ���ԥ��å��������Ǥ��ʤ��ä���� */
		/* ����ߥ�å����֤����ξ��֤� */
		TOPPERS_set_fiq_irq(irq_fiq_mask);
		goto retry;
	}

	ARM_MEMORY_CHANGED;

	sil_get_pid(&prcid);
	TOPPERS_spn_var = prcid;

	return irq_fiq_mask;
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
TOPPERS_sil_unl_spn(uint32_t irq_fiq_mask)
{
	TOPPERS_spn_var = 0;

	ARM_MEMORY_CHANGED;

	*((volatile unsigned int *)TOPPERS_MUTEX_ID_REG) = TOPPERS_SIL_LOC_MUTEX_ID;
	*((volatile unsigned int *)TOPPERS_MUTEX_CNT_REG) = 1;

	/* ���ԥ��å��μ������ξ��֤� */
	TOPPERS_set_fiq_irq(irq_fiq_mask);
}

/*
 *  ���ԥ��å��ζ�������
 *  ���ץ��å������ԥ��å���������Ƥ�����˲������롥 
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID       prcid;

	sil_get_pid(&prcid);
	if (TOPPERS_spn_var == prcid) {
		*((volatile unsigned int *)TOPPERS_MUTEX_ID_REG) = TOPPERS_SIL_LOC_MUTEX_ID;
		*((volatile unsigned int *)TOPPERS_MUTEX_CNT_REG) = 1;
	}
}

/*
 *  ���ԥ��å�
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_irq_fiq_mask))

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_TARGET_SIL_H */
