$ 
$     �ѥ�2�Υ��åװ�¸�ƥ�ץ졼�ȡ�AT91SKYEYE�ѡ�
$     ARMCC�Ȥζ�����

$ 
$ ͭ����CPU�㳰�ϥ�ɥ��ֹ�
$ 
$EXCNO_VALID = { 
	0x10001,0x10002,0x10003,0x10004,0x10006;
	0x20001,0x20002,0x20003,0x20004,0x20006;
	0x30001,0x30002,0x30003,0x30004,0x30006;
	0x40001,0x40002,0x40003,0x40004,0x40006
}$

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ桤CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INTNO_VALID = { 
	0x10000,0x10001,...,0x1001f;
	0x20000,0x20001,...,0x2001f;
	0x30000,0x30001,...,0x3001f;
	0x40000,0x40001,...,0x4001f
}$

$INHNO_VALID = INTNO_VALID$

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT�ǻ��ѤǤ������ߥϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$INTNO_CFGINT_VALID  = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -1,-2,...,-7 }$

$ 
$  �����°����Υ������åȰ�¸���Ѥ���ӥå�
$ 
$TARGET_INTATR = TA_HIGHLEVEL$

$ 
$  ���֥������ȴ�Ϣ�Υ�������������ʥץ��å���
$ 

$ 
$  ���饹���Ф������
$ 

$ 
$  ���饹��
$ 
$NUM_CLASS = 9$

$ 
$ ���饹 TCL_1�ʥ��饹ID 1�ˤ˴ؤ������
$ 

$  ������դ��ץ��å�(ID����)
$CLASS_AFFINITY_INI[1] = 1$

$  �ޥ����졼������ǽ�ʥץ��å��Υޥ�������
$CLASS_AFFINITY_MASK[1] = 0x0000000f$

$  ���֥������ȥ�å�
$ P_LOCK�ξ��˻��Ѥ��륪�֥������ȥ�å�����ĥץ��å���ID�����
$CLASS_OBJ_LOCK[1] = 1$

$ 
$ ���饹 TCL_2�ʥ��饹ID 2�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x0000000f$
$CLASS_OBJ_LOCK[2] = 2$

$ 
$ ���饹 TCL_3�ʥ��饹ID 3�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[3] = 3$
$CLASS_AFFINITY_MASK[3] = 0x0000000f$
$CLASS_OBJ_LOCK[3] = 3$

$ 
$ ���饹 TCL_4�ʥ��饹ID 4�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[4] = 4$
$CLASS_AFFINITY_MASK[4] = 0x0000000f$
$CLASS_OBJ_LOCK[4] = 4$

$ 
$ ���饹 TCL_1_ONLY�ʥ��饹ID 5�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[5] = 1$
$CLASS_AFFINITY_MASK[5] = 0x00000001$
$CLASS_OBJ_LOCK[5] = 1$

$ 
$ ���饹 TCL_2_ONLY�ʥ��饹ID 6�ˤ˴ؤ������
$ 
$CLASS_AFFINITY_INI[6] = 2$
$CLASS_AFFINITY_MASK[6] = 0x00000002$
$CLASS_OBJ_LOCK[6] = 2$

$ 
$ ���饹 TCL_3_ONLY�ʥ��饹ID 7�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[7] = 3$
$CLASS_AFFINITY_MASK[7] = 0x00000004$
$CLASS_OBJ_LOCK[7] = 3$

$ 
$ ���饹 TCL_4_ONLY�ʥ��饹ID 8�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[8] = 4$
$CLASS_AFFINITY_MASK[8] = 0x00000008$
$CLASS_OBJ_LOCK[8] = 4$

$ 
$ ���饹 TCL_SYSTIM_PRC�ʥ��饹ID 9�� �˴ؤ������
$ 
$CLASS_AFFINITY_INI[9] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[9] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1) $
$CLASS_OBJ_LOCK[9] = TOPPERS_SYSTIM_PRCID$

$ 
$  ������¸�ƥ�ץ졼�ȤΥ��󥯥롼�ɡ�ARM�ѡ�
$ 
$INCLUDE"../../arch/arm_gcc/common/core.tf"$

$ 
$  �����ͥ���٥ơ��֥�
$ 

$FOREACH prcid RANGE(1, TNUM_PRCID)$

const PRI _kernel_prc$prcid$_inh_ipm_table[TNUM_INH] = {$NL$
$FOREACH inhno INHNO_VALID$
	$IF (inhno & 0xffff0000) == (prcid << 16) $
		$IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
		  $TAB$$INT.INTPRI[inhno]$,
		$ELSE$
		  $TAB$0,
		$END$
		$SPC$$FORMAT("/* 0x%x */", +inhno)$$NL$
	$END$
$END$
};$NL$
$NL$

$END$

$ 
$  �����ͥ���٥ơ��֥륢�������ơ��֥�
$ 
const PRI* const _kernel_p_inh_ipm_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_inh_ipm_table
$END$
$NL$};$NL$
$NL$

$ 
$  ����ߥޥ����ơ��֥�
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const uint32_t _kernel_prc$prcid$_ipm_mask_table[8]={$NL$
$FOREACH intpri { 0,-1,...,-7 }$
	$intmask = 0$
	$FOREACH intno (INT.ID_LIST)$
		$IF CLASS_AFFINITY_INI[INT.CLASS[intno]] == prcid $
			$IF INT.INTPRI[intno] >= intpri $
				$intmask = intmask | (1 << (INT.INTNO[intno] & 0x0000FFFF))$
			$END$
		$END$
	 $END$
 $TAB$UINT32_C($FORMAT("0x%08x", intmask)$), /* Priority $+intpri$ */$NL$
$END$
};$NL$
$NL$
$END$

$ 
$  ����ߥޥ����ơ��֥륢�������ơ��֥�
$ 
const uint32_t* const _kernel_p_ipm_mask_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_ipm_mask_table
$END$
$NL$};$NL$
$NL$

$ 
$  ����ߥϥ�ɥ�ơ��֥�
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_inh_table[TNUM_INH] = {$NL$
$FOREACH inhno INHNO_VALID$
	$IF (inhno & 0xffff0000) == (prcid << 16) $
		$IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
			$TAB$(FP)($INH.INTHDR[inhno]$),
		$ELSE$
			$TAB$(FP)(_kernel_default_int_handler),
		$END$
		$SPC$$FORMAT("/* 0x%x */", +inhno)$$NL$
	$END$
$END$
};$NL$
$NL$

$END$

$ 
$  ����ߥϥ�ɥ�ơ��֥륢�������ơ��֥�
$ 
const FP* const _kernel_p_inh_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_inh_table
$END$
$NL$};$NL$
$NL$
