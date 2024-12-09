/*
 * cevabx_timers.h
 *
 *  Created on: Aug 25, 2019
 *      Author: ephif
 */
#ifndef HEADERS_CEVA_TIMERS_H_
#define HEADERS_CEVA_TIMERS_H_


#include "ceva_csl_defs.h"
#if ( defined( SENSPRO ) || ( ( defined XM6 ) && ( CEVA_DSP_RTL >= 130 ) ) )


#include "ceva_timers.h"
#include "ceva_hw_conf.h"
#include "ceva_hw_exceptions.h"
#include "ceva_xm_bc.h"
typedef enum{
	SINGLE_COUNT = 0,
	AUTO_RESTART = 1,
	FREE_RUNNING = 2,
	EVENT_COUNT  = 3,
} T_TimerCountModes;
//Time Scale - The ratio of counter clock: counter clock = core clock(DIV_1), 2*(core clock) = counter clock
//                                       4*(core clock) = counter clock,   16*(core clock) = counter clock
typedef enum{
	 TIMER_CLK_DIV_1  = 0,
	 TIMER_CLK_DIV_2  = 1,
	 TIMER_CLK_DIV_4  = 2,
	 TIMER_CLK_DIV_16 = 3
} T_TimeScale;
//When TIMERx is in Event Count mode, source if one of the bellow
typedef enum{
     INTERNAL_EVENT = 0,
	 EXTERNAL_EVENT = 1
}T_EventSource;
//At end of count event, sets the polarity of the TIMERx_OUT signal
//ACTIVE_HIGH - TIMERx_OUT signal is low expect for: at the end of count event, TIMERx_OUT is raised (active high)
//              For the number of cycles defined by TIMERx_CFG.TM, afterwards, the signal is low again
//ACTIVE_LOW -  TIMERx_OUT signal is high expect for: at the end of count event, TIMERx_OUT is cleared (active low)
//              for the number of cycles defined by TIMERx_CFG.TM, afterwards, the signal is high again
typedef enum{
    ACTIVE_HIGH = 0,
	ACTIVE_LOW  = 1,
}T_TimerOutPolarity;

//selects the "active" period of the TIMERx_OUT signal
typedef enum{
   CNTR_CLK_CYCLES_ENDLESS = 0, //TIMERx_OUT signal is active until TIMERx_CFG.CT is set
   CNTR_CLK_CYCLES_2 = 1, //TIMERx_OUT signal is active for 2 counter clock cycles
   CNTR_CLK_CYCLES_4 = 2, //TIMERx_OUT signal is active for 4 counter clock cycles
   CNTR_CLK_CYCLES_8 = 3  //TIMERx_OUT signal is active for 8 counter clock cycles
}T_TimerOutMode;

//Selects Cascade mode for Timer configuration
typedef enum{
	INDEPENDENT_CNT = 0,
	CASCADE_CNT     = 1
}T_CascadeMode;

typedef enum{
   CONTINUE_IN_DEBUG = 0,
   STOP_IN_DEBUG     = 1,
}T_DebugEnableMode;

// Selects if Timerx_CC is on latch mode
typedef enum
{
	TIMER_RU_COUNT_LATCH 	= 0,
	TIMER_RU_COUNT_UNLATCH 	= 1
}E_Timer_conf_RU;

#ifdef SENSPRO
	#define T_TimerIrq T_TIMER_IRQ
#endif


/*
 * TIMER Installed count function
 * Description: returns the number of TIMERs which are installed for current environment
 * Input:       N/A
 * Output:      The number of installed TIMERs in the current environment
 * */
#define  TIMER_installed_count()\
		CSL_HW_CONFIG_NUM_TIMERS


/*
 * TIMER allocation function
 * Description: allocates the first available timer using the configuration, using WATCHDOG in this allocation is not allowed
 * Input:       timer_config -Timer configuration to allocate timer by
 * Output:      The number of the allocated timer if successful, otherwise, -1
 *              Please notice, if allocated timer in cascade configuration succeeded than allocated timers are X, and X+1
 * */
#define TIMER_allocate(_timer_config)  (uint8_t)TIMER_allocate_bc(((_timer_config)->timer_cfg));


#ifdef SENSPRO

	/*
	 * TIMER rd irq
	 * Description: Reads the Timer IRQ register
	 * Input:       timer_irq - a pointer to timer_irq value
	 * Output:      N/A
	 * */
	#define    TIMER_rd_irq(_timer_irq) ((_timer_irq)->value) = HW_EXCPTIONS_get_timers_irq_status();

	/*
	 * TIMER clr irq
	 * Description: clears fields of Timer IRQ register
	 * Input:       timer_irq - irq values to clear, asserted values are cleared
	 * Output:      N/A
	 * */
	#define    TIMER_clr_irq(_timer_irq) HW_EXCPTIONS_clear_timers_irq_status((*_timer_irq));

#endif // SENSPRO







#endif /* defined SENSPRO || (defined XM6 && CEVA_DSP_RTL >= 130)*/
#endif /* HEADERS_CEVA_TIMERS_H_ */
