//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"
#include <stm32f10x.h>

// ----------------------------------------------------------------------------
//
// STM32F1 empty sample (trace via ITM).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


void delay(volatile uint32_t d)
{
  while (d-- != 0)
    ;
}

void c_pin_on(volatile uint32_t pin){
	GPIOC->ODR |= (1<<pin);        // set green LED
}

void c_pin_off(volatile uint32_t pin){
	GPIOC->ODR &= ~(1<<pin);        // clr green LED
}

int main(int argc, char* argv[])
{
	// At this stage the system clock should have already been configured
	// at high speed.

	// Infinite loop
	RCC->APB2ENR = RCC_APB2ENR_IOPCEN;  // enable PORTC

	GPIOC->CRH = (0b0010 << 20);  // CNF=0, MODE=2 (2MHz output) (isto kot 0b 0000 0000 0010 0000 0000 0000 0000 0000) // PC013
	//GPIOC->CRH = (0b0010 << 4);   // CNF=0, MODE=2 (2MHz output) (isto kot 0b 0000 0000 0000 0000 0000 0000 0010 0000) // PC09
	//GPIOC->CRH = (0b0010);        // CNF=0, MODE=2 (2MHz output) (isto kot 0b 0000 0000 0000 0000 0000 0000 0010 0000) // PC08
	//GPIOC->CRL = (0b0010 << 4);   // CNF=0, MODE=2 (2MHz output) (isto kot 0b 0000 0000 0000 0000 0000 0000 0010 0000) // PC01
	//GPIOC->CRL = (0b0010);        // CNF=0, MODE=2 (2MHz output) (isto kot 0b 0000 0000 0000 0000 0000 0000 0000 0010) // PC00

	while (1)    {             // forever loop
		  c_pin_on(13);        // set green LED
	      delay(300000);

	      c_pin_off(13);		// clr green LED
	      delay(800000);
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
