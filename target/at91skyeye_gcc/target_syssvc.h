/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_syssvc.h 790 2011-03-03 15:40:19Z ertl-honda $
 */

/*
 *  �����ƥॵ���ӥ��Υ��åװ�¸����AT91SKYEYE�ѡ�
 *
 *  �����ƥॵ���ӥ��Υ��åװ�¸���Υ��󥯥롼�ɥե����롥���Υե������
 *  ���Ƥϡ�����ݡ��ͥ�ȵ��ҥե�����˵��Ҥ��졤���Υե������̵���ʤ�
 *  �����ߡ�
 */

#ifndef TOPPERS_TARGET_SYSSVC_H
#define TOPPERS_TARGET_SYSSVC_H

#include "at91skyeye.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define TARGET_NAME    "AT91SKYEYE(ARM)"

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 *
 *  �������åȰ�¸����ˡ�ǡ�ʸ��c��ɽ��/����/��¸���롥
 */
extern void	target_fput_log(char_t c);

#ifdef TOPPERS_ENABLE_TRACE
/*
 *  �ȥ졼�����Υե��������
 */
extern void	target_fput_log_file(char_t c);
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ���ꥢ��ݡ��ȿ������
 */
#define TNUM_PORT    TNUM_PRCID    /* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

/*
 *  �����ƥ����������Ϣ����������
 *
 *  �ǥե�����ͤ��̤ꡥ
 */

/*
 *  �����ƥ�������������Ѥ����ѿ��Υ�����������
 */
#define SEC_LOGTASK(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc1p_logtask"),nocommon))
#define SEC_PRC1_LOGTASK(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc1p_logtask"),nocommon))
#define SEC_PRC2_LOGTASK(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc2p_logtask"),nocommon))
#define SEC_PRC3_LOGTASK(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc3p_logtask"),nocommon))
#define SEC_PRC4_LOGTASK(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc4p_logtask"),nocommon))

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф����Ѥ����ѿ��Υ�����������
 */
#define SEC_SERIAL1(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc1p_serial"),nocommon))
#define SEC_SERIAL2(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc2p_serial"),nocommon))
#define SEC_SERIAL3(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc3p_serial"),nocommon))
#define SEC_SERIAL4(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc4p_serial"),nocommon))

/*
 *  �����ƥ����ǽ�����Ѥ����ѿ��Υ�����������
 */
#define SEC_SYSLOG(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc1p_syslogcb"),nocommon))
#define SEC_PRC1_SYSLOG(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc1p_syslogcb"),nocommon))
#define SEC_PRC2_SYSLOG(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc2p_syslogcb"),nocommon))
#define SEC_PRC3_SYSLOG(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc3p_syslogcb"),nocommon))
#define SEC_PRC4_SYSLOG(type, variable) \
			type variable __attribute__((section(".bss._kernel_prc4p_syslogcb"),nocommon))

#endif /* TOPPERS_TARGET_SYSSVC_H */
