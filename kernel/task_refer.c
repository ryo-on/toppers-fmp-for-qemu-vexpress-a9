/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
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
 *  @(#) $Id: task_refer.c 529 2010-02-16 09:17:03Z ertl-honda $
 */

/*
 *		�������ξ��ֻ��ȵ�ǽ
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "semaphore.h"
#include "eventflag.h"
#include "dataqueue.h"
#include "pridataq.h"
#include "mailbox.h"
#include "mempfix.h"
#include "time_event.h"
#include "mp.h"

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_REF_TSK_ENTER
#define LOG_REF_TSK_ENTER(tskid, pk_rtsk)
#endif /* LOG_REF_TSK_ENTER */

#ifndef LOG_REF_TSK_LEAVE
#define LOG_REF_TSK_LEAVE(ercd, pk_rtsk)
#endif /* LOG_REF_TSK_LEAVE */

/*
 *  �������ξ��ֻ���
 */
#ifdef TOPPERS_ref_tsk

ER
ref_tsk(ID tskid, T_RTSK *pk_rtsk)
{
	TCB		*p_tcb;
	uint_t	tstat;
	ER		ercd;
	PCB		*p_pcb;

	LOG_REF_TSK_ENTER(tskid, pk_rtsk);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);

	t_lock_cpu();
	p_tcb = get_tcb_self(tskid, get_my_p_pcb());
	p_pcb = t_acquire_tsk_lock(p_tcb);
	tstat = p_tcb->tstat;
	if (TSTAT_DORMANT(tstat)) {
		/*
 		 *  �оݥ��������ٻ߾��֤ξ��
		 */
		pk_rtsk->tskstat = TTS_DMT;
	}
	else {
		/*
 		 *  ���������֤μ�Ф�
		 */
		if (TSTAT_SUSPENDED(tstat)) {
			if (TSTAT_WAITING(tstat)) {
				pk_rtsk->tskstat = TTS_WAS;
			}
			else {
				pk_rtsk->tskstat = TTS_SUS;
			}
		}
		else if (TSTAT_WAITING(tstat)) {
			pk_rtsk->tskstat = TTS_WAI;
		}
		else if (p_tcb == p_pcb->p_runtsk) {
			pk_rtsk->tskstat = TTS_RUN;
		}
		else {
			pk_rtsk->tskstat = TTS_RDY;
		}

		/*
 		 *  ����ͥ���٤ȥ١���ͥ���٤μ�Ф�
		 */
		pk_rtsk->tskpri = EXT_TSKPRI(p_tcb->priority);
		pk_rtsk->tskbpri = EXT_TSKPRI(p_tcb->priority);

		if (TSTAT_WAITING(tstat)) {
			/*
	 		 *  �Ԥ��װ����Ԥ��оݤΥ��֥������Ȥ�ID�μ�Ф�
			 */
			switch (tstat & TS_WAIT_MASK) {
			case TS_WAIT_SLP:
				pk_rtsk->tskwait = TTW_SLP;
				break;
			case TS_WAIT_DLY:
				pk_rtsk->tskwait = TTW_DLY;
				break;
			case TS_WAIT_SEM:
				pk_rtsk->tskwait = TTW_SEM;
				pk_rtsk->wobjid = SEMID(((SEMCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_FLG:
				pk_rtsk->tskwait = TTW_FLG;
				pk_rtsk->wobjid = FLGID(((FLGCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_SDTQ:
				pk_rtsk->tskwait = TTW_SDTQ;
				pk_rtsk->wobjid = DTQID(((DTQCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_RDTQ:
				pk_rtsk->tskwait = TTW_RDTQ;
				pk_rtsk->wobjid = DTQID(((DTQCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_SPDQ:
				pk_rtsk->tskwait = TTW_SPDQ;
				pk_rtsk->wobjid = PDQID(((PDQCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_RPDQ:
				pk_rtsk->tskwait = TTW_RPDQ;
				pk_rtsk->wobjid = PDQID(((PDQCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_MBX:
				pk_rtsk->tskwait = TTW_MBX;
				pk_rtsk->wobjid = MBXID(((MBXCB*)(p_tcb->p_wobjcb)));
				break;
			case TS_WAIT_MPF:
				pk_rtsk->tskwait = TTW_MPF;
				pk_rtsk->wobjid = MPFID(((MPFCB*)(p_tcb->p_wobjcb)));
				break;
			}

			/*
	 		 *  �����ॢ���Ȥ���ޤǤλ��֤μ�Ф�
			 */
			if ((p_tcb->tmevtb).callback != NULL) {
				pk_rtsk->lefttmo =
				  (TMO) tmevt_lefttim(p_pcb->p_tevtcb,
									  &(p_tcb->tmevtb));
			}
			else {
				pk_rtsk->lefttmo = TMO_FEVR;
			}
		}

		/*
 		 *  �����׵ᥭ�塼���󥰿��μ�Ф�
		 */
		pk_rtsk->wupcnt = p_tcb->wupque ? 1U : 0U;
	}

	/*
	 *  ��ư�׵ᥭ�塼���󥰿��μ�Ф�
	 */
	pk_rtsk->actcnt = p_tcb->actque ? 1U : 0U;

	/*
	 *  ����ư�����դ��ץ��å��μ�Ф�
	 */
	pk_rtsk->actprc = p_tcb->actprc;

	/*
	 *  ���դ��ץ��å��μ�Ф�
	 */
	pk_rtsk->prcid = p_tcb->p_pcb->prcid;

	ercd = E_OK;
	release_tsk_lock(p_pcb);
	t_unlock_cpu();

  error_exit:
	LOG_REF_TSK_LEAVE(ercd, pk_rtsk);
	return(ercd);
}

#endif /* TOPPERS_ref_tsk */
