/*************************************************************************************\
*                                                                                     *
* Copyright (C) CEVA Inc. All rights reserved                                         *
*                                                                                      *
*                                                                                     *
* THIS PRODUCT OR SOFTWARE IS MADE AVAILABLE EXCLUSIVELY TO LICENSEES THAT HAVE       *
* RECEIVED EXPRESS WRITTEN AUTHORIZATION FROM CEVA TO DOWNLOAD OR RECEIVE THE         *
* PRODUCT OR SOFTWARE AND HAVE AGREED TO THE END USER LICENSE AGREEMENT (EULA).       *
* IF YOU HAVE NOT RECEIVED SUCH EXPRESS AUTHORIZATION AND AGREED TO THE               *
* CEVA EULA, YOU MAY NOT DOWNLOAD, INSTALL OR USE THIS PRODUCT OR SOFTWARE.           *
*                                                                                     *
* The information contained in this document is subject to change without notice and  *
* does not represent a commitment on any part of CEVA®, Inc. CEVA®, Inc. and its      *
* subsidiaries make no warranty of any kind with regard to this material, including,  *
* but not limited to implied warranties of merchantability and fitness for a          *
* particular purpose whether arising out of law, custom, conduct or otherwise.        *
*                                                                                     *
* While the information contained herein is assumed to be accurate, CEVA®, Inc.       *
* assumes no responsibility for any errors or omissions contained herein, and         *
* assumes no liability for special, direct, indirect or consequential damage,         *
* losses, costs, charges, claims, demands, fees or expenses, of any nature or kind,   *
* which are incurred in connection with the furnishing, performance or use of this    *
* material.                                                                           *
*                                                                                     *
* This document contains proprietary information, which is protected by U.S. and      *
* international copyright laws. All rights reserved. No part of this document may be  *
* reproduced, photocopied, or translated into another language without the prior      *
* written consent of CEVA®, Inc.                                                      *
*                                                                                     *
\*************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \file   debug_log.h
/// \brief  Definitions for using debugging log facility
/// \author Yury Schwarzman
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_

typedef enum {
    DBG_LOG_STREAM_TYPE_STDOUT,
    DBG_LOG_STREAM_TYPE_STDERR,
    DBG_LOG_STREAM_TYPE_FILE
} dbg_log_stream_type_e;

typedef struct dbg_log_handler_t_
{
    dbg_log_stream_type_e type;
    void* p_handle;
    struct dbg_log_handler_t_* p_next_handler;
} dbg_log_handler_t;

typedef enum {
    LOG_LEVEL_CRITICAL, // A serious error, indicating that the program itself may be unable to continue running.
    LOG_LEVEL_ERROR,	// Due to a more serious problem, the software has not been able to perform some function.
    LOG_LEVEL_WARNING,	// An indication that something unexpected happened, or indicative of some problem in the near future (e.g. "disk space low"). The software is still working as expected.
    LOG_LEVEL_INFO,	    // Confirmation that things are working as expected.
    LOG_LEVEL_DEBUG	    // Detailed information, typically of interest only when diagnosing problems.
} dbg_log_level_e;

#define DBG_LOG_MAX_CONTEXT_NAME_LEN 40

typedef struct dbg_log_context_t_
{
    char name[DBG_LOG_MAX_CONTEXT_NAME_LEN];
    int name_print_enable;
    dbg_log_level_e curr_level;
    dbg_log_handler_t* p_handler_list;
} dbg_log_context_t;

#define DBG_LOG_DEFAULT NULL

void dbg_log_get_stdout_handler( dbg_log_handler_t* p_handler );

void dbg_log_get_stderr_handler( dbg_log_handler_t* p_handler );

int dbg_log_open_file_handler( dbg_log_handler_t* p_handler, const char* file_name );

void dbg_log_close_file_handler( dbg_log_handler_t* p_log_handler );

void dbg_log_init_context( dbg_log_context_t* p_ctx, const char* name, dbg_log_level_e level, dbg_log_handler_t* p_log_handler );

void dbg_log_context_attach_handler( dbg_log_context_t*, dbg_log_handler_t* p_log_handler );

void dbg_log_destroy_context( dbg_log_context_t* );

dbg_log_level_e dbg_log_context_get_level( const dbg_log_context_t* p_ctx );

void dbg_log_context_set_level( dbg_log_context_t*, dbg_log_level_e level );

void dbg_log_context_enable_name_print( dbg_log_context_t* p_ctx, int enable );

void dbg_log_print( dbg_log_context_t* p_ctx, dbg_log_level_e level, const char* msg, ... );

void dbg_log_println(dbg_log_context_t* p_ctx, dbg_log_level_e level, const char* msg, ...);

void dbg_log_set_default_context( dbg_log_context_t* p_ctx );

dbg_log_context_t* dbg_log_get_default_context( void );

#endif // _DEBUG_LOG_H_
