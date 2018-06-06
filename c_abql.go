package main

/*
#cgo CFLAGS: -I${SRCDIR}/libabql
#cgo LDFLAGS: -L${SRCDIR}/libabql -labql
#include "abql.h"
#include <time.h>
*/
import "C"

type C_ABQL struct {
	l *C.struct_ABQL
}

func NewC_ABQL() *C_ABQL {
	timespec := C.struct_timespec{0, SLEEP_NS}
	return &C_ABQL{C.ABQL_Create(QUEUE_SZ, &timespec)}
}

func (l *C_ABQL) Lock() int {
	return int(C.ABQL_Lock(l.l))
}

func (l *C_ABQL) Unlock(ticket int) {
	C.ABQL_Unlock(l.l, C.atomic_int(ticket))
}
