/*
 *  @(#) $Id: core_cfg1_out.h 955 2012-10-30 07:31:22Z ertl-honda $
 */

/*
 *		cfg1_out.c���󥯤��뤿���ɬ�פʥ����֤����
 */

void sta_ker(void){}
void _kernel_target_mprc_initialize(void){}
uint_t _kernel_start_sync;
STK_T *const	_kernel_istkpt_table[TNUM_PRCID];

/*
 *  ���ե��åȥե�������������뤿������
 */
const uint8_t   MAGIC_1 = 0x12;
const uint16_t  MAGIC_2 = 0x1234;
const uint32_t  MAGIC_4 = 0x12345678;

const TCB TCB_enatex = {
	{ NULL, NULL }, NULL, 0U, 0U,
	false, false, true,
	0U, NULL, { NULL, NULL }, 0U,
#if TTYPE_KLOCK != G_KLOCK
	false, /* pend_relwai */
	false, /* pend_chgpri */
	0U,    /* pend_newpri */
#endif /* TTYPE_KLOCK != G_KLOCK */
	0U, {0U, NULL, NULL}, NULL, {{0U, 0U, 0U}}
};
