CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = program

$(TARGET): hash_table.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

rebuild: clean $(TARGET)