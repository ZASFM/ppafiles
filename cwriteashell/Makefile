CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = program

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

rebuild: clean $(TARGET)