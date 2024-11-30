all:
	@echo "Make Libraries" 
	$(MAKE) -C libraries/sqlite3
	@echo "Make Server" 
	$(MAKE) -C server
	@echo "Make Client"
	$(MAKE) -C client 
	@echo "SUCCESS"

reinstall:
	$(MAKE) -C libraries/sqlite3 reinstall
	$(MAKE) -C server reinstall
	$(MAKE) -C client reinstall
	@echo "All reinstalled"

uninstall:
	$(MAKE) -C libraries/sqlite3 uninstall
	$(MAKE) -C server uninstall
	$(MAKE) -C client uninstall
	@echo "All uninstalled"
