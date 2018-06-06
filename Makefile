CC=go build
GOBUILDFLAGS= --ldflags '-extldflags "-static"'

all: main.go

clean:
	rm -f main

main.go: libabql.so
	$(CC) $(GOBUILDFLAGS) -o main.out $@

libabql.so:
	make -C libabql/
