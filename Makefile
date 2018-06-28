CC = g++
CC_FLAGS = -std=c++11 -W -Wall -Werror -I./
EXEC = my_tar
OBJS = main.o append.o compare.o concatenate.o create.o extract.o list.o update.o

$(EXEC): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $@

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c -o $@ main.cpp

append.o: append.cpp append.hpp
	$(CC) $(CC_FLAGS) -c -o $@ append.cpp

compare.o: compare.cpp compare.hpp
	$(CC) $(CC_FLAGS) -c -o $@ compare.cpp

concatenate.o: concatenate.cpp concatenate.hpp
	$(CC) $(CC_FLAGS) -c -o $@ concatenate.cpp

create.o: create.cpp create.hpp
	$(CC) $(CC_FLAGS) -c -o $@ create.cpp

extract.o: extract.cpp extract.hpp
	$(CC) $(CC_FLAGS) -c -o $@ extract.cpp

list.o: list.cpp list.hpp
	$(CC) $(CC_FLAGS) -c -o $@ list.cpp
update.o : update.cpp update.hpp
	$(CC) $(CC_FLAGS) -c -o $@ update.cpp

all: $(EXEC)

clean : 
	rm -rf $(OBJS) $(EXEC)
