OUTPUT(a.elf)

/* By default, program starts from reset address (the default location of the interrupt table) */
ENTRY(__cxd_inttbl_start)

/** Memory configuration parameters.
 *  The parameters become application symbols and can be referred from application
 */
__internal_code_start = DEFINED(__internal_code_start) ? __internal_code_start : 0x00000000;
__internal_code_size  = DEFINED(__internal_code_size ) ? __internal_code_size  : 128k;
__internal_data_start = DEFINED(__internal_data_start) ? __internal_data_start : 0x00000000;
__internal_data_size  = DEFINED(__internal_data_size ) ? __internal_data_size  : 256k;
__sram0_start      	  = DEFINED(__sram0_start        ) ? __sram0_start         : 0x44000000;
__sram0_size          = DEFINED(__sram0_size         ) ? __sram0_size          : 0x40000;
__sram1_start      	  = DEFINED(__sram1_start        ) ? __sram1_start         : 0x44040000;
__sram1_size          = DEFINED(__sram1_size         ) ? __sram1_size          : 0x40000;
__psram_start      	  = DEFINED(__psram_start        ) ? __psram_start         : 0x80000000;
__psram_size          = DEFINED(__psram_size         ) ? __psram_size          : 0x800000;
__rom_start           = DEFINED(__rom_start          ) ? __rom_start           : 0xC0000000;
__rom_size            = DEFINED(__rom_size           ) ? __rom_size            : 1024M;

__malloc_size         = DEFINED(__malloc_size        ) ? __malloc_size         : 4k;
__stack_size          = DEFINED(__stack_size         ) ? __stack_size          : 16k;
__arg_sect_size       = DEFINED(__arg_sect_size      ) ? __arg_sect_size       : 512;

MEMORY {
    INTERNAL_CODE  (rx) : ORIGIN = __internal_code_start, LENGTH = __internal_code_size
    INTERNAL_DATA  (rw) : ORIGIN = __internal_data_start, LENGTH = __internal_data_size
    SRAM0         (rwx) : ORIGIN = __sram0_start        , LENGTH = __sram0_size
    SRAM1         (rwx) : ORIGIN = __sram1_start        , LENGTH = __sram1_size
    PSRAM      	  (rwx) : ORIGIN = __psram_start        , LENGTH = __psram_size
    ROM            (rx) : ORIGIN = __rom_start          , LENGTH = __rom_size
}

SECTIONS {
    .inttbl : ALIGN(0x20) {
        /** The interrupt vector table. Contains the NMI
         *  and maskable interrupt handlers
         */
        . = 0x0;
        KEEP(*(.inttbl))
        . = ALIGN(0x20);
    	KEEP(*(.sinttbl))
    } >INTERNAL_CODE

    .text.internal :  ALIGN(0x20)  {
    	PROVIDE(__text_start = ABSOLUTE(.));
        /* The __call_saved* functions need to be placed at low addresses for
         * calling with absolute call instructions
         */
        *(.text.__call_saved*)
        *(.text .text.*)
		/* Program sections in external memory should be aligned to the fetch line width
		*/
		/* Place all CSL code in the external memory, because some configurations have no PTCM */
        *(CSL_CODE_SECTION CSL_CODE_SECTION.*)   
        . = ALIGN(0x40);     
        PROVIDE(__text_end = ABSOLUTE(.));
    	PROVIDE(__text_fd_start = ABSOLUTE(.));
        *(.text_fd .text_fd.*)
        . = ALIGN(0x20);
        PROVIDE(__text_fd_end = ABSOLUTE(.));
        . = ALIGN(0x100);
        *(.external_timer_interrupt)
        . = ALIGN(0x100);
        *(.external_mailbox_interrupt)
        . = ALIGN(0x100);
        *(.external_wframe0_interrupt)
        . = ALIGN(0x100);
        *(.external_wframe1_interrupt)
        . = ALIGN(0x100);
        *(.external_rframe0_interrupt)
        . = ALIGN(0x100);
        *(.external_rframe1_interrupt)
        . = ALIGN(0x100);
    } >INTERNAL_CODE 

    .data.internal : ALIGN(0x20) {
        PROVIDE(__data_internal_start = ABSOLUTE(.));
        /* Don't map any data at address zero to avoid issues with C NULL
         * pointer checks
         */
        . += 0x4;

        PROVIDE(__data_start = ABSOLUTE(.));
        *(.data .data.*)
        PROVIDE(__data_end = ABSOLUTE(.));
        PROVIDE(__data_size = ABSOLUTE(+__data_end - __data_start));

        PROVIDE(__sdata_start = ABSOLUTE(.));
        *(.sdata .sdata.*)
        PROVIDE(__sdata_end = ABSOLUTE(.));
        PROVIDE(__sdata_size = ABSOLUTE(+__sdata_end - __sdata_start));

        PROVIDE(__rodata_start = ABSOLUTE(.));
        *(.rodata .rodata.*)
        . = ALIGN(0x100);
        PROVIDE(__rodata_end = ABSOLUTE(.));
        PROVIDE(__rodata_size = ABSOLUTE(+__rodata_end - __rodata_start));

        *(CSL_INTERNAL_DATA_ALLOCATION CSL_INTERNAL_DATA_ALLOCATION.*)
        *(CSL_GENERAL_DATA_ALLOCATION CSL_GENERAL_DATA_ALLOCATION.*)
        *(int_sect int_sect.*)

        *(internal_test_data)
        
        PROVIDE(__data_internal_end = ABSOLUTE(.));
        PROVIDE(__data_internal_size = ABSOLUTE(__data_internal_end - __data_internal_start));
    } >INTERNAL_DATA

    .cst.call : ALIGN(4) {
        PROVIDE(__cst_call_start = ABSOLUTE(.));
        *(.cst.call)
        PROVIDE(__cst_call_end = ABSOLUTE(.));
    } >INTERNAL_DATA

    .cst.mov : ALIGN(4) {
        PROVIDE(__cst_mov_start = ABSOLUTE(.));
        *(.cst.mov)
        PROVIDE(__cst_mov_end = ABSOLUTE(.));
    } >INTERNAL_DATA

    .bss (NOLOAD) : ALIGN(0x20) {
        PROVIDE(__bss_start = ABSOLUTE(.));
        *(.bss .bss.*)
        PROVIDE(__common_start = ABSOLUTE(.));
        *(COMMON)
        *(.data_fd .data_fd.*)
        PROVIDE(__common_end = ABSOLUTE(.));
        PROVIDE(__common_size = ABSOLUTE(+__common_end - __common_start));
        PROVIDE(__bss_end = ABSOLUTE(.));
        PROVIDE(__bss_size = ABSOLUTE(+__bss_end - __bss_start));
    } >INTERNAL_DATA

   
    
    __MALLOC_SECT (NOLOAD) : ALIGN(0x10) {
        PROVIDE(__malloc_start = ABSOLUTE(.));
        . = . + __malloc_size;
        PROVIDE(__malloc_end = ABSOLUTE(.));
    } >INTERNAL_DATA
    
     __STACK_SECT (NOLOAD) : ALIGN(0x10) {
        __stack_start = ABSOLUTE(.);
        . = . + __stack_size;
        __stack_end = ABSOLUTE(.);
    } >SRAM0
    
     /* Program arguments are loaded by `_start` routine from `__arg_sect_start`.
     * When the user has set a zero size for the section, argc, and argv
     * will be zero and NULL, respectively.
     * Although likely small, they are on the slow path so by default they
     * go at the end of external memory
     */
    __ARG_SECT (NOLOAD) : ALIGN(0x10) {
        __arg_sect_start = .;
        . = . + (__arg_sect_size ? __arg_sect_size + 4 : 0);
        __arg_sect_end = .;
    } >SRAM0

    .text.external : ALIGN(0x20) {
        
    } >SRAM0

    .data.external : ALIGN(0x20) {
        /** .data1, .rodata1, .sdata1 are all for large symbols which cannot
         * fit in limited internal memory. We put them in external memory by
         * default. */
        PROVIDE(__data_external_start = ABSOLUTE(.));

        PROVIDE(__data1_start = ABSOLUTE(.));
        *(.data1 .data1.*)
        PROVIDE(__data1_end = ABSOLUTE(.));

        PROVIDE(__sdata1_start = ABSOLUTE(.));
        *(.sdata1 .sdata1.*)
        PROVIDE(__sdata1_end = ABSOLUTE(.));
        PROVIDE(__sdata1_size = ABSOLUTE(+__sdata1_end - __sdata1_start));

        PROVIDE(__rodata1_start = ABSOLUTE(.));
        *(.rodata1 .rodata1.*)
        PROVIDE(__rodata1_end = ABSOLUTE(.));
        PROVIDE(__rodata1_size = ABSOLUTE(+__rodata1_end - __rodata1_start));

        /* Constructors and destructors are called once per program invocation,
         * so are never in the hot path; they shouldn't waste space in limited
         * internal memory so we place them in slower, external memory */

        . = ALIGN(4); /* constructors must be aligned on a word boundary */
        PROVIDE(__init_array_start = ABSOLUTE(.));
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)));
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array*) SORT_BY_INIT_PRIORITY(.ctors*)));
        PROVIDE(__init_array_end = ABSOLUTE(.));

        PROVIDE(__fini_array_start = ABSOLUTE(.));
        /* destructors are run in reverse order of their priority */
        KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)));
        KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array*) SORT_BY_INIT_PRIORITY(.dtors*)));
        PROVIDE(__fini_array_end = ABSOLUTE(.));

        PROVIDE(__data_external_end = ABSOLUTE(.));
        PROVIDE(__data_external_size = ABSOLUTE(__data_external_end - __data_external_start));
    } >SRAM0

    .bss1 (NOLOAD) : ALIGN(0x20) {
        /**
         * `.bss1` is for large zero-initialized symbols that do not fit in
         * internal data
         */
        PROVIDE(__bss1_start = ABSOLUTE(.));
        *(.bss1 .bss1.*)
        PROVIDE(__large_common_start = ABSOLUTE(.));
        *(LARGE_COMMON)
        PROVIDE(__large_common_end = ABSOLUTE(.));
        PROVIDE(__large_common_size = ABSOLUTE(+__large_common_end - __large_common_start));
        PROVIDE(__bss1_end = ABSOLUTE(.));
        PROVIDE(__bss1_size = ABSOLUTE(+__bss1_end - __bss1_start));
    } >SRAM0


    data_internal_loadable_addr = LOADADDR(.data.internal);
    data_external_loadable_addr = LOADADDR(.data.external);
	
    .interrupt.external : ALIGN(0x100) {
       
    } >SRAM0
    
    .sram1.data : ALIGN(0x100) {
    	PROVIDE(__data_sram1_start = ABSOLUTE(.));
        *(.sram1_data .sram1_data.*)
        PROVIDE(__data_sram1_end = ABSOLUTE(.));
        . = ALIGN(0x100);
        PROVIDE(__rodata_sram1_start = ABSOLUTE(.));
        *(.sram1_rodata .sram1_rodata.*)
        . = ALIGN(0x100);
        PROVIDE(__rodata_sram1_end = ABSOLUTE(.));
    } >SRAM1
    
    .npu.inst.external : ALIGN(0x100) {
    	. = ALIGN(0x100);
        PROVIDE(__npu_inst_start = ABSOLUTE(.));
        *(.npu_inst .npu_inst.*)
        PROVIDE(__npu_inst_end = ABSOLUTE(.));
        PROVIDE(__npu_inst_size = ABSOLUTE(+__npu_inst_end - __npu_inst_start));
    } >PSRAM
    
    .npu.data.external : ALIGN(0x100) {
    	. = ALIGN(0x100);
    	PROVIDE(__npu_weight_start = ABSOLUTE(.));
        *(.npu_weight .npu_weight.*)
        PROVIDE(__npu_weight_end = ABSOLUTE(.));
        . = ALIGN(0x100);
    	PROVIDE(__npu_feature_start = ABSOLUTE(.));
        *(.npu_feature .npu_feature.*)
        PROVIDE(__npu_feature_end = ABSOLUTE(.));
        PROVIDE(__npu_feature_size = ABSOLUTE(+__npu_feature_end - __npu_feature_start));
    } >PSRAM

    /DISCARD/ : {
        /* Note:  The CEVA Debugger and Restriction Checker use information 
         * stored in the ".note.CEVA-arch" section. Do NOT discard this section
         * for projects in development phase. This section has no effect on the
         * applications footprint */
        *(.comment)
        *(.note.GNU-stack)
        /* The X-DSP ABI uses a custom relocation format stored in its own
         * section. These are left in the binary by default but are unneeded. */
        *(.ceva_reloc)
    }

}
