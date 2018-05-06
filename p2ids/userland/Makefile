#userspace .c makefile

SRCS = monitor.c
OBJS = $(SRCS:.c=.o)
BIN = monitor
CFLAGS = -g
LDFLAGS = -g

all: $(BIN)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f $(OBJS)
	-rm -f $(BIN)

#kernel makefile
#obj-y := kernel_myList.o
