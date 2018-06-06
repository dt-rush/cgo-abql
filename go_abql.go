package main

import (
	"sync/atomic"
	"time"
)

type Go_ABQL struct {
	arr          []int
	queue_sz     int
	ticket       uint32
	dequeueCount uint32
}

func NewGo_ABQL() *Go_ABQL {
	abql := Go_ABQL{
		make([]int, QUEUE_SZ),
		QUEUE_SZ,
		0,
		0}
	abql.arr[0] = 1
	return &abql
}

func (l *Go_ABQL) Lock() int {
	ticket := atomic.AddUint32(&l.ticket, 1) - 1
	for ticket-atomic.LoadUint32(&l.dequeueCount) >= uint32(l.queue_sz) {
		time.Sleep(time.Microsecond)
	}
	for l.arr[ticket%uint32(l.queue_sz)] != 1 {
		time.Sleep(time.Microsecond)
	}
	return int(ticket)
}

func (l *Go_ABQL) Unlock(ticket int) {
	l.arr[ticket%l.queue_sz] = 0
	l.arr[(ticket+1)%l.queue_sz] = 1
	atomic.AddUint32(&l.dequeueCount, 1)
}
