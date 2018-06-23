CC = g++

CC_FLAGS = -W -Werror -Wall -I./

EXEC = create

OBJS = create.o

$(EXEC): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $@
$(OBJS): create.cpp
	$(CC) $(CC_FLAGS) -c -o $@ create.cpp
all: $(EXEC)

clean :
	rm -rf $(OBJS) $(EXEC)
