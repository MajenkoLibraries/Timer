#ifndef _TIMER_H
#define _TIMER_H

#if (ARDUINO >= 100)
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

struct tcon_s {
	union {
		uint32_t val;
		struct {
			unsigned _unused:1;
			unsigned tcs:1;
			unsigned tsync:1;
			unsigned _spare:1;
			unsigned tckps:3;
			unsigned tgate:1;
			unsigned _space:3;
			unsigned twip:1;
			unsigned twdis:1;
			unsigned sidl:1;
			unsigned frz:1;
			unsigned on:1;
			unsigned _blank:16;
		};
	};
} __attribute__((packed));

class Timer {
	public:
		int _vec;
		int _irq;
		int _spl;
		int _ipl;
		volatile uint32_t *_pr;
		volatile tcon_s *_tcon;
		int _ps_size;
		
		Timer();
		void begin();
		void setFrequency(uint32_t f);
		void start();
		void stop();
		void attachInterrupt(void (*isr)());
		void detatchInterrupt();
};

class Timer1 : public Timer {
	public:
		Timer1();	
		Timer1(int);	
};

class Timer2 : public Timer {
	public:
		Timer2();	
		Timer2(int);	
};

class Timer3 : public Timer {
	public:
		Timer3();	
		Timer3(int);	
};

class Timer4 : public Timer {
	public:
		Timer4();	
		Timer4(int);
};

class Timer5 : public Timer {
	public:
		Timer5();	
		Timer5(int);};

#endif
