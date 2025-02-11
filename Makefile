CC = gcc
CFLAGS = -Wall -Wextra -g 
SRC_DIR = src
OBJ_DIR = obj
BIN = lol_api

SRC = $(wildcard $(SRC_DIR)/*.c routes/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(BIN): $(OBJ) main.c
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

fclean: clean

re: fclean $(BIN)

.PHONY: clean fclean re
