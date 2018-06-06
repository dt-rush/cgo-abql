cgo-abql
===

Written to teach myself about Array-Based Queueing Locks, C11 atomic 
types/operations, building C static libraries, statically-linking C libraries
into Go.

`libabql/` contains the Array-Based Queueing Lock implementation and a 
program to demonstrate it (`test.c`).

`main.go` imports and uses the library

Build
===

Run `make`
