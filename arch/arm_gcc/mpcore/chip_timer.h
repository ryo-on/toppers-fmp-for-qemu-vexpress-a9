/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_timer.h 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�ARM PrimeCell Timer Module�ѡ�
 */

#ifndef TOPPERS_CHIP_TIMER_H
#define TOPPERS_CHIP_TIMER_H

#include <sil.h>
#include "mpcore.h"

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
/*
 *  �����륿���������Ѥ����
 */
#define INHNO_TIMER_PRC1     (0x00010000 | DIC_IRQNO_TM) /* ����ߥϥ�ɥ��ֹ� */
#define INHNO_TIMER_PRC2     (0x00020000 | DIC_IRQNO_TM) /* ����ߥϥ�ɥ��ֹ� */
#define INHNO_TIMER_PRC3     (0x00030000 | DIC_IRQNO_TM) /* ����ߥϥ�ɥ��ֹ� */
#define INHNO_TIMER_PRC4     (0x00040000 | DIC_IRQNO_TM) /* ����ߥϥ�ɥ��ֹ� */

#define INTNO_TIMER_PRC1     (0x00010000 | DIC_IRQNO_TM) /* ������ֹ� */
#define INTNO_TIMER_PRC2     (0x00020000 | DIC_IRQNO_TM) /* ������ֹ� */
#define INTNO_TIMER_PRC3     (0x00030000 | DIC_IRQNO_TM) /* ������ֹ� */
#define INTNO_TIMER_PRC4     (0x00040000 | DIC_IRQNO_TM) /* ������ֹ� */

/*
 *  �����Х륿���������Ѥ����
 */
#if TOPPERS_SYSTIM_PRCID == 1
#define INHNO_TIMER_SYSTIM    (0x00010000 | DIC_IRQNO_TM)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x00010000 | DIC_IRQNO_TM)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 2
#define INHNO_TIMER_SYSTIM    (0x00020000 | DIC_IRQNO_TM)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x00020000 | DIC_IRQNO_TM)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 3
#define INHNO_TIMER_SYSTIM    (0x00030000 | DIC_IRQNO_TM)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x00030000 | DIC_IRQNO_TM)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 4
#define INHNO_TIMER_SYSTIM    (0x00040000 | DIC_IRQNO_TM)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x00040000 | DIC_IRQNO_TM)  /* ������ֹ� */
#endif /* TOPPERS_SYSTIM_PRCID == 1 */

#define INTATR_TIMER    0U            /* �����°�� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �������ͤ�����ɽ���η�
 */
typedef uint32_t    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *  1������(1MHz) �˥�����ȥ����󤹤�
 */
#define TIMER_CLOCK          MPCORE_TM_LOAD_1MS // cycles for 1ms
#define TO_CLOCK(nume, deno) (TIMER_CLOCK * (nume) / (deno))
#define TO_USEC(clock)       (((SYSUTM) clock) * 1000U / TIMER_CLOCK)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK        ((CLOCK) 0xffffffffU)

/*
 *  �����ޤθ����ͤ�����ȯ�������ͤȤߤʤ�����Ƚ��
 */
#define GET_TOLERANCE    100U    /* �����٤�θ��Ѥ��͡�ñ�̤�����ɽ����*/
#define BEFORE_IREQ(clock) \
            ((clock) >= TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
extern void    target_timer_initialize(intptr_t exinf);

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
extern void    target_timer_terminate(intptr_t exinf);

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
target_timer_get_current(void)
{
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - sil_rew_mem((void *)MPCORE_TM_COUNT));
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline bool_t
target_timer_probe_int(void)
{
	if((sil_rew_mem((void *)MPCORE_TM_ISR) & MPCORE_TM_ISR_SCBIT)
	   == MPCORE_TM_ISR_SCBIT){
		return true;
	}
	else {
		return false;
	}
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
extern void    target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CHIP_TIMER_H */
