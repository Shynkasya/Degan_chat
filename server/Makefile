NAME = uchat_server
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
CLIBS = -I../libraries/sqlite3
LIBS = ../libraries/sqlite3/libsqlite3.a -lpthread -ldl
#LIBS = libsqlite3.a
.PHONY: all clean uninstall reinstall
all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(CLIBS) -o $(NAME) src/*.c $(LIBS)  
	$(CC) $(CFLAGS) -o pidkiller pidkiller.c

clean:
	rm -rf obj

uninstall: clean
	rm -rf $(NAME)
	rm -rf pidkiller
	
reinstall: uninstall all
