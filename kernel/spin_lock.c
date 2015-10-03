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
 *  @(#) $Id: spin_lock.c 891 2012-02-08 12:34:04Z ertl-honda $
 */

/*
 *		���ԥ��å���ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "spin_lock.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_LOC_SPN_ENTER
#define LOG_LOC_SPN_ENTER(spnid)
#endif  /* LOG_LOC_SPN_ENTER */

#ifndef LOG_LOC_SPN_LEAVE
#define LOG_LOC_SPN_LEAVE(ercd)
#endif  /* LOG_LOC_SPN_LEAVE */

#ifndef LOG_ILOC_SPN_ENTER
#define LOG_ILOC_SPN_ENTER(spnid)
#endif  /* LOG_ILOC_SPN_ENTER */

#ifndef LOG_ILOC_SPN_LEAVE
#define LOG_ILOC_SPN_LEAVE(ercd)
#endif  /* LOG_ILOC_SPN_LEAVE */

#ifndef LOG_TRY_SPN_ENTER
#define LOG_TRY_SPN_ENTER(spnid)
#endif  /* LOG_TRY_SPN_ENTER */

#ifndef LOG_TRY_SPN_LEAVE
#define LOG_TRY_SPN_LEAVE(ercd)
#endif  /* LOG_TRY_SPN_LEAVE */

#ifndef LOG_ITRY_SPN_ENTER
#define LOG_ITRY_SPN_ENTER(spnid)
#endif  /* LOG_ITRY_SPN_ENTER */

#ifndef LOG_ITRY_SPN_LEAVE
#define LOG_ITRY_SPN_LEAVE(ercd)
#endif  /* LOG_ITRY_SPN_LEAVE */

#ifndef LOG_UNL_SPN_ENTER
#define LOG_UNL_SPN_ENTER(spnid)
#endif  /* LOG_UNL_SPN_ENTER */

#ifndef LOG_UNL_SPN_LEAVE
#define LOG_UNL_SPN_LEAVE(ercd)
#endif  /* LOG_UNL_SPN_LEAVE */

#ifndef LOG_IUNL_SPN_ENTER
#define LOG_IUNL_SPN_ENTER(spnid)
#endif  /* LOG_IUNL_SPN_ENTER */

#ifndef LOG_IUNL_SPN_LEAVE
#define LOG_IUNL_SPN_LEAVE(ercd)
#endif  /* LOG_IUNL_SPN_LEAVE */

#ifndef LOG_REF_SPN_ENTER
#define LOG_REF_SPN_ENTER(spnid, pk_rspn)
#endif  /* LOG_REF_SPN_ENTER */

#ifndef LOG_REF_SPN_LEAVE
#define LOG_REF_SPN_LEAVE(ercd, pk_rspn)
#endif  /* LOG_REF_SPN_LEAVE */

/*
 *  ���ԥ��å��ο�
 */
#define tnum_spn		((uint_t)(tmax_spnid - TMIN_SPNID + 1))
#define INDEX_SPN(spnid)	((uint_t)((spnid) - TMIN_SPNID))
#define get_spncb(spnid)	(p_spncb_table[INDEX_SPN(spnid)])

#if TTYPE_SPN == NATIVE_SPN

/*
 *  �ͥ��ƥ�������
 */

/*
 *  ���ԥ��å���ǽ�ν����
 */
#ifdef TOPPERS_spnini

void
initialize_spin_lock(void)
{
	uint_t	i;
	SPNCB	*p_spncb;
	PCB		*my_p_pcb;

	my_p_pcb = get_my_p_pcb();

	my_p_pcb->locspnid = 0;
	if (x_sense_mprc()) {
		for (i = 0; i < tnum_spn;  i++) {
			p_spncb = p_spncb_table[i];
			p_spncb->p_spninib = &(spninib_table[i]);
			p_spncb->lock_flg = false;
			x_initialize_spin((i + 1), &(p_spncb->spn_lock));
		}
	}
}

#endif /* TOPPERS_spnini */

/*
 *  ���ԥ��å��ζ���������PCB���locspnid���оݤˤ����
 */
#ifdef TOPPERS_force_unlock_spin

void
force_unlock_spin(PCB *my_p_pcb)
{
	SPNCB   *p_spncb;

	if (my_p_pcb->locspnid != 0U) {
		p_spncb = get_spncb(my_p_pcb->locspnid);
		x_unlock_spin(&(p_spncb->spn_lock));
		p_spncb->lock_flg = false;
		my_p_pcb->locspnid = 0;
	}
}

#endif /* TOPPERS_force_unlock_spin */

/*
 *  ���ԥ��å��μ���
 */
#ifdef TOPPERS_loc_spn

ER
loc_spn(ID spnid)
{
	ER		ercd;
	SPNCB	*p_spncb;

	LOG_LOC_SPN_ENTER(spnid);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	/*
	 *  ���Ǥ˥�å���������Ƥ������locspnid != 0�ˤʤ顤CHECK_TSKCTX_UNL()
	 *  �ǥ��顼�Ȥʤ�Τǡ�locspnid�Υ����å���ɬ�פʤ���
	 */
	t_lock_cpu();
	t_lock_spin(&(p_spncb->spn_lock));
	p_spncb->lock_flg = true;
	(get_my_p_pcb())->locspnid = spnid;
	ercd = E_OK;

  error_exit:
	LOG_LOC_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_loc_spn */

/*
 *  ���ԥ��å��μ������󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iloc_spn

ER
iloc_spn(ID spnid)
{
	ER		ercd;
	SPNCB	*p_spncb;

	LOG_ILOC_SPN_ENTER(spnid);
	CHECK_INTCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	/*
	 *  ���Ǥ˥�å���������Ƥ������locspnid != 0�ˤʤ顤CHECK_TSKCTX_UNL()
	 *  �ǥ��顼�Ȥʤ�Τǡ�locspnid�Υ����å���ɬ�פʤ���
	 */
	i_lock_cpu();
	i_lock_spin(&(p_spncb->spn_lock));
	p_spncb->lock_flg = true;
	(get_my_p_pcb())->locspnid = spnid;
	ercd = E_OK;

  error_exit:
	LOG_ILOC_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iloc_spn */

/*
 *  ���ԥ��å��μ����ʥݡ���󥰡�
 */
#ifdef TOPPERS_try_spn

ER
try_spn(ID spnid)
{
	ER		ercd;
	SPNCB	*p_spncb;

	LOG_TRY_SPN_ENTER(spnid);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	t_lock_cpu();
	if (x_try_lock_spin(&(p_spncb->spn_lock))) {
		t_unlock_cpu();
		ercd = E_OBJ;
	}
	else {
		p_spncb->lock_flg = true;
		(get_my_p_pcb())->locspnid = spnid;
		ercd = E_OK;
	}

  error_exit:
	LOG_TRY_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_try_spn */

/*
 *  ���ԥ��å��μ����ʥݡ����, �󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_itry_spn

ER
itry_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;

	LOG_ITRY_SPN_ENTER(spnid);
	CHECK_INTCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	i_lock_cpu();
	if (x_try_lock_spin(&(p_spncb->spn_lock))) {
		i_unlock_cpu();
		ercd = E_OBJ;
	}
	else {
		p_spncb->lock_flg = true;
		(get_my_p_pcb())->locspnid = spnid;
		ercd = E_OK;
	}

  error_exit:
	LOG_ITRY_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_itry_spn */

/*
 *  ���ԥ��å����ֵ�
 */
#ifdef TOPPERS_unl_spn

ER
unl_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;
	bool_t	locked;

	LOG_UNL_SPN_ENTER(spnid);
	CHECK_TSKCTX();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	locked = t_sense_lock();
	if (!locked) {
		t_lock_cpu();
	}
	my_p_pcb = get_my_p_pcb();
	if (my_p_pcb->locspnid != spnid) {
		if (!locked) {
			t_unlock_cpu();
		}
		ercd = E_ILUSE;
	}
	else {
		/*
		 *  ���ԥ��å������ȤΥ졼���󥰤��򤱤뤿�ᡤ���ԥ��å���
		 *  ���������������ꡥ
		 */
		my_p_pcb->locspnid = 0;
		p_spncb->lock_flg = false;
		x_unlock_spin(&(p_spncb->spn_lock));
		t_unlock_cpu();
		ercd = E_OK;
	}

  error_exit:
	LOG_UNL_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_unl_spn */

/*
 *  ���ԥ��å����ֵѡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iunl_spn

ER
iunl_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;
	bool_t	locked;

	LOG_IUNL_SPN_ENTER(spnid);
	CHECK_INTCTX();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	locked = i_sense_lock();
	if (!locked) {
		i_lock_cpu();
	}
	my_p_pcb = get_my_p_pcb();
	if (my_p_pcb->locspnid != spnid) {
		if (!locked) {
			i_unlock_cpu();
		}
		ercd = E_ILUSE;
	}
	else {
		/*
		 *  ���ԥ��å������ȤΥ졼���󥰤��򤱤뤿�ᡤ���ԥ��å���
		 *  ���������������ꡥ
		 */
		p_spncb->lock_flg = false;
		my_p_pcb->locspnid = 0;
		x_unlock_spin(&(p_spncb->spn_lock));
		i_unlock_cpu();
		ercd = E_OK;
	}

  error_exit:
	LOG_IUNL_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iunl_spn */

/*
 *  ���ԥ��å��ξ��ֻ���
 */
#ifdef TOPPERS_ref_spn

ER
ref_spn(ID spnid, T_RSPN *pk_rspn)
{
	ER		ercd;
	SPNCB   *p_spncb;

	LOG_REF_SPN_ENTER(spnid, pk_rspn);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	pk_rspn->spnstat = (p_spncb->lock_flg) ? TSPN_LOC : TSPN_UNL;
	ercd = E_OK;

  error_exit:
	LOG_REF_SPN_LEAVE(ercd, pk_rspn);
	return(ercd);
}

#endif /* TOPPERS_ref_spn */

#else /* TTYPE_SPN == EMULATE_SPN */

/*
 *  ���ߥ�졼���������
 */

/*
 *  ���ԥ��å���ǽ�ν����
 */
#ifdef TOPPERS_spnini

void
initialize_spin_lock(void)
{
	uint_t	i;
	SPNCB	*p_spncb;
	PCB		*my_p_pcb;

	my_p_pcb = get_my_p_pcb();

	my_p_pcb->locspnid = 0;
	if (x_sense_mprc()) {
		for (i = 0; i < tnum_spn;  i++) {
			p_spncb = p_spncb_table[i];
			p_spncb->lock_flg = false;
			p_spncb->p_spninib = &(spninib_table[i]);
		}
	}
}

#endif /* TOPPERS_spnini */

/*
 *  ���ԥ��å��ζ���������PCB���locspnid���оݤˤ����
 */
#ifdef TOPPERS_force_unlock_spin

void
force_unlock_spin(PCB *my_p_pcb)
{
	SPNCB   *p_spncb;

	if (my_p_pcb->locspnid != 0U) {
		p_spncb = get_spncb(my_p_pcb->locspnid);
		p_spncb->lock_flg = false;
		my_p_pcb->locspnid = 0;
	}
}

#endif /* TOPPERS_force_unlock_spin */

/*
 *  ���ԥ��å��μ���
 */
#ifdef TOPPERS_loc_spn

ER
loc_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;

	LOG_LOC_SPN_ENTER(spnid);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	t_lock_cpu();
  retry:
	t_acquire_obj_lock(&GET_OBJLOCK(p_spncb));
	if (p_spncb->lock_flg) {
		/* ���Ǥ˥�å�����Ƥ������ */
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		goto retry;
	}
	else {
		/* ��å�����Ƥ��ʤ��ä���� */
		my_p_pcb = get_my_p_pcb();
		p_spncb->lock_flg = true;
		my_p_pcb->locspnid = spnid;
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		ercd = E_OK;
	}

  error_exit:
	LOG_LOC_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_loc_spn */

/*
 *  ���ԥ��å��μ������󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iloc_spn

ER
iloc_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;

	LOG_ILOC_SPN_ENTER(spnid);
	CHECK_INTCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	i_lock_cpu();
  retry:
	i_acquire_obj_lock(&GET_OBJLOCK(p_spncb));
	if (p_spncb->lock_flg) {
		/* ���Ǥ˥�å�����Ƥ������ */
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		goto retry;
	}
	else {
		/* ��å�����Ƥ��ʤ��ä���� */
		my_p_pcb = get_my_p_pcb();
		p_spncb->lock_flg = true;
		my_p_pcb->locspnid = spnid;
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		ercd = E_OK;
	}

  error_exit:
	LOG_ILOC_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iloc_spn */

/*
 *  ���ԥ��å��μ����ʥݡ���󥰡�
 */
#ifdef TOPPERS_try_spn

ER
try_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;

	LOG_TRY_SPN_ENTER(spnid);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	t_lock_cpu();
	t_acquire_obj_lock(&GET_OBJLOCK(p_spncb));
	if (p_spncb->lock_flg) {
		/* ���Ǥ˥�å�����Ƥ������ */
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		t_unlock_cpu();
		ercd = E_OBJ;
	}
	else {
		/* ��å�����Ƥ��ʤ��ä���� */
		my_p_pcb = get_my_p_pcb();
		p_spncb->lock_flg = true;
		my_p_pcb->locspnid = spnid;
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		ercd = E_OK;
	}

  error_exit:
	LOG_TRY_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_try_spn */

/*
 *  ���ԥ��å��μ����ʥݡ����, �󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_itry_spn


ER
itry_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;

	LOG_ITRY_SPN_ENTER(spnid);
	CHECK_INTCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	i_lock_cpu();
	i_acquire_obj_lock(&GET_OBJLOCK(p_spncb));
	if (p_spncb->lock_flg) {
		/* ���Ǥ˥�å�����Ƥ������ */
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		i_unlock_cpu();
		ercd = E_OBJ;
	}
	else {
		/* ��å�����Ƥ��ʤ��ä���� */
		my_p_pcb = get_my_p_pcb();
		p_spncb->lock_flg = true;
		my_p_pcb->locspnid = spnid;
		release_obj_lock(&GET_OBJLOCK(p_spncb));
		ercd = E_OK;
	}

  error_exit:
	LOG_ITRY_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_itry_spn */

/*
 *  ���ԥ��å����ֵ�
 */
#ifdef TOPPERS_unl_spn

ER
unl_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;
	bool_t	locked;

	LOG_UNL_SPN_ENTER(spnid);
	CHECK_TSKCTX();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	/*
	 *  ���ԥ��å������ϡ�1�ѿ���p_spncb->lock_flg�ˤ�false�ˤ��������
	 *  �Τǡ��ץ��å�����¾����ϹԤ�ʤ��� 
	 */
	locked = t_sense_lock();
	if (!locked) {
		t_lock_cpu();
	}
	my_p_pcb = get_my_p_pcb();
	if (my_p_pcb->locspnid != spnid) {
		if (!locked) {
			t_unlock_cpu();
		}
		ercd = E_ILUSE;
	}
	else {
		p_spncb->lock_flg = false;
		my_p_pcb->locspnid = 0;
		t_unlock_cpu();
		ercd = E_OK;
	}

  error_exit:
	LOG_UNL_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_unl_spn */

/*
 *  ���ԥ��å����ֵѡ��󥿥�������ƥ������ѡ�
 */
#ifdef TOPPERS_iunl_spn

ER
iunl_spn(ID spnid)
{
	ER		ercd;
	SPNCB   *p_spncb;
	PCB		*my_p_pcb;
	bool_t	locked;

	LOG_IUNL_SPN_ENTER(spnid);
	CHECK_INTCTX();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	locked = i_sense_lock();
	if (!locked) {
		i_lock_cpu();
	}
	my_p_pcb = get_my_p_pcb();
	if (my_p_pcb->locspnid != spnid) {
		if (!locked) {
			i_unlock_cpu();
		}
		ercd = E_ILUSE;
	}
	else {
		p_spncb->lock_flg = false;
		my_p_pcb->locspnid = 0;
		i_unlock_cpu();
		ercd = E_OK;
	}

  error_exit:
	LOG_IUNL_SPN_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iunl_spn */

/*
 *  ���ԥ��å��ξ��ֻ���
 */
#ifdef TOPPERS_ref_spn

ER
ref_spn(ID spnid, T_RSPN *pk_rspn)
{
	ER		ercd;
	SPNCB   *p_spncb;

	LOG_REF_SPN_ENTER(spnid, pk_rspn);
	CHECK_TSKCTX_UNL();
	CHECK_SPNID(spnid);
	p_spncb = get_spncb(spnid);

	pk_rspn->spnstat = (p_spncb->lock_flg) ? TSPN_LOC : TSPN_UNL;
	ercd = E_OK;

  error_exit:
	LOG_REF_SPN_LEAVE(ercd, pk_rspn);
	return(ercd);
}

#endif /* TOPPERS_ref_spn */

#endif /* TTYPE_SPN == EMULATE_SPN */
