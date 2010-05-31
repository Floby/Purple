mod_purple.cpp: PurpleModule.hpp Exceptions.hpp
	@touch $@

Processor.hpp: PScript.hpp Exceptions.hpp ModuleManager.hpp
	@echo $? is more recent than $@
	@touch $@

RequestProcessor.hpp: Processor.hpp
	@echo $? is more recent than $@
	@touch $@

PurpleModule.cpp: PurpleModule.hpp RequestProcessor.hpp
	@touch $@

PScript.cpp: PScript.hpp Exceptions.hpp
	@touch $@


ModuleProcessor.hpp: Processor.hpp
	@touch $@
