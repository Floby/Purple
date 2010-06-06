
export V8_INCLUDEDIR=/usr/local/include/v8
export V8_JUICE_INCLUDEDIR=/usr/local/include/v8/juice
export LD_FLAGS=-rdynamic -lv8-juice -lv8
export PURPLE_INCLUDEDIR=$(homedir)/include
export I_FLAGS=-I$(APXS_INCLUDEDIR) -I$(V8_INCLUDEDIR) -I$(V8_JUICE_INCLUDEDIR)
export C_FLAGS=$(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB)

