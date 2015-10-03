$ 
$       オフセットファイル生成用テンプレートファイル（AT91SKYEY用）
$ 

$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/genoffset.tf"$

$ 
$  コア依存テンプレートのインクルード（ARM用）
$ 
$INCLUDE"../../arch/arm_gcc/common/core_offset.tf"$

$ 
$  オフセット値のマクロ定義の生成
$ 
$DEFINE("PCB_p_firstlock", offsetof_PCB_p_firstlock)$
$DEFINE("PCB_p_secondlock", offsetof_PCB_p_secondlock)$
$DEFINE("PCB_locspnid", offsetof_PCB_locspnid)$

$DEFINE("PCB_excpt_nest_count", offsetof_PCB_excpt_nest_count)$
$DEFINE("PCB_istkpt", offsetof_PCB_istkpt)$
$DEFINE("PCB_p_exch_tbl", offsetof_PCB_p_exch_tbl)$

$DEFINE("PCB_idf", offsetof_PCB_idf)$
$DEFINE("PCB_ipm", offsetof_PCB_ipm)$
$DEFINE("PCB_p_ipm_mask_tbl", offsetof_PCB_p_ipm_mask_tbl)$
$DEFINE("PCB_p_inh_tbl", offsetof_PCB_p_inh_tbl)$
$DEFINE("PCB_p_inh_ipm_tbl", offsetof_PCB_p_inh_ipm_tbl)$
