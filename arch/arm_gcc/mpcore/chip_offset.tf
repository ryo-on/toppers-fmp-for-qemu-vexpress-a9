$
$       ���ե��åȥե����������ѥƥ�ץ졼�ȥե������AT91SKYEY�ѡ�
$

$
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$
$INCLUDE "kernel/genoffset.tf"$

$
$  ������¸�ƥ�ץ졼�ȤΥ��󥯥롼�ɡ�ARM�ѡ�
$
$INCLUDE"../common/core_offset.tf"$

$
$  ���ե��å��ͤΥޥ������������
$
$DEFINE("PCB_p_firstlock", offsetof_PCB_p_firstlock)$
$DEFINE("PCB_p_secondlock", offsetof_PCB_p_secondlock)$
$DEFINE("PCB_locspnid", offsetof_PCB_locspnid)$

$DEFINE("PCB_excpt_nest_count", offsetof_PCB_excpt_nest_count)$
$DEFINE("PCB_istkpt", offsetof_PCB_istkpt)$
$DEFINE("PCB_p_exch_tbl", offsetof_PCB_p_exch_tbl)$

$DEFINE("PCB_p_inh_tbl", offsetof_PCB_p_inh_tbl)$

