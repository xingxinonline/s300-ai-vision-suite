/*************************************************************************************\
* Copyright (C) CEVA(R) Inc. All rights reserved                                      *
*                                                                                     *
* This information embodies materials and concepts, which are proprietary and         *
* confidential to CEVA Inc., and is made available solely pursuant to the terms       *
* of a written license agreement, or NDA, or another written agreement, as            *
* applicable ("CEVA Agreement"), with CEVA Inc. or any of its subsidiaries ("CEVA").  *
*                                                                                     *
* This information can be used only with the written permission from CEVA, in         *
* accordance with the terms and conditions stipulated in the CEVA Agreement, under    *
* which the information has been supplied and solely as expressly permitted for       *
* the purpose specified in the CEVA Agreement.                                        *
*                                                                                     *
* This information is made available exclusively to licensees or parties that have    *
* received express written authorization from CEVA to download or receive the         *
* information and have agreed to the terms and conditions of the CEVA Agreement.      *
*                                                                                     *
* IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE CEVA          *
* AGREEMENT, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS INFORMATION.                   *
*                                                                                     *
* The information contained in this document is subject to change without notice      *
* and does not represent a commitment on any part of CEVA. Unless specifically        *
* agreed otherwise in the CEVA Agreement, CEVA make no warranty of any kind with      *
* regard to this material, including, but not limited to implied warranties of        *
* merchantability and fitness for a particular purpose whether arising out of law,    *
* custom, conduct or otherwise.                                                       *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA assumes no   *
* responsibility for any errors or omissions contained herein, and assumes no         *
* liability for special, direct, indirect or consequential damage, losses, costs,     *
* charges, claims, demands, fees or expenses, of any nature or kind, which are        *
* incurred in connection with the furnishing, performance or use of this material.    *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may     *
* be reproduced, photocopied, or translated into another language without the prior   *
* written consent of CEVA.                                                            *
\*************************************************************************************/
#ifndef CEVA_MCCI_H_
#define CEVA_MCCI_H_
/*********************************************************************************************
 * @module          MCCI
 * @file            ceva_mcci.h
 * @author          Ravid Rzaev
 * @date            14/11/2021
 * @brief           Define the structure, configuration values and function of
                    the Multi-Core Configuration Programming model registers
**********************************************************************************************/
//**********************************************************
//********************** Includes **************************
//**********************************************************
#include "ceva_assert.h"
#include "ceva_memory_map.h"

CSL_CPP_START



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	MCCI Programming Model Registers Structures
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

 /***********************
 * Name: T_COM_REG
 * Register: COM_REGx
 ************************/
 typedef union T_COM_REG
{
	struct
	{
		uint32_t com_reg	 		: 32; // Messaging memory register space(Command Registers)
	} fields;
	uint32_t value;
} T_COM_REG;


 /***********************
 * Name: T_COM_STS
 * Register: COM_STS
 ************************/
 typedef union T_COM_STS
{
	struct
	{
		uint32_t com_sts	 		: 32; // Write status COM_REG0-31 registers indication
	} fields;
	uint32_t value;
} T_COM_STS;


 /***********************
 * Name: T_COM_INT_EN
 * Register: COM_INT_EN
 ************************/
 typedef union T_COM_INT_EN
{
	struct
	{
		uint32_t com_int_en			: 32; // Interrupt masking COM_STS status indication
	} fields;
	uint32_t value;
} T_COM_INT_EN;

 /***********************
 * Name: T_START_ADDR
 * Register: START_ADDR
 ************************/
 typedef union T_START_ADDR
{
	struct
	{
		uint32_t start_addr			: 21; // IDM snooping base address range
		uint32_t 					: 11; // Reserved
	} fields;
	uint32_t value;
} T_START_ADDR;


 /***********************
 * Name: T_TOP_ADDR
 * Register: TOP_ADDR
 ************************/
 typedef union T_TOP_ADDR
{
	struct
	{
		uint32_t top_addr			: 21; // IDM snooping top address range
		uint32_t 					: 11; // Reserved
	} fields;
	uint32_t value;
} T_TOP_ADDR;


 /***********************
 * Name: T_SNOOP_CSR
 * Register: SNOOP_CSR
 ************************/
 typedef union T_SNOOP_CSR
{
	struct
	{
		uint32_t snoop_rd_wr			: 2;
		uint32_t snoop_edap_sts			: 1; // EDAP snooping detection
		uint32_t snoop_edap_int_en		: 1; // EDAP snooping detection interrupt enable
#if !(defined(CEVABX) && defined(HW_CONFIG_BUS_PROTOCOL_AHB))
		uint32_t snoop_axis0_sts		: 1; // axis0 snooping detection
		uint32_t snoop_axis0_int_en		: 1; // axis0 snooping detection interrupt enable
		uint32_t snoop_axis1_sts		: 1; // axis1 snooping detection
		uint32_t snoop_axis1_int_en		: 1; // axis1 snooping detection interrupt enable
		uint32_t snoop_axis2_sts		: 1; // axis2 snooping detection
		uint32_t snoop_axis2_int_en		: 1; // axis2 snooping detection interrupt enable
#else /* (defined(CEVABX) && defined(HW_CONFIG_BUS_PROTOCOL_AHB)) */
		uint32_t 						: 6; // Reserved
#endif /* !(defined(CEVABX) && defined(HW_CONFIG_BUS_PROTOCOL_AHB)) */
		uint32_t 						: 22; // Reserved
	} fields;
	uint32_t value;
} T_SNOOP_CSR;



/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	MCCI Programming Model Configuration Values
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*****************************************************
 * E_MCCI_snoop_csr_snoop_rd_wr
 * 		Register: SNOOP_CSR
 * 		Field: SNOOP_RD_WR
 *		Description: Snooping Read Write Access Type
 *****************************************************/
typedef enum
{
	MCCI_SNOOP_CSR_SNOOP_RD_WR_DISABLED						= 0,
	MCCI_SNOOP_CSR_SNOOP_RD_WR_READ_ENABLED					= 1,
	MCCI_SNOOP_CSR_SNOOP_RD_WR_WRITE_ENABLED					= 2,
	MCCI_SNOOP_CSR_SNOOP_RD_WR_READ_AND_WRITE_ENABLED		= 3
} E_MCCI_snoop_csr_snoop_rd_wr;


/*****************************************************
 * E_MCCI_snoop_external_port
 * Description: Driver Operation, chose snooping port (EDAP / AXIs0 / AXIs1 / AXIs2)
 *****************************************************/
typedef enum
{
	MCCI_SNOOP_EXTERNAL_PORT_EDAP							= 0x2
#if !(defined(CEVABX) && defined(HW_CONFIG_BUS_PROTOCOL_AHB))
	, MCCI_SNOOP_EXTERNAL_PORT_AXIS0							= 0x4
	, MCCI_SNOOP_EXTERNAL_PORT_AXIS1							= 0x6
	, MCCI_SNOOP_EXTERNAL_PORT_AXIS2							= 0x8
#endif // #if defined(CEVABX) && defined(HW_CONFIG_BUS_PROTOCOL_AHB)
} E_MCCI_snoop_external_port;


/*****************************************************
 * E_MCCI_snoop_number
 *		Description: Driver Operation, chose snoop number
 *****************************************************/
typedef enum
{
	MCCI_SNOOP_0						= 0,
	MCCI_SNOOP_1						= 1,
} E_MCCI_snoop_number;


/*********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************
 *
 *	MCCI Programming Model Driver Functions
 *
 *********************************************************************************************
 *********************************************************************************************
 *********************************************************************************************/

/*********************************************************************************************
* @function	MCCI_start_snooping
* @author	Ravid Rzaev
* @date 	14/11/2021
* @brief	Starts snooping with the given addresses and read write access type.
* @param	snoop_num:	Snoop number.
* @param	start_address:	IDM snooping base address.
* @param	top_address:	IDM snooping top address.
* @param	snoop_rd_wr:	Snooping Read Write Access Type.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	E_csl_status MCCI_start_snooping(E_MCCI_snoop_number snoop_num, uint32_t start_address, uint32_t top_address, E_MCCI_snoop_csr_snoop_rd_wr snoop_rd_wr) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	E_csl_status MCCI_start_snooping(uint32_t start_address, uint32_t top_address, E_MCCI_snoop_csr_snoop_rd_wr snoop_rd_wr) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */


/*********************************************************************************************
* @function	MCCI_snoop_disable
* @author	Ravid Rzaev
* @date 	14/11/2021
* @brief	Disable snooping operation.
* @param	snoop_num:	Snoop number.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	E_csl_status MCCI_snoop_disable(E_MCCI_snoop_number snoop_num) PRAGMA_CSECT("CSL_CODE_SECTION");

#else /* CEVABX || XM4 */
	E_csl_status MCCI_snoop_disable(void) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */



/*********************************************************************************************
* @function	MCCI_snoop_get_start_address
* @author	Ravid Rzaev
* @date 	15/11/2021
* @brief	Returns the snoop start address.
* @param	snoop_num:	Snoop number.
* @return	Snooping start address.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	uint32_t MCCI_snoop_get_start_address(E_MCCI_snoop_number snoop_num) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	uint32_t MCCI_snoop_get_start_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */


/*********************************************************************************************
* @function	MCCI_snoop_get_top_address
* @author	Ravid Rzaev
* @date 	15/11/2021
* @brief	Returns the snoop top address.
* @param	snoop_num:	Snoop number.
* @return	Snooping top address.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	uint32_t MCCI_snoop_get_top_address(E_MCCI_snoop_number snoop_num) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	uint32_t MCCI_snoop_get_top_address(void) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */


/*********************************************************************************************
* @function	MCCI_snoop_enable_detection_interrupt
* @author	Ravid Rzaev
* @date 	15/11/2021
* @brief	Enables snooping detection interrupt of the given port.
* @param	snoop_num:	Snoop number.
* @param	ext_port:		external port.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	E_csl_status MCCI_snoop_enable_detection_interrupt(E_MCCI_snoop_number snoop_num, E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	E_csl_status MCCI_snoop_enable_detection_interrupt(E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */


/*********************************************************************************************
* @function	MCCI_snoop_disable_detection_interrupt
* @author	Ravid Rzaev
* @date 	15/11/2021
* @brief	Disables snooping detection interrupt of the given port.
* @param	snoop_num:	Snoop number.
* @param	ext_port:		external port.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	E_csl_status MCCI_snoop_disable_detection_interrupt(E_MCCI_snoop_number snoop_num, E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	E_csl_status MCCI_snoop_disable_detection_interrupt(E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */



/*********************************************************************************************
* @function	MCCI_snoop_has_idm_access
* @author	Ravid Rzaev
* @date 	16/11/2021
* @brief	Returns the detection status of IDM access by the given port.
* @param	snoop_num:		Snoop number.
* @param	ext_port:		external port.
* @return	CSL_TRUE or CSL_FALSE.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	bool MCCI_snoop_has_idm_access(E_MCCI_snoop_number snoop_num, E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	bool MCCI_snoop_has_idm_access(E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */



/*********************************************************************************************
* @function	MCCI_snoop_is_active
* @author	Ravid Rzaev
* @date 	16/11/2021
* @brief	Returns the current snooping status (active or not).
* @param	snoop_num:		Snoop number.
* @return	CSL_TRUE or CSL_FALSE.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	bool MCCI_snoop_is_active(E_MCCI_snoop_number snoop_num) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	bool MCCI_snoop_is_active(void) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */



/*********************************************************************************************
* @function	MCCI_snoop_clear_idm_access_detection
* @author	Ravid Rzaev
* @date 	16/11/2021
* @brief	Clears the detection status of IDM access by the given port.
* @param	snoop_num:		Snoop number.
* @param	ext_port:		external port.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
#if defined SENSPRO || defined XM6
	E_csl_status MCCI_snoop_clear_idm_access_detection(E_MCCI_snoop_number snoop_num, E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#else /* CEVABX || XM4 */
	E_csl_status MCCI_snoop_clear_idm_access_detection(E_MCCI_snoop_external_port ext_port) PRAGMA_CSECT("CSL_CODE_SECTION");
#endif /* SENSPRO || XM6 */


/*********************************************************************************************
* @function	MCCI_get_command_register_value
* @author	Ravid Rzaev
* @date 	22/11/2021
* @brief	Returns the value given COM_REGx number.
* @param	com_reg_number:		COM_REGx register number.
* @return	The value of COM_REGx.
*********************************************************************************************/
uint32_t MCCI_get_command_register_value(uint8_t com_reg_number) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	MCCI_get_command_status_indication
* @author	Ravid Rzaev
* @date 	22/11/2021
* @brief	Returns the value command status register.
* @param	com_reg_number:		COM_REGx register number.
* @return	The value of COM_STS.
*********************************************************************************************/
uint32_t MCCI_get_command_status_indication(void) PRAGMA_CSECT("CSL_CODE_SECTION");


/*********************************************************************************************
* @function	MCCI_clear_command_status_indication
* @author	Ravid Rzaev
* @date 	22/11/2021
* @brief	Clears the status indication of the given status number
* @param	status_num:	the number of the status indication (the relevant bit in COM_STS register).
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status MCCI_clear_command_status_indication(uint8_t status_num) PRAGMA_CSECT("CSL_CODE_SECTION");



/*********************************************************************************************
* @function	MCCI_clear_command_status_indication
* @author	Ravid Rzaev
* @date 	22/11/2021
* @brief	Enable or Disable interrupt for the given com_reg number
* @param	com_reg_number:	the number of the com_reg to enable/disable interrupt.
* @param	enable:			CSL_TRUE or CSL_FALSE.
* @return	CSL_SUCCESS or CSL failure code.
*********************************************************************************************/
E_csl_status MCCI_enable_interrupt(uint8_t com_reg_number, bool enable) PRAGMA_CSECT("CSL_CODE_SECTION");


CSL_CPP_END

#endif /* CEVA_MCCI_H_ */
