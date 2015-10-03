/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: mpcore.h 844 2011-07-15 05:00:49Z ertl-honda $
 */

/*
 *  MPCORE �Υϡ��ɥ������񸻤Υġ����¸�������
 */

#ifndef TOPPERS_MPCORE_TOOL_H
#define TOPPERS_MPCORE_TOOL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ץ�ؤΥ��������ޥ���
 */
#define CP15_CONTROL_READ(x)     Asm("mrc p15, 0, %0, c1, c0, 0":"=r"(x))
#define CP15_CONTROL_WRITE(x)    Asm("mcr p15, 0, %0, c1, c0, 0"::"r"(x))

#define CP15_AUXILIARY_READ(x)   Asm("mrc p15, 0, %0, c1, c0, 1":"=r"(x))
#define CP15_AUXILIARY_WRITE(x)  Asm("mcr p15, 0, %0, c1, c0, 1"::"r"(x))

#define CP15_ICACHE_INVALIDATE()           Asm("mcr p15, 0, %0, c7, c5, 0"::"r"(0))
#if __TARGET_ARCH_ARM == 6
#define CP15_DCACHE_INVALIDATE()           Asm("mcr p15, 0, %0, c7, c6, 0"::"r"(0))
#define CP15_DCACHE_CLEAN_AND_INVALIDATE() Asm("MCR p15, 0, %0, c7, c14, 0"::"r"(0))
#elif __TARGET_ARCH_ARM == 7
#define CP15_DCACHE_INVALIDATE(x)           Asm("mcr p15, 0, %0, c7, c6, 2"::"r"(x))
#define CP15_DCACHE_CLEAN_AND_INVALIDATE(x) Asm("MCR p15, 0, %0, c7, c14, 2"::"r"(x))
#endif /* __TARGET_ARCH_ARM == 7 */

#if __TARGET_ARCH_ARM == 6
#define CP15_PBUFFER_FLUSH()               Asm("mcr p15, 0, %0, c7, c5, 4"::"r"(0):"memory")
#define CP15_DATA_SYNC_BARRIER()           Asm("mcr p15, 0, %0, c7, c10, 4"::"r"(0):"memory")
#define CP15_DATA_MEMORY_BARRIER()         Asm("mcr p15, 0, %0, c7, c10, 5"::"r" (0):"memory")
#elif __TARGET_ARCH_ARM == 7
#define CP15_PBUFFER_FLUSH()               Asm("isb":::"memory")
#define CP15_DATA_SYNC_BARRIER()           Asm("dsb":::"memory")
#define CP15_DATA_MEMORY_BARRIER()         Asm("dmb":::"memory")
#endif /* __TARGET_ARCH_ARM == 7 */

#define CP15_INVALIDATE_UNIFIED_TLB() Asm("mcr p15, 0, %0, c8, c7,  0"::"r"(0))

#define CP15_TTBCR_WRITE(x) Asm("mcr p15, 0, %0, c2, c0, 2"::"r"(x))
#define CP15_TTB0_READ(x)   Asm("mrc p15, 0, %0, c2, c0, 0":"=r"(x))
#define CP15_TTB0_WRITE(x)  Asm("mcr p15, 0, %0, c2, c0, 0"::"r"(x))

#define CP15_DOMAINS_WRITE(x) Asm("mcr p15, 0, %0, c3, c0, 0":: "r"(x))

#define CP15_CPUID_READ(x)     Asm("mrc p15, 0, %0, c0, c0, 5":"=r"(x))

#define CP15_CACHE_SIZE_ID_READ(x)         Asm("mrc p15, 1, %0, c0, c0, 0":"=r"(x))

#if __TARGET_ARCH_ARM == 7
#define CP15_CACHE_SIZE_SELECTION_WRITE(x) Asm("mcr p15, 2, %0, c0, c0, 0"::"r"(x))
#define CP15_CACHE_SIZE_SELECTION_READ(x)  Asm("mrc p15, 2, %0, c0, c0, 0":"=r"(x))
#define CP15_NSACR_WRITE(x) Asm("mcr p15, 0, %0, c1, c1, 2"::"r"(x))
#define CP15_NSACR_READ(x)  Asm("mrc p15, 0, %0, c1, c1, 2":"=r"(x))

#define CP15_NSACR_NS_SMP (1 << 18)

#endif /* __TARGET_ARCH_ARM == 7 */

#define CPU15_PONLY_THREAD_ID_READ(x)  Asm("mrc p15, 0, %0, c13, c0, 4":"=r"(x))
#define CPU15_PONLY_THREAD_ID_WRITE(x) Asm("mcr p15, 0, %0, c13, c0, 4":: "r"(x))

#define CP15_SET_VBAR(x)    Asm("mcr p15, 0, %0, c12, c0, 0"::"r"(x))

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_MPCORE_TOOL_H */
