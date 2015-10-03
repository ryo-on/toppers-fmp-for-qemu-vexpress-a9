/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: arm_primecell_uart.h 961 2012-12-04 00:29:28Z ertl-sangorrin $
 */

/*
 *   ARM PrimCell UART�� �ʰ�SIO�ɥ饤��
 */

#ifndef TOPPERS_ARM_PRIMECELL_UART_H
#define TOPPERS_ARM_PRIMECELL_UART_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block	SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_RDY_SND    1U        /* ������ǽ������Хå� */
#define SIO_RDY_RCV    2U        /* �������Υ�����Хå� */

/*
 * UART�Υ쥸��������
 */
#define UART_DR     0x00  /* �ǡ����쥸���� */
#define UART_RSR    0x04  /* �������ơ������쥸���� */
#define UART_TECR   0x04  /* ���顼���ꥢ���쥸���� */
#define UART_FR     0x18  /* �ե饰�쥸���� */
#define UART_IBRD   0x24  /* �����ܡ��졼�ȥ쥸���� */
#define UART_FBRD   0x28  /* ʬ���ܡ��졼�ȥ쥸���� */
#define UART_LCR_H  0x2C  /* �饤�󥳥�ȥ���쥸����(H) */
#define UART_CR     0x30  /* ����ȥ���쥸���� */
#define UART_IFLS   0x34  /* �����FIFO��٥�����쥸���� */
#define UART_IMSC   0x38  /* ����ߥޥ����쥸���� */
#define UART_RIS    0x3C  /* ����ߥ��ơ������쥸���� */
#define UART_MIS    0x40  /* �ޥ�������ߥ��ơ������쥸���� */
#define UART_ICR    0x44  /* ����ߥ��ꥢ�쥸���� */

#define UART_LCR_H_FEN       0x10  /* FIFO��ͭ���� */
#define UART_LCR_H_WLEN_8    0x60  /* 8bitĹ       */

#define UART_CR_RXE    0x0200   /* ������ͭ���� */
#define UART_CR_TXE    0x0100   /* ������ͭ���� */
#define UART_CR_UARTEN 0x0001   /* UART��ͭ���� */

#define UART_FR_TXFF 0x20     /* �Хåե����ե�ʤ�"1"     */
#define UART_FR_RXFE 0x10     /* ͭ���ʥǡ������ʤ����"1" */

#define UART_IMSC_RXIM 0x0010 /* ��������ߥޥ���          */
#define UART_IMSC_TXIM 0x0020 /* ��������ߥޥ���          */


/*
 *  Reset the PrimeCell UART PL011 hardware to a default status
 */
extern void arm_primecell_uart_reset(ID siopid);

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void arm_primecell_uart_initialize(void);

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
extern bool_t arm_primecell_uart_openflag(ID siopid);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB *arm_primecell_uart_opn_por(ID siopid, intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void arm_primecell_uart_cls_por(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern bool_t arm_primecell_uart_snd_chr(SIOPCB *siopcb, char_t c);

/*
 * Put a character in polling mode
 */
extern void arm_primecell_uart_pol_putc(ID siopid, char_t c);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern int_t arm_primecell_uart_rcv_chr(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void  arm_primecell_uart_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void arm_primecell_uart_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
extern void arm_primecell_uart_isr(intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void arm_primecell_uart_irdy_snd(intptr_t exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void arm_primecell_uart_irdy_rcv(intptr_t exinf);

/*
 *  SIOPCB�ؤΥݥ��󥿤���ݡ����ֹ���֤�
 */
extern ID arm_primecell_uart_get_siopid(SIOPCB *p_siopcb);

/*
 *  ������ֹ���֤�
 */
extern uint8_t arm_primecell_uart_get_intno(SIOPCB *p_siopcb);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_ARM_PRIMECELL_UART_H */
