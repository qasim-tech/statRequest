
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
 
main: Unittest.o Request.o StatRequest.o
	$(CC) $(CFLAGS) -o unittest Unittest.o Request.o StatRequest.o

Unittest.o: Unittest.cpp
	$(CC) $(CFLAGS) -c Unittest.cpp

Request.o: Request.cpp Request.hpp
	$(CC) $(CFLAGS) -c Request.cpp

StatRequest.o: StatRequest.cpp StatRequest.hpp
	$(CC) $(CFLAGS) -c StatRequest.cpp
 