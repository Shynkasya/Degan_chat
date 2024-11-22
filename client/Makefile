NAME = uchat
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean uninstall reinstall
all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) src/*.c  

clean:
	rm -rf obj

uninstall: clean
	rm -rf $(NAME)
	
reinstall: uninstall all
