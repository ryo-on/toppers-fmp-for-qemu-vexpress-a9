/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_config.h 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *  ���åװ�¸�⥸�塼���MPCORE�ѡ�
 *
 *  �����ͥ�Υ��åװ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 */

#ifndef TOPPERS_CHIP_CONFIG_H
#define TOPPERS_CHIP_CONFIG_H

/*
 *  ���åװ�¸���ΤΥϡ��ɥ������񸻤����
 */
#include "mpcore.h"

#ifdef USE_IPI_DIS_HANDER_BYPASS
#define OMIT_KER_REQ_ON_IPI

#ifndef TOPPERS_MACRO_ONLY
/*
 *  �����ͥ뽪λ�����׵�
 */
extern void ext_ker_request(void);
#endif /* TOPPERS_MACRO_ONLY */
#endif /* USE_IPI_DIS_HANDER_BYPASS */

/*
 *  ������ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INTNO_MASK(intno) (intno & 0xffffU)

/*
 *  ������ֹ����³�ץ��å��Υץ��å�ID�ʾ��16bit��
 */
#define INTNO_PRCID(intno) (intno >> 16U)

/*
 *  ����ߥϥ�ɥ��ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INHNO_MASK(intno) (intno & 0xffffU)

/*
 *  ����ߥϥ�ɥ��ֹ�ȳ�����ֹ�˴ؤ������
 */
#define TMIN_INTNO  DIC_TMIN_INTNO
#define TMAX_INTNO  DIC_TMAX_INTNO
#define TNUM_INT    DIC_TNUM_INT

#define TMIN_INHNO  DIC_TMIN_INTNO
#define TMAX_INHNO  DIC_TMAX_INTNO
#define TNUM_INH    DIC_TNUM_INT

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ץ��å���APCB�ؤΥݥ��󥿤μ���
 *  ���󥯥롼�ɽ���δط��塤target_pcb.h �ˤϵ��ҤǤ��ʤ����ᤳ����������롥
 */
Inline APCB*
get_my_p_apcb(void)
{
	return &((get_my_p_tpcb())->arm_pcb);
}

/*
 *  �ޥ����ץ��å������֤�
 */
Inline bool_t
x_sense_mprc(void){
	if(x_prc_index() == (TOPPERS_MASTER_PRCID - 1)) {
		return true;
	}
	else {
		return false;
	}
}

/*
 *  ��å��ط�
 */

/*
 *  ���㥤����ȥ�å��ν������G_LOCK�ξ���
 */
Inline void
x_initialize_giant_lock(LOCK *p_giant_lock)
{
	*p_giant_lock = 0;
}

/*
 *  ��������å��ν����
 */
Inline void
x_initialize_tsk_lock(LOCK *p_tsk_lock)
{
	*p_tsk_lock = 0;
}

/*
 *  ���֥������ȥ�å��ν����
 */
Inline void
x_initialize_obj_lock(LOCK *p_obj_lock)
{
	*p_obj_lock = 0;
}

/*
 *  ������ֹ���ϰϤ�Ƚ��
 */
#if TMIN_INTNO == 0
#define VALID_INTNO(prcid, intno) ((INTNO_MASK(intno) <= TMAX_INTNO) \
                                    && (INTNO_PRCID(intno) == 0U || INTNO_PRCID(intno) == prcid))
#else /* !TMIN_INTNO == 0 */
#define VALID_INTNO(prcid, intno) (((TMIN_INTNO <= (INTNO_MASK(intno)) && (INTNO_MASK(intno)) <= TMAX_INTNO)) \
                                    && (INTNO_PRCID(intno) == 0U || INTNO_PRCID(intno) == prcid))
#endif /* TMIN_INTNO == 0 */

#define VALID_INTNO_DISINT(prcid, intno)	VALID_INTNO(prcid, intno)
#define VALID_INTNO_CFGINT(prcid, intno)	VALID_INTNO(prcid, intno)

/*
 *  ����ߥϥ�ɥ����Ͽ�ѥơ��֥��kernel_cfg.c��
 */
extern const FP* const p_inh_table[TNUM_PRCID];

/*
 *  ����ߥϥ�ɥ������
 *
 *  ����ߥϥ�ɥ��ֹ�inhno�γ���ߥϥ�ɥ�ε�ư���Ϥ�inthdr�����ꤹ��
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{
#if TMIN_INTNO == 0
		assert((INHNO_MASK(inhno) <= TMAX_INHNO));
#else /* !TMIN_INTNO == 0 */
	assert(((TMIN_INHNO <= INHNO_MASK(inhno)) && (INHNO_MASK(inhno) <= TMAX_INHNO)));
#endif /* TMIN_INTNO == 0 */
}

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ͥ���٥ޥ������饤�֥��
 *
 *  DIC�Ǥϡ�DIC���ͥ���٥쥸������CPU�γ����ͥ���٥ޥ�����IPM�ˤ����ꤹ�롥
 *  �����ͥ���٥ޥ������ͤ��礭���ۤ���ͥ���٤Ǥ��롥
 *  �����ͥ���٥ޥ����Ϥ��ʳ���ARM11��CA9�ǰۤʤ롥
 *    ��ARM11(ARMv6) : 16�ʳ���0x00 �� 0x0f��
 *    ��CA9(ARMv7)   : 32�ʳ���0x00 �� 0x1f��
 *  IPM����¸���Ƥ�������ˡ������ͥ���٤γ���ɽ����-1����Ϣ³��������͡�
 *  ��Ȥ����Ȥ��ǽ�Ǥ��뤬��;�פʷ׻���ɬ�פˤʤ롥������򤱤뤿�ᡤIPM��
 *  ��¸������ˤϡ�DIC�ǰ���ͥ���٤η����Ȥ��롥�����ͤ�����ͥ���٥ޥ���
 *  ������ɽ���ȸƤӡ�IIPM�Ƚ񤯤��Ȥˤ��롥
 */

/*
 *  �����ͥ���٥ޥ����Υӥåȥޥ���
 */
#if __TARGET_ARCH_ARM == 6
#ifndef TOPPERS_MACRO_ONLY
#define IPM_BIT_MASK  0x0fU
#else /* TOPPERS_MACRO_ONLY */
#define IPM_BIT_MASK  0x0f
#endif /* TOPPERS_MACRO_ONLY */
#define IPM_BIT_OFFSET 4
#elif __TARGET_ARCH_ARM == 7
#ifndef TOPPERS_MACRO_ONLY
#define IPM_BIT_MASK  0x1fU
#else /* TOPPERS_MACRO_ONLY */
#define IPM_BIT_MASK  0x1f
#endif /* TOPPERS_MACRO_ONLY */
#define IPM_BIT_OFFSET 3
#endif /* __TARGET_ARCH_ARM == 7 */

/*
 *  �����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 *
 *  ������֥����Υ������ե����뤫�饤�󥯥롼�ɤ�����Τ���ˡ���
 *  ���㥹�Ȥ��ʤ�������Ѱդ��Ƥ��롥
 */
#ifndef TOPPERS_MACRO_ONLY
#define EXT_IPM(iipm)    ((PRI)(iipm - IPM_BIT_MASK))    /* ����ɽ������ɽ���� */
#define INT_IPM(ipm)    ((uint8_t)(ipm + IPM_BIT_MASK))  /* ����ɽ��������ɽ���� */
#else /* TOPPERS_MACRO_ONLY */
#define EXT_IPM(iipm)    (iipm - IPM_BIT_MASK)           /* ����ɽ������ɽ���� */
#define INT_IPM(ipm)    (ipm + IPM_BIT_MASK)             /* ����ɽ��������ɽ���� */
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  TIPM_ENAALL�ʳ����ͥ���٥ޥ���������ˤ�����ɽ��
 */
#define IIPM_ENAALL        (INT_IPM(TIPM_ENAALL))

#ifndef TOPPERS_MACRO_ONLY

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint8_t
current_iipm(void)
{
	return(dic_cpu_current_priority());
}

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_iipm(uint8_t iipm)
{
	dic_cpu_set_priority(iipm);
}

/*
 * (��ǥ���)�����ͥ���٥ޥ���������
 */
Inline void
x_set_ipm(PRI intpri)
{
	set_iipm(INT_IPM(intpri));
}

#define t_set_ipm(intpri) x_set_ipm(intpri)
#define i_set_ipm(intpri) x_set_ipm(intpri)

/*
 *  (��ǥ���)�����ͥ���٥ޥ����λ���
 */
Inline PRI
x_get_ipm(void)
{
	return(EXT_IPM(current_iipm()));
}

#define t_get_ipm() x_get_ipm()
#define i_get_ipm() x_get_ipm()

/*
 *  �����°�����������ơ��֥�
 *
 *  �����°���ơ��֥�ؤΥݥ��󥿡������°���ơ��֥�ϡ������°��������
 *  ����Ƥ����"1"�����ꤵ��Ƥ��ʤ����"0"�Ȥʤ�
 */
extern const uint8_t* const p_cfgint_table[];

#define my_cfgint_table (p_cfgint_table[x_prc_index()])

/*
 * �ʥ�ǥ��Ρ˳�����׵�ػߥե饰�Υ��å�
 *
 *  ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��åȤ��ơ�����ߤ�
 *  �ػߤ��롥
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	if (my_cfgint_table[INTNO_MASK(intno)] == 0){
		return(false);
	}

	dic_disable_int(INTNO_MASK(intno));
	return(true);
}

#define t_disable_int(intno)  x_disable_int(intno)
#define i_disable_int(intno)  t_disable_int(intno)

/*
 *  (��ǥ���)����׵�ػߥե饰�β��
 *
 *  ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��ꥢ���ơ�����ߤ�
 *  ���Ĥ��롥
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	if (my_cfgint_table[INTNO_MASK(intno)] == 0){
		return(false);
	}

	dic_enable_int(INTNO_MASK(intno));
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
	dic_clear_pending(INTNO_MASK(intno));
}

#define t_clear_int(intno) x_clear_int(intno)
#define i_clear_int(intno) x_clear_int(intno)

/*
 *  ������׵�Υ����å�
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	return(dic_probe_int(INTNO_MASK(intno)));
}

#define t_probe_int(intno) x_probe_int(intno)
#define i_probe_int(intno) x_probe_int(intno)

/*
 *  ������׵�饤���°��������
 *
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);

/*
 * ����ߥϥ�ɥ���������ɬ�פ�IRC���
 *
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 * ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  str_ker() �����ǥޥ����ץ��å��ǹԤ������
 */
extern void chip_mprc_initialize(void);

/*
 *  ���åװ�¸�ν����
 */
extern void chip_initialize(void);

/*
 *  ���åװ�¸���ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���
 */
extern void chip_exit(void);

/*
 *  ����ߥϥ�ɥ��chip_support.S��
 */
extern void interrupt_handler(void);

/*
 *  ̤����γ���ߤ����ä����ν���
 */
extern void default_int_handler(void);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ARM��¸�⥸�塼��
 */
#include "arm_gcc/common/core_config.h"

/*
 *  ���åװ�¸�⥸�塼��Υġ����¸��
 */
#include <chip_config_tool.h>

#endif /* TOPPERS_CHIP_CONFIG_H */
