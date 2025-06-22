all: sender receiver

sender: sender.c fifo_snd.c
	gcc -o sender sender.c fifo_snd.c

receiver: receiver.c fifo_recv.c
	gcc -o receiver receiver.c fifo_recv.c

clean:
	rm sender receiver