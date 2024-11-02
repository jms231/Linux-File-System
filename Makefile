CC = gcc
OBJ = proj2find1working find2working proj2find3working

all: $(OBJ)

proj2find1working: proj2find1working.o
	$(CC) -o $@ $^

find2working: find2working.o
	$(CC) -o $@ $^

proj2find3working: proj2find3working.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^

clean:
	rm -f $(OBJ) *.o
