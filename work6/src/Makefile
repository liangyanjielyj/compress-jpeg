EXE = ./Jpegmanager

SRC_C= main.c	\
	jpg_eb.c \
        jpge.c \

# C Complier
CC=gcc

CFLAGS= -I../include -DOS_IS_64BIT -D__ENVIRONMENT_LINUX__ -pipe -g -O0 -W -D_REENTRANT -D_CMNET_ -Wall

# C++ Complier
CCC=g++
CCFLAGS=$(CFLAGS)

MYLIBPATH = -L../lib

OBJS=$(SRC_C:.C=.o) $(SRC_c:.c=.o) $(SRC_cpp:.cpp=.o)
.SUFFIXES:
.SUFFIXES: .$(DBSUFFIX) .c .C .cpp .o .h .hpp

$(EXE): $(OBJS)
	$(CCC) -o $(EXE) $(CCFLAGS) $(LDFLAGS) $(OBJS) $(MYLIBPATH) $(DBLIB) 

all:
	-rm -f $(EXE) $(OBJS)
	$(MAKE) -f $(MAKEFILE)

.C.o:
	$(CCC) -v -o $@ -c $(CCFLAGS) $<
.c.o:
	$(CC) -v -o $@ -c $(CFLAGS) $<

clean:

	rm -f *.o $(UPDATEEXE) $(EXE) core
