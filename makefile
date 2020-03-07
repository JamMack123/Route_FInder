CC=g++
OBJS=server.o
CFLAGS=-c -O2 
LFLAGS=-static
PROGRAM=server


server: $(OBJS)
	$(CC) server.o -o $(PROGRAM) $(LFLAGS)

$(OBJS): server.cpp
	$(CC) server.cpp -o $(OBJS) $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
