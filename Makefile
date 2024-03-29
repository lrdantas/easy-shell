TARGET = easyshell
LIBS = -lm
CC = gcc
CFLAGS = -Wall
.PHONY: default all clean
default: $(TARGET)
all: default
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
.PRECIOUS: $(TARGET) $(OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ -lreadline -lncurses
clean:
	-rm -f *.o
	-rm -f $(TARGET)
