/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_kernel.h 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *  kernel.h�Υ��åװ�¸����MPCORE�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h�ǥ��󥯥롼�ɤ���롥¾�Υե�
 *  ���뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥󥯥롼��
 *  �������ˡ�t_stddef.h�����󥯥롼�ɤ����Τǡ������˰�¸���Ƥ��
 *  ����
 */

#ifndef TOPPERS_CHIP_KERNEL_H
#define TOPPERS_CHIP_KERNEL_H

#include "mpcore.h"

/*
 *  ARM�Ƕ��̤����
 */
#include "arm_gcc/common/core_kernel.h"

/*
 *  ���ݡ��Ȥ��뵡ǽ�����
 */
#define TOPPERS_TARGET_SUPPORT_ENA_INT			/* ena_int�򥵥ݡ��Ȥ��� */
#define TOPPERS_TARGET_SUPPORT_DIS_INT			/* dis_int�򥵥ݡ��Ȥ��� */
#ifdef TOPPERS_SYSTIM_LOCAL
#define TOPPERS_TARGET_SUPPORT_GET_UTM			/* get_utm�򥵥ݡ��Ȥ��� */
#endif /* TOPPERS_SYSTIM_LOCAL */

/*
 *  Custom�Υ����ɥ���������
 */
#define TOPPERS_CUSTOM_IDLE

/*
 *  �����ͥ���٤��ϰ�
 */
#if __TARGET_ARCH_ARM == 6
#define TMIN_INTPRI   (-15)   /* �����ͥ���٤κǾ��͡ʺǹ��͡�*/
#else /* __TARGET_ARCH_ARM == 7 */
#define TMIN_INTPRI   (-31)   /* �����ͥ���٤κǾ��͡ʺǹ��͡�*/
#endif /* __TARGET_ARCH_ARM == 7 */
#define TMAX_INTPRI   (-1)    /* �����ͥ���٤κ����͡ʺ����͡�*/

/*
 *  ������ƥ��å������
 */
#define TIC_NUME  1U   /* ������ƥ��å��μ�����ʬ�� */
#define TIC_DENO  1U   /* ������ƥ��å��μ�����ʬ�� */

#ifndef TOPPERS_MACRO_ONLY
#if __TARGET_ARCH_ARM == 7
/*
 *  ��ǽɾ���Ѥδؿ�
 *  CA9/MPCore �� r1�ʹߤ���ܤ���Ƥ��� Global Timer ����Ѥ��롥
 */

/* ��ǽ��¬�ѤΥ����󥿤Υǡ����� */
typedef uint64_t PERFCNT;

/*
 *  �ѥե����ޥ󥹥����󥿤ν����
 */
Inline void
x_init_pcc(void)
{
	/* ���������� */
	sil_wrw_mem((void *)MPCORE_GTC_CNT, 0);

	/* �����󥿡��쥸�����ν���� */
	sil_wrw_mem((void *)MPCORE_GTC_COUNT_L, 0);
	sil_wrw_mem((void *)MPCORE_GTC_COUNT_U, 0);

	/* ����ڥ��Х�塼�쥸�����ν���� */
	sil_wrw_mem((void *)MPCORE_GTC_COMPV_L, 0xffffffff);
	sil_wrw_mem((void *)MPCORE_GTC_COMPV_U, 0xffffffff);

	/* ������ȳ��� */
	sil_wrw_mem((void *)MPCORE_GTC_CNT, MPCORE_GTC_CNT_TIMENA);
}

/*
 *  �ѥե����ޥ󥹥����󥿤��ɤ߹���
 */
Inline void
x_get_pcc(PERFCNT *p_count)
{
	uint32_t count_l;
	uint32_t count_h_p, count_h;

	/*
	 * 32bit������2�Ĥ�64bit�����󥿤�¸�����Ƥ��뤿�ᡤ
	 * ��夲���θ�����ɤ߹��ߤȤ��롥
	 */
	count_h_p = sil_rew_mem((void *)MPCORE_GTC_COUNT_U);
	count_l = sil_rew_mem((void *)MPCORE_GTC_COUNT_L);
	count_h = sil_rew_mem((void *)MPCORE_GTC_COUNT_U);
	if (count_h_p != count_h) {
		count_l = sil_rew_mem((void *)MPCORE_GTC_COUNT_L);
	}

	*p_count = count_h;
	*p_count = *p_count << 32;
	*p_count += count_l;
}

/*
 *  �ѥե����ޥ󥹥����󥿤Υꥻ�å�
 */
Inline void
x_rst_pcc(void)
{
	uint32_t tmp, tmp1;

	/* ��������� */
	tmp = sil_rew_mem((void *)MPCORE_GTC_CNT);
	tmp1 = tmp & ~MPCORE_GTC_CNT_TIMENA;
	sil_wrw_mem((void *)MPCORE_GTC_CNT, tmp1);

	/* �����󥿡��쥸�����ν���� */
	sil_wrw_mem((void *)MPCORE_GTC_COUNT_L, 0);
	sil_wrw_mem((void *)MPCORE_GTC_COUNT_U, 0);

	/* �����󥿺Ƴ� */
	sil_wrw_mem((void *)MPCORE_GTC_CNT, tmp);
}

/*
 *  �������ͤ�nsec�ؤ��Ѵ�
 */
Inline uint64_t
x_cnv_nsec(PERFCNT count) {
	return (count * (1000U / MPCORE_GTC_CLOCK_FREQ_MHZ));
}

#endif /* __TARGET_ARCH_ARM == 7 */
#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS__KERNEL_H */
