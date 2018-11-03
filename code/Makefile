CC = g++
CFLAGS =
EXEC_NAME = triangleToSAT
OBJ_FILES = triangleToSAT.o
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean :
	rm -f $(EXEC_NAME) *.o