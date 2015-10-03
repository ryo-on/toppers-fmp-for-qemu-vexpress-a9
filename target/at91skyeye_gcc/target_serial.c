/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007 by GJ Business Division RICOH COMPANY,LTD. JAPAN  
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
 *  @(#) $Id: target_serial.c 926 2012-03-30 10:18:29Z ertl-honda $
 */

/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�AT91SKYEYE�ѡ�
 */

#include <kernel.h>
#include <t_syslog.h>
#include "at91skyeye.h"
#include "target_serial.h"
#include <target_syssvc.h>

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block 
{
	void* us_thr;
	void* us_rpr;
	void* us_rcr;
	void* us_csr;
	uint_t intno;
}
SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block 
{
	const SIOPINIB  *p_siopinib;  /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	intptr_t        exinf;        /* ��ĥ���� */
	uint8_t usart_rev_buf;        /* �����ѥХåե� */
	bool_t    openflag;           /* �����ץ�Ѥߥե饰 */
	bool_t    sendflag;           /* ��������ߥ��͡��֥�ե饰 */
	bool_t    getready;           /* ʸ��������������� */
	bool_t    putready;           /* ʸ���������Ǥ������ */
};

/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
static const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{
		(void*)(USART0_THR),
		(void*)(USART0_RPR),
		(void*)(USART0_RCR),
		(void*)(USART0_CSR),
		(uint_t)(INTNO_SIO_PRC1),
	},
#if TNUM_SIOP >= 2
	{
		(void*)(USART0_THR),
		(void*)(USART0_RPR),
		(void*)(USART0_RCR),
		(void*)(USART0_CSR),
		(uint_t)(INTNO_SIO_PRC2),
	},
#endif /* TNUM_SIOP >= 2 */
#if TNUM_SIOP >= 3
	{
		(void*)(USART0_THR),
		(void*)(USART0_RPR),
		(void*)(USART0_RCR),
		(void*)(USART0_CSR),
		(uint_t)(INTNO_SIO_PRC3),
	},
#endif /* TNUM_SIOP >= 3 */
#if TNUM_PORT >= 4
	{
		(void*)(USART0_THR),
		(void*)(USART0_RPR),
		(void*)(USART0_RCR),
		(void*)(USART0_CSR),
		(uint_t)(INTNO_SIO_PRC4),
	}
#endif /* TNUM_SIOP >= 4 */
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SEC_SERIAL1(static SIOPCB, siopcb1);
#if TNUM_SIOP >= 2
SEC_SERIAL2(static SIOPCB, siopcb2);
#endif /* TNUM_SIOP >= 2 */
#if TNUM_SIOP >= 3
SEC_SERIAL3(static SIOPCB, siopcb3);
#endif /* TNUM_SIOP >= 3 */
#if TNUM_SIOP >= 4
SEC_SERIAL4(static SIOPCB, siopcb4);
#endif /* TNUM_SIOP >= 4 */

static SIOPCB* const p_siopcb_table[TNUM_SIOP] = {
	&siopcb1
#if TNUM_SIOP >= 2
	,&siopcb2
#endif /* TNUM_SIOP >= 2 */
#if TNUM_SIOP >= 3
	,&siopcb3
#endif /* TNUM_SIOP >= 3 */
#if TNUM_SIOP >= 4
	,&siopcb4
#endif /* TNUM_SIOP >= 4 */
};

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)  (p_siopcb_table[INDEX_SIOP(siopid)])


void
at91skyeye_init_uart(uint_t siopid)
{
	SIOPCB *p_siopcb = get_siopcb(siopid);
      
	/* �����ǡ����γ�Ǽ�襢�ɥ쥹������ */
	sil_wrw_mem((void *)(USART0_RPR), (uint32_t)(&(p_siopcb->usart_rev_buf)));
	sil_wrw_mem((void *)(USART0_RCR), 0x0001);
}

/*
 * ʸ�������������?
 */ 
Inline bool_t
uart_getready(SIOPCB *p_siopcb)
{
	return(sil_rew_mem((void*)(p_siopcb->p_siopinib->us_rcr)) == 0);
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline bool_t
uart_putready(SIOPCB *p_siopcb)
{
	return(true);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline uint8_t
uart_getchar(SIOPCB *p_siopcb)
{
	char_t c;
     
	c = p_siopcb->usart_rev_buf;
	sil_wrw_mem((void *)(p_siopcb->p_siopinib->us_rpr), (uint32_t)(&(p_siopcb->usart_rev_buf)));
	sil_wrw_mem((void *)(p_siopcb->p_siopinib->us_rcr), 0x0001);
    
	return(c);
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
uart_putchar(SIOPCB *p_siopcb, uint8_t c)
{
	sil_wrw_mem((void*)(p_siopcb->p_siopinib->us_thr),c);
}

/*
 *  ��������ߵ���
 */
Inline void
uart_enable_send(SIOPCB *p_siopcb)
{

}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_send(SIOPCB *p_siopcb)
{

}


/*
 *  ��������ߵ���
 */
Inline void
uart_enable_rcv(SIOPCB *p_siopcb)
{

}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_rcv(SIOPCB *p_siopcb)
{

}


/*
 *  SIO�ɥ饤�Фν����
 */
void
sio_initialize(intptr_t exinf)
{
	uint_t  i = (uint_t)exinf;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	(p_siopcb_table[i])->p_siopinib = &(siopinib_table[i]);
	(p_siopcb_table[i])->openflag = false;
	(p_siopcb_table[i])->sendflag = false;
}

/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
at91skyeye_uart_opn_por(SIOPCB *p_siopcb, intptr_t exinf)
{   
	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;

	return(p_siopcb);
}


/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB  *p_siopcb = get_siopcb(siopid);
	bool_t    opnflg;
	ER      ercd;
    
	/*
	 *  �����ץ󤷤��ݡ��Ȥ����뤫��opnflg���ɤ�Ǥ�����
	 */
	opnflg = p_siopcb->openflag;

	/*
	 *  �ǥХ�����¸�Υ����ץ������
	 */
	at91skyeye_uart_opn_por(p_siopcb, exinf);

	/*
	 *  ���ꥢ��I/O����ߤΥޥ����������롥
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopcb->p_siopinib->intno);
		assert(ercd == E_OK);
	}
	return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  �ǥХ�����¸�Υ�����������
	 */
	p_siopcb->openflag = false;
    
	/*
	 *  ���ꥢ��I/O����ߤ�ޥ������롥
	 */
	dis_int(p_siopcb->p_siopinib->intno);
}


/*
 *  SIO�γ���ߥϥ�ɥ�
 */
void
sio_handler(void)
{
	SIOPCB *p_siopcb = get_siopcb((x_prc_index() + 1));
	if (uart_getready(p_siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	if (uart_putready(p_siopcb)) {
		/*
		 *  ������ǽ������Хå��롼�����ƤӽФ���
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char_t c)
{    
	if (uart_putready(siopcb)){
		uart_putchar(siopcb, c);
		return(true);
	}
	return(false);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
	if (uart_getready(siopcb)) {
		return((int_t)(uint8_t) uart_getchar(siopcb));
	}
	return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	  case SIO_RDY_SND:
		uart_enable_send(siopcb);
		break;
	  case SIO_RDY_RCV:
		uart_enable_rcv(siopcb);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	  case SIO_RDY_SND:
		uart_disable_send(siopcb);
		break;
	  case SIO_RDY_RCV:
		uart_disable_rcv(siopcb);
		break;
	}
}
