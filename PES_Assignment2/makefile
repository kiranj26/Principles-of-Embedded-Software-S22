EXEC     = assgn2
CC       = gcc

CFLAGS   = -Wall -Werror 
#CFLAGS   = -Wall -Werror -DDEBUG

LDFLAGS  = 

SRC      = main.c cbfifo.c test_cbfifo.c lllifo.c test_lllifo.c
OBJ      = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
		$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
		@rm -rf *.o
