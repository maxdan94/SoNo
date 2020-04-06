CC=gcc
CFLAGS=-O9 -lm
LDFLAGS=
EXEC=main

all: $(EXEC)

main: order_core.o order_deg.o order_rand.o order_df.o main.o
	$(CC) -o ord order_core.o order_deg.o order_rand.o order_df.o main.o $(CFLAGS)

order_rand.o: order_rand.c
	$(CC) -o order_rand.o -c order_rand.c $(CFLAGS)

order_core.o: order_core.c
	$(CC) -o order_core.o -c order_core.c $(CFLAGS)

order_deg.o: order_deg.c
	$(CC) -o order_deg.o -c order_deg.c $(CFLAGS)

order_df.o: order_df.c
	$(CC) -o order_df.o -c order_df.c $(CFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm *.o ord
