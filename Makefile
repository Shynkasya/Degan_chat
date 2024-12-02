.PHONY: all uninstall reinstall
all:
	@echo "Make Libraries" 
	$(MAKE) -C libraries/sqlite3
	@echo "Make Server" 
	$(MAKE) -C server
	@echo "Make Client"
	$(MAKE) -C client 
	mv client/HolyChat ./
	mv server/uchat_server ./
	mv server/pidkiller ./
	@echo "SUCCESS"
uninstall:
	$(MAKE) -C libraries/sqlite3 uninstall
	$(MAKE) -C server uninstall
	$(MAKE) -C client uninstall
	@echo "All uninstalled"

reinstall: uninstall all

