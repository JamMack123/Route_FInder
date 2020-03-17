CC=g++
OBJS=server.o serialport.o 
CFLAGS=-c -O2 
LFLAGS=-static
PROGRAM=server


server: $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

server.o: server.cpp
	$(CC) server.cpp -o server.o $(CFLAGS)

serialport.o: serialport.cpp
	$(CC) serialport.cpp -o serialport.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
