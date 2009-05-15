
CC = gcc

INCLUDE = .
CFLAGS = -g -Wall -ansi
PKG_LIBS = gtk+-2.0
GTK_FLAGS = `pkg-config --cflags $(PKG_LIBS)`
GTK_LIBS = `pkg-config --libs $(PKG_LIBS)`

all: tickety

tickety: tickety_task.o tickety_file.o tickety_ui.o tickety.h
	$(CC) -o tickety tickety.c tickety_ui.o tickety_file.o $(CFLAGS) $(GTK_FLAGS) $(GTK_LIBS)

tickety_ui.o: tickety_task.o tickety_ui.h tickety_ui.h tickety_common.h
	$(CC) -c tickety_ui.c $(CFLAGS) $(GTK_FLAGS)

tickety_file.o: tickety_task.o tickety_file.h tickety_common.h
	$(CC) -c tickety_file.c $(CFLAGS)

tickety_task.o: tickety_task.h tickety_common.h
	$(CC) -c tickety_task.c $(CFLAGS)

clean:
	rm -f tickety tickety.exe
	rm -f *.o
