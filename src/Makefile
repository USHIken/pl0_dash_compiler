
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm 

pl0_cmplr.o: main.c codegen.c table.c compile.c getSource.c 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^