SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
HDR_FILES = $(wildcard $(INC_DIR)/*.h)

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic `pkg-config --cflags gtk+-3.0 jansson`
LDFLAGS = `pkg-config --libs gtk+-3.0 jansson` -lssl -lcrypto

TARGET = uchat

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR_FILES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

uninstall: clean
	@rm -f $(TARGET)

.PHONY: all clean uninstall reinstall
