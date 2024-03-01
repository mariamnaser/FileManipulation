CC      = gcc
TARGET  = main
C_FILES = $(filter-out $(TARGET).c, $(wildcard *.c))
OBJS    = $(patsubst %.c,%.o,$(C_FILES))
CFLAGS  = -g -Wall -Werror -pedantic-errors
LDFLAGS =

.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS) $(TARGET).c
	$(CC) $(CFLAGS) $(OBJS) $(TARGET).c -o -.dSYM $(TARGET) $(LDFLAGS)
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o -.dSYM $@ $<
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
	rm -d -r $(TARGET).dSYM
