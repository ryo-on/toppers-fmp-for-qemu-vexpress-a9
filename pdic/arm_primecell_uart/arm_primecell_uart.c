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
 *  @(#) $Id: arm_primecell_uart.c 961 2012-12-04 00:29:28Z ertl-sangorrin $
 */

/*
 *   ARM PrimeCell UART�� �ʰ�SIO�ɥ饤��
 */

#include <sil.h>
#include "target_syssvc.h"
#include "arm_primecell_uart.h"

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
    void  *dr;    /* �ǡ����쥸���� */
    void  *rsr;   /* �������ơ������쥸���� */
    void  *fr;    /* �ե饰�쥸���� */
    void  *ibrd;  /* �����ܡ��졼�ȥ쥸���� */
    void  *fbrd;  /* ʬ���ܡ��졼�ȥ쥸���� */
    void  *lcr_h; /* �饤�󥳥�ȥ���쥸����(H) */
    void  *cr;    /* ����ȥ���쥸���� */
    void  *imsc;  /* ����ߥޥ����쥸���� */
    uint8_t lcr_h_def; /* �饤�󥳥�ȥ���쥸������������ */
    uint8_t ibrd_def;  /* �����ܡ��졼�ȥ쥸������������ */
    uint8_t fbrd_def;  /* ʬ���ܡ��졼�ȥ쥸������������ */
    uint32_t intno;    /* ������ֹ� */
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
    const SIOPINIB  *siopinib;  /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
    intptr_t  exinf;            /* ��ĥ���� */
    bool_t    openflag;           /* �����ץ�Ѥߥե饰 */
    bool_t    sendflag;           /* ��������ߥ��͡��֥�ե饰 */
    bool_t    getready;           /* ʸ��������������� */
    bool_t    putready;           /* ʸ���������Ǥ������ */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
    {(void *)(UART0_BASE + UART_DR),
     (void *)(UART0_BASE + UART_RSR),
     (void *)(UART0_BASE + UART_FR),
     (void *)(UART0_BASE + UART_IBRD),
     (void *)(UART0_BASE + UART_FBRD),
     (void *)(UART0_BASE + UART_LCR_H),
     (void *)(UART0_BASE + UART_CR),
     (void *)(UART0_BASE + UART_IMSC),
     UART_LCR_H_WLEN_8,
     UART_IBRD_38400,
     UART_FBRD_38400,
     INTNO_SIO0,
    },
#if TNUM_PORT >= 2
    {(void *)(UART1_BASE + UART_DR),
     (void *)(UART1_BASE + UART_RSR),
     (void *)(UART1_BASE + UART_FR),
     (void *)(UART1_BASE + UART_IBRD),
     (void *)(UART1_BASE + UART_FBRD),
     (void *)(UART1_BASE + UART_LCR_H),
     (void *)(UART1_BASE + UART_CR),
     (void *)(UART1_BASE + UART_IMSC),
     UART_LCR_H_WLEN_8,
     UART_IBRD_38400,
     UART_FBRD_38400,
     INTNO_SIO1,
    },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
    {(void *)(UART2_BASE + UART_DR),
     (void *)(UART2_BASE + UART_RSR),
     (void *)(UART2_BASE + UART_FR),
     (void *)(UART2_BASE + UART_IBRD),
     (void *)(UART2_BASE + UART_FBRD),
     (void *)(UART2_BASE + UART_LCR_H),
     (void *)(UART2_BASE + UART_CR),
     (void *)(UART2_BASE + UART_IMSC),
     UART_LCR_H_WLEN_8,
     UART_IBRD_38400,
     UART_FBRD_38400,
     INTNO_SIO2,
    },
#endif /* TNUM_PORT >= 3 */
#if TNUM_PORT >= 4
    {(void *)(UART3_BASE + UART_DR),
     (void *)(UART3_BASE + UART_RSR),
     (void *)(UART3_BASE + UART_FR),
     (void *)(UART3_BASE + UART_IBRD),
     (void *)(UART3_BASE + UART_FBRD),
     (void *)(UART3_BASE + UART_LCR_H),
     (void *)(UART3_BASE + UART_CR),
     (void *)(UART3_BASE + UART_IMSC),
     UART_LCR_H_WLEN_8,
     UART_IBRD_38400,
     UART_FBRD_38400,
     INTNO_SIO3,
    }
#endif /* TNUM_PORT >= 4 */
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)	((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  ʸ��������Ǥ��뤫��
 */
Inline bool_t
arm_primecell_uart_getready(SIOPCB *p_siopcb)
{
    return((sil_rew_mem(p_siopcb->siopinib->fr) & UART_FR_RXFE) != UART_FR_RXFE);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline bool_t
arm_primecell_uart_putready(SIOPCB *p_siopcb)
{
    return((sil_rew_mem(p_siopcb->siopinib->fr) & UART_FR_TXFF) != UART_FR_TXFF);
}

/*
 *  ��������ʸ���μ�Ф�
 */
Inline char_t
arm_primecell_uart_getchar(SIOPCB *p_siopcb)
{
    return((char_t)sil_rew_mem(p_siopcb->siopinib->dr));
}

/*
 *  ��������ʸ���ν����
 */
Inline void
arm_primecell_uart_putchar(SIOPCB *p_siopcb, char_t c)
{
    sil_wrw_mem(p_siopcb->siopinib->dr, c);
}

/*
 *  ��������ߵ���
 */
Inline void
arm_primecell_uart_enable_send(SIOPCB *p_siopcb)
{
    sil_wrw_mem(p_siopcb->siopinib->imsc,
                sil_rew_mem(p_siopcb->siopinib->imsc) | UART_IMSC_TXIM);
}

/*
 *  ��������߶ػ�
 */
Inline void
arm_primecell_uart_disable_send(SIOPCB *p_siopcb)
{
    sil_wrw_mem(p_siopcb->siopinib->imsc,
				sil_rew_mem(p_siopcb->siopinib->imsc) & ~UART_IMSC_TXIM);
}


/*
 *  ��������ߵ���
 */
Inline void
arm_primecell_uart_enable_rcv(SIOPCB *p_siopcb)
{
	sil_wrw_mem(p_siopcb->siopinib->imsc,
				sil_rew_mem(p_siopcb->siopinib->imsc) | UART_IMSC_RXIM);
}

/*
 *  ��������߶ػ�
 */
Inline void
arm_primecell_uart_disable_rcv(SIOPCB *p_siopcb)
{
	sil_wrw_mem(p_siopcb->siopinib->imsc,
				sil_rew_mem(p_siopcb->siopinib->imsc) & ~UART_IMSC_RXIM);
}

/*
 *  SIO�ɥ饤�Фν����
 */
void
arm_primecell_uart_initialize(void)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		p_siopcb->siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
bool_t
arm_primecell_uart_openflag(ID siopid)
{
	SIOPCB          *p_siopcb;

	p_siopcb = get_siopcb(siopid);

	return(p_siopcb->openflag);
}

/*
 *  Reset the PrimeCell UART PL011 hardware to a default status
 */
void
arm_primecell_uart_reset(ID siopid)
{
        char_t __attribute__((__unused__)) c;  /* for removing warning */
        int index;

        index = INDEX_SIOP(siopid);

        /* UART��� */
        sil_wrw_mem(siopinib_table[index].cr, 0x00);

        /* ���顼�ե饰�򥯥ꥢ */
        sil_wrw_mem(siopinib_table[index].rsr, 0x00);

        /* FIFO����ˤ��� */
        while((sil_rew_mem(siopinib_table[index].fr) & UART_FR_RXFE) != UART_FR_RXFE) {
                /* �Хåե�������ɤ߹��� */
                c = sil_rew_mem(siopinib_table[index].dr);
        }

        /* �ܡ��졼�Ȥ����� */
        sil_wrw_mem(siopinib_table[index].ibrd, UART_IBRD_38400);
        sil_wrw_mem(siopinib_table[index].fbrd, UART_FBRD_38400);

        /* �ǡ����ե����ޥåȤȡ�FIFO�Υ⡼�ɤ����� */
        sil_wrw_mem(siopinib_table[index].lcr_h, UART_LCR_H_WLEN_8);

        /* UART�Ƴ� */
        sil_wrw_mem(siopinib_table[index].cr,
                    (sil_rew_mem(siopinib_table[index].cr)
                    | UART_CR_RXE | UART_CR_TXE | UART_CR_UARTEN));
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
arm_primecell_uart_opn_por(ID siopid, intptr_t exinf)
{
        SIOPCB *p_siopcb;

        arm_primecell_uart_reset(siopid);

        p_siopcb = get_siopcb(siopid);
        p_siopcb->exinf = exinf;
        p_siopcb->getready = p_siopcb->putready = false;
        p_siopcb->openflag = true;

        return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
arm_primecell_uart_cls_por(SIOPCB *p_siopcb)
{
    /* UART��� */
	sil_wrw_mem(p_siopcb->siopinib->cr, 0x00);
    p_siopcb->openflag = false;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
arm_primecell_uart_snd_chr(SIOPCB *p_siopcb, char_t c)
{
    if (arm_primecell_uart_putready(p_siopcb)){
        arm_primecell_uart_putchar(p_siopcb, c);
        return(true);
    }
    return(false);
}

/*
 * Put a character in polling mode
 */
void
arm_primecell_uart_pol_putc(ID siopid, char_t c)
{
    int index = INDEX_SIOP(siopid);

    /* Delay until the buffer has space */
    while((sil_rew_mem(siopinib_table[index].fr) & UART_FR_TXFF) == UART_FR_TXFF);
    /* Write the character to the data register */
    sil_wrw_mem(siopinib_table[index].dr, c);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int_t
arm_primecell_uart_rcv_chr(SIOPCB *p_siopcb)
{
	if (arm_primecell_uart_getready(p_siopcb)) {
		return((int_t)(uint8_t) arm_primecell_uart_getchar(p_siopcb));
	}
	return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
arm_primecell_uart_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
    switch (cbrtn) {
      case SIO_RDY_SND:
        arm_primecell_uart_enable_send(p_siopcb);
        break;
      case SIO_RDY_RCV:
        arm_primecell_uart_enable_rcv(p_siopcb);
        break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
arm_primecell_uart_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
    switch (cbrtn) {
      case SIO_RDY_SND:
        arm_primecell_uart_disable_send(p_siopcb);
        break;
      case SIO_RDY_RCV:
        arm_primecell_uart_disable_rcv(p_siopcb);
        break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
arm_primecell_uart_isr_siop(SIOPCB *p_siopcb)
{
    if (arm_primecell_uart_getready(p_siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        arm_primecell_uart_irdy_rcv(p_siopcb->exinf);
    }
    if (arm_primecell_uart_putready(p_siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        arm_primecell_uart_irdy_snd(p_siopcb->exinf);
    }
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
arm_primecell_uart_isr(intptr_t exinf)
{
    arm_primecell_uart_isr_siop(get_siopcb(exinf));
}

/*
 *  SIOPCB�ؤΥݥ��󥿤���ݡ����ֹ���֤�
 */
ID
arm_primecell_uart_get_siopid(SIOPCB *p_siopcb)
{
	return (ID)((p_siopcb - siopcb_table) + 1);
}

/*
 *  ������ֹ���֤�
 */
uint8_t
arm_primecell_uart_get_intno(SIOPCB *p_siopcb)
{
	return p_siopcb->siopinib->intno;
}
