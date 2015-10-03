/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: chip_config.h 881 2011-12-31 14:06:52Z ertl-honda $
 */

/*
 *  ���åװ�¸�⥸�塼��Υġ����¸����MPCORE�ѡ�
 *
 *  �����ͥ�Υ��åװ�¸���Υ��󥯥롼�ɥե�����Υġ����¸����
 *  chip_config.h ���饤�󥯥롼�ɤ���롥
 */

#ifndef TOPPERS_CHIP_CONFIG_TOOL_H
#define TOPPERS_CHIP_CONFIG_TOOL_H

#ifndef TOPPERS_MACRO_ONLY
/*
 *  ��å����������ؿ�
 *  x_lock_cpu()/x_unlock_cpu()��Ȥ����ᡤ������¸�⥸�塼���ARM�ѡˤ�
 *  �ɤ߹���Ǥ���������롥
 */

/*
 *  ��å��������Ի��γ�����Ԥ�
 *
 *  MPCore�Ǥϡ���å��������Ի��˥��ԥ�򷫤��֤��ΤǤϤʤ���wfe�ˤ�ꡤ
 *  ���٥���Ԥ��Ȥ��뤳�Ȥ��侩����Ƥ��롥
 *  wfe�ˤ�륤�٥���Ԥ��κݡ�����߱��������㲼�����ʤ����ᡤ����ߤ��
 *  �Ĥ������֤ơ����٥���Ԥ��Ȥ���٤��Ǥ��롥wfe̿�Ἣ���ϡ�����ߤ��
 *  �ߡ����Ĥ����ʤ����ᡤ����msr̿��ˤ�����ߤ���Ĥ��롥
 *
 *  ���κݡ�msr�¹Ԥˤ�����ߤ����Ĥ��줿ľ��(wfe��¹Ԥ�������)�˳��
 *  �ߤ����ꡤ���θ����ߥϥ�ɥ餫��Υ꥿������wfe�ˤʤꡤ���٥�Ȥ�
 *  ƨ����ǽ�����ͤ����롥
 *
 *  �������ʤ��顤 ����ߥϥ�ɥ餫��Υ꥿����(���Τˤ��㳰���̤���Υ꥿
 *  ����)��Ԥ��ȡ����٥�ȥ쥸���������åȤ��졤wfe�¹Ի��˥��٥�ȥ쥸��
 *  �������åȤ���Ƥ���ȡ����ꥢ����wfe����¨�¤˥꥿���󤹤뤿�������
 *  �ʤ���
 */

/*
 *  1���ܤΥ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_acquire_lock(LOCK *p_lock)
{
	int		locked;

	while(true) {
		Asm("   mov      r2, #0x01   \n"
			"\t ldrex    r1, [%1]    \n"
			"\t cmp      r1, #0x00   \n"
			"\t msrne    cpsr_c, %2  \n" /* ����ߤε���(bit0-7�Τ߽񤭴���) */
			"\t wfene                \n"
			"\t msrne    cpsr_c, %3  \n" /* ����ߤζػ�(bit0-7�Τ߽񤭴���) */
			"\t strexeq  r1, r2,[%1] \n"
			"\t mov      %0, r1      \n"
			:"=r"(locked)
			:"r"(p_lock),"I"(CPSR_SVC|CPSR_ALWAYS_SET),"I"(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
			:"r1","r2", "cc");

		if(locked == 0){
			/* ��å��������� */
			mpcore_data_memory_barrier();
			Asm("":::"memory");
			return;
		}
	}
}

#define t_acquire_lock(p_lock) x_acquire_lock(p_lock)
#define i_acquire_lock(p_lock) x_acquire_lock(p_lock)

#if TTYPE_KLOCK != G_KLOCK

/*
 *  2���ܰʾ�Υ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline bool_t
x_acquire_nested_lock(LOCK *p_lock)
{
	PCB		*p_pcb;
	int		locked;

	while(true) {
		Asm("   mov      r2, #0x01   \n"
			"\t ldrex    r1, [%1]    \n"
			"\t cmp      r1, #0x00   \n"
			"\t msrne    cpsr_c, %2  \n" /* ����ߤε���(bit0-7�Τ߽񤭴���) */
			"\t wfene                \n"
			"\t msrne    cpsr_c, %3  \n" /* ����ߤζػ�(bit0-7�Τ߽񤭴���) */
			"\t strexeq  r1, r2,[%1] \n"
			"\t mov      %0, r1      \n"
			:"=r"(locked)
			:"r"(p_lock),"I"(CPSR_SVC|CPSR_ALWAYS_SET),"I"(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
			:"r1","r2", "cc");
		if(locked == 0){
			/* ��å��������� */
			mpcore_data_memory_barrier();
			Asm("":::"memory");
			return(false);
		}
		/*
		 * �ޥ����졼����󤹤��ǽ��������ΤǤ�����������
		 * �󥿥�������ƥ����Ȥξ�硤�ޥ����졼����󤷤ʤ����ᡤ
		 * while���˼¹Ԥ��Ƥ�褤����1��ǥ�å����Ȥ줿��硤
		 * ��Ψ�������Τǡ������Ǽ������롥
		 */
		p_pcb = get_my_p_pcb();
		if (p_pcb->p_firstlock == NULL) {
			return(true);
		}
	}
}

#define t_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)
#define i_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)

#endif /* TTYPE_KLOCK != G_KLOCK */

/*
 *  ��å��β����ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_release_lock(LOCK *p_lock)
{
	Asm("":::"memory");
	mpcore_data_memory_barrier();
	*p_lock = 0;
	mpcore_data_sync_barrier();
	Asm("sev");
}

/*
 *  �������Ĥ��ʤ���å������ؿ�
 */
Inline void
x_acquire_lock_without_preemption(LOCK *p_lock)
{
	int		locked;

	while(true) {
		Asm("   mov      r2, #0x01   \n"
			"\t ldrex    r1, [%1]    \n"
			"\t cmp      r1, #0x00   \n"
			"\t wfene                \n"
			"\t strexeq  r1, r2,[%1] \n"
			"\t mov      %0, r1      \n"
			:"=r"(locked):"r"(p_lock):"r1","r2", "cc");
		if(locked == 0){
			/* ��å��������� */
			mpcore_data_memory_barrier();
			Asm("":::"memory");
			return;
		}
	}
}

/*
 *  ���ԥ��å���ǽ�Υͥ��ƥ��֥�å������ǻ��Ѥ���ؿ�
 */

/*
 *  ���ԥ��å��η�
 */
typedef uint32_t SPNLOCK;

/*
 *  ���ԥ��å��ν����
 */
Inline void
x_initialize_spin(ID spnid, SPNLOCK *p_spn_lock)
{
	*p_spn_lock = 0;
}

/*
 *  ���ԥ��å��μ���
 */
Inline void
x_lock_spin(SPNLOCK *p_spn_lock)
{
	x_acquire_lock(p_spn_lock);
}

#define t_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)
#define i_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)

/*
 *  ���ԥ��å��μ����λ��
 */
Inline bool_t
x_try_lock_spin(SPNLOCK *p_spn_lock)
{
	int locked;

	Asm("   mov      r2, #0x01   \n"
		"\t ldrex    r1, [%1]    \n"
		"\t cmp      r1, #0x00   \n"
		"\t strexeq  r1, r2,[%1] \n"
		"\t mov      %0, r1      \n"
		:"=r"(locked):"r"(p_spn_lock):"r1","r2", "cc");

	if (locked == 0) {
		/* ����������� */
		mpcore_data_memory_barrier();
		Asm("":::"memory");
		return(false);
	}

	return(true);
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
x_unlock_spin(SPNLOCK *p_spn_lock)
{
	x_release_lock(p_spn_lock);
}
#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CHIP_CONFIG_TOOL_H */
