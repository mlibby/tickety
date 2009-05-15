#   Copyright 2009, Michael C. Libby
#
#   This file is part of Tickety.
#
#   Tickety is free software: you can redistribute it and/or modify it
#   under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Tickety is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Tickety.  If not, see <http://www.gnu.org/licenses/>.


CC = gcc

INCLUDE = .
CFLAGS = -g -Wall -ansi
PKG_LIBS = gtk+-2.0
GTK_FLAGS = `pkg-config --cflags $(PKG_LIBS)`
GTK_LIBS = `pkg-config --libs $(PKG_LIBS)`

all: tickety

tickety: tickety_task.o tickety_file.o tickety_task.o tickety_ui.o tickety.h
	$(CC) -o tickety tickety.c tickety_task.o tickety_ui.o tickety_file.o \
	$(CFLAGS) $(GTK_FLAGS) $(GTK_LIBS)

tickety_ui.o: tickety_task.o tickety_ui.h tickety_ui.h tickety_common.h
	$(CC) -c tickety_ui.c $(CFLAGS) $(GTK_FLAGS)

tickety_file.o: tickety_task.o tickety_file.h tickety_common.h
	$(CC) -c tickety_file.c $(CFLAGS)

tickety_task.o: tickety_task.h tickety_common.h
	$(CC) -c tickety_task.c $(CFLAGS)

clean:
	rm -f tickety tickety.exe
	rm -f *.o
