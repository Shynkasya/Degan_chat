.PHONY: all uninstall reinstall
all:
	#@echo "Make Libraries" 
	#$(MAKE) -C libraries/sqlite3
	@echo "Make Server" 
	$(MAKE) -C server
	@echo "Make Client"
	$(MAKE) -C client 
	mv client/uchat ./
	mv server/uchat_server ./
	mv server/pidkiller ./
	@echo "SUCCESS"
uninstall:
	#$(MAKE) -C libraries/sqlite3 uninstall
	$(MAKE) -C server uninstall
	$(MAKE) -C client uninstall
	rm -rf ./uchat
	rm -rf ./uchat_server
	rm -rf ./pidkiller
	@echo "All uninstalled"

reinstall: uninstall all

