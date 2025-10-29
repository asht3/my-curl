CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TARGET = my_curl
SRCS = src/main.c \
	   src/url_parser.c \
	   src/network_utils.c \
	   src/http_client.c \
	   src/utils.c \

OBJ_DIR = obj
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean fclean re