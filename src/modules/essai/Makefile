include ../../../config.mk
include $(srcdir)/flags.mk
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)


all: essai.so

exe: $(OBJ)
	g++ -Wall -fPIC -L/home/floby/dev/purple/build -lmod_purple -lv8 $(I_FLAGS) $(C_FLAGS) -I$(srcdir) -o $@ $^

essai.so: $(OBJ)
	echo $(SRC)
	echo $^
	g++ -fPIC -shared $(I_FLAGS) $(C_FLAGS) -I$(srcdir) -o $@ $^

%o: %cpp
	env | grep FLAGS
	g++ -c -fPIC -Wall $(I_FLAGS) -I$(srcdir) $(C_FLAGS) -o $@ $^

clean:
	rm -f *.o *.so


