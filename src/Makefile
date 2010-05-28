##
##  Makefile -- Build procedure for fast3lpoad Apache module
##
##  This is a C++ module so things have to be handled a little differently.

include ../config.mk

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
V8_INCLUDEDIR=/usr/local/include/v8
LD_FLAGS=-lv8

#   the default target
all: $(SONAME)

$(SONAME): $(OBJ)
	g++ -fPIC -shared -o $@ $^ $(APXS_LIBS_SHLIB) $(LD_FLAGS)

%o : %cpp
	g++ -c -fPIC -I$(APXS_INCLUDEDIR) -I$(V8_INCLUDEDIR) -I. -I- $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -Wall -o $@ $< 

# compile the shared object file. use g++ instead of letting apxs call
# ld so we end up with the right c++ stuff. We do this in two steps,
# compile and link.

# compile
mod_cpphello.o: mod_cpphello.cpp
	g++ -c -fPIC -I$(APXS_INCLUDEDIR) -I. -I- $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -Wall -o $@ $< 

# link
mod_cpphello.so: mod_cpphello.o 
	g++ -fPIC -shared -o $@ $< $(APXS_LIBS_SHLIB) $(LD_FLAGS)

public-header.h:
	touch public-header.h

# display the apxs variables
check_apxs_vars:
	@echo APXS_CC $(APXS_CC);\
	echo APXS_TARGET $(APXS_TARGET);\
	echo APXS_CFLAGS $(APXS_CFLAGS);\
	echo APXS_SBINDIR $(APXS_SBINDIR);\
	echo APXS_CFLAGS_SHLIB $(APXS_CFLAGS_SHLIB);\
	echo APXS_INCLUDEDIR $(APXS_INCLUDEDIR);\
	echo APXS_LD_SHLIB $(APXS_LD_SHLIB);\
	echo APXS_LIBEXECDIR $(APXS_LIBEXECDIR);\
	echo APXS_LDFLAGS_SHLIB $(APXS_LDFLAGS_SHLIB);\
	echo APXS_SYSCONFDIR $(APXS_SYSCONFDIR);\
	echo APXS_LIBS_SHLIB $(APXS_LIBS_SHLIB)

#   cleanup
clean:
	-rm -f *.so *.o *~

#   install and activate shared object by reloading Apache to
#   force a reload of the shared object file
reload: install restart

#   the general Apache start/restart/stop
#   procedures
start:
	$(APACHECTL) start
restart:
	$(APACHECTL) restart
stop:
	$(APACHECTL) stop

