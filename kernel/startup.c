/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: startup.c 843 2011-07-15 03:17:19Z ertl-honda $
 */

/*
 *		�����ͥ�ν�����Ƚ�λ����
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "mp.h"
#include "spin_lock.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_KER_ENTER
#define LOG_KER_ENTER()
#endif /* LOG_KER_ENTER */

#ifndef LOG_KER_LEAVE
#define LOG_KER_LEAVE()
#endif /* LOG_KER_LEAVE */

#ifndef LOG_EXT_KER_ENTER
#define LOG_EXT_KER_ENTER()
#endif /* LOG_EXT_KER_ENTER */

#ifndef LOG_EXT_KER_LEAVE
#define LOG_EXT_KER_LEAVE(ercd)
#endif /* LOG_EXT_KER_LEAVE */

#ifdef TOPPERS_sta_ker

/*
 *  �����ͥ�ε�ư
 */
void
sta_ker(void)
{
	PCB *my_p_pcb;

	/*
	 *  �������åȰ�¸�ν����
	 */
	target_initialize();

	/*
	 *  �ƥ⥸�塼��ν����
	 *
	 *  �����।�٥�ȴ����⥸�塼���¾�Υ⥸�塼������˽����
	 *  ����ɬ�פ����롥
	 */
	initialize_pcb();
	initialize_tmevt();
	initialize_object();

	/*
	 *  ������롼����μ¹�
	 *
	 *  �ޥ����ץ��å��ˤ��μ¹Ԥ���λ���Ƥ��顤���졼�֥ץ��å��ϼ�
	 *  �Ԥ��롥
	 */
	barrier_sync(1);

	if (x_sense_mprc()) {
		call_global_inirtn();
	}

	barrier_sync(2);

	call_local_inirtn();

	/*
	 *  ���֥������Ȥν�����Ԥ��ΥХꥢƱ��
	 */
	barrier_sync(3);

	/*
	 *  �����ͥ�ư��γ���
	 */
	my_p_pcb = get_my_p_pcb();
	my_p_pcb->kerflg = true;
	LOG_KER_ENTER();
	start_dispatch();
	assert(0);
}

#endif /* TOPPERS_sta_ker */

/*
 *  �����ͥ�ν�λ
 */
#ifdef TOPPERS_ext_ker

ER
ext_ker(void)
{
	PCB *my_p_pcb;

	SIL_PRE_LOC;

	LOG_EXT_KER_ENTER();

	/*
	 *  ����ߥ�å����֤˰ܹ�
	 */
	SIL_LOC_INT();

	my_p_pcb = get_my_p_pcb();

	/*
	 *  ���ԥ��å���������Ƥ�����ϡ����ԥ��å���������
	 */
	force_unlock_spin(my_p_pcb);

	/*
	 *  �����ͥ�ư��ν�λ
	 */
	LOG_KER_LEAVE();
	my_p_pcb->kerflg = false;

	/*
	 *  ¾�Υץ��å��ؽ�λ�������׵᤹��
	 */
	ext_ker_request();

	/*
	 *  �����ͥ�ν�λ�����θƽФ�
	 *
	 *  �󥿥�������ƥ����Ȥ��ڤ괹���ơ�exit_kernel��ƤӽФ���
	 */
	call_exit_kernel();

	/* 
	 *  ����ѥ���ηٹ��к��ʤ�������뤳�ȤϤʤ��Ϥ��� 
	 */ 
	SIL_UNL_INT();
	LOG_EXT_KER_LEAVE(E_SYS);
	return(E_SYS);
}

/*
 *  �����ͥ�ν�λ����
 */
void
exit_kernel(void)
{
	/*
	 *  SIL���ԥ��å��ζ�������
	 */
	TOPPERS_sil_force_unl_spn();

	barrier_sync(4);

	/*
	 *  ��λ�����롼����μ¹�
	 */
	call_local_terrtn();

	barrier_sync(5);

	if (x_sense_mprc()) {
		call_global_terrtn();
	}

	barrier_sync(6);

	/*
	 *  �������åȰ�¸�ν�λ����
	 */
	target_exit();
	assert(0);
}

#endif /* TOPPERS_ext_ker */
