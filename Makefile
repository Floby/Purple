include config.mk

#all: shared-object modules
all: shared-object 

clean: clean-src
	rm $(builddir)/$(SONAME);

clean-src:
	@cd $(srcdir) && $(MAKE) clean

shared-object: $(builddir)/$(SONAME) 

$(builddir)/$(SONAME) : $(srcdir)/$(SONAME)
	mv $(srcdir)/$(SONAME) $(builddir)/

$(srcdir)/$(SONAME) :
	@cd $(srcdir) && $(MAKE)

public-headers: $(incdir)/$(NAME).h

$(incdir)/$(NAME).h : $(srcdir)/public-header.h
	cp $(srcdir)/public-header.h $(incdir)/

$(srcdir)/public-header.h:
	@cd $(srcdir) && $(MAKE) public-header.h

modules: public-headers
	@cd $(srcdir)/modules && $(MAKE)
	cp -v $(srcdir)/modules/m_*/*.so $(builddir)/modules/

# install the shared object file into Apache 
#install: install-so install-modules
install: install-so

install-so: shared-object
	$(APXS) -i -n '$(NAME)' $(builddir)/$(SONAME)

install-modules: modules
	cp -v $(builddir)/modules/*.so $(PURPLE_MODULES)/bin/

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
#
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


