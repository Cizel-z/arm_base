#include <stdint.h>



void __start(void){

	const uint32_t *src;
	uint32_t *dest;

	for (dest = &_sbss; dest < &_ebss; ){
		*dest++ = 0;
    }

	for (src = &_eronly, dest = &_sdata; dest < &_edata; ){
		*dest++ = *src++;
	}


	
	// app_main();

	for (;;) {
		// should never get here
	}
}


