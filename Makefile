all: tickety

CC = gcc

INCLUDE = .
CFLAGS = -g -Wall -ansi
PKG_LIBS = gtk+-2.0
GTK_CFLAGS = `pkg-config --cflags $(PKG_LIBS)`
GTK_LIBS = `pkg-config --libs $(PKG_LIBS)`

debug:
	$(CC) -o tickety tickety.c $(GTK_CFLAGS) $(GTK_LIBS) -DDEBUG

tickety: tickety.c
	$(CC) -o tickety tickety.c $(GTK_CFLAGS) $(GTK_LIBS)

clean:
	rm tickety
	rm tickety.exe