#ifndef __CEVA_SYMBOLS_H__
#define __CEVA_SYMBOLS_H__


/* #undef CEVA_PROJECT_SYMBOLS */
#ifndef CEVA_PROJECT_SYMBOLS

	/*
	 * Hardware configurations
	 *
	 * */


	#define HW_CONFIG_NUM_VCU_UNITS 			1
	#define HW_CONFIG_BTB_WAYS 				4
	#define HW_CONFIG_BTB_ENTRIES 				256
	#define HW_CONFIG_MCCI_NUM 				8

	#define HW_CONFIG_NUM_BLOCKS 				2
	#define HW_CONFIG_NUM_BANKS_PER_BLOCK 		8
	#define HW_CONFIG_IDM_SIZE 				256
/* #undef HW_CONFIG_DATA_CACHE_SIZE */

	
	#define HW_CONFIG_NUM_QMANS 				4
/* #undef HW_CONFIG_NUM_BMAN */
	
	#define HW_CONFIG_IPM_SIZE 				128
	#define HW_CONFIG_CODE_CACHE_SIZE 			128
	#define HW_CONFIG_PCAC_WAYS 				4

	#define HW_CONFIG_NUM_ICU_GROUPS 			1
	#define HW_CONFIG_NUM_TIMERS 				4

/* #undef HW_CONFIG_BUS_PROTOCOL_AHB */

/* #undef HW_CONFIG_AXIS0_PRESENT */
/* #undef HW_CONFIG_AXIS1_PRESENT */
/* #undef HW_CONFIG_AXIS2_PRESENT */
	#define HW_CONFIG_EDP_PRESENT 				128


	#define HW_CONFIG_EDAP_PRESENT 			128
	#define HW_CONFIG_EPP_PRESENT 				128


/* #undef HW_CONFIG_AXIM0_PRESENT */
/* #undef HW_CONFIG_AXIM1_PRESENT */

	#define CEVA_CORE_SAFE 					Disabled


	/*
	 * Infra Symbols
	 *
	 * */

	#define CEVA_DSP_ARCH 						senspro250




	/*
	 * if not defined - define as zero
	 *
	 * */

	#ifndef HW_CONFIG_BTB_WAYS
		#define HW_CONFIG_BTB_WAYS 0
	#endif
	#ifndef HW_CONFIG_BTB_ENTRIES
		#define HW_CONFIG_BTB_ENTRIES 0
	#endif
	#ifndef HW_CONFIG_MCCI_NUM
		#define HW_CONFIG_MCCI_NUM 0
	#endif
	#ifndef HW_CONFIG_DATA_CACHE_SIZE
		#define HW_CONFIG_DATA_CACHE_SIZE 0
	#endif


	#ifndef HW_CONFIG_NUM_QMANS
		#define HW_CONFIG_NUM_QMANS 0
	#endif
	#ifndef HW_CONFIG_NUM_BMAN
		#define HW_CONFIG_NUM_BMAN 0
	#endif
	#ifndef HW_CONFIG_IPM_SIZE
		#define HW_CONFIG_IPM_SIZE 0
	#endif
	#ifndef HW_CONFIG_CODE_CACHE_SIZE
		#define HW_CONFIG_CODE_CACHE_SIZE 0
	#endif
	#ifndef HW_CONFIG_PCAC_WAYS
		#define HW_CONFIG_PCAC_WAYS 0
	#endif

	
	
	#ifndef HW_CONFIG_NUM_ICU_GROUPS
		#define HW_CONFIG_NUM_ICU_GROUPS 0
	#endif
	#ifndef HW_CONFIG_NUM_TIMERS
		#define HW_CONFIG_NUM_TIMERS 0
	#endif
	#ifndef HW_CONFIG_AXIS0_PRESENT
		#define HW_CONFIG_AXIS0_PRESENT 0
	#endif
	#ifndef HW_CONFIG_AXIS1_PRESENT
		#define HW_CONFIG_AXIS1_PRESENT 0
	#endif
	#ifndef HW_CONFIG_AXIS2_PRESENT
		#define HW_CONFIG_AXIS2_PRESENT 0
	#endif
	#ifndef HW_CONFIG_EDP_PRESENT
		#define HW_CONFIG_EDP_PRESENT 0
	#endif

	#ifndef HW_CONFIG_EDAP_PRESENT
		#define HW_CONFIG_EDAP_PRESENT 0
	#endif
	#ifndef HW_CONFIG_EPP_PRESENT
		#define HW_CONFIG_EPP_PRESENT 0
	#endif
	#ifndef HW_CONFIG_AXIM0_PRESENT
		#define HW_CONFIG_AXIM0_PRESENT 0
	#endif
	#ifndef HW_CONFIG_AXIM1_PRESENT
		#define HW_CONFIG_AXIM1_PRESENT 0
	#endif
	#ifndef CEVA_CORE_SAFE
		#define CEVA_CORE_SAFE 0
	#endif




#endif /* ifndef CEVA_PROJECT_SYMBOLS */
#endif /* __CEVA_SYMBOLS_H__ */
