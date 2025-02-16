OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
invert.exe: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.exe