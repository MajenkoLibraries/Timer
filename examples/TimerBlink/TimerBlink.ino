#include <Timer.h>

// Create a new timer object using T4
Timer4 timer;

const int LED = PIN_LED1;
const int PRESCALE = 10;

void setup() {
	pinMode(LED, OUTPUT);

	// The timer can't do a 1Hz interrupt, so let's do 10Hz and
	// manually pre-scale it down.
	timer.setFrequency(1 * PRESCALE);

	// Link in out ISR routine. Note, it is a real ISR routine,
	// so requires all the right attributes etc.
	timer.attachInterrupt(isr);

	// Start the timer running,
	timer.start();
}

void loop() {
}

// Be sure to set the ISR routine to be an interrupt
void __attribute__((interrupt)) isr() {
	static uint8_t ledState = 0;

	// ctr is our prescale counter. When this reaches 10
	// we will blink the LED.
	static int ctr = 0;

	ctr++;

	// And here we blink the LED.
	if (ctr == PRESCALE) {
		digitalWrite(LED, ledState);
		ledState = HIGH - ledState;
		ctr = 0;
	}

	// And tell the chip we have handled the interrupt by
	// clearing the flag.
	clearIntFlag(_TIMER_4_IRQ);
}
