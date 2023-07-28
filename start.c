/****************************************************************************
 *
 *   Copyright (C) 2014-2015 Fonrich. All rights reserved.
 *   Author: yong.zhang <yong.zhang@fonrich.com>
 *
 ****************************************************************************/

#include <config.h>
#include <stdint.h>
#include <up/up.h>
#include <chip/chip.h>
#include <qroutine.h>

#include <n32g003_internal.h>

void __start(void){

	const uint32_t *src;
	uint32_t *dest;

//	showprogress('A');
	
	/* Clear .bss.  We'll do this inline (vs. calling memset) just to be
	 * certain that there are no issues with the state of global variables.
	 */
	for (dest = &_sbss; dest < &_ebss; ){
		*dest++ = 0;
    }

//	showprogress('B');

	/* Move the initialized data section from his temporary holding spot in
	 * FLASH into the correct place in SRAM.  The correct place in SRAM is
	 * give by _sdata and _edata.  The temporary location is in FLASH at the
	 * end of all of the other read-only data (.text, .rodata) at _eronly.
	 */
	for (src = &_eronly, dest = &_sdata; dest < &_edata; ){
		*dest++ = *src++;
	}

	// showprogress('C');
	N32_ALL_CLK_Configuration();
    console_init(115200);
	printf("begin console_init uart2\r\n");
	
	// showprogress('D');
	isr_attach(UP_IRQ_SYSTICK, isr_tick, 0);

	isr_attach(UP_IRQ_PENDSV, isr_pendsv, 0);
	// showprogress('E');
	
	app_main();

	for (;;) {
		// should never get here
	}
}


