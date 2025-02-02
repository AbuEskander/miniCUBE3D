SRCS = main.c player.c
SRC_DIR = src
OBJ_DIR = build
CC = cc
NAME = miniCUBED
MINIX = minilibx-linux
LIBS = -L./minilibx-linux/ -lmlx_Linux -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Werror -Wextra -I./includes -I./minilibx-linux/ $(LIBS)
SRCSDIR=$(addprefix src/,$(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCSDIR))
LIBFT = libft

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MINIX)
	$(CC) $(OBJS) $(CFLAGS)  -o $(NAME)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
clean: 
	@make -C $(MINIX) clean
	rm -f  $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re