SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)


all: fs.so

fs.so: $(OBJ)
	echo $(SRC)
	echo $^
	g++ -fPIC -shared $(I_FLAGS) $(C_FLAGS) -I$(srcdir) -o $@ $^

%o: %cpp
	g++ -c -fPIC -Wall $(I_FLAGS) -I$(srcdir) $(C_FLAGS) -o $@ $^

clean:
	rm -f *.o *.so
