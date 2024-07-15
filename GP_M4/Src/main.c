
/*-------------------------- Includes ------------------------- */
#include "FreeRTOS.h"
#include "task.h"
#include "app.h"

/* ------------------------------------------------------------ */

void reset_system(void);

int main(void)
{

	/* Assembly */
//	reset_system();
	vSysInit();
	vTaskStartScheduler();

	for(;;);
	return 0;
}



#include "stm32f4xx.h"  // Include the appropriate header file for your device

void reset_system(void) {
    // Define a pointer to the reset handler address, which is stored at the second word in the vector table
    uint32_t reset_handler_address = *((uint32_t *)0x08000004);

    // Use inline assembly to set the stack pointer and branch to the reset handler
    __asm volatile (
        "ldr sp, [%0]\n"  // Load the stack pointer with the initial value from the vector table
        "bx %1\n"         // Branch to the reset handler
        :: "r" (0x08000000), "r" (reset_handler_address)
    );
}
