$ 
$     �ѥ�2�Υ�����¸�ƥ�ץ졼�ȡ�ARM�ѡ�
$ 

$ 
$ DEF_EXC�ǻ��ѤǤ���CPU�㳰�ϥ�ɥ��ֹ�
$ 
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

$ 
$  �㳰�ϥ�ɥ�ơ��֥�
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_exch_table[TNUM_EXCH] = {$NL$
$JOINEACH excno {0,1,...,6} ",\n"$ 
    $number = excno|(prcid<<16)$
	$IF LENGTH(EXC.EXCNO[number])$
		$TAB$(FP)($EXC.EXCHDR[number]$)
	$ELSE$
		$TAB$(FP)(_kernel_default_exc_handler)
	$END$
	$SPC$$FORMAT("/* %d */", +excno)$
$END$
$NL$};$NL$
$NL$

$END$

$ 
$  �㳰�ϥ�ɥ饢�������ơ��֥�
$ 
const FP* const _kernel_p_exch_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_exch_table
$END$
$NL$};$NL$
$NL$
