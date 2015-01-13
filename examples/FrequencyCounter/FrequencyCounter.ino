#include <Timer.h>

// Create a new timer object using T4
Timer4 timer;
// And a counter object using T5
Timer5 counter;

// This is where we will store the current incoming frequency.
volatile uint32_t currentHz = 0;

void setup() {
	// We want the maximum resolution we can get.
	// Like this we can measure 65535 pulses (it's a 16
	// bit timer), so up to 655350Hz with a 10Hz resolution
	// before it wraps round.
	
	// To measure higher frequencies we can either increase
	// the prescaler (and multiply the result accordingly)
	// or decrease the sample time.

	counter.setPrescaler(1);
	counter.setPeriod(0xFFFF);
	
	// The timer should get its clock source from the input pin
	counter.setClockSource(TIMER_IN);
	
	// Ensure the counter is empty at the beginning.
	counter.reset();

	// We'll run at a frequency of 10Hz. That's 100ms per tick.  We can't go
	// much slower than that, the chip is too fast.
	timer.setFrequency(10);

	// Link in out ISR routine. Note, it is a real ISR routine,
	// so requires all the right attributes etc.
	timer.attachInterrupt(isr);

	// Start the timer and counter running,
	timer.start();
	counter.start();

	Serial.begin(115200);
}

void loop() {
	// For now we'll just dump the current frequency to the
	// serial terminal.
	Serial.print(currentHz);
	Serial.println("Hz");
	delay(100);
}

// Be sure to set the ISR routine to be an interrupt
void __attribute__((interrupt)) isr() {

	// We're running at a frequency of 10Hz, so the reading will
	// be the number of pulses in 0.1 seconds. Multiply
	// it by 10 to get the number of pulses in 1 second, which
	// is the number of Hz, of course.
	currentHz = counter.getAndResetCount() * 10;

	// And tell the chip we have handled the interrupt by
	// clearing the flag.
	clearIntFlag(_TIMER_4_IRQ);
}
