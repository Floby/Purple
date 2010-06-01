all:  test.so

test.so: test.o
	g++ -fPIC -shared $(I_FLAGS) $(C_FLAGS) -I$(srcdir) -o $@ $^

test.o: test.cpp
	g++ -c -fPIC -Wall $(I_FLAGS) -I$(srcdir) $(C_FLAGS) -o $@ $^

clean:
	rm -f *.o *.so
