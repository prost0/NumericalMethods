CC = g++
LD = g++
CCFLAGS = -std=c++11
LDFLAGS =  
OBJ = main.o matrix.o vector.o
.SUFFIXES: .cpp .o

all: prog

prog: $(OBJ)
	$(LD) $(LDFLAGS) -o prog $(OBJ)

main.o: main.cpp

matrix.o:matrix.cpp matrix.hpp

vector.o:vector.cpp vector.hpp

.cpp.o: 
	$(CC) $(CCFLAGS) -c $< -o $@

matrix.cpp: matrix.hpp

vector.cpp: vector.hpp

splines.cpp:splines.hpp

clean: 
	rm *.o prog.exe

# flags="-Wextra -Wall -pedantic -std=c99 -lm"

# all:start

# start: main.o m_matrix.o
# 	gcc $(flags) -o main.o m_matrix.o

# main.o: main.c
# 	gcc -c $(flags) main.c

# m_matrix.o: m_matrix_norm.h m_matrix.c
# 	gcc -c $(flags) m_matrix_norm.h m_matrix.c 

# clean 
# 	rm -f *.o