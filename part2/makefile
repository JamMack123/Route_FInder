CC=g++
OBJS=server.o dijkstra.o digraph.o serialport.o
CFLAGS=-c -O2 
LFLAGS=-static
PROGRAM=server


server: $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

server.o: server.cpp
	$(CC) server.cpp -o server.o $(CFLAGS)

dijkstra.o: dijkstra.cpp
	$(CC) dijkstra.cpp -o dijkstra.o $(CFLAGS)

digraph.o: digraph.cpp
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)

serialport.o: serialport.cpp
	$(CC) serialport.cpp -o serialport.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
