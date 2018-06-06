#ifndef ABQL_H
#define ABQL_H

#include <stdatomic.h>
#include <time.h>

typedef struct {
	int *arr;
	int queue_sz;
	atomic_int ticket;
	atomic_int dequeueCount;
} ABQL;

#define ABQL_SLEEP_MICROSECOND (const struct timespec[]){{0, 1000}}, NULL

ABQL *ABQL_Create(int queue_sz);
atomic_int ABQL_Lock(ABQL *l);
void ABQL_Unlock(ABQL *l, atomic_int ticket);

#endif /* ABQL_H */
