/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: mailbox.h 378 2009-09-11 16:21:24Z ertl-honda $
 */

/*
 *		�᡼��ܥå�����ǽ
 */

#ifndef TOPPERS_MAILBOX_H
#define TOPPERS_MAILBOX_H

#include <queue.h>

/*
 *  �᡼��ܥå���������֥�å�
 *
 *  ���ι�¤�Τϡ�Ʊ�����̿����֥������Ȥν�����֥�å��ζ�����ʬ
 *  ��WOBJINIB�ˤ��ĥ�ʥ��֥������Ȼظ�����ηѾ��������ˤ�����Τǡ�
 *  �ǽ�Υե�����ɤ����̤ˤʤäƤ��롥
 */
typedef struct mailbox_initialization_block {
	ATR			mbxatr;			/* �᡼��ܥå���°�� */
#if TTYPE_KLOCK == P_KLOCK
	LOCK		*p_obj_lock;		/* ��å��ؤΥݥ��� */
#endif /* TTYPE_KLOCK == P_KLOCK */
	PRI			maxmpri;		/* ��å�����ͥ���٤κ����� */
} MBXINIB;

/*
 *  �᡼��ܥå��������֥�å�
 *
 *  ���ι�¤�Τϡ�Ʊ�����̿����֥������Ȥδ����֥�å��ζ�����ʬ��WOBJCB��
 *  ���ĥ�ʥ��֥������Ȼظ�����ηѾ��������ˤ�����Τǡ��ǽ��2�Ĥ�
 *  �ե�����ɤ����̤ˤʤäƤ��롥
 *
 *  ��å��������塼����å�������ͥ���ٽ�ξ��ˤϡ�pk_last�ϻȤ��
 *  �����ޤ�����å��������塼�����ξ���pk_head��NULL�ξ��ˤˤ⡤
 *  pk_last��̵���Ǥ��롥
 */
typedef struct mailbox_control_block {
	QUEUE		wait_queue;		/* �᡼��ܥå����Ԥ����塼 */
	const MBXINIB *p_mbxinib;	/* ������֥�å��ؤΥݥ��� */
#if TTYPE_KLOCK == F_KLOCK
	LOCK		obj_lock;		/* ���֥������ȥ�å� */
#endif /* TTYPE_KLOCK == F_KLOCK */
	T_MSG		*pk_head;		/* ��Ƭ�Υ�å����� */
	T_MSG		*pk_last;		/* �����Υ�å����� */
} MBXCB;

/*
 *  �᡼��ܥå���ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mbxid;

/*
 *  �᡼��ܥå���������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MBXINIB	mbxinib_table[];

/*
 *  �᡼��ܥå��������֥�å��ؤΥݥ��󥿥ơ��֥��kernel_cfg.c��
 */
extern MBXCB* const		p_mbxcb_table[];

/*
 *  �᡼��ܥå��������֥�å�����᡼��ܥå���ID����Ф�����Υޥ���
 */
#define	MBXID(p_mbxcb)	((ID)((((p_mbxcb->p_mbxinib) - mbxinib_table) + TMIN_MBXID)))

/*
 *  �᡼��ܥå�����ǽ�ν����
 */
extern void	initialize_mailbox(void);

#endif /* TOPPERS_MAILBOX_H */
