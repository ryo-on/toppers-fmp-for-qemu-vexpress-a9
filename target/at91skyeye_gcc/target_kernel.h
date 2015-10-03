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
 *  @(#) $Id: target_kernel.h 739 2010-11-24 04:14:37Z ertl-honda $
 */

/*
 *  kernel.h�Υ��åװ�¸����AT91SKYEYE�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h�ǥ��󥯥롼�ɤ���롥¾�Υե�
 *  ���뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥󥯥롼��
 *  �������ˡ�t_stddef.h�����󥯥롼�ɤ����Τǡ������˰�¸���Ƥ��
 *  ����
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  ������¸�Ƕ��̤������ARM�ѡ�
 */
#include "arm_gcc/common/core_kernel.h"

/*
 *  �����ƥ����δ�������
 */
#if !defined(TOPPERS_SYSTIM_LOCAL) && !defined(TOPPERS_SYSTIM_GLOBAL)
#define TOPPERS_SYSTIM_LOCAL			/* �����륿���������Υ����ƥ���� */
//#define TOPPERS_SYSTIM_GLOBAL			/* �����Х륿���������Υ����ƥ���� */
#endif /* defined(TOPPERS_SYSTIM_LOCAL) || defined(TOPPERS_SYSTIM_GLOBAL) */

/*
 *  �������åȰ�¸���ǥ��ݡ��ȤǤ��뵡ǽ
 */
#define TOPPERS_TARGET_SUPPORT_DIS_INT		/* dis_int */
#define TOPPERS_TARGET_SUPPORT_ENA_INT		/* ena_int */
#ifdef TOPPERS_SYSTIM_LOCAL
#define TOPPERS_TARGET_SUPPORT_GET_UTM		/* get_utm */
#endif /* TOPPERS_SYSTIM_LOCAL */

/*
 *  �����Х륿�����������Υ����ƥ��������ץ��å���ID��
 */
#ifndef TOPPERS_SYSTIM_PRCID
#define TOPPERS_SYSTIM_PRCID  1
#endif /* TOPPERS_SYSTIM_PRCID */

/*
 *  �ޥ����ץ��å���ID��
 */
#ifndef TOPPERS_MASTER_PRCID
#define TOPPERS_MASTER_PRCID  1
#endif  /* TOPPERS_MASTER_PRCID */

/*
 * �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 *  �����ͥ���٤��ϰ�
 */
#define TMIN_INTPRI   (-7)        /* �����ͥ���٤κǾ��͡ʺǹ��͡�*/
#define TMAX_INTPRI   (-1)        /* �����ͥ���٤κ����͡ʺ����͡�*/

/*
 *  ������ƥ��å������
 */
#define TIC_NUME     1U            /* ������ƥ��å��μ�����ʬ�� */
#define TIC_DENO     1U            /* ������ƥ��å��μ�����ʬ�� */

/*
 *  ������°��
 */
#define	TA_POSEDGE		0x02U		/* �ݥ��ƥ��֥��å��ȥꥬ */
#define	TA_LOWLEVEL		0x00U		/* ����٥�ȥꥬ */
#define	TA_HIGHLEVEL	0x08U		/* �ϥ���٥�ȥꥬ */

/*
 *  ���饹��ID���
 */
#define TCL_1   1
#define TCL_2   2
#define TCL_3   3
#define TCL_4   4
#define TCL_1_ONLY   5
#define TCL_2_ONLY   6 
#define TCL_3_ONLY   7
#define TCL_4_ONLY   8
#define TCL_SYSTIM_PRC   9

#endif /* TOPPERS_TARGET_KERNEL_H */
