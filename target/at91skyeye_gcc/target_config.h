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
 *  @(#) $Id: target_config.h 926 2012-03-30 10:18:29Z ertl-honda $
 */

/*
 *  ���åװ�¸�⥸�塼���AT91SKYEYE�ѡ�
 *
 *  �����ͥ�Υ��åװ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 *
 *  UMA����ǥǡ�����¤������
 *  -> �����������Ȥ��롥 
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  ���åץ����ƥ�Υϡ��ɥ������񸻤����
 */
#include "at91skyeye.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ���ݡ��Ȥ��Ƥ���SKYEY�ΥС������
 */
#define SUPPORT_SKYEYE_VER  0x1024
#define SUPPORT_DEVM_VER    0x2020

/*
 *  ���ԥ��å���ǽ������
 */
#ifndef TTYPE_SPN
#define TTYPE_SPN NATIVE_SPN
//#define TTYPE_SPN EMULATE_SPN
#endif /* TTYPE_SPN */

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN   4

/*
 *  ��å���ID
 */
#if TTYPE_KLOCK == G_KLOCK

/* ���㥤����ȥ�å����� */
#define GIANT_LOCK  0x00

#else /* TTYPE_KLOCK == P_KLOCK */

/* �ץ��å���å����� */
#define PRC1_TSK_LOCK  0x00
#define PRC2_TSK_LOCK  0x02
#define PRC3_TSK_LOCK  0x04
#define PRC4_TSK_LOCK  0x06
#define PRC1_OBJ_LOCK  0x01
#define PRC2_OBJ_LOCK  0x03
#define PRC3_OBJ_LOCK  0x05
#define PRC4_OBJ_LOCK  0x07

#endif /* TTYPE_KLOCK == G_KLOCK */

/*
 *  �٥������롼���������ʤ����Υ٥��������ɥ쥹����Ƭ����
 */ 
#define VECTOR_START  0x00

/*
 *  �ǡ������������ν�����򤷤ʤ�
 */
#define TOPPERS_OMIT_DATA_INIT

/*
 *  FMP�����ͥ�ư����Υ���ޥåפȴ�Ϣ�������
 */
#define RAM_START       RAM_BASE_ADDRESSS

#define FIQ_DATA_SIZE   256U

/*
 *  �ǥե���Ȥ��󥿥�������ƥ������ѤΥ����å��ΰ�����
 */
#define DEFAULT_PRC1_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC2_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC3_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC4_ISTKSZ      (1024 * 8)   /* 8KB */
                                                   
/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    20
#define SIL_DLY_TIM2    10

/*
 *  ����ߥϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_INHNO 0U
#define TMAX_INHNO 31U
#define TNUM_INH   32U

/*
 *  ������ֹ�˴ؤ������
 */ 
#define TMIN_INTNO 0U
#define TMAX_INTNO 31U
#define TNUM_INT   32U

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ץ��å���APCB�ؤΥݥ��󥿤μ���
 *  ���󥯥롼�ɽ���δط��塤target_pcb.h �ˤϵ��ҤǤ��ʤ����ᤳ����������롥
 */
Inline APCB*
get_my_p_apcb(void)
{
	return(&((get_my_p_tpcb())->arm_pcb));
}

/*
 * �ޥ����ץ��å���Ƚ��
 */
Inline bool_t
x_sense_mprc(void){
	if(x_prc_index() == (TOPPERS_MASTER_PRCID - 1)) {
		return(true);
	}
	else{
		return(false);
	}
}

/*
 * �ޥ���ץ��å��ѵ�ǽ
 */

#if TTYPE_KLOCK == G_KLOCK
/*
 *  ���㥤����ȥ�å��ν������G_LOCK�ξ���
 */
Inline void
x_initialize_giant_lock(LOCK *p_giant_lock)
{
	*p_giant_lock = GIANT_LOCK;
}

#endif /* TTYPE_KLOCK == G_KLOCK */

#if TTYPE_KLOCK == P_KLOCK

/*
 *  ��������å��ν������P_LOCK�ξ���
 */
Inline void
x_initialize_tsk_lock(LOCK *p_tsk_lock)
{
	if (x_prc_index() == 0) {
		*p_tsk_lock = PRC1_TSK_LOCK;
	}
	else if (x_prc_index() == 1) {
		*p_tsk_lock = PRC2_TSK_LOCK;
	}
	else if (x_prc_index() == 2) {
		*p_tsk_lock = PRC3_TSK_LOCK;
	}
	else if (x_prc_index() == 3) {
		*p_tsk_lock = PRC4_TSK_LOCK;
	}
}

/*
 *  ���֥������ȥ�å��ν����
 */
Inline void
x_initialize_obj_lock(LOCK *p_obj_lock)
{
	if (x_prc_index() == 0) {
		*p_obj_lock = PRC1_OBJ_LOCK;
	}
	else if (x_prc_index() == 1) {
		*p_obj_lock = PRC2_OBJ_LOCK;
	}
	else if (x_prc_index() == 2) {
		*p_obj_lock = PRC3_OBJ_LOCK;
	}
	else if (x_prc_index() == 3) {
		*p_obj_lock = PRC4_OBJ_LOCK;
	}
}

#endif /* TTYPE_KLOCK == P_KLOCK */

/*
 *  ������ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INTNO_MASK(intno) (intno&0xffffU)

/*
 *  ������ֹ����³�ץ��å��Υץ��å�ID�ʾ��16bit��
 */
#define INTNO_PRCID(intno) (intno >> 16U)

/*
 *  ������ֹ���ϰϤ�Ƚ��
 *
 *  �ӥåȥѥ���������Τ��ưפˤ��뤿��ˡ�8�Ϸ��֤ˤʤäƤ��롥
 *  intno�����̵���ѿ��ʤΤǡ�TMIN_INTNO��0�ξ��ϲ��¥����å��Ϥ��ʤ���
 */
#if TMIN_INTNO == 0
#define VALID_INTNO(prcid, intno) (((INTNO_MASK(intno)) <= TMAX_INTNO) && (INTNO_PRCID(intno) == prcid))
#else /* !TMIN_INTNO == 0 */
#define VALID_INTNO(prcid, intno) (((TMIN_INTNO <= (INTNO_MASK(intno)) && (INTNO_MASK(intno)) <= TMAX_INTNO)) \
                                    && (INTNO_PRCID(intno) == prcid))
#endif /* TMIN_INTNO == 0 */
#define VALID_INTNO_DISINT(prcid, intno)	VALID_INTNO(prcid, intno)
#define VALID_INTNO_CFGINT(prcid, intno)	VALID_INTNO(prcid, intno)

/*
 *  ����ߥϥ�ɥ����Ͽ�ѥơ��֥��kernel_cfg.c��
 */
extern const FP* const p_inh_table[TNUM_PRCID];

/*
 *  ����ߥϥ�ɥ��ͥ���١�kernel_cfg.c��
 */
extern const PRI* const p_inh_ipm_table[TNUM_PRCID];

/*
 *  ����ߥϥ�ɥ������
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{

}

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)

/*
 *  TOPPERSɸ�����߽�����ǥ�μ¸�
 */
               
/*
 *  �����ͥ���٥ޥ������饤�֥��
 *
 *  AT91SAM7S�ϳ����ͥ���٥ޥ�����IRC��ǥϡ��ɥ�����Ū�˻��Ĥ���
 *  ���եȥ�����¦�����ͤ��ɤ߽񤭤Ǥ��ʤ����ᡤ������׵�ػߥե�
 *  ���ˤ������ͥ���٥ޥ�����¸�����
 */
/*
 *  �����ͥ������Υޥ����ѥ������kernel_cfg.h��
 */
extern const uint32_t* const p_ipm_mask_table[TNUM_PRCID];

#define my_ipm_mask_table (p_ipm_mask_table[x_prc_index()])

#endif /* TOPPERS_MACRO_ONLY */  

/*
 *  IPM��imp_mask_table�Υ���ǥå������Ѵ�����ޥ���
 */
#define INDEX_IPM(ipm)  (-(ipm))

#ifndef TOPPERS_MACRO_ONLY

/*
 *  (��ǥ���)�����ͥ���٥ޥ���������
 * 
 *  ���ꤵ�줿ͥ���٤����ꤵ�줿������׵�ػߥե饰�Υơ��֥���ͤȡʥ��
 *  ���Ρ˳Ƴ���ߤγ�����׵�ػߥե饰�ξ��֤��ݻ������ѿ����ͤȤ�
 *  OR��IRC�γ�����׵�ػߥե饰�˥��åȤ������ꤷ��ͥ���٤������ѿ�
 *  ipm����¸���롥
 */
Inline void
x_set_ipm(PRI intpri)
{
	TPCB *p_tpcb;
	uint32_t ipm_mask;

	p_tpcb = get_my_p_tpcb();
	ipm_mask = my_ipm_mask_table[INDEX_IPM(intpri)];

	/*
	 *  AT91SAM7S�γ���ߥ���ȥ���ϥ��͡��֥�쥸������
	 *  ���ꥢ���쥸���������뤿�ᡤ��ö���Ƥγ���ߤ�ػߤ��Ƥ��顤
	 *  ����γ���ߤΤߵ��Ĥ���ɬ�פ�����
	 */
	/* ������߶ػ� */
	at91skyeye_disable_int(~0U);
	/* �ޥ������ꤵ��Ƥ��ʤ�����ߤΤߵ��� */
	at91skyeye_enable_int(~(ipm_mask|(p_tpcb->idf)));
	p_tpcb->ipm = intpri;
}

#define t_set_ipm(intpri) x_set_ipm(intpri)
#define i_set_ipm(intpri) x_set_ipm(intpri)

/*
 *  (��ǥ���)�����ͥ���٥ޥ����λ���
 *
 *  ipm���ͤ��֤�
 */
Inline PRI
x_get_ipm(void)
{
	TPCB *p_tpcb;

	p_tpcb = get_my_p_tpcb();

	return(p_tpcb->ipm);
}

#define t_get_ipm() x_get_ipm()
#define i_get_ipm() x_get_ipm()

/*
 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ�
 */
extern uint32_t	bitpat_cfgint;

/*
 * �ʥ�ǥ��Ρ˳�����׵�ػߥե饰�Υ��å�
 *
 *  ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��åȤ��ơ�����ߤ�
 *  �ػߤ��롥�ޤ����ʥ�ǥ��Ρ˳�����׵�ػߥե饰���������idf����
 *  ������ӥåȤ�򥻥åȤ��롥
 *  ������׵��ޥ������뵡ǽ�򥵥ݡ��Ȥ��Ƥ��ʤ����ˤϡ�false���֤�
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	if ((p_tpcb->bitpat_cfgint & INTNO_BITPAT(INTNO_MASK(intno))) == 0U) {
		return(false);
	}
	at91skyeye_disable_int(INTNO_BITPAT(INTNO_MASK(intno)));
	p_tpcb->idf |= INTNO_BITPAT(INTNO_MASK(intno));
	return(true);
}

#define t_disable_int(intno)  x_disable_int(intno)
#define i_disable_int(intno)  t_disable_int(intno)

/* 
 * (��ǥ���)����׵�ػߥե饰�β��
 *
 * ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��ꥢ���ơ�����ߤ�
 * ���Ĥ��롥�ޤ����ʥ�ǥ��Ρ˳�����׵�ػߥե饰���������idf����
 * ������ӥåȤ�򥯥ꥢ���롥
 * ������׵��ޥ������뵡ǽ�򥵥ݡ��Ȥ��Ƥ��ʤ����ˤϡ�false���֤�
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	TPCB *p_tpcb = get_my_p_tpcb();
	uint32_t ipm_mask = my_ipm_mask_table[INDEX_IPM(p_tpcb->ipm)];

	if ((p_tpcb->bitpat_cfgint & INTNO_BITPAT(INTNO_MASK(intno))) == 0U) {
		return(false);
	}
	p_tpcb->idf &= ~INTNO_BITPAT(INTNO_MASK(intno));
	/* ������߶ػ� */
	at91skyeye_disable_int(~0U);
	/* �ޥ������ꤵ��Ƥ��ʤ�����ߤΤߵ��� */
	at91skyeye_enable_int(~(ipm_mask|(p_tpcb->idf)));

	return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 * ������׵�Υ��ꥢ
 */
Inline void
x_clear_int(INTNO intno)
{
	at91skyeye_clear_int(INTNO_BITPAT(INTNO_MASK(intno)));
}

#define t_clear_int(intno) x_clear_int(intno) 
#define i_clear_int(intno) x_clear_int(intno) 


/*
 *  ������׵�Υ����å�
 */
Inline bool_t
x_probe_int(INTNO intno)
{
    return(at91skyeye_probe_int(INTNO_BITPAT(INTNO_MASK(intno))));
}

#define t_probe_int(intno) x_probe_int(intno)
#define i_probe_int(intno) x_probe_int(intno)

/*
 *  ������׵�饤���°��������
 *
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);

/*
 *  ����ߥϥ�ɥ���������ɬ�פ�IRC���
 *
 *  AT91SAM7S�Ǥϡ�ɬ�פʽ����Ϥʤ�
 */
Inline void
i_begin_int(INTNO intno)
{
    
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 *
 *  AT91SAM7S�Ǥϡ�ɬ�פʽ����Ϥʤ�
 */
Inline void
i_end_int(INTNO intno)
{
    
}

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void target_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���
 */
extern void target_exit(void) NoReturn;

/*
 *  ����ߥϥ�ɥ��chip_support.S��
 */
extern void interrupt_handler(void);

/*
 *  ̤����γ���ߤ����ä����ν���
 */
extern void default_int_handler(void);


/*
 *  �ޥ���ץ��å������ε�ǽ
 */

/*
 * �ץ��å��ֳ���ߤ˻��Ѥ��������ֹ��IRQ0��
 */
#define INTERPROCLVL 16

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ������¸�⥸�塼���ARM�ѡ�
 */
#include "core_config.h"

#ifndef TOPPERS_MACRO_ONLY
/*
 *  ��å����������ؿ�
 *  x_lock_cpu()/x_unlock_cpu()��Ȥ����ᡤ������¸�⥸�塼���ARM�ѡˤ�
 *  �ɤ߹���Ǥ���������롥 
 */
/*
 *  1���ܤΥ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_acquire_lock(LOCK *p_lock)
{
	while(true) {
		sil_wrw_mem((void *)MUTEX_ID_REG, *p_lock);
		if(sil_rew_mem((void *)MUTEX_CNT_REG) == 1){
			/* ��å��������� */
			ARM_MEMORY_CHANGED;
			return;
		}
		/* ����ߤε��� */
		x_unlock_cpu();
		x_lock_cpu();
	}
}

#define t_acquire_lock(p_lock) x_acquire_lock(p_lock)
#define i_acquire_lock(p_lock) x_acquire_lock(p_lock)

#if TTYPE_KLOCK != G_KLOCK

/*
 *  2���ܰʾ�Υ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline bool_t
x_acquire_nested_lock(LOCK *p_lock)
{
	PCB		*p_pcb;

	while(true) {
		sil_wrw_mem((void *)MUTEX_ID_REG, *p_lock);
		if(sil_rew_mem((void *)MUTEX_CNT_REG) == 1){
			/* ��å��������� */
			ARM_MEMORY_CHANGED;
			return(false);
		}
		/* ����ߤε��� */
		x_unlock_cpu();
		x_lock_cpu();
		/*
		 * �ޥ����졼����󤹤��ǽ��������ΤǤ�����������  
		 * �󥿥�������ƥ����Ȥξ�硤�ޥ����졼����󤷤ʤ����ᡤ
		 * while���˼¹Ԥ��Ƥ�褤����1��ǥ�å����Ȥ줿��硤
		 * ��Ψ�������Τǡ������Ǽ������롥
		 */
		p_pcb = get_my_p_pcb(); 
		if (p_pcb->p_firstlock == NULL) {
			return(true);
		}
	}
}

#define t_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)
#define i_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)

#endif /* TTYPE_KLOCK != G_KLOCK */

/*
 *  ��å��β����ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_release_lock(LOCK *p_lock)
{
	ARM_MEMORY_CHANGED;
	sil_wrw_mem((void *)MUTEX_ID_REG, *p_lock);
	sil_wrw_mem((void *)MUTEX_CNT_REG, 1);
}

/*
 *  �������Ĥ��ʤ���å������ؿ�
 */
Inline void 
x_acquire_lock_without_preemption(LOCK *p_lock)
{
	while(true) {
		sil_wrw_mem((void *)MUTEX_ID_REG, *p_lock);
		if(sil_rew_mem((void *)MUTEX_CNT_REG) == 1){
			/* ��å��������� */
			ARM_MEMORY_CHANGED;
			return;
		}
	}
}

/*
 *  ���ԥ��å���ǽ�Υͥ��ƥ��֥�å������ǻ��Ѥ���ؿ�
 */

/*
 *  ���ԥ��å��η��ʥͥ��ƥ��֥�å��ξ���
 */
typedef uint32_t SPNLOCK;

/*
 *  ���ԥ��å�ID����ºݤΥ�å���ID�ؤ��Ѵ�
 */
#define TO_NATIVE_ID(spnid)		(spnid + 19)

/*
 *  ���ԥ��å��ν����
 */
Inline void
x_initialize_spin(ID spnid, SPNLOCK *p_spn_lock)
{
	*p_spn_lock = TO_NATIVE_ID(spnid);
	sil_wrw_mem((void *)MUTEX_ID_REG, *p_spn_lock);
	sil_wrw_mem((void *)MUTEX_CNT_REG, 1);
}

/*
 *  ���ԥ��å��μ���
 */
Inline void
x_lock_spin(SPNLOCK *p_spn_lock)
{
	x_acquire_lock(p_spn_lock);
}

#define t_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)
#define i_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)

/*
 *  ���ԥ��å��μ����λ��
 */
Inline bool_t
x_try_lock_spin(SPNLOCK *p_spn_lock)
{
	sil_wrw_mem((void *)MUTEX_ID_REG, *p_spn_lock);
	if (sil_rew_mem((void *)MUTEX_CNT_REG) != 1) {
		/* ���� */
		return(true);
	}
	else {
		/* ���� */
		ARM_MEMORY_CHANGED;
		return(false);
	}
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
x_unlock_spin(SPNLOCK *spn_lock)
{
	x_release_lock(spn_lock);
}

#ifdef TOPPERS_ENABLE_GCOV_PART
/*
 *  GCOV���������ѥ饤�֥��
 */
/*
 *  GCOV������ؿ�
 */
extern void gcov_init(void);

/*
 *  GCOV���Ǵؿ�
 */
extern void gcov_pause(void);

/*
 * GCOV�Ƴ��ؿ�
 */
extern void gcov_resume(void);

/*
 *  GCOV���ϴؿ�
 */
extern void gcov_dump(void);
#endif /* TOPPERS_ENABLE_GCOV_PART */
#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_TARGET_CONFIG_H */
