CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS =
EXEC = xd
EXEC1 = bad_xd

all: $(EXEC) $(EXEC1)

$(EXEC): $(EXEC).o 
	$(CC) $^ $(LFLAGS) -o $@

$(EXEC1): $(EXEC1).o 
	$(CC) $^ $(LFLAGS) -o $@

clean:
	rm -rf $(EXEC) *.o
	rm -rf $(EXEC1) *.o 

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format

