OPT_GCC = -std=c99 -Wall -Wextra

all: cons prod

cons:
	cc $(OPT_GCC) -o cons consumer.c

prod:
	cc $(OPT_GCC) -o prod producer.c

run: cons prod
	./prod
	./cons

clean:
	rm -f cons prod

