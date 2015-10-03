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
 *  @(#) $Id: mpcore.h 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *  MPCORE �Υϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_MPCORE_H
#define TOPPERS_MPCORE_H

#include <sil.h>

/*
 *  MPCORE �Υϡ��ɥ������񸻤Υġ����¸�������
 */
#include <mpcore_tool.h>


#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ץ�Υӥå����
 */
#define CP15_CONTROL_XP_BIT   (1 << 23)
#define CP15_CONTROL_I_BIT    (1 << 12)
#define CP15_CONTROL_C_BIT    (1 <<  2)
#define CP15_CONTROL_M_BIT    (1 <<  0)

#if __TARGET_ARCH_ARM == 6
#define CP15_AUXILIARY_SA_BIT (1 << 5)
#define CP15_CPUID_BIT        (0x0f)
#else /* __TARGET_ARCH_ARM == 7 */
#define CP15_AUXILIARY_SA_BIT (1 << 6)
#define CP15_AUXILIARY_EX_BIT (1 << 7)
#define CP15_CPUID_BIT        (0x03)
#endif /* __TARGET_ARCH_ARM == 7 */

#define CP15_TTB0_RGN_S       (1 << 1)
#define CP15_TTB0_RGN_WBWA    (1 << 3)

#if __TARGET_ARCH_ARM == 7
#define CP15_TTB0_IRGN_WBWA   ((1 << 6)|(0))
#endif /* __TARGET_ARCH_ARM == 7 */


/*
 *  ���ץ���Ѥ����롼����
 */

/*
 *  �ץ��å�INDEX��0���ꥸ��ˤμ���
 */
Inline uint32_t
x_prc_index(void)
{
	uint32_t index;

	CP15_CPUID_READ(index);
	return((index & 0x0fU));
}

/*
 *  Data Synchronization Barrier
 *  �����ȯ�Ԥ��줿 read �� write �ν�λ���Ԥ�
 *  ������å��塤�֥����ץ�ǥ��������TLB�����ν�λ���Ԥ�
 *  ������̿��θ�˽񤫤줿̿��ϼ¹Ԥ���ʤ�
 */
Inline void
mpcore_data_sync_barrier(void)
{
	CP15_DATA_SYNC_BARRIER();
}

/*
 *  Data Memory Barrier
 *  ���ץ����ε��Ҥ˽��äơ���˽񤫤줿̿��ǤΥ��ꥢ��������
 *     ��λ����ޤ��Ԥġ�
 *
 */
Inline void
mpcore_data_memory_barrier(void)
{
	CP15_DATA_MEMORY_BARRIER();
}

/*
 *  TLB��̵����
 */
Inline void
mpcore_invalidate_unfied_tlb(void)
{
	CP15_DATA_SYNC_BARRIER();
}

/*
 *  D����å����̵����
 */
Inline void
mpcore_dcache_invalidate(void)
{
#if __TARGET_ARCH_ARM == 6
	CP15_DCACHE_INVALIDATE();
#elif __TARGET_ARCH_ARM == 7
	uint32_t bits = 0;
	uint32_t ways = 0;
	uint32_t sets = 0;

	CP15_CACHE_SIZE_SELECTION_WRITE(0);
	CP15_PBUFFER_FLUSH();
	for (ways = 0; ways < 4; ways++){
		for (sets = 0; sets < 256; sets++){
			bits = ways << 30 | sets << 5;
			CP15_DCACHE_INVALIDATE(bits);
		}
	}
#endif /* __TARGET_ARCH_ARM == 7 */
}

/*
 *  D����å���Υ��꡼���̵����
 */
Inline void
mpcore_dcache_clean_and_invalidate(void)
{
#if __TARGET_ARCH_ARM == 6
	CP15_DCACHE_CLEAN_AND_INVALIDATE();
#elif __TARGET_ARCH_ARM == 7
	uint32_t bits = 0;
	uint32_t  ways = 0;
	uint32_t sets = 0;

	CP15_CACHE_SIZE_SELECTION_WRITE(0);
	CP15_PBUFFER_FLUSH();
	for (ways = 0; ways < 4; ways++){
		for (sets = 0; sets < 256; sets++){
			bits = ways << 30 | sets << 5;
			CP15_DCACHE_CLEAN_AND_INVALIDATE(bits);
		}
	}
#endif /* __TARGET_ARCH_ARM == 7 */
}

/*
 *  I����å����̵����
 */
Inline void
mpcore_icache_invalidate(void)
{
	CP15_ICACHE_INVALIDATE();
}

/*
 *  �ץ�ե��å��Хåե��򥯥ꥢ
 */
Inline void
mpcore_pbuffer_flash(void)
{
	CP15_PBUFFER_FLUSH();
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ��¢�����޴�Ϣ�����
 */
#define MPCORE_TM_LR     (MPCORE_PMR_BASE + 0x0600)  /* ���ɥ쥸����           */
#define MPCORE_TM_COUNT  (MPCORE_PMR_BASE + 0x0604)  /* �����󥿡��쥸����       */
#define MPCORE_TM_CNT    (MPCORE_PMR_BASE + 0x0608)  /* ����ȥ���쥸����     */
#define MPCORE_TM_ISR    (MPCORE_PMR_BASE + 0x060C)  /* ����ߥ��ơ������쥸���� */

#define MPCORE_TM_CNT_EN        0x1
#define MPCORE_TM_CNT_AR        0x2
#define MPCORE_TM_CNT_IEN       0x4
#define MPCORE_TM_CNT_PS_OFFSET   8

#define MPCORE_TM_ISR_SCBIT    0x01

#if __TARGET_ARCH_ARM == 7
/*
 * Global Timer��Ϣ�������r1�ʾ�ǥ��ݡ��ȡ�
 */
#define MPCORE_GTC_COUNT_L (MPCORE_PMR_BASE + 0x0200)  /* �����󥿡��쥸����L       */
#define MPCORE_GTC_COUNT_U (MPCORE_PMR_BASE + 0x0204)  /* �����󥿡��쥸����H       */
#define MPCORE_GTC_CNT     (MPCORE_PMR_BASE + 0x0208)  /* ����ȥ���쥸����      */
#define MPCORE_GTC_COMPV_L (MPCORE_PMR_BASE + 0x0210)  /* ����ڥ��Х�塼�쥸����L */
#define MPCORE_GTC_COMPV_U (MPCORE_PMR_BASE + 0x0214)  /* ����ڥ��Х�塼�쥸����H */

#define MPCORE_GTC_CNT_TIMENA 0x01 /* �����ޡ����͡��֥� */

#endif /* __TARGET_ARCH_ARM == 7 */

/*
 *  Snoop Control Unit
 */
#define MPCORE_SCU_CTRL    (MPCORE_PMR_BASE + 0x0000)  /* ����ȥ���쥸���� */
#define MPCORE_SCU_CONFIG  (MPCORE_PMR_BASE + 0x0004)  /* ����ե�����졼�����쥸���� */
#define MPCORE_SCU_CPUST   (MPCORE_PMR_BASE + 0x0008)  /* CPU���ơ����� */
#define MPCORE_SCU_IALL    (MPCORE_PMR_BASE + 0x000C)  /* ����Х�åɥ����� */
#if __TARGET_ARCH_ARM == 6
#define MPCORE_SCU_PM_CTRL (MPCORE_PMR_BASE + 0x0010)  /* �ѥե����ޥ󥹥�˥�����쥸���� */
#define MPCORE_SCU_PM_EVT0 (MPCORE_PMR_BASE + 0x0014)  /* ��˥������󥿥��٥��0 */
#define MPCORE_SCU_PM_EVT1 (MPCORE_PMR_BASE + 0x0018)  /* ��˥������󥿥��٥��1 */
#define MPCORE_SCU_PM_MN0  (MPCORE_PMR_BASE + 0x001C)  /* ��˥�������0 */
#define MPCORE_SCU_PM_MN1  (MPCORE_PMR_BASE + 0x0020)  /* ��˥�������1 */
#define MPCORE_SCU_PM_MN2  (MPCORE_PMR_BASE + 0x0024)  /* ��˥�������2 */
#define MPCORE_SCU_PM_MN3  (MPCORE_PMR_BASE + 0x0028)  /* ��˥�������3 */
#define MPCORE_SCU_PM_MN4  (MPCORE_PMR_BASE + 0x002C)  /* ��˥�������4 */
#define MPCORE_SCU_PM_MN5  (MPCORE_PMR_BASE + 0x0030)  /* ��˥�������5 */
#define MPCORE_SCU_PM_MN6  (MPCORE_PMR_BASE + 0x0034)  /* ��˥�������6 */
#define MPCORE_SCU_PM_MN7  (MPCORE_PMR_BASE + 0x0038)  /* ��˥�������7 */
#endif /* __TARGET_ARCH_ARM == 6 */
#define MPCORE_SCU_SNSAC   (MPCORE_PMR_BASE + 0x0054)  /* �Υ󥻥��奢������������ȥ���쥸����*/


#define MPCORE_SCU_CTRL_EN (1 << 0)   /* SCU���͡��֥� */

#define MPCORE_SCU_PM_CTRL_ENA  (1 << 0)    /* �ѥե����ޥ󥹥�˥�ͭ���� */
#define MPCORE_SCU_PM_CTRL_RST  (1 << 1)    /* �ѥե����ޥ󥹥�˥��ꥻ�å� */

#define MPCORE_SCU_PM_EVT_CYC_COUNT0_4 (31 << 0) /* �������륫����Ȼ��� */

#define MPCORE_SCU_IALL_WAYS   (0x0000ffffU)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  SCU�ν����
 */
extern void scu_init(void);

#if __TARGET_ARCH_ARM == 6
/*
 * SCU�����󥿤ν������MN0����ѡ�
 */
extern void scu_counter_init(void);

/*
 * SCU�����ޤΥꥻ�å�
 */
Inline void
scu_counter_reset(void)
{
	sil_wrw_mem((void *)MPCORE_SCU_PM_CTRL,
			sil_rew_mem((void *)MPCORE_SCU_PM_CTRL) | MPCORE_SCU_PM_CTRL_RST);
}

/*
 * SCU�����ޤθ����ͤ��ɤ�
 */
Inline uint_t
scu_counter_get_current(void)
{
	return (sil_rew_mem((void *)MPCORE_SCU_PM_MN0));
}
#endif /* __TARGET_ARCH_ARM == 6 */
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  Distributed Interrupt Controller CPU Interface
 *
 *  ͥ���٤ϡ�0x0��0xF ��16�ʳ���
 *  0x0���ǹ�ͥ���٤ǡ�0xF������ͥ���١�
 */
#define DIC_CPUIF_CR   (MPCORE_PMR_BASE + 0x0100)  /* ����ȥ���쥸���� */
#define DIC_CPUIF_PMR  (MPCORE_PMR_BASE + 0x0104)  /* ͥ���٥ޥ����쥸���� */
#define DIC_CPUIF_BPR  (MPCORE_PMR_BASE + 0x0108)  /* �Х��ʥ�ݥ���ȥ쥸���� */
#define DIC_CPUIF_IAR  (MPCORE_PMR_BASE + 0x010C)  /* Interrupt Acknowledge Register */
#define DIC_CPUIF_EOI  (MPCORE_PMR_BASE + 0x0110)  /* End of Interrupt Register */
#define DIC_CPUIF_RII  (MPCORE_PMR_BASE + 0x0114)  /* Running Interrupt Register */

#define DIC_CPUIF_CR_EN          0x01 /* ���ΥӥåȤϡ�non-secure�ǤΤ�ͭ�� */
#define DIC_CPUIF_CR_EN_S        0x01
#define DIC_CPUIF_CR_EN_NS       0x02
#define DIC_CPUIF_CR_EN_ACKCTL   0x04
#define DIC_CPUIF_CR_FIQEN       0x08
#define DIC_CPUIF_CR_EN_SBPR     0x10

#if __TARGET_ARCH_ARM == 6
#define DIC_CPUIF_PMR_OFFSET 0x04
#define DIC_CPUIF_BPR_ALL    0x03  /* ���ƤΥӥåȤ�ͭ�� */
#define DIC_CPUIF_BPR_3      0x04  /* 3�ӥå�ͭ��        */
#define DIC_CPUIF_BPR_2      0x05  /* 2�ӥå�ͭ��        */
#define DIC_CPUIF_BPR_1      0x06  /* 1�ӥå�ͭ��        */
#elif __TARGET_ARCH_ARM == 7
#define DIC_CPUIF_PMR_OFFSET 0x03
#define DIC_CPUIF_BPR_ALL    0x00  /* ���ƤΥӥåȤ�ͭ�� */
#define DIC_CPUIF_BPR_4      0x03  /* 4�ӥå�ͭ��        */
#define DIC_CPUIF_BPR_3      0x04  /* 3�ӥå�ͭ��        */
#define DIC_CPUIF_BPR_2      0x05  /* 2�ӥå�ͭ��        */
#define DIC_CPUIF_BPR_1      0x06  /* 1�ӥå�ͭ��        */
#endif /* __TARGET_ARCH_ARM == 7 */


/*
 *  Distributed Interrupt Controller
 */
#define DIC_CR     (MPCORE_PMR_BASE + 0x1000)  /* ����ȥ���쥸���� */
#define DIC_ICT    (MPCORE_PMR_BASE + 0x1004)  /* Interrupt Controller �����ץ쥸���� */
#if __TARGET_ARCH_ARM == 7
#define DIC_IID    (MPCORE_PMR_BASE + 0x1008)  /* Distributor Implementer ID */
#define DIC_SEC    (MPCORE_PMR_BASE + 0x1080)  /* ����ߥ������ƥ� */
#endif /* __TARGET_ARCH_ARM == 7 */
#define DIC_SE     (MPCORE_PMR_BASE + 0x1100)  /* ����ߥ��͡��֥륻�å�   */
#define DIC_CE     (MPCORE_PMR_BASE + 0x1180)  /* ����ߥ��͡��֥륯�ꥢ�� */
#define DIC_SP     (MPCORE_PMR_BASE + 0x1200)  /* ����ߥ��åȥڥ�ǥ��� */
#define DIC_CP     (MPCORE_PMR_BASE + 0x1280)  /* ����ߥ��ꥢ���ڥ�ǥ��� */
#define DIC_IPR    (MPCORE_PMR_BASE + 0x1400)  /* �����ͥ���٥쥸���� */
#define DIC_ITR    (MPCORE_PMR_BASE + 0x1800)  /* ����ߥ������åȥ쥸����/CA9��SPI�������åȥ쥸���� */
#define DIC_ICR    (MPCORE_PMR_BASE + 0x1C00)  /* ����ߥ���ե�����졼�����쥸���� */
#define DIC_SIR    (MPCORE_PMR_BASE + 0x1F00)  /* ���եȥ���������ߥ쥸����  */
#if __TARGET_ARCH_ARM == 7
#define DIC_PPIS   (MPCORE_PRM_BASE + 0x1D00)  /* PPI���ơ����� */
#define DIC_SPIS   (MPCORE_PRM_BASE + 0x1D04)  /* SPI���ơ����� */
#endif /* __TARGET_ARCH_ARM == 7 */

#define DIC_CR_ENABLE 0x01
#define DIC_CR_NS_ENABLE 0x02

/*
 *  �������Υץ��å��λ���
 */
#define DIC_ITR_CPU0  0x01
#define DIC_ITR_CPU1  0x02
#define DIC_ITR_CPU2  0x04
#define DIC_ITR_CPU3  0x08

#define DIC_SIR_CPU0  0x01
#define DIC_SIR_CPU1  0x02
#define DIC_SIR_CPU2  0x04
#define DIC_SIR_CPU3  0x08
#define DIC_SIR_CPUS  0x0f

#define DIC_SIR_CPU_OFFSET 16

/*
 *  �����ͥ����
 */
#define DIC_MAX_PRIORITY  0x00
#if __TARGET_ARCH_ARM == 6
#define DIC_MIN_PRIORITY  0x0f
#elif __TARGET_ARCH_ARM == 7
#define DIC_MIN_PRIORITY  0x1f
#endif /* __TARGET_ARCH_ARM == 7 */

/*
 *  ����ե�����졼�����쥸������������
 */
#define DIC_ICR_EDGE     0x03   /* ���å������ */
#define DIC_ICR_LEVEL    0x01   /* ��٥����� */

/*
 *  DIC�ǥ��ݡ��Ȥ��Ƥ������߿�
 */
#define DIC_TMIN_INTNO      0U

#ifndef DIC_TMAX_INTNO
#define DIC_TMAX_INTNO    255U
#endif /* DIC_TMAX_INTNO */

#ifndef DIC_TNUM_INT
#define DIC_TNUM_INT      256U
#endif /* DIC_TNUM_INT */

/*
 *  �����Х����ߤγ����ֹ�
 */
#define TMIN_GLOBAL_INTNO   32U

/*
 * ������ֹ�(DIC�Ǥ��ֹ�)
 */
#define DIC_IRQNO_IPI0     0
#define DIC_IRQNO_IPI1     1
#define DIC_IRQNO_IPI2     2
#define DIC_IRQNO_IPI3     3
#define DIC_IRQNO_IPI4     4
#define DIC_IRQNO_IPI5     5
#define DIC_IRQNO_IPI6     6
#define DIC_IRQNO_IPI7     7
#define DIC_IRQNO_IPI8     8
#define DIC_IRQNO_IPI9     9
#define DIC_IRQNO_IPI10   10
#define DIC_IRQNO_IPI11   11
#define DIC_IRQNO_IPI12   12
#define DIC_IRQNO_IPI13   13
#define DIC_IRQNO_IPI14   14
#define DIC_IRQNO_IPI15   15

#define DIC_IRQNO_TM      29
#define DIC_IRQNO_WDT     30

#ifndef TOPPERS_MACRO_ONLY
/*
 *  DIC CPU���󥿥ե�������Ϣ�Υɥ饤��
 */
/*
 *  CPU�γ����ͥ���٥ޥ���������
 */
Inline void
dic_cpu_set_priority(int pri)
{
	sil_wrw_mem((void *)DIC_CPUIF_PMR,
				(pri << DIC_CPUIF_PMR_OFFSET));
}

/*
 *  CPU�γ����ͥ���٥ޥ��������
 */
Inline int
dic_cpu_current_priority(void)
{
	return (sil_rew_mem((void *)(DIC_CPUIF_PMR)) >>
			DIC_CPUIF_PMR_OFFSET);
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
dic_cpu_end_int(uint8_t id)
{
	sil_wrw_mem((void *)(DIC_CPUIF_EOI), id);
}

/*
 *  DIC�Υץ��å��γ����ͥ���٤ΤɤΥӥåȤ���Ѥ��뤫
 */
Inline void
dic_cpu_set_bp(int mask_bit)
{
	sil_wrw_mem((void *)DIC_CPUIF_BPR, mask_bit);
}

/*
 *  CPU���󥿥ե������ν����
 */
extern void dic_cpu_init(void);

/*
 *  CPU���󥿥ե������ν�λ
 */
extern void dic_cpu_stop(void);

/*
 *  DIC DIS���󥿥ե�������Ϣ�Υɥ饤��
 */

/*
 *  ����߶ػ�
 */
extern void dic_disable_int(uint8_t id);

/*
 *  ����ߵ���
 */
extern void dic_enable_int(uint8_t id);

/*
 *  ����ߥڥ�ǥ��󥰥��ꥢ
 */
extern void dic_clear_pending(uint8_t id);

/*
 *  ����ߥڥ�ǥ��󥰥��å�
 */
extern void dic_set_pending(uint8_t id);

/*
 *  ������׵�Υ����å�
 */
extern bool_t dic_probe_int(uint8_t id);

/*
 *  ���������Υ��å�
 */
extern void dic_config(uint8_t id, uint8_t config);

/*
 *  �����ͥ���٤Υ��å�
 *  ����ɽ�����Ϥ���
 */
extern void dic_set_priority(uint8_t id, int pri);

/*
 *  DIC����ߥ������åȤ�����
 *  CPU��OR�ǻ���
 */
extern void dic_set_target(uint8_t id, uint8_t cpus);

/*
 *  DIC���󥿥ե������ν����(SPI�Τ߽����)
 */
extern void dic_init(void);

/*
 *  �ƥ����Ǽ¹Ԥ���DIC���󥿥ե�������SGI��PPI�ν����
 */
extern void dic_sgi_ppi_init(void);

/*
 * GIC�γ���ߥ������ƥ�����
 * ������ֹ�Ȥ��Υ������ƥ��ǻ���
 * ���� ns (non secure bit) :
 *     0 -> secure(FIQ) setting
 *     1 -> non-secure(IRQ) setting
 */
extern void dic_set_security(int intno, unsigned int ns);

/*
 *  DIC���󥿥ե������ν�λ
 */
extern void dic_stop(void);

/*
 *  ���եȥ���������ߤ�ȯ��
 */
Inline void
dic_swi(int cpu, int id)
{
	CP15_DATA_SYNC_BARRIER();
	sil_wrw_mem((void *)DIC_SIR, (cpu << DIC_SIR_CPU_OFFSET)|id);
	CP15_DATA_SYNC_BARRIER();
}

/*
 *  SMP�⡼�ɤ�ͭ����
 */
extern void mpcore_smp_mode_enable(void);

/*
 *  MMU��Ϣ
 */

/*
 * �Ѵ��ơ��֥�ؤ���������
 * va   : ���ۥ��ɥ쥹
 * pa   : ʪ�����ɥ쥹
 * size : ������
 * s    : ��ͭ����
 * tex  : C B�Ȥ��Ȥ߹�碌���Ѳ�
 * ap   : ����������
 * c    : ����å���
 * b    : �Хåե�
 */
typedef struct{
	uintptr_t   va;
	uintptr_t   pa;
	uint32_t    size;
	uint8_t     ns;
	uint8_t     s;
	uint8_t     tex;
	uint8_t     ap;
	uint8_t     c;
	uint8_t     b;
}MEMORY_ATTRIBUTE;

/*
 *  MMU�ν����
 */
extern void mpcore_mmu_init(void);

/*
 *  MMU�ˤ�����Υޥåԥ�
 */
extern void mmu_map_memory(MEMORY_ATTRIBUTE *m_attribute);

/*
 *  I/D����å����ξ����ͭ����
 */
extern void mpcore_cache_enable(void);

/*
 *  I/D����å����ξ����̵����
 */
extern void mpcore_cache_disable(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_MPCORE_H */
