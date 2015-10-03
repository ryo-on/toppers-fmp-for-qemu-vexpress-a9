/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: test_lib.c 514 2010-02-01 09:42:03Z ertl-honda $
 */


/* 
 *		�ƥ��ȥץ�����ѥ饤�֥��
 */

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <log_output.h>
#include "syssvc/syslog.h"
#include "target_syssvc.h"
#include "test_lib.h"

/*
 *  �����å��ݥ�����̲ᥫ������ѿ��������Ǥ򡤣��ǽ��������뤳�Ȥ�����
 */ 
static ID	check_count[TNUM_PRCID];

/*
 *	���ʿ��Ǵؿ�
 */
static BIT_FUNC	check_bit_func = NULL;

/*
 *	���ʿ��Ǵؿ�������
 */
void
set_bit_func(BIT_FUNC bit_func)
{
	check_bit_func = bit_func;
}

/*
 *  �����ƥ���ν��Ͻ���
 */
void
syslog_flush(void)
{
	SYSLOG	syslog;
	ER_UINT	rercd;

	/*
	 *  ���Хåե��˵�Ͽ���줿����������٥���ϵ�ǽ���Ѥ��ƽ�
	 *  �Ϥ��롥
	 */
	while ((rercd = syslog_rea_log(&syslog)) >= 0) {
		if (rercd > 0) {
			syslog_lostmsg((uint_t) rercd, target_fput_log);
		}
		if (syslog.logtype >= LOG_TYPE_COMMENT) {
			syslog_print(&syslog, target_fput_log);
			target_fput_log('\n');
		}
	}
}

/*
 *	�ƥ��ȥץ����ν�λ
 */
void
test_finish(void)
{
	SIL_PRE_LOC;

	SIL_LOC_INT();
	syslog_flush();
	ext_ker();
}

/*
 *	�����å��ݥ����
 */

void
check_point(uint_t count)
{
	bool_t	errorflag = false;
	ER		rercd;
	ID      prcid;

	SIL_PRE_LOC;

	/*
	 *  ����ߥ�å����֤�
	 */
	SIL_LOC_INT();

	/*
	 *  PRCID����
	 */
	sil_get_pid(&prcid);

	/*
	 *  �������󥹥����å�
	 */
	if (++check_count[prcid-1] == count) {
		syslog_2(LOG_NOTICE, "PE %d : Check point %d passed.", prcid, count);
	}
	else {
		syslog_2(LOG_ERROR, "## PE %d : Unexpected check point %d.", prcid, count);
		errorflag = true;
	}

	/*
	 *  �����ͥ���������֤θ���
	 */
	if (check_bit_func != NULL) {
		rercd = (*check_bit_func)();
		if (rercd < 0) {
			syslog_2(LOG_ERROR, "## Internal inconsistency detected (%s, %d).",
								itron_strerror(rercd), SERCD(rercd));
			errorflag = true;
		}
	}

	/*
	 *  ���顼�����Ф��줿���ϡ��ƥ��ȥץ�����λ���롥
	 */
	if (errorflag) {
		test_finish();
	}

	/*
	 *  ����ߥ�å����֤���
	 */
	SIL_UNL_INT();
}

/*
 *	��λ�����å��ݥ���ȤǤ�Ʊ�����ѿ�
 */
static volatile uint_t check_finish_enter[TNUM_PRCID];
static volatile uint_t check_finish_leave;

/*
 *	��λ�����å��ݥ����
 */
void
check_finish(uint_t count)
{
	volatile uint_t i, j;
	volatile uint_t flag;
	ID       prcid;

	/*
	 *  PRCID����
	 */
	sil_get_pid(&prcid);

	check_point(count);
	syslog_1(LOG_NOTICE, "PE %d : All check points passed.", prcid);

	/*
	 * ext_ker()ȯ���������ץ��å���Ʊ����Ȥ�
	 */
	check_finish_enter[prcid - 1] = 1;

	if (prcid == TOPPERS_MASTER_PRCID) {
		do{
			flag = 0;
			for(i = 0; i < TNUM_PRCID; i++){
				if (check_finish_enter[i] == 1){
					flag++;
				}
			}
			for (j = 0; j < 100; j++);
		}while (flag < TNUM_PRCID);
		check_finish_leave = 1;
	}
	else {
		while (check_finish_leave != 1) {
			for (j = 0; j < 100; j++);
		}
	}

	test_finish();
}
/*
 *	�������å��Υ��顼����
 */
void
_check_assert(const char *expr, const char *file, int_t line)
{
	syslog_3(LOG_ERROR, "## Assertion `%s' failed at %s:%u.",
								expr, file, line);
	test_finish();
}

/*
 *	���顼�����ɥ����å��Υ��顼����
 */
void
_check_ercd(ER ercd, const char *file, int_t line)
{
	syslog_3(LOG_ERROR, "## Unexpected error %s detected at %s:%u.",
								itron_strerror(ercd), file, line);
	test_finish();
}

/*
 *  �ХꥢƱ�����ѿ�
 */
static volatile uint_t local_phase[TNUM_PRCID];
static volatile uint_t global_phase;

/*
 *  �ХꥢƱ��
 */
void
barrier_sync(uint_t phase)
{
	volatile uint_t i, j;
	volatile uint_t flag;
	ID     prcid;

	SIL_PRE_LOC;

	/*
	 *  ����ߥ�å����֤�
	 */
	SIL_LOC_INT();

	/*
	 *  PRCID����
	 *  �ɤΤ褦�ʾ��֤Ǥ�����Ǥ���褦�� sil_get_pid() ����Ѥ��롥
	 */
	sil_get_pid(&prcid);

	local_phase[prcid - 1] = phase;

	if (prcid == TOPPERS_MASTER_PRCID) {
		do{
			flag = 0;
			for (i = 0; i < TNUM_PRCID; i++){
				if (local_phase[i] == phase){
					flag++;
				}
			}
			for (j = 0; j < 100; j++);
		}while (flag < TNUM_PRCID);
		global_phase = phase;
	}
	else {
		while (global_phase != phase) {
			for (j = 0; j < 100; j++);
		}
	}

	/*
	 *  ����ߥ�å����֤���
	 */
	SIL_UNL_INT();
}
