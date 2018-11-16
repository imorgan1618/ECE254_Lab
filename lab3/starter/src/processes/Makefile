# Makefile, ECE254 lab5 Linux Concurrency Control
# Jonathan Shahen, 2018/09/03
# Yiqing Huang, 2014/07/16

CC = gcc
CFLAGS = -Wall -ggdb -std=c99
LD = gcc
LDFLAGS = -ggdb
LDLIBS = -lrt -lpthread -lm

OBJS1 = sender.o point.o
OBJS2 = receiver.o point.o

all: sender.out receiver.out produce

sender.out: $(OBJS1)
	$(LD) -o $@ $(OBJS1) $(LDFLAGS) $(LDLIBS)

receiver.out: $(OBJS2)
	$(LD) -o $@ $(OBJS2) $(LDFLAGS) $(LDLIBS)

produce: produce.o
	$(LD) $(LDFLAGS) -o $@.out $^ $(LDLIBS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *.d *.o *.out
