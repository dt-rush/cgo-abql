package main

/*
#cgo CFLAGS: -I${SRCDIR}/libabql
#cgo LDFLAGS: -L${SRCDIR}/libabql -labql
#include "abql.h"
*/
import "C"
import (
	"fmt"
	"time"
)

func main() {
	l := C.ABQL_Create(4)
	go func() {
		ticket := C.ABQL_Lock(l)
		fmt.Println("got Lock in goroutine")
		time.Sleep(3 * time.Second)
		fmt.Println("unlocking in goroutine...")
		C.ABQL_Unlock(l, ticket)
	}()
	time.Sleep(time.Second)
	ticket := C.ABQL_Lock(l)
	fmt.Println("got Lock in main")
	fmt.Println("unlocking in main...")
	C.ABQL_Unlock(l, ticket)
	fmt.Println("Done.")
}
