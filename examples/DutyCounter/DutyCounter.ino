#include <Timer.h>

// T4 will count the time between falling gates
Timer4 period;

// T5 will count how long the gate is high
Timer5 counter;

// This is where we will store the current incoming frequency.
volatile uint32_t currentCount = 0;

// The time for the current square wave
volatile uint32_t currentPeriod = 0;

// Increase this to measure lower frequencies. Valid values
// are 1, 2, 4, 8, 16, 32, 64 and 256.
const uint16_t prescale = 8;

void setup() {

	// First set the granularity of the counting. Higher prescales
	// allow for lower frequency measurements
	counter.setPrescaler(prescale);
	counter.setPeriod(0xFFFF);

	period.setPrescaler(prescale);
	period.setPeriod(0xFFFF);

	// Turn on accumulated gate mode.
	counter.enableGate();
	
	// The timers should get their clock source from the peripheral bus clock
	counter.setClockSource(TIMER_PB);
	period.setClockSource(TIMER_PB);
	
	// Ensure the counters are empty at the beginning.
	counter.reset();
	period.reset();
	// In gated timer mode the interrupt will fire when the gate goes low
	counter.attachInterrupt(isr);

	// And start the counters running.
	counter.start();
	period.start();
	
	Serial.begin(115200);

	// Clear the screen with the ANSI code ESC[2J
	Serial.print("\e[2J");
}

void loop() {

	// If we have a valid frequency then display it
	if (currentCount > 0) {

		uint32_t frequency = (getPeripheralClock() / prescale) / currentPeriod;
		uint32_t dutyCycle = currentCount * 100 / currentPeriod;

		// The ESC[4;4H is the ANSI code to set the cursor position to Y=4 and X=4
		// (in that order) with 1,1 being the upper-left corner.
		Serial.print("\e[4;4HFrequency: ");

		// The getPeripheralClock() function calculates the correct peripheral bus clock
		// from the configuration flags in the chip.  We also need to double the count
		// to simulate the low period of a 50% duty cycle square wave.
		Serial.print(frequency);
		
		Serial.print("Hz at ");
		Serial.print(dutyCycle);
		Serial.println("% duty cycle          ");

		// Be sure to reset the current count to 0 so we don't
		// keep displaying the last frequency when the counter doesn't
		// trigger because of no input
		currentCount = 0;
	} else {
		// There is no current count, so we'll just say it's idle.
		Serial.println("\e[4;4HFrequency: IDLE                         ");
	}
	delay(100);
}

// Be sure to set the ISR routine to be an interrupt
void __attribute__((interrupt)) isr() {

	// We want to record the current count and reset
	// the counter to 0 ready for the next pulse.  We
	// have a convenient method to do just that.
	currentCount = counter.getAndResetCount();

	// Store the current count since the last trailing
	// edge of the gate signal for the full wave period.
	currentPeriod = period.getAndResetCount();

	// And tell the chip we have handled the interrupt by
	// clearing the flag.
	clearIntFlag(_TIMER_5_IRQ);
}
