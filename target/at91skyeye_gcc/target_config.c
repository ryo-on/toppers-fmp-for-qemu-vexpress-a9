/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 *  Copyright (C) 2007-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.c 843 2011-07-15 03:17:19Z ertl-honda $
 */

/*
 * ���åװ�¸�⥸�塼���AT91SKYEYE�ѡ�
 */

#include "kernel_impl.h"
#include <sil.h>
#include "target_serial.h"
#include "mp.h"
#include <stdlib.h>

#ifdef TOPPERS_ENABLE_TRACE
#include <stdio.h>
static FILE *trace_log_file;
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  SIL_LOC_SPN()����������ץ��å��δ���
 */
uint32_t TOPPERS_spn_var;

/*
 *  ʸ����ν��ϡʥС����������å��ѡ�
 */
static void
target_fput_str(char *c) {
	while(*c != '\0') {
		at91skyeye_putc(*c++);
	}
}

/*
 *  ���� to ʸ���Ѵ�(4bit��)
 */
static char
num_to_char(uint8_t num) {
	if (num <= 9) {
		return ('0' + num);
	}
	else {
		return ('a' + (num - 10));
	}
}

/*
 *  �С�������ֹ�ν���
 */
static void
version_put(uint16_t version) {
	char c;

	c = num_to_char((version >> 12) & 0x0f);
	at91skyeye_putc(c);
	at91skyeye_putc('.');
	c = num_to_char((version >> 8) & 0x0f);
	at91skyeye_putc(c);
	c = num_to_char((version >> 4) & 0x0f);
	at91skyeye_putc(c);
	at91skyeye_putc('.');
	c = num_to_char((version) & 0x0f);
	at91skyeye_putc(c);
	at91skyeye_putc('.');
}

/*
 *  �С����������å�
 */
static void
version_check(void) {

	/* SkyEye �ΥС��������ǧ */
	if (sil_rew_mem((void *)(SKYEYE_VER_REG)) != SUPPORT_SKYEYE_VER) {
		target_fput_str("SkyEye version is mismatch!!");
		at91skyeye_putc('\n');
		target_fput_str("Suppoted version is ");
		version_put(SUPPORT_SKYEYE_VER);
		at91skyeye_putc('\n');
		target_fput_str("Tool version is ");
		version_put(sil_rew_mem((void *)(SKYEYE_VER_REG)));
		at91skyeye_putc('\n');
		target_fput_str("Kernel Exit...");
		at91skyeye_putc('\n');
		target_exit();
	}

	/* DeviceManger Extension �ΥС��������ǧ */
	if ((sil_rew_mem((void *)(DEVM_VER_REG)) & 0xfff0)
		!= (SUPPORT_DEVM_VER & 0xfff0)) {
		target_fput_str("DeviceManager Extension version is mismatch!!");
		at91skyeye_putc('\n');
		target_fput_str("Suppoted version is ");
		version_put(SUPPORT_DEVM_VER);
		at91skyeye_putc('\n');
		target_fput_str("Tool version is ");
		version_put((sil_rew_mem((void *)(DEVM_VER_REG)) & 0xfff0));
		at91skyeye_putc('\n');
		target_fput_str("Kernel Exit...");
		at91skyeye_putc('\n');
		target_exit();
	}
}

/*
 *  str_ker() �����ǥޥ����ץ��å��ǹԤ������
 */
void
target_mprc_initialize(void)
{

}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	TPCB *p_tpcb = get_my_p_tpcb();
	uint32_t index = x_prc_index();

	/*
	 *  target_fput_log ����ǽ�ˤʤ�褦��UART������
	 */
	at91skyeye_init_uart(x_prc_index() + 1);

	/*
	 *  �С������γ�ǧ
	 */
	version_check();

	/*
	 *  ARM��¸�ν����
	 */
	core_initialize();
    
	/*
	 * �Ƴ���ߤγ�����׵�ػߥե饰���ػ�
	 */
	p_tpcb->idf = ~0U;

	/*
	 * �����ͥ���٥ޥ�����0
	 */ 
	p_tpcb->ipm = 0U;

	/*
	 * ���Ƥγ���ߤ�ޥ���
	 */ 
	at91skyeye_disable_int(~0U);

	/*
	 * ���Ƥγ�����װ��򥯥ꥢ
	 */
	at91skyeye_clear_int(~0U);

	/*
	 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ����������롥
	 */
	p_tpcb->bitpat_cfgint = 0U;
    
	/*
	 *  ����ߥޥ����ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_ipm_mask_tbl = p_ipm_mask_table[index];

	/*
	 *  ����ߥϥ�ɥ�ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_inh_tbl = p_inh_table[index];

	/*
	 *  �����ͥ���٥ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_inh_ipm_tbl = p_inh_ipm_table[index];

#ifdef TOPPERS_ENABLE_TRACE
	if (x_sense_mprc()) {
		trace_log_file = fopen("kernel_trace.log","w");
	}
#endif /* TOPPERS_ENABLE_TRACE */
}

/*
 *  exit()�κǸ�˸ƤӽФ����ؿ���SkyEye��λ�����롥
 *  �ޥ����ץ��å��ʳ����ƤӽФ���
 */
extern void _exit(int) NoReturn;

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	/*
	 *  ���٤Ƥγ���ߤ�ޥ������롥
	 */
	at91skyeye_disable_int(~0U);

	/*
	 *  ARM��¸�ν�λ����
	 */
	core_terminate();

	/*
	 *  ��ȯ�Ķ���¸�ν�λ����
	 */
	at91skyeye_exit();

#ifdef TOPPERS_ENABLE_TRACE
	if (x_sense_mprc()) {
		fclose(trace_log_file);
	}
#endif /* TOPPERS_ENABLE_TRACE */

#ifdef TOPPERS_ENABLE_GCOV_PART
	_exit(0);
#else /* TOPPERS_ENABLE_GCOV_FULL */
	if (x_sense_mprc()) {
		exit(0);
	}
	else {
		_exit(0);
	}
#endif /* TOPPERS_ENABLE_GCOV_PART */
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼����Ѥ���¬���ѥ����ޤν�����ؿ�
 */
void
perf_timer_initialize(intptr_t exinf)
{
}

/*
 *  �������륫���󥿤μ���
 */
void
cycle_counter_get(uint32_t *p_time)
{
	*p_time = cycle_counter_get_current();
}

/*
 *  �������åȰ�¸��ʸ������
 */
void
target_fput_log(char_t c)
{
	if (c == '\n') {
		at91skyeye_putc('\r');
	}
	at91skyeye_putc(c);
}

#ifdef TOPPERS_ENABLE_TRACE
/*
 *  �ȥ졼�����Υե��������
 */
void
target_fput_log_file(char_t c)
{
	if (c == '\n') {
		fputc('\r', trace_log_file);
	}
	fputc(c, trace_log_file);
}
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ������׵�饤���°��������
 *
 *  FMP�����ͥ�Ǥ����Ѥ����ꤷ�ơ��ѥ�᡼�����顼�ϥ����������ǥ�����
 *  �����Ƥ��롥FI4�����ͥ�����Ѥ�����ˤϡ����顼���֤��褦�ˤ��٤�
 *  �Ǥ�����
 *
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	assert(VALID_INTNO_CFGINT(ID_PRC(x_prc_index()), intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ�������
	 */
	p_tpcb->bitpat_cfgint |= INTNO_BITPAT(INTNO_MASK(intno));
    
	/* 
	 * ���ä������ߤ�ػߤ���
	 */    
	x_disable_int(intno);

	if ((intatr & TA_ENAINT) != 0U){
		(void)x_enable_int(intno);
	}    
}

#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 * ̤����γ���ߤ����ä����ν���
 */
void
default_int_handler(void){
	ID prc_id = ID_PRC(x_prc_index());

	syslog_1(LOG_EMERG, "Processor %d : Unregistered Interrupt occurs.", prc_id);
	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */


extern void start_master(void);

/*
 *  ����ѥ���Υ������ȥ��åץ롼���󤫤�ƤӽФ���롥
 *  sta_ker()��ƤӽФ��ƥ����ͥ�򥹥����Ȥ����롥 
 */
int
main(void)
{
	start_master();
	return 1;
}

#ifdef TOPPERS_ENABLE_GCOV_PART
/*
 *  GCOV���������ѥ饤�֥��
 */

extern void __gcov_flush();

/*
 *  GCOV������ؿ�
 *   ���Х�å���.gcda�˽��Ϥ���SkyEye��*.gcda�ե�����������롥
 */
void
gcov_init(void)
{
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	__gcov_flush();
	sil_wrw_mem((void*)0xFFFE1020, 0);
	SIL_UNL_SPN();
}

/*
 *  GCOV���Ǵؿ�
 *   ���Х�å���.gcda�˽��Ϥ���SkyEye��*.gcda�ե������*.gcda.bak�إ�͡��ह�롥
 */
void
gcov_pause(void)
{
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	__gcov_flush();
	sil_wrw_mem((void*)0xFFFE1024, 0);
	SIL_UNL_SPN();
}

/*
 *  GCOV�Ƴ��ؿ�
 *   ���Х�å���.gcda�˽��Ϥ���SkyEye��*.gcda.bak�ե������*.gcda�إ�͡��ह�롥
 */
void
gcov_resume(void)
{
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	__gcov_flush();
	sil_wrw_mem((void*)0xFFFE1028, 0);
	SIL_UNL_SPN();
}

/*
 *  GCOV���ϴؿ�
 *   ���Х�å���.gcda�˽��Ϥ��롥
 */
void
gcov_dump(void)
{
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	__gcov_flush();
	SIL_UNL_SPN();
}
#endif /* TOPPERS_ENABLE_GCOV_PART */
