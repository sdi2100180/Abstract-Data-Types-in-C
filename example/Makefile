# Sample Makefile to compile the libADT with a C file using it

# executable file
EXEC = example

# compiler
CC = gcc

# compiler options
CFLAGS = -Wall -Werror -g

# object files
OBJS = main.o

# produce executable file including libADT (assuming libADT is in the lib folder)
$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -L. ../lib/libADT.a

# delete files
clean:
	rm -f $(EXEC) $(OBJS)

# compile and run
run: $(EXEC)
	./$(EXEC)