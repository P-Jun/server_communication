CC = gcc
CFLAGS=-O2 -Wall
LDLIBS = -lpthread -lmysqlclient

all: server_con

server_con: server_con.c trans.c

clean:
	rm -rf *~ server_con *.o
