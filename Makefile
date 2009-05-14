
CC = gcc

INCLUDE = .
PKG_LIBS = gtk+-2.0
CFLAGS = -g -Wall -ansi `pkg-config --cflags $(PKG_LIBS)` `pkg-config --libs $(PKG_LIBS)`

all: tickety

tickety: tickety_ui.o
	$(CC) -o tickety tickety.c tickety_ui.o $(CFLAGS)

tickey_ui.o:
	$(CC) -o tickety_ui.o tickety_ui.c $(CFLAGS)

clean:
	rm -f tickety
	rm -f tickety.o tickety_ui.o
	rm -f tickety.exe