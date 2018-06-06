#ifndef ABQL_H
#define ABQL_H

#include <stdatomic.h>
#include <time.h>

struct ABQL {
	int *arr;
	struct timespec *sleep;
	int queue_sz;
	atomic_int ticket;
	atomic_int dequeueCount;
};

struct ABQL *ABQL_Create(int queue_sz, struct timespec *sleep);
atomic_int ABQL_Lock(struct ABQL *l);
void ABQL_Unlock(struct ABQL *l, atomic_int ticket);

#endif /* ABQL_H */
