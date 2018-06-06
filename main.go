package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"runtime/pprof"
	"time"
)

var profile = flag.Bool("profile", false,
	"whether to run a cpuprofile and output a .pprof file")

var locktype = flag.String("locktype", "c",
	"values are either 'c' or 'go', to determine which ABQL implementation "+
		"we'll use")

type ABQL interface {
	Lock() (ticket int)
	Unlock(ticket int)
}

func main() {

	flag.Parse()

	if *profile {
		f, err := os.Create(fmt.Sprintf("%s.pprof", locktype))
		if err != nil {
			log.Fatal(err)
		}
		pprof.StartCPUProfile(f)
		defer pprof.StopCPUProfile()
	}

	var l ABQL
	switch *locktype {
	case "c":
		l = NewC_ABQL()
	case "go":
		l = NewGo_ABQL()
	}

	fmt.Printf("Testing locktype '%s'\n", *locktype)

	go func() {
		ticket := l.Lock()
		fmt.Println("got Lock in goroutine")
		time.Sleep(3 * time.Second)
		fmt.Println("unlocking in goroutine...")
		l.Unlock(ticket)
	}()
	time.Sleep(time.Second)
	ticket := l.Lock()
	fmt.Println("got Lock in main")
	fmt.Println("unlocking in main...")
	l.Unlock(ticket)
	fmt.Println("Done.")
}
