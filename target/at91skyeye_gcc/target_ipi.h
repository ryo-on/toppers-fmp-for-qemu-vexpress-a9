/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_ipi.h 572 2010-04-20 08:08:09Z ertl-honda $
 */

/*
 *  �ץ��å��ֳ���ߥɥ饤�С�AT91SKYEYE�ѡ�
 */

#ifndef TOPPERS_TARGET_IPI_H
#define TOPPERS_TARGET_IPI_H

#include "at91skyeye.h"

/*
 *  ������ֹ�ȳ���ߥϥ�ɥ��ֹ�
 */
#define INTNO_IPI_PRC1  (0x10000|IRQ_IPI)  /* ������ֹ� */
#define INHNO_IPI_PRC1  (0x10000|IRQ_IPI)  /* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC1 -2                 /* �����ͥ���� */

#define INTNO_IPI_PRC2  (0x20000|IRQ_IPI)  /* ������ֹ� */
#define INHNO_IPI_PRC2  (0x20000|IRQ_IPI)  /* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC2 -2                 /* �����ͥ���� */

#define INTNO_IPI_PRC3  (0x30000|IRQ_IPI)  /* ������ֹ� */
#define INHNO_IPI_PRC3  (0x30000|IRQ_IPI)  /* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC3 -2                 /* �����ͥ���� */

#define INTNO_IPI_PRC4  (0x40000|IRQ_IPI)  /* ������ֹ� */
#define INHNO_IPI_PRC4  (0x40000|IRQ_IPI)  /* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC4 -2                 /* �����ͥ���� */

/*
 * �ץ��å��ֳ���ߤ˻��Ѥ���COM��ID
 */  
#define IPI_COMID   0

/*
 *  �ץ��å��ֳ���ߤ�ȯ��
 */
Inline void
target_ipi_raise(uint_t procid)
{
	sil_wrw_mem((void *)IPI_REG, ((procid << 16) | IPI_COMID));
}

/*
 *  �ץ��å��ֳ���ߤΥ��ꥢ
 */
Inline void
target_ipi_clear(void)
{

}

#endif /* TOPPERS_TARGET_IPI_H */
