all:
	gcc -Wall -o scheduler_pro main.c priority_queue.c rfc_parser.c scheduler.c

clean:
	rm -f scheduler_pro