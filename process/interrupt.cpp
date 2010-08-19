#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "interrupt.h"



interrupt::interrupt(const char *_handler, int _number)
{
	running_since = 0;
	number = _number;
	strncpy(handler, _handler, 31);
	wake_ups = 0;
	disk_hits = 0;
	accumulated_runtime = 0;
	waker = NULL;
	raw_count = 0;
}


void interrupt::start_interrupt(uint64_t time)
{
	running_since = time;
	raw_count ++;
}

void interrupt::end_interrupt(uint64_t time)
{
	uint64_t delta;

	delta = time - running_since;
	accumulated_runtime += delta;
}

double interrupt::Witts(void)
{
	double cost;

	cost = 0.1 * wake_ups + (accumulated_runtime / 1000000.0);

	return cost;
}

const char * interrupt::description(void)
{
	sprintf(desc, "Interrupt (%2i) %15s      time  %5.1fms    wakeups %3i  (total: %i)", number,
			handler,  accumulated_runtime / 1000000.0, wake_ups, raw_count);
	return desc;
}
