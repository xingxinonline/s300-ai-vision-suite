/******************************************************************************\
* Name        : tests_aux.c
* Author      : Eran Rebenshtok
* Copyright   :
* Description : CSL Tests auxilary API tests
\******************************************************************************/
#include "csl_test.h"

 /*********************************************************************************************
 *
 *	Tests global variables
 *
 *********************************************************************************************/
volatile uint8_t ALIGN(g_buffer_internal[MEM_BUFF_INTERNAL_SIZE], BUFF_ALIGN) 													PRAGMA_DSECT_NO_LOAD("int_sect");
volatile uint8_t ALIGN(g_buffer_external[MEM_BUFF_EXTERNAL_SIZE], BUFF_ALIGN) 													PRAGMA_DSECT_NO_LOAD("ext_sect");
#ifdef CEVABX
	volatile uint8_t ALIGN(g_buffer_external_cacheable1[MEM_BUFF_EXTERNAL_CACHE_SIZE], BUFF_ALIGN) 									PRAGMA_DSECT_NO_LOAD("ext_sect_cache");
	volatile uint8_t ALIGN(g_buffer_external_cacheable2[MEM_BUFF_EXTERNAL_CACHE_SIZE], BUFF_ALIGN) 									PRAGMA_DSECT_NO_LOAD("ext_sect_cache");
#endif /* CEVABX */
uint8_t ALIGN(g_buffer_external_dbg[MEM_BUFF_EXTERNAL_DBG_SIZE], BUFF_ALIGN) 											PRAGMA_DSECT_NO_LOAD("ext_sect_dbg");
volatile uint32_t g_is_move_to_supervisor = CSL_FALSE;

 /*********************************************************************************************
 *
 *	Tests service functions
 *
 *********************************************************************************************/
void reset_memory(uint8_t* src, uint32_t size)
{
	memset(src, 0, size);
}

void set_memory_inc(uint8_t* dst, uint32_t size)
{
	uint32_t counter = 0;
	while (size--)
		*dst++ = ++counter;
}

void set_memory_dec(uint8_t* dst, uint32_t size)
{
	uint32_t counter = 0;
	while (size--)
		*dst++ = --counter;
}


#if defined SENSPRO || defined CEVABX


/*********************************************************************************************
* @function	HW_EXCPTIONS_move_to_user_mode
* @author	Ravid Rzaev
* @date 	11/04/2021
* @brief	Sets the core's to user mode.
* @return	E_csl_status
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_move_to_user_mode(void)
{
	__asm__ volatile( "mov #RESTRICT, r1.ui\n"
                  "nop #0x4\n"
                  "nop #0x3\n"
                  "movp {supervisor} r1.ui, retregi.ui\n"
                  "mov #0x100, r1.ui\n"
                  "nop #0x4\n"
                  "nop #0x3\n"
                  "movp {supervisor} r1.ui, ntcsr.ui\n"
                  "reti\n"
                  "RESTRICT:" );

	return CSL_SUCCESS;
}


/*********************************************************************************************
* @author	Ravid Rzaev
* @date 	11/04/2021
* @brief	handler function for HW_EXCPTIONS_move_to_supervisor_mode() function
*           or a general trap function (according to g_is_move_to_supervisor)
*********************************************************************************************/
__asm__ ( ".EXTERN g_is_move_to_supervisor\n"
#if CSL_USER_CONF_ASSERT_TRAPE == CSL_CONFIG_ENABLED
		".EXTERN g_assertion_fault_occurred\n"
#endif /* CSL_USER_CONF_ASSERT_TRAPE == CSL_CONFIG_ENABLED */
		".globl __cxd_trap_handler\n"
          "__cxd_trap_handler:\n"
          "push{in2} r0.ui, r1.ui\n"
          "mov #g_is_move_to_supervisor, r1.ui\n"
          "ld (r1.ui).ui, r0.ui\n"
        "nop\n"
          "brrcmp{eq,ds0} r0.ui, #0, #assersion\n"
          "mov #0x0, r1.ui\n"
          "nop #0x4\n"
          "nop #0x3\n"
          "movp {supervisor} r1.ui, ntcsr.ui\n"
          "movp {supervisor} r1.ui, cecsr.ui\n"
          "pop{in2} r0.ui, r1.ui\n"
          "reti\n"
          "assersion:\n"
#if CSL_USER_CONF_ASSERT_TRAPE == CSL_CONFIG_ENABLED
	#if (CEVABX1 == 1)
          "mov #g_assertion_fault_occurred, r1.ui\n"
		  "mov #0x1, r0.ui\n"
	#else /* (CEVABX1 != 1) */
          "mov #g_assertion_fault_occurred, r1.ui || mov #0x1, r0.ui\n"
	#endif /* (CEVABX1 == 1) */
#endif /* CSL_USER_CONF_ASSERT_TRAPE == CSL_CONFIG_ENABLED */
		  "st r0.ui, (r1.ui).ui\n"
          "pop{in2} r0.ui, r1.ui\n"
          "reti" );


/*********************************************************************************************
* @function	HW_EXCPTIONS_move_to_supervisor_mode
* @author	Ravid Rzaev
* @date 	11/04/2021
* @brief	Sets the core's to supervisor mode.
* @return	E_csl_status
*********************************************************************************************/
E_csl_status HW_EXCPTIONS_move_to_supervisor_mode(void)
{
    g_is_move_to_supervisor = CSL_TRUE;
	__asm__ volatile( "trap\n"
                  "nop" );
    g_is_move_to_supervisor = CSL_FALSE;

	return CSL_SUCCESS;

}

#endif /* SENSPRO */

