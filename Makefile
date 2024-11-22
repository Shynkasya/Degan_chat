INC = inc
OBJ = obj
SRC = src
LIBMX = libmx

CC = clang
CCFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic 

SERVER = uchat_server
CLIENT = uchat

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(NAME)


$(OBJ)/%.o: $(SRC)/%.c $(wildcard $(INC)/*.h)
	@mkdir -p $(OBJ)
	@$(CC) $(CCFLAGS) -I $(INC) -c $< -o $@

$(SERVER): $(OBJS)
	@$(CC) $(CCFLAGS) -I $(INC) -I $^ -o $@
	
	$(SERVER): $(OBJS)
	@$(CC) $(CCFLAGS) -I $(INC) -I $^ -o $@

.PHONY: clean uninstall reinstall

uninstall: clean
	@rm -f $(NAME)
	@make $@ -C $(LIBMX)

clean:
	@rm -rf $(OBJ)
	@make $@ -C $(LIBMX)

reinstall: uninstall all
