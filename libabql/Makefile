CC=gcc
CFLAGS= -c -fpic -std=gnu11
LDFLAGS= -shared
RM= rm -f

LIBNAME=libabql
STATIC_LIBNAME=$(LIBNAME).a
DYNAMIC_LIBNAME=$(LIBNAME).so
SOURCE=abql.c
OBJECT=abql.o

all: $(STATIC_LIBNAME) $(DYNAMIC_LIBNAME) cleanbuild

cleanbuild:
	$(RM) *.o

clean:
	$(RM) *.o *.a *.so test.out

test: 
	$(CC) *.c -pthread -std=gnu11 -o test.out

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) $^

$(STATIC_LIBNAME): $(OBJECT)
	ar rcs $@ $^

$(DYNAMIC_LIBNAME): $(OBJECT)
	$(CC) $(LDFLAGS) -o $@ $^


