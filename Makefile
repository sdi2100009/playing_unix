CC = gcc
CFLAGS = -Wall -Wextra -O2

all: manager client

manager: manager.c
	$(CC) $(CFLAGS) -o manager manager.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f manager client
