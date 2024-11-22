SQLITE3 = sqlite3.o
SQLITE3_LIBNAME = libsqlite3.a

CC = gcc -c


.PHONY: all clean uninstall reinstall

all: $(SQLITE3)


$(SQLITE3):
	$(CC) sqlite3.c 
	ar -rcs $(SQLITE3_LIBNAME) sqlite3.o

uninstall: clean
	rm -rf $(SQLITE3_LIBNAME)
	
clean:
	rm -rf *.o
	

reinstall: uninstall all
