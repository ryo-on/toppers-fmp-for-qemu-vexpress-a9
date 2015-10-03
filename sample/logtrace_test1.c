/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: logtrace_test1.c 63 2009-01-09 00:30:47Z ertl-honda $
 */

/* 
 *		�ȥ졼��������ץ�ץ����(1)������
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "logtrace_test1.h"
#include "logtrace/trace_config.h"

extern void target_fput_log(char_t c);

/*
 *  �����ӥ�������Υ��顼�Υ�����
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

/*
 *  �¹Լ¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
volatile char_t	message[3];

/*
 *  �롼�ײ��
 */
ulong_t	task_loop;		/* ��������ǤΥ롼�ײ�� */
ulong_t	tex_loop;		/* �㳰�����롼������ǤΥ롼�ײ�� */

/*
 *  �¹Լ¹Ԥ���륿����
 */
void task(intptr_t exinf)
{
	int_t		tskno = (int_t) exinf;
	char_t		c;

	SVC_PERROR(ena_tex());
	while (1) {
		c = message[tskno-1];
		if (message[tskno-1] != 0) {
			message[tskno-1] = 0;
		}
		switch (c) {
		case 'e':
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			SVC_PERROR(ext_tsk());
			assert(0);
		case 's':
			syslog(LOG_INFO, "#%d#slp_tsk()", tskno);
			SVC_PERROR(slp_tsk());
			break;
		case 'S':
			syslog(LOG_INFO, "#%d#tslp_tsk(10000)", tskno);
			SVC_PERROR(tslp_tsk(10000));
			break;
		case 'd':
			syslog(LOG_INFO, "#%d#dly_tsk(10000)", tskno);
			SVC_PERROR(dly_tsk(10000));
			break;
		case 'y':
			syslog(LOG_INFO, "#%d#dis_tex()", tskno);
			SVC_PERROR(dis_tex());
			break;
		case 'Y':
			syslog(LOG_INFO, "#%d#ena_tex()", tskno);
			SVC_PERROR(ena_tex());
			break;
		case 'M':
			syslog(LOG_INFO, "#%d#mig_tsk(PE1)", tskno);
			SVC_PERROR(mig_tsk(0, 1));
			break;
		case 'm':
			syslog(LOG_INFO, "#%d#mig_tsk(PE2)", tskno);
			SVC_PERROR(mig_tsk(0, 2));
			break;
#ifdef CPUEXC1
		case 'z':
			syslog(LOG_NOTICE, "#%d#raise CPU exception", tskno);
			RAISE_CPU_EXCEPTION;
			break;
		case 'Z':
			SVC_PERROR(loc_cpu());
			syslog(LOG_NOTICE, "#%d#raise CPU exception", tskno);
			RAISE_CPU_EXCEPTION;
			SVC_PERROR(unl_cpu());
			break;
#endif /* CPUEXC1 */
		default:
			break;
		}
	}
}

/*
 *  �¹Ԥ��Ƽ¹Ԥ���륿�����ѤΥ������㳰�����롼����
 */
void tex_routine(TEXPTN texptn, intptr_t exinf)
{
	volatile ulong_t	i;
	int_t	tskno = (int_t) exinf;

	syslog(LOG_NOTICE, "task%d receives exception 0x%04x.", tskno, texptn);
	for (i = 0; i < tex_loop; i++);

	if ((texptn & 0x8000U) != 0U) {
		syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
		SVC_PERROR(ext_tsk());
		assert(0);
	}
}

/*
 *  CPU�㳰�ϥ�ɥ�
 */
#ifdef CPUEXC1

void
cpuexc_handler(void *p_excinf)
{
	ID		tskid;

	syslog(LOG_NOTICE, "CPU exception handler (p_excinf = %08p).", p_excinf);
	if (sns_ctx() != true) {
		syslog(LOG_WARNING,
					"sns_ctx() is not true in CPU exception handler.");
	}
	if (sns_dpn() != true) {
		syslog(LOG_WARNING,
					"sns_dpn() is not true in CPU exception handler.");
	}
	syslog(LOG_INFO, "sns_loc = %d sns_dsp = %d sns_tex = %d",
									sns_loc(), sns_dsp(), sns_tex());
	syslog(LOG_INFO, "xsns_dpn = %d xsns_xpn = %d",
									xsns_dpn(p_excinf), xsns_xpn(p_excinf));

	if (xsns_xpn(p_excinf)) {
		syslog(LOG_NOTICE, "Sample program ends with exception.");
		SVC_PERROR(ext_ker());
		assert(0);
	}

	SVC_PERROR(iget_tid(&tskid));
	SVC_PERROR(iras_tex(tskid, 0x8000U));
}

#endif /* CPUEXC1 */

/*
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void cyclic_handler(intptr_t exinf)
{
	SVC_PERROR(irot_rdq(HIGH_PRIORITY));
	SVC_PERROR(irot_rdq(MID_PRIORITY));
	SVC_PERROR(irot_rdq(LOW_PRIORITY));
}

/*
 *  ���顼��ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void alarm_handler(intptr_t exinf)
{
	SVC_PERROR(irot_rdq(HIGH_PRIORITY));
	SVC_PERROR(irot_rdq(MID_PRIORITY));
	SVC_PERROR(irot_rdq(LOW_PRIORITY));
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(intptr_t exinf)
{
	ER_UINT	ercd; 

	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int_t) exinf);

	/*
	 *  ���ꥢ��ݡ��Ȥν����
	 *
	 *  �����ƥ����������Ʊ�����ꥢ��ݡ��Ȥ�Ȥ����ʤɡ����ꥢ��
	 *  �ݡ��Ȥ������ץ�Ѥߤξ��ˤϤ�����E_OBJ���顼�ˤʤ뤬���پ��
	 *  �ʤ���
	 */
	ercd = serial_opn_por(TASK_PORTID_PRC1);
	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
									itron_strerror(ercd), SERCD(ercd));
	}
	SVC_PERROR(serial_ctl_por(TASK_PORTID_PRC1,
							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*
	 *  �������ε�ư
	 */
	SVC_PERROR(act_tsk(TASK1));
	SVC_PERROR(act_tsk(TASK2));
	SVC_PERROR(act_tsk(TASK3));

	dly_tsk(10);
	rot_rdq(MID_PRIORITY); /* TASK2 ���ڤ��ؤ� */
	dly_tsk(10);
	rot_rdq(MID_PRIORITY); /* TASK3 ���ڤ��ؤ� */
	dly_tsk(10);
	rot_rdq(MID_PRIORITY); /* TASK1 ���ڤ��ؤ� */

	dly_tsk(10);
	message[0] = 's';  /* TASK1 �Ԥ����֤� */
	dly_tsk(10);
	message[1] = 's';  /* TASK2 �Ԥ����֤� */
	dly_tsk(10);
	message[2] = 's';  /* TASK3 �Ԥ����֤� */

	dly_tsk(10);
	wup_tsk(TASK1);    /* TASK1 �¹Բ�ǽ���֤� */
	wup_tsk(TASK2);    /* TASK2 �¹Բ�ǽ���֤� */
	wup_tsk(TASK3);    /* TASK3 �¹Բ�ǽ���֤� */

	dly_tsk(10);
	mig_tsk(TASK1, 2); /* TASK1 ��PE2�إޥ����졼�� */
	dly_tsk(10);
	mig_tsk(TASK2, 2); /* TASK2 ��PE2�إޥ����졼�� */
	dly_tsk(10);
	mig_tsk(TASK3, 2); /* TASK3 ��PE2�إޥ����졼�� */

	dly_tsk(10);
	message[0] = 'M';  /* TASK1 ��PE1�إޥ����졼�� */
	dly_tsk(10);
	message[1] = 'M';  /* TASK2 ��PE1�إޥ����졼�� */  
	dly_tsk(10);
	message[2] = 'M';  /* TASK3 ��PE1�إޥ����졼�� */  

	dly_tsk(10);
	message[0] = 'e';  /* TASK1 ��λ */
	dly_tsk(10);
	message[1] = 'e';  /* TASK2 ��λ */
	dly_tsk(10);
	message[2] = 'e';  /* TASK3 ��λ */

	/*
	 *  �����ϥ�ɥ�ε�ư
	 */
	sta_cyc(CYCHDR1);

	dly_tsk(50);

	msta_cyc(CYCHDR1, 2); /* PE2�إޥ����졼�� */

	dly_tsk(50);

	msta_cyc(CYCHDR1, 1); /* PE1�إޥ����졼�� */

	dly_tsk(50);

	stp_cyc(CYCHDR1);

	/*
	 *  ���顼��ϥ�ɥ�ε�ư
	 */
	sta_alm(ALMHDR1, 10);

	dly_tsk(20);

	msta_alm(ALMHDR1, 10, 2); /* PE2�إޥ����졼�� */

	dly_tsk(20);

	msta_alm(ALMHDR1, 10, 1); /* PE1�إޥ����졼�� */

	dly_tsk(20);

	ext_ker();
}
