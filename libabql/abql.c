#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

#include "abql.h"

ABQL *ABQL_Create(int queue_sz) {
	// malloc the struct
	ABQL *l = malloc(sizeof(ABQL));
	// malloc the array
	l->queue_sz = queue_sz;
	l->arr = malloc(queue_sz * sizeof(int));
	memset(l->arr, 0, queue_sz * sizeof(int));
	// set the first flag to 1
	l->arr[0] = 1;
	// init the atomic ticket counters
	atomic_init (&l->ticket, 0);
	atomic_init (&l->dequeueCount, 0);
	return l;
}

atomic_int ABQL_Lock(ABQL *l) {
	// if we're here, we can safely grab a ticket and start waiting on the flag
	atomic_int ticket = atomic_fetch_add (&l->ticket, 1);
	// wait until the number waiting in queue is < queue_sz (since we don't want
	// to wrap around and jump the queue by waiting on a flag which is already
	// being waited-on
	while (ticket - atomic_load(&l->dequeueCount) >= l->queue_sz) {
		nanosleep(ABQL_SLEEP_MICROSECOND);
	}
	while (l->arr[ticket % l->queue_sz] != 1) {
		nanosleep(ABQL_SLEEP_MICROSECOND);
	}
	return ticket;
}

void ABQL_Unlock(ABQL *l, atomic_int ticket) {
	l->arr[ticket % l->queue_sz] = 0;
	l->arr[(ticket + 1) % l->queue_sz] = 1;
	atomic_fetch_add(&(l->dequeueCount), 1);
}
