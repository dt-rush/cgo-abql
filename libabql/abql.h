#ifndef ABQL_H
#define ABQL_H

#include <stdatomic.h>
#include <time.h>

struct ABQL {
	int *arr;
	int queue_sz;
	atomic_int ticket;
	atomic_int dequeueCount;
};

#define ABQL_SLEEP_MICROSECOND (const struct timespec[]){{0, 1000}}, NULL

struct ABQL *ABQL_Create(int queue_sz);
atomic_int ABQL_Lock(struct ABQL *l);
void ABQL_Unlock(struct ABQL *l, atomic_int ticket);

#endif /* ABQL_H */
