$ 
$     �ѥ�2�Υ��åװ�¸�ƥ�ץ졼�ȡ�MPCORE�ѡ�
$ 

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
$  DEF_INT�ǻ��ѤǤ������ߥϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$INTNO_CFGINT_VALID  = INTNO_VALID$

$ 
$ ATT_ISR�Υ������åȰ�¸�Υ����å�
$ �ɤΥץ��å��Ǥ�����դ���ǽ�ʳ�����ֹ�ϡ�������դ���ǽ�ץ��å��ˤΤ�
$ ���դ���ǽ�Ǥ��롥
$ 
$FUNCTION TARGET_CHECK_ATT_ISR$
	$IF ((ISR.INTNO[ARGV[1]] & 0xffff0000) == 0) 
		&& ((1 << (CLASS_AFFINITY_INI[ISR.CLASS[ARGV[1]]] - 1)) != CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("processor affinity of `0x%1$x\' in %2% is not match with class %3% processor affinity mask `0x%4$x\'."), +ISR.INTNO[ARGV[1]], "ATT_ISR", ISR.CLASS[ARGV[1]], +CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$$END$
	$END$
$END$

$ 
$  ARM��¸�ƥ�ץ졼�ȤΥ��󥯥롼��
$ 
$INCLUDE"../common/core.tf"$

$ 
$  ����ߥϥ�ɥ�ơ��֥�
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_inh_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(0, (TNUM_INH - 1))$
	$minhno = inhno | (prcid << intno_cpu_shift)$
	$IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$IF LENGTH(INH.INHNO[minhno]) && (CLASS_AFFINITY_INI[INH.CLASS[minhno]] == prcid)$
			$TAB$(FP)($INH.INTHDR[minhno]$),
		$ELSE$
			$TAB$(FP)(_kernel_default_int_handler),
		$END$
	$END$
	$SPC$$FORMAT("/* 0x%x */", +minhno)$$NL$
$END$
};$NL$
$NL$

$END$$NL$

$ 
$  ����ߥϥ�ɥ饢�������ơ��֥�
$ 
const FP* const _kernel_p_inh_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_inh_table
$END$
$NL$};$NL$
$NL$

$ 
$  �����°���ơ��֥�
$ 
$NL$
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const uint8_t _kernel_prc$prcid$_cfgint_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(0, (TNUM_INH - 1))$
	$minhno = inhno | (prcid << intno_cpu_shift)$
	$IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
		$TAB$1U,
	$ELSE$
		$IF LENGTH(INH.INHNO[minhno]) && (CLASS_AFFINITY_INI[INH.CLASS[minhno]] == prcid)$
			$TAB$1U,
		$ELSE$
			$TAB$0U,
		$END$
	$END$
	$SPC$$FORMAT("/* 0x%x */", +minhno)$$NL$
$END$
};$NL$
$NL$

$END$$NL$

$ 
$  �����°�����������ơ��֥�
$ 
const uint8_t* const _kernel_p_cfgint_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_cfgint_table
$END$
$NL$};$NL$
$NL$
