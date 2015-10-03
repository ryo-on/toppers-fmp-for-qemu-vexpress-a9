/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_timer.c 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�ARM PrimeCell Timer Module�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"


/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
target_timer_int_clear()
{
	/* �ڥ�ǥ��󥰥ӥåȤ򥯥ꥢ */
	sil_wrw_mem((void *)MPCORE_TM_ISR, MPCORE_TM_ISR_SCBIT);
}

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);

	/* ��������� */
	sil_wrw_mem((void *)MPCORE_TM_CNT, 0x00);

	/* �ڥ�ǥ��󥰥ӥåȥ��ꥢ */
	target_timer_int_clear();

	/* �����ͤ����� */
	sil_wrw_mem((void *)MPCORE_TM_LR, cyc - 1);

	/*
	 * �����ޡ���������(����ߵ���)
	 * 1MHz�ǥ�����Ȥ���褦�˥ץꥹ�����顼������
	 */
	sil_wrw_mem((void *)MPCORE_TM_CNT,
				(MPCORE_TM_PS_1MS << MPCORE_TM_CNT_PS_OFFSET)
				| MPCORE_TM_CNT_IEN | MPCORE_TM_CNT_AR | MPCORE_TM_CNT_EN);
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	/* ����ߥ��ꥢ */
	target_timer_int_clear();

	/* ��������� */
	sil_wrw_mem((void *)MPCORE_TM_CNT, 0x00);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
	ID prcid;

#ifdef TOPPERS_ENA_PERF
	extern void perf_int_latency();
	if (x_sense_mprc()) {
		perf_int_latency();
	}
#endif /* TOPPERS_ENA_PERF */

	/* ����ߥ��ꥢ */
	target_timer_int_clear();

	iget_pid(&prcid);
	i_begin_int((0x10000 << (prcid - 1))|DIC_IRQNO_TM);
	signal_time();     /* ������ƥ��å��ζ��� */
	i_end_int((0x10000 << (prcid - 1))|DIC_IRQNO_TM);
}
