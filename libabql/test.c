#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "abql.h"
#include "utils.h"

typedef struct {
	struct ABQL *l;
	int id;
} LockerArgs;

void *locker(void *lockerArgs) {

	LockerArgs *args = (LockerArgs*)lockerArgs;
	struct ABQL *l = args->l;
	int id = args->id;
	free(lockerArgs);

	for (int i = 0; i < 4; i++) {
		atomic_int ticket = ABQL_Lock(l);
		printfflush("locker %d got lock.\n", id);
		// sleep 1 second
		SLEEP_MS(3000);
		printfflush("locker %d unlocking...\n", id);
		ABQL_Unlock(l, ticket);
		// sleep 500 ms
		SLEEP_MS(500);
	}
}

int main (int argc, char *argv[]) {

	// array of locker pthread ID's (used for join later)
	const int N_LOCKERS = 12;
	pthread_t *pthread_locker_ids = malloc(N_LOCKERS * sizeof(pthread_t));

	// the lock
	// configured to sleep for a microsecond while spinning
	struct timespec sleep = {0, 1000};
	struct ABQL *l = ABQL_Create(4, &sleep);

	// start the locker threads
	for (int i = 0; i < N_LOCKERS; i++) {
		LockerArgs *lockerArgs = malloc(sizeof(LockerArgs));
		lockerArgs->l = l;
		lockerArgs->id = i;
		pthread_create(
				pthread_locker_ids + i,
				NULL, 
				locker, 
				lockerArgs);
	}
	for (int i = 0; i < N_LOCKERS; i++) {
		pthread_join(pthread_locker_ids[i], NULL);
	}
	printfflush("All locker() threads joined.\n");
	exit(0);
}
