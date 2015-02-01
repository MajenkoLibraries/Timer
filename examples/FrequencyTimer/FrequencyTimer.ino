#include <Timer.h>

// T5 will count how long the gate is high
Timer5 counter;

// This is where we will store the current incoming frequency.
volatile uint32_t currentCount = 0;

// Increase this to measure lower frequencies. Valid values
// are 1, 2, 4, 8, 16, 32, 64 and 256.
const uint16_t prescale = 2;

void setup() {

	// First set the granularity of the counting. Higher prescales
	// allow for lower frequency counting
	counter.setPrescaler(prescale);
	counter.setPeriod(0xFFFF);

	// Turn on accumulated gate mode.
	counter.enableGate();
	
	// The timer should get its clock source from the peripheral bus clock
	counter.setClockSource(TIMER_PB);
	
	// Ensure the counter is empty at the beginning.
	counter.reset();

	// In gated timer mode the interrupt will fire when the gate goes low
	counter.attachInterrupt(isr);

	// And start the counter running.
	counter.start();

	Serial.begin(115200);

	// Clear the screen with the ANSI code ESC[2J
	Serial.print("\e[2J");
}

void loop() {

	// If we have a valid frequency then display it
	if (currentCount > 0) {

		// The ESC[4;4H is the ANSI code to set the cursor position to Y=4 and X=4
		// (in that order) with 1,1 being the upper-left corner.
		Serial.print("\e[4;4HFrequency: ");

		// The getPeripheralClock() function calculates the correct peripheral bus clock
		// from the configuration flags in the chip.  We also need to double the count
		// to simulate the low period of a 50% duty cycle square wave.
		Serial.print((getPeripheralClock() / prescale) / (currentCount*2));
		Serial.println("Hz    ");

		// Be sure to reset the current count to 0 so we don't
		// keep displaying the last frequency when the counter doesn't
		// trigger because of no input
		currentCount = 0;
	} else {
		// There is no current count, so we'll just say it's idle.
		Serial.println("\e[4;4HFrequency: IDLE            ");
	}
	delay(100);
}

// Be sure to set the ISR routine to be an interrupt
void __attribute__((interrupt)) isr() {

	// We want to record the current count and reset
	// the counter to 0 ready for the next pulse.  We
	// have a convenient method to do just that.
	currentCount = counter.getAndResetCount();

	// And tell the chip we have handled the interrupt by
	// clearing the flag.
	clearIntFlag(_TIMER_5_IRQ);
}
