all: TCP_Sender TCP_Receiver

TCP_Receiver: TCP_Receiver.o
	gcc -o TCP_Receiver TCP_Receiver.o

TCP_Sender: TCP_Sender.o
	gcc -o TCP_Sender TCP_Sender.o

TCP_Sender.o: TCP_Sender.c TCP_Sender.h
	gcc -c TCP_Sender.c

TCP_Receiver.o: TCP_Receiver.c TCP_Receiver.h
	gcc -c TCP_Receiver.c

clean:
	rm *.o TCP_Sender TCP_Receiver
	

