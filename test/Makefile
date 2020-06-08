CFLAGS=-Wall -g

all: libzerocopyMQ test
	gcc generador.c -o generador
libzerocopyMQ:
	$(MAKE) -C ../libzerocopyMQ

test: test.o libzerocopyMQ.so
	$(CC) -o $@ $< ./libzerocopyMQ.so

test.o: zerocopyMQ.h

clean:
	rm -f *.o test


