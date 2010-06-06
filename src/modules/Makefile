subdirs=$(wildcard *)


all: modules

modules:
	@for d in $(subdirs) ; do \
		if test -d "$$d" ; then \
		    echo going in $$d ;\
		    (cd $$d && pwd && $(MAKE)) ;\
		fi; \
	done

clean: 
	@for d in $(subdirs) ; do \
		if test -d "$$d" ; then \
		    echo going in $$d ;\
		    (cd $$d && pwd  && $(MAKE) clean) ;\
		fi; \
	done
	rm -f $(builddir)/modules/*.so
