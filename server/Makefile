NAME = uchat_server
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LIBS = ../libraries/sqlite3/libsqlite3.a
#LIBS = libsqlite3.a
.PHONY: all clean uninstall reinstall
all: $(NAME)

$(NAME):
	mkdir obj
	$(CC) $(CFLAGS) -o $(NAME) src/*.c $(LIBS) 

clean:
	rm -rf obj

uninstall: clean
	rm -rf $(NAME)
	
reinstall: uninstall all
