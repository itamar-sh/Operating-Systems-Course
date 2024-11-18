SRC=container.cpp sockets.cpp
OBJS=$(SRC:.cpp=.o)
TARGETS=container sockets

CC=g++
TAR=tar
TARFLAGS=-cvf
TARNAME=ex5.tar
TARSRCS=$(SRC) Makefile README

all: $(TARGETS)

container: container.cpp
	$(CC) $^ -o container

sockets: sockets.cpp
	$(CC) $^ -o sockets

clean:
	$(RM) $(TARGETS) *~ *core

tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)
