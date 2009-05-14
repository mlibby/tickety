
CC = gcc

INCLUDE = .
CFLAGS = -g -Wall -ansi 
PKG_LIBS = gtk+-2.0
GTK_FLAGS = `pkg-config --cflags $(PKG_LIBS)` `pkg-config --libs $(PKG_LIBS)`

all: tickety

tickety: tickety_file.o tickety_ui.o
	$(CC) -o tickety tickety.c tickety_ui.o $(CFLAGS) $(GTK_FLAGS)

tickety_ui.o:
	$(CC) -c -o tickety_ui.o tickety_ui.c $(CFLAGS) $(GTK_FLAGS)

tickety_file.o:
	$(CC) -c -o tickety_file.o tickety_file.c $(CFLAGS)

clean:
	rm -f tickety tickety.exe
	rm -f tickety.o tickety_ui.o tickety_file.o
