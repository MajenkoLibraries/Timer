#include <Timer.h>

Timer::Timer() {
	// Constructor code here
	_tcon = NULL;
	_pr = NULL;
	_vec = 0;
	_irq = 0;
	_ipl = 0;
	_spl = 0;
	_ps_size = 2;
}

void Timer::begin() {
	// Initialization code here
}

void Timer::setFrequency(uint32_t f) {
	uint32_t baseclock = F_CPU;
	uint8_t ps = 0;

	if (_ps_size == 2) {
		if (baseclock / f > 65535) {
			baseclock = F_CPU / 8;
			ps = 1;
		}
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 64;
	        ps = 2;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 256;
	        ps = 3;
	    }
	} else {
		if (baseclock / f > 65535) {
			baseclock = F_CPU / 2;
			ps = 1;
		}
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 4;
	        ps = 2;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 8;
	        ps = 3;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 16;
	        ps = 4;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 32;
	        ps = 5;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 64;
	        ps = 6;
	    }
	
	    if (baseclock / f > 65535) {
	        baseclock = F_CPU / 256;
	        ps = 7;
	    }
	}
	_tcon->tckps = ps;
	*_pr = baseclock / f;
}

void Timer::start() {
	_tcon->on = 1;
}


void Timer::stop() {
	_tcon->on = 0;
}

void Timer::attachInterrupt(void (*isr)()) {
	setIntVector(_vec, isr);
	setIntPriority(_vec, _ipl, _spl);
	clearIntFlag(_irq);
	setIntEnable(_irq);
}

void Timer::detatchInterrupt() {
	clearIntEnable(_irq);
	setIntPriority(_vec, 0, 0);
	clearIntVector(_vec);
}

Timer1::Timer1() {
	_vec = _TIMER_1_VECTOR;
	_irq = _TIMER_1_IRQ;
	_ipl = 4;
	_spl = 0;
	_tcon = (tcon_s *)&T1CON;
	_pr = &PR1;
	_ps_size = 2;
}

Timer1::Timer1(int ipl) {
	_vec = _TIMER_1_VECTOR;
	_irq = _TIMER_1_IRQ;
	_ipl = ipl;
	_spl = 0;
	_tcon = (tcon_s *)&T1CON;
	_pr = &PR1;
	_ps_size = 2;
}

Timer2::Timer2() {
	_vec = _TIMER_2_VECTOR;
	_irq = _TIMER_2_IRQ;
	_ipl = 4;
	_spl = 0;
	_tcon = (tcon_s *)&T2CON;
	_pr = &PR2;
	_ps_size = 3;
}

Timer2::Timer2(int ipl) {
	_vec = _TIMER_2_VECTOR;
	_irq = _TIMER_2_IRQ;
	_ipl = ipl;
	_spl = 0;
	_tcon = (tcon_s *)&T2CON;
	_pr = &PR2;
	_ps_size = 3;
}

Timer3::Timer3() {
	_vec = _TIMER_3_VECTOR;
	_irq = _TIMER_3_IRQ;
	_ipl = 4;
	_spl = 0;
	_tcon = (tcon_s *)&T3CON;
	_pr = &PR3;
	_ps_size = 3;
}

Timer3::Timer3(int ipl) {
	_vec = _TIMER_3_VECTOR;
	_irq = _TIMER_3_IRQ;
	_ipl = ipl;
	_spl = 0;
	_tcon = (tcon_s *)&T3CON;
	_pr = &PR3;
	_ps_size = 3;
}

Timer4::Timer4() {
	_vec = _TIMER_4_VECTOR;
	_irq = _TIMER_4_IRQ;
	_ipl = 4;
	_spl = 0;
	_tcon = (tcon_s *)&T4CON;
	_pr = &PR4;
	_ps_size = 3;
}

Timer4::Timer4(int ipl) {
	_vec = _TIMER_4_VECTOR;
	_irq = _TIMER_4_IRQ;
	_ipl = ipl;
	_spl = 0;
	_tcon = (tcon_s *)&T4CON;
	_pr = &PR4;
	_ps_size = 3;
}

Timer5::Timer5() {
	_vec = _TIMER_5_VECTOR;
	_irq = _TIMER_5_IRQ;
	_ipl = 4;
	_spl = 0;
	_tcon = (tcon_s *)&T5CON;
	_pr = &PR5;
	_ps_size = 3;
}

Timer5::Timer5(int ipl) {
	_vec = _TIMER_5_VECTOR;
	_irq = _TIMER_5_IRQ;
	_ipl = ipl;
	_spl = 0;
	_tcon = (tcon_s *)&T5CON;
	_pr = &PR5;
	_ps_size = 3;
}