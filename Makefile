cc = gcc
CFLAGS = -wall -wextra -02

mag7sort: src/main.c
	$(CC) $(CFLAGS) -o mag7sort src/main.c

clean:
	rm -f mag7sort