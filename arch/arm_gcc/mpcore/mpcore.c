/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: mpcore.c 955 2012-10-30 07:31:22Z ertl-honda $
 */

#include "kernel_impl.h"

/*
 *  DIC CPU���󥿥ե�������Ϣ
 */

/*
 *  CPU���󥿥ե������ν����
 */
void
dic_cpu_init(void)
{
	/* CPU���󥿥ե�������̵���� */
	sil_wrw_mem((void *)DIC_CPUIF_CR, 0);

	/* ����ͥ���٤����� */
	dic_cpu_set_priority(DIC_MIN_PRIORITY);

	/* �����ͥ���٤����ӥå�ͭ���� */
	dic_cpu_set_bp(DIC_CPUIF_BPR_ALL);

	/* �ڥ�ǥ��󥰤��Ƥ����ǽ��������Τǡ�EOI �ˤ�ꥯ�ꥢ */
	sil_wrw_mem((void *)DIC_CPUIF_EOI,
				sil_rew_mem((void *)DIC_CPUIF_IAR));

	/* CPU���󥿥ե�������ͭ���� */
#ifdef TOPPERS_SAFEG_SECURE
    sil_wrw_mem((void *)DIC_CPUIF_CR, (DIC_CPUIF_CR_EN_S|DIC_CPUIF_CR_EN_NS|DIC_CPUIF_CR_FIQEN) );
#else /* !TOPPERS_SAFEG_SECURE */
	sil_wrw_mem((void *)DIC_CPUIF_CR, DIC_CPUIF_CR_EN);
#endif /* TOPPERS_SAFEG_SECURE */
}

/*
 *  CPU���󥿥ե������ν�λ
 */
void
dic_cpu_stop(void)
{
	/* CPU���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(DIC_CPUIF_CR), 0);
}


/*
 * DIC DIS���󥿥ե�������Ϣ
 */

/*
 *  ����߶ػ�
 */
void
dic_disable_int(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(DIC_CE + offset_addr), (1 << offset_bit));
}

/*
 *  ����ߵ���
 */
void
dic_enable_int(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(DIC_SE + offset_addr), (1 << offset_bit));
}

/*
 * ����ߥڥ�ǥ��󥰥��ꥢ
 */
void
dic_clear_pending(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(DIC_CP + offset_addr), (1 << offset_bit));
}

/*
 *  ����ߥڥ�ǥ��󥰥��å�
 */
void
dic_set_pending(uint8_t id){
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(DIC_SP + offset_addr), (1 << offset_bit));
}

/*
 *  ������׵�Υ����å�
 */
bool_t
dic_probe_int(uint8_t id){
	uint32_t state;
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	state = sil_rew_mem((void *)(DIC_SP + offset_addr));

	if ((state & (1 << offset_bit)) == (1 << offset_bit)) {
		return(true);
	}
	else {
		return(false);
	}
}

/*
 *  ����ߥ���ե�����졼���������
 */
void
dic_config(uint8_t id, uint8_t config){
	uint16_t offset_addr;
	uint16_t offset_bit;
	uint32_t cfgr_reg_val;
	SIL_PRE_LOC;

	offset_addr = (id / 16) * 4;
	offset_bit  = (id % 16) * 2;

	SIL_LOC_SPN();
	cfgr_reg_val  = sil_rew_mem((void *)(DIC_ICR + offset_addr));
	cfgr_reg_val &= ~(0x03U << offset_bit);
	cfgr_reg_val |= (0x03U & config) << offset_bit;
	sil_wrw_mem((void *)(DIC_ICR + offset_addr), cfgr_reg_val);
	SIL_UNL_SPN();
}

/*
 *  �����ͥ���٤Υ��å�
 *  ����ɽ�����Ϥ���
 */
void
dic_set_priority(uint8_t id, int pri){
	uint16_t offset_addr;
	uint16_t offset_bit;
	uint32_t pr_reg_val;
	SIL_PRE_LOC;

	offset_addr = (id / 4) * 4;
	offset_bit  = ((id % 4) * 8) + IPM_BIT_OFFSET;

	SIL_LOC_SPN();
	pr_reg_val  = sil_rew_mem((void *)(DIC_IPR + offset_addr));
	pr_reg_val &= ~(IPM_BIT_MASK << offset_bit);
	pr_reg_val |= (IPM_BIT_MASK & pri) << (offset_bit);
	sil_wrw_mem((void *)(DIC_IPR + offset_addr), pr_reg_val);
	SIL_UNL_SPN();
}

/*
 *  DIC����ߥ������åȤ�����
 *  cpus�ϥ������åȤȤ���CPU�Υӥåȥѥ�����ǻ���
 *   CPU0 : 0x01
 *   CPU1 : 0x02
 *   CPU2 : 0x04
 *   CPU3 : 0x08
 */
void
dic_set_target(uint8_t id, uint8_t cpus)
{
	uint32_t offset_addr;
	uint32_t offset_bit;
	uint32_t itr_reg_val;
	SIL_PRE_LOC;

	offset_addr = (id / 4) * 4;
	offset_bit  = (id % 4) * 8;

	SIL_LOC_SPN();
	itr_reg_val  = sil_rew_mem((void *)(DIC_ITR + offset_addr));
	itr_reg_val &= ~(0xf << offset_bit);
	itr_reg_val |= (cpus << offset_bit);
	sil_wrw_mem((void *)(DIC_ITR + offset_addr), itr_reg_val);
	SIL_UNL_SPN();
}

/*
 *  DIC���󥿥ե������ν����(SPI�Τ߽����)
 */
void
dic_init(void)
{
	int i;

	/* DIC���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(DIC_CR), 0);

#if __TARGET_ARCH_ARM == 7
#ifdef TOPPERS_SAFEG_SECURE
	/* ����ߥ������ƥ�������NonSecure�� */
	for(i = TMIN_GLOBAL_INTNO/32; i < DIC_TNUM_INT/32; i++){
		sil_wrw_mem((void *)(DIC_SEC + (4 * i)), 0xffffffff);
	}
#endif /* TOPPERS_SAFEG_SECURE */
#endif /* __TARGET_ARCH_ARM == 7 */

	/* ����ߤ����ƶػ� */
	for(i = TMIN_GLOBAL_INTNO/32; i < DIC_TNUM_INT/32; i++){
		sil_wrw_mem((void *)(DIC_CE + (4 * i)), 0xffffffff);
	}

	/* �ڥ�ǥ��󥰤򥯥ꥢ */
	for(i = TMIN_GLOBAL_INTNO/32; i < DIC_TNUM_INT/32; i++){
		sil_wrw_mem((void *)(DIC_CP + (4 * i)), 0xffffffff);
	}

	/* ͥ���ٺ��������  */
	for(i = TMIN_GLOBAL_INTNO/4; i < DIC_TNUM_INT/4; i++){
		sil_wrw_mem((void *)(DIC_IPR + (4 * i)), 0xffffffff);
	}

	/* �������åȽ����������CPU0�ء� */
	for(i = TMIN_GLOBAL_INTNO/4; i < DIC_TNUM_INT/4; i++){
		sil_wrw_mem((void *)(DIC_ITR + (4 * i)), 0x01010101);
	}

	/* �⡼�ɽ����(1-N Level) */
	for(i = TMIN_GLOBAL_INTNO/16; i < DIC_TNUM_INT/16; i++){
		sil_wrw_mem((void *)(DIC_ICR + (4 * i)), 0x55555555);
	}

	/* DIC���󥿥ե�������ͭ���� */
	sil_wrw_mem((void *)(DIC_CR), DIC_CR_ENABLE);
}

/*
 *  �ƥ����Ǽ¹Ԥ���DIC���󥿥ե�������SGI��PPI�ν����
 */
void
dic_sgi_ppi_init(void)
{
	int i;
#ifdef TOPPERS_SAFEG_SECURE
	/*
	 *  ����Non-Secure�ˤ���
	 */
	/* SGI������ */
	for(i = 0; i < 16; i++) {
		dic_set_security(i, 1);
	}
	/* PPI������ */
	dic_set_security(27, 1);
	dic_set_security(28, 1);
	dic_set_security(29, 1);
	dic_set_security(29, 1);
	dic_set_security(30, 1);
	dic_set_security(31, 1);
#endif /* TOPPERS_SAFEG_SECURE */

	/* ����ߤ����ƶػ� */
	for(i = 0; i < TMIN_GLOBAL_INTNO/32; i++){
		sil_wrw_mem((void *)(DIC_CE + (4 * i)), 0xffffffff);
	}

	/* �ڥ�ǥ��󥰤򥯥ꥢ */
	for(i = 0; i < TMIN_GLOBAL_INTNO/32; i++){
		sil_wrw_mem((void *)(DIC_CP + (4 * i)), 0xffffffff);
	}

#ifdef TOPPERS_SAFEG_SECURE
	/* ͥ���ٺ��������  */
    /* Linux����������ʤ���������˽���� */
	for(i = 0; i < 32/4; i++){
        /*
         * �����0xffffffff�Ǥ褤����Linux����������ꥳ���ʹߤ�
         * �����γ����ͥ���٤����ꤷ�ʤ����ᡤ���������ꤹ�롥
         * (Linux�Ǥϡ�0xa0a0a0a0�Ǥ��٤Ƥγ���ߤ��������Ƥ��뤬
         *  �Υ󥻥��奢¦�����ͥ���ٳ���ߤϥ����奢¦���鸫���
         *  1�ӥåȥ��եȤ�����̥ӥåȤ�1�Ȥʤä���Τ˸����뤿��
         *  0xd0d0d0d0���ͤˤʤ�)
         */
		sil_wrw_mem((void *)(DIC_IPR + (4 * i)), 0xd0d0d0d0);
	}
#else /* !TOPPERS_SAFEG_SECURE */
	/* ͥ���ٺ��������  */
	for(i = 0; i < TMIN_GLOBAL_INTNO/4; i++){
		sil_wrw_mem((void *)(DIC_IPR + (4 * i)), 0xffffffff);
	}
#endif /* TOPPERS_SAFEG_SECURE */

	/* �⡼�ɽ����(1-N Level) */
	for(i = 0; i < TMIN_GLOBAL_INTNO/16; i++){
		sil_wrw_mem((void *)(DIC_ICR + (4 * i)), 0x55555555);
	}
}

#if __TARGET_ARCH_ARM == 7
/*
 * ����ߥ������ƥ�����
 * ������ֹ�Ȥ��Υ������ƥ��ǻ���
 * ���� ns (non secure bit) :
 *     0 -> secure(FIQ) setting
 *     1 -> non-secure(IRQ) setting
 */
void
dic_set_security(int intno, unsigned int ns){
	unsigned int reg = DIC_SEC + ((intno/32)*4);
	if (ns == 1) {
		sil_wrw_mem((void *)(reg),
					sil_rew_mem((void *)(reg)) | (1 << (intno%32)));
	}
	else {
		sil_wrw_mem((void *)(reg),
					sil_rew_mem((void *)(reg)) & ~(1 << (intno%32)));
	}
}
#endif /* __TARGET_ARCH_ARM == 7 */

/*
 *  DIC���󥿥ե������ν�λ
 */
void
dic_stop(void)
{
	/* DIC���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(DIC_CR), 0);
}

/*
 *
 * SCU��Ϣ�δؿ�
 *
 */

/*
 *  CP15��AUXILIARY�쥸������SA�ӥåȤ򥻥åȤ���SMP�⡼�ɤˤ���
 */
Inline void
enable_sa(void){
	uint32_t bits;

	CP15_AUXILIARY_READ(bits);
	bits |= CP15_AUXILIARY_SA_BIT;
	CP15_AUXILIARY_WRITE(bits);
}

Inline void
scu_enable(void){
	uint32_t scu_ctrl;

	/* SCU�� tag RAMS ��̵���� */
	sil_wrw_mem((void*)MPCORE_SCU_IALL, MPCORE_SCU_IALL_WAYS);

	/* SCU��ͭ���� */
	scu_ctrl  = sil_rew_mem((void *)MPCORE_SCU_CTRL);
	scu_ctrl |= MPCORE_SCU_CTRL_EN;
	sil_wrw_mem((void *)MPCORE_SCU_CTRL, scu_ctrl);
}

/*
 *  SCU�ν���������ʥޥ����ץ��å��Τ߼¹ԡ�
 */
void
scu_init(void){
	/* SCU ��ͭ���� */
	scu_enable();

	/* ���ƤΥ����Υ⡼�ɤ�NORMAL�Ȥ��� */
	sil_wrw_mem((void *)MPCORE_SCU_CPUST, 0x00U);

#ifdef TOPPERS_SAFEG_SECURE
	/* �Υ�ȥ饹��¦�����A9��¢�����ޤؤΥ������������ */
	sil_wrw_mem((void *)MPCORE_SCU_SNSAC, 0xFFF); // ��CPU�����
#endif /* TOPPERS_SAFEG_SECURE */
}

/*
 *  SMP�⡼�ɤ����ꤹ��
 */
void
mpcore_smp_mode_enable(void){
	uint32_t sr;

	/* ������߶ػ� */
	sr = current_sr();
	set_sr(sr|CPSR_IRQ_BIT|CPSR_FIQ_BIT);

	/* ���㥷���̵�� */
	mpcore_dcache_clean_and_invalidate();
	mpcore_icache_invalidate();

	/* Data Synchronization Barrier */
	mpcore_data_sync_barrier();

	/* TLB�ν���� */
	mpcore_invalidate_unfied_tlb();

#ifndef TOPPERS_SAFEG_NONSECURE
	/* CP15��SMP/nAMP bit �򥻥åȤ��� */
	enable_sa();
#endif /* TOPPERS_SAFEG_NONSECURE */

	/* ����߶ػ߾��֤򸵤��᤹ */
	set_sr(sr);
}

/*
 *  D����å���򳫻�
 */
void
mpcore_dcache_enable(void)
{
	uint32_t bits;

	CP15_CONTROL_READ(bits);

	/* ���Ǥ�ON�ʤ�꥿���� */
	if (bits & CP15_CONTROL_C_BIT){
		return;
	}

	mpcore_dcache_invalidate();

	bits |= CP15_CONTROL_C_BIT;
	CP15_CONTROL_WRITE(bits);
}

/*
 *  D����å������ߤ���̵���Ȥ��롥
 *  CA9�Ǥϡ�D����å��夬̵���ʾ��֤�Clean and Invalidate()��¹Ԥ���ȡ�
 *  ˽�����뤿�ᡤD����å���ξ��֤�Ƚ�Ǥ��ơ�̵���ʾ��ϡ�Invalidate
 *  �Τߤ�Ԥ���
 */
void
mpcore_dcache_disable(void)
{
	uint32_t bits;

	CP15_CONTROL_READ(bits);
	if( bits & CP15_CONTROL_C_BIT ){
		bits &= ~CP15_CONTROL_C_BIT;
		CP15_CONTROL_WRITE(bits);
		mpcore_dcache_clean_and_invalidate();
	}
	else{
		mpcore_dcache_invalidate();
	}
}

/*
 * I����å���γ���
 */
void mpcore_icache_enable (void)
{
	uint32_t bits;

	CP15_CONTROL_READ(bits);

	/*
	 *  ���Ǥ�ͭ���ʤ�꥿����
	 */
	if(bits & CP15_CONTROL_I_BIT){
		return;
	}

	mpcore_icache_invalidate();

	bits |= CP15_CONTROL_I_BIT;
	CP15_CONTROL_WRITE(bits);
}

/*
 *  I����å�������
 */
void
mpcore_icache_disable (void)
{
	uint32_t bits;

	CP15_CONTROL_READ(bits);
	bits &= ~CP15_CONTROL_I_BIT;
	CP15_CONTROL_WRITE(bits);

	mpcore_icache_invalidate();
}

/*
 *  I/D����å����ξ����ͭ����
 */
void
mpcore_cache_enable(void)
{
	mpcore_dcache_enable();
	mpcore_icache_enable();
}

/*
 *  I/D����å����ξ����̵����
 */
void
mpcore_cache_disable(void)
{
	mpcore_dcache_disable();
	mpcore_icache_disable();
}

/*
 *  MMU��Ϣ�Υɥ饤��
 */

/*
ARMv7��Section�ơ��֥�λ���
  31:20 : Section base address
  19    : NS
  17    : nG
  16    :  S
  15    : AP[2]
  14:12 : TEX[2:0]
  11:10 : AP[1:0]
  8:5   : Domain
  4     : XN
  3     : C
  2     : B
  0     : PXN

 */

#define DOMAIN_NO  1
#define PAGE_TABLE_SIZE  0x00004000 /* 4KB */

/*
 * �ڡ����ơ��֥�
 */
static uint8_t PageTable[TNUM_PRCID][PAGE_TABLE_SIZE]  __attribute__ ((aligned (0x4000)));

#define my_PageTable (PageTable[x_prc_index()])

#define SIZE_1M    0x00100000

/*
 * ����˽���,����Υޥåԥ󥰤�Ԥ�
 * �ޥåԥ󥰤�ñ�̤�1MB
 */
void
mmu_map_memory(MEMORY_ATTRIBUTE *m_attribute)
{
	uint32_t size;
	uintptr_t va;
	uintptr_t pa;
	uint32_t ttb;
	uint32_t *sptr;
	uint32_t fix_val;

	size = m_attribute->size;
	va   = m_attribute->va;
	pa   = m_attribute->pa;

	/* MBñ�̤ˤʤ�褦�˥����������� */
	size = (size + 0x000FFFFF) & ~0x000FFFFF;

	/*
	 * �ڡ����ơ��֥�Υ١������ɥ쥹�����
	 */
	CP15_TTB0_READ(ttb);

	fix_val =  (m_attribute->s << 16) | (m_attribute->tex << 12) | (m_attribute->ap << 10)
		        | (m_attribute->c << 3) | (m_attribute->b << 2) | (1 << 1);
	sptr  = (uint32_t *)((ttb & 0xFFFFC000) | (((va & 0xFFF00000) >> 20) << 2));

	while(size > 0) {
		sptr  = (uint32_t *)((ttb & 0xFFFFC000) | (((va & 0xFFF00000) >> 20) << 2));
		*sptr++ = pa | fix_val;
		va   += SIZE_1M;
		pa   += SIZE_1M;
		size -= SIZE_1M;
	}
}

/*
 *  MMU�ν����
 */
void
mpcore_mmu_init(void)
{
	uint32_t bits = 0;

	/* �ץ�ե��å��Хåե��򥯥ꥢ */
	mpcore_pbuffer_flash();

	/*
	 * TTBR0���Ѥ����Ѥ˻���
	 */
	CP15_TTBCR_WRITE(0);

	/*
	 * �Ѵ��ơ��֥�(TT)�Ȥ��ơ�PageTable����Ѥ���
	 * Shared�ӥåȤ򥻥å�
	 */
#if __TARGET_ARCH_ARM == 6
	CP15_TTB0_WRITE((((uint32_t)my_PageTable)|CP15_TTB0_RGN_S|CP15_TTB0_RGN_WBWA));
#else /* __TARGET_ARCH_ARM == 7 */
	CP15_TTB0_WRITE((((uint32_t)my_PageTable)|CP15_TTB0_RGN_S|CP15_TTB0_RGN_WBWA|CP15_TTB0_IRGN_WBWA));
#endif /* __TARGET_ARCH_ARM == 7 */

	/* �ץ�ե��å��Хåե��򥯥ꥢ */
	mpcore_pbuffer_flash();

	/*
	 *  �������åȰ�¸���Ǥ�MMU�ν����
	 */
	target_mmu_init();

	/*
	 * �ɥᥤ���ֹ�򥻥å�
	 */
	CP15_DOMAINS_WRITE(DOMAIN_NO);

	/*
	 * CONTROL���ץ��å��� M�ӥåȡ�XP�ӥåȤ򥻥åȤ��ơ�
	 * MMU��ͭ���ˤ���
	 */
	CP15_CONTROL_READ(bits);
	bits |= CP15_CONTROL_M_BIT | CP15_CONTROL_XP_BIT;
	CP15_CONTROL_WRITE(bits);
}

#if __TARGET_ARCH_ARM == 6
/*
 * SCU�����󥿤ν������MN0����ѡ�
 */
void
scu_counter_init(void)
{
	/*
	 *  MN0�� Cycle Count ������
	 */
	sil_wrw_mem((void *)MPCORE_SCU_PM_EVT0,
				sil_rew_mem((void *)MPCORE_SCU_PM_EVT0) | MPCORE_SCU_PM_EVT_CYC_COUNT0_4);

	/*
	 *  �ꥻ�åȤȥ�������
	 */
	sil_wrw_mem((void *)MPCORE_SCU_PM_CTRL,
			sil_rew_mem((void *)MPCORE_SCU_PM_CTRL) | MPCORE_SCU_PM_CTRL_RST | MPCORE_SCU_PM_CTRL_ENA);
}
#endif /* __TARGET_ARCH_ARM == 6 */
