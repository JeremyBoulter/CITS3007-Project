CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
TARGET = crypto

all: $(TARGET)

$(TARGET): crypto.c
	$(CC) $(CFLAGS) -o $(TARGET) crypto.c

clean:
	rm -f $(TARGET)