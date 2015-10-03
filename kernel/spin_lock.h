/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
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
 *  @(#) $Id: spin_lock.h 771 2011-01-21 02:06:07Z ertl-honda $
 */

/*
 *		���ԥ��å���ǽ
 */

#ifndef TOPPERS_SPIN_LOCK_H
#define TOPPERS_SPIN_LOCK_H

#if TTYPE_SPN == NATIVE_SPN

/*
 *  ���ԥ��å�������֥�å�
 */
typedef struct spin_lock_initialization_block {
	ATR			spnatr;			/* ���ԥ��å�°�� */
} SPNINIB;

/*
 *  ���ԥ��å������֥�å�
 */
typedef struct spin_lock_control_block {
	SPNLOCK		spn_lock;		/* ��å�����о� */
	const SPNINIB *p_spninib;	/* ������֥�å��ؤΥݥ��� */
	bool_t		lock_flg;		/* ���ԥ��å��θ��ߤΥ�å����� */
} SPNCB;

#else /* TTYPE_SPN == EMULATE_SPN */

#if TTYPE_KLOCK == F_KLOCK
#error Can not use EMULATE_SPN with F_KLOCK. Use NATIVE_SPN.
#endif /* TTYPE_KLOCK == F_KLOCK */

/*
 *  ���ԥ��å�������֥�å�
 */
typedef struct spin_lock_initialization_block {
	ATR			spnatr;			/* ���ԥ��å�°�� */
#if TTYPE_KLOCK == P_KLOCK
	LOCK		*p_obj_lock;		/* ��å��ؤΥݥ��� */
#endif /* TTYPE_KLOCK == P_KLOCK */
} SPNINIB;

/*
 *  ���ԥ��å������֥�å�
 */
typedef struct spin_lock_control_block {
	QUEUE		dummy;			/* ¾��Ʊ�����֥������Ȥ�Ʊ���ޥ����Ȥ�����Υ��ߡ� */        
	const SPNINIB *p_spninib;	/* ������֥�å��ؤΥݥ��� */
	bool_t		lock_flg;		/* ���ԥ��å��θ��ߤΥ�å����� */
} SPNCB;

#endif /* TTYPE_SPN == EMULATE_SPN */

/*
 *  ���ԥ��å�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const SPNINIB	spninib_table[];

/*
 *  ���ԥ��å������֥�å��ؤΥݥ��󥿥ơ��֥��kernel_cfg.c��
 */
extern SPNCB* const	p_spncb_table[];

/*
 *  ���ԥ��å�ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_spnid;

/*
 *  ���ԥ��å���ǽ�ν����
 */
extern void	initialize_spin_lock(void);

/*
 *  ���ԥ��å��ζ���������PCB���lockspnid���оݤˤ����
 */
extern void	force_unlock_spin(PCB *my_p_pcb);

#endif /* TOPPERS_SPIN_LOCK_H */
