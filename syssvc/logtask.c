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
 *  @(#) $Id: logtask.c 569 2010-04-15 02:23:27Z ertl-honda $
 */

/*
 *		�����ƥ��������
 */

#include <kernel.h>
#include <t_syslog.h>
#include <log_output.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "logtask.h"

/*
 *  �����ƥ�����������ѿ����֤Υǥ��ե�������
 */
#ifndef SEC_LOGTASK
#define SEC_LOGTASK(type, variable) type variable
#endif /* SEC_PREC1_SYSLOG */

#ifndef SEC_LOGTASK_BEGIN
#define SEC_LOGTASK_BEGIN
#endif /* SEC_LOGTASK_BEGIN */

#ifndef SEC_LOGTASK_END
#define SEC_LOGTASK_END
#endif /* SEC_LOGTASK_END */

#ifndef SEC_PRC1_LOGTASK
#define SEC_PRC1_LOGTASK(type, variable) type variable
#endif /* SEC_PREC1_SYSLOG */

#ifndef SEC_PRC1_LOGTASK_BEGIN
#define SEC_PRC1_LOGTASK_BEGIN
#endif /* SEC_PRC1_LOGTASK_BEGIN */

#ifndef SEC_PRC1_LOGTASK_END
#define SEC_PRC1_LOGTASK_END
#endif /* SEC_PREC1_LOGTASK_END */

#ifndef SEC_PRC2_LOGTASK
#define SEC_PRC2_LOGTASK(type, variable) type variable
#endif /* SEC_PREC2_SYSLOG */

#ifndef SEC_PRC2_LOGTASK_BEGIN
#define SEC_PRC2_LOGTASK_BEGIN
#endif /* SEC_PRC2_LOGTASK_BEGIN */

#ifndef SEC_PRC2_LOGTASK_END
#define SEC_PRC2_LOGTASK_END
#endif /* SEC_PREC2_LOGTASK_END */

#ifndef SEC_PRC3_LOGTASK
#define SEC_PRC3_LOGTASK(type, variable) type variable
#endif /* SEC_PREC3_SYSLOG */

#ifndef SEC_PRC3_LOGTASK_BEGIN
#define SEC_PRC3_LOGTASK_BEGIN
#endif /* SEC_PRC3_LOGTASK_BEGIN */

#ifndef SEC_PRC3_LOGTASK_END
#define SEC_PRC3_LOGTASK_END
#endif /* SEC_PREC3_LOGTASK_END */

#ifndef SEC_PRC4_LOGTASK
#define SEC_PRC4_LOGTASK(type, variable) type variable
#endif /* SEC_PREC4_SYSLOG */

#ifndef SEC_PRC4_LOGTASK_BEGIN
#define SEC_PRC4_LOGTASK_BEGIN
#endif /* SEC_PRC4_LOGTASK_BEGIN */

#ifndef SEC_PRC4_LOGTASK_END
#define SEC_PRC4_LOGTASK_END
#endif /* SEC_PREC4_LOGTASK_END */

/*
 *  �����ƥ���������ν�����Υݡ���ID�Υơ��֥�
 */
#ifdef G_SYSLOG

SEC_LOGTASK_BEGIN
SEC_LOGTASK(static ID, logtask_portid);
SEC_LOGTASK_END

#else  /* G_SYSLOG */

#if TNUM_PRCID >= 1
SEC_PRC1_LOGTASK_BEGIN
SEC_PRC1_LOGTASK(static ID, logtask_portid_prc1);
SEC_PRC1_LOGTASK_END
#endif /* TNUM_PRCID >= 1 */

#if TNUM_PRCID >= 2
SEC_PRC2_LOGTASK_BEGIN
SEC_PRC2_LOGTASK(static ID, logtask_portid_prc2);
SEC_PRC2_LOGTASK_END
#endif /* TNUM_PRCID >= 2 */

#if TNUM_PRCID >= 3
SEC_PRC3_LOGTASK_BEGIN
SEC_PRC3_LOGTASK(static ID, logtask_portid_prc3);
SEC_PRC3_LOGTASK_END
#endif /* TNUM_PRCID >= 3 */

#if TNUM_PRCID >= 4
SEC_PRC4_LOGTASK_BEGIN
SEC_PRC4_LOGTASK(static ID, logtask_portid_prc4);
SEC_PRC4_LOGTASK_END
#endif /* TNUM_PRCID >= 4 */

#if TNUM_PRCID >= 5
#error Logtask Not Support more than 5 processor!
#endif /* TNUM_PRCID >= 5 */

static ID* const	p_logtask_portid_table[] = {
#if TNUM_PRCID >= 1
	&logtask_portid_prc1,
#endif /* TNUM_PRCID >= 1 */
#if TNUM_PRCID >= 2
	&logtask_portid_prc2,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	&logtask_portid_prc3,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	&logtask_portid_prc4,
#endif /* TNUM_PRCID >= 4 */
};
#endif /* G_SYSLOG */

/*
 *  �������Υݡ���ID�ؤΥ��������ޥ���
 */
#ifdef G_SYSLOG

Inline ID
get_my_logtask_portid(void)
{
	return logtask_portid;
}

Inline void
set_my_logtask_portid(ID id)
{
	logtask_portid = id;
}

#else  /* G_SYSLOG */

Inline ID
get_my_logtask_portid(void)
{
	ID prcid;
	sil_get_pid(&prcid);

	return *(p_logtask_portid_table[prcid - 1]);
}

Inline void
set_my_logtask_portid(ID id)
{
	ID prcid;
	sil_get_pid(&prcid);

	*(p_logtask_portid_table[prcid - 1]) = id;
}

#endif /* G_SYSLOG */

/*
 *  ���ꥢ�륤�󥿥ե������ؤ�1ʸ������
 */
static void
logtask_putc(char_t c)
{
	ID my_logtask_portid = get_my_logtask_portid();
	
	serial_wri_dat(my_logtask_portid, &c, 1);
}

/*
 *  �����ƥ�����Ϥ��Ԥ���碌
 */
ER
logtask_flush(uint_t count)
{
	T_SYSLOG_RLOG	rlog;
	T_SERIAL_RPOR	rpor;
	ER				ercd, rercd;
	ID my_logtask_portid = get_my_logtask_portid();

	if (sns_dpn()) {
		ercd = E_CTX;
	}
	else {
		for (;;) {
			if (syslog_ref_log(&rlog) < 0) {
				ercd = E_SYS;
				goto error_exit;
			}
			if (rlog.count <= count) {
				if (count == 0U) {
					/*
					 *  count��0�ξ��ˤϡ����ꥢ��Хåե����������
					 *  ǧ���롥
					 */
					if (serial_ref_por(my_logtask_portid, &rpor) < 0) {
						ercd = E_SYS;
						goto error_exit;
					}
					if (rpor.wricnt == 0U) {
						ercd = E_OK;
						goto error_exit;
					}
				}
				else {
					ercd = E_OK;
					goto error_exit;
				}
			}

			/*
			 *  LOGTASK_FLUSH_WAIT�ߥ����Ԥġ�
			 */
			rercd = dly_tsk(LOGTASK_FLUSH_WAIT);
			if (rercd < 0) {
				ercd = (rercd == E_RLWAI) ? rercd : E_SYS;
				goto error_exit;
			}
		}
	}

  error_exit:
	return(ercd);
}

/*
 *  �����ƥ��������������
 */
void
logtask_main(intptr_t exinf)
{
	SYSLOG	syslog;
	uint_t	lost;
	ER_UINT	rercd;
	ID my_logtask_portid;

	my_logtask_portid = (ID) exinf;
	set_my_logtask_portid(my_logtask_portid);
	serial_opn_por(my_logtask_portid);
	syslog_msk_log(LOG_UPTO(LOG_NOTICE), LOG_UPTO(LOG_EMERG));
	syslog_1(LOG_NOTICE, "System logging task is started on port %d.",
													my_logtask_portid);
	for (;;) {
		lost = 0U;
		while ((rercd = syslog_rea_log(&syslog)) >= 0) {
			lost += (uint_t) rercd;
			if (syslog.logtype >= LOG_TYPE_COMMENT) {
				if (lost > 0U) {
					syslog_lostmsg(lost, logtask_putc);
					lost = 0U;
				}
				syslog_print(&syslog, logtask_putc);
				logtask_putc('\n');
			}
		}
		if (lost > 0U) {
			syslog_lostmsg(lost, logtask_putc);
		}
		if(E_OK != dly_tsk(LOGTASK_INTERVAL)){
			syslog_0(LOG_NOTICE, "syslog : Error dly_tsk() !");
		}
	}
}

/*
 *  �����ƥ���������ν�λ����
 */
void
logtask_terminate(intptr_t exinf)
{
	char_t	c;
	SYSLOG	syslog;
	bool_t	msgflg = false;
	ER_UINT	rercd;
	ID my_logtask_portid = get_my_logtask_portid();

	/*
	 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф������Хåե������Ѥ��줿�ǡ���
	 *  �����٥���ϵ�ǽ���Ѥ��ƽ��Ϥ��롥
	 */
	while (serial_get_chr(my_logtask_portid, &c)) {
		target_fput_log(c);
	}

	/*
	 *  ���Хåե��˵�Ͽ���줿����������٥���ϵ�ǽ���Ѥ��ƽ�
	 *  �Ϥ��롥
	 */
	while ((rercd = syslog_rea_log(&syslog)) >= 0) {
		if (!msgflg) {
			/*
			 *  ���Хåե��˻Ĥä�������Ǥ��뤳�Ȥ򼨤�ʸ������
			 *  �Ϥ��롥
			 */
			syslog_printf("-- buffered messages --\n", NULL, target_fput_log);
			msgflg = true;
		}
		if (rercd > 0) {
			syslog_lostmsg((uint_t) rercd, target_fput_log);
		}
		if (syslog.logtype >= LOG_TYPE_COMMENT) {
			syslog_print(&syslog, target_fput_log);
			target_fput_log('\n');
		}
	}
}
