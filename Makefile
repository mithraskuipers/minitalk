# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/23 23:30:26 by mikuiper      #+#    #+#                  #
#    Updated: 2022/04/24 19:13:13 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Library Name #
CLIENT	=	client
SERVER	=	server

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRC_C	=	client.c
SRC_S	=	server.c
INC		=	-I. -I$(LIBFT_DIR) -I$(LIBFT_DIR)/stack -I$(LIBFT_DIR)/get_next_line

# Compiling Variables #
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

# Debugger #
ifeq ($(DEBUG), 1)
	D_FLAG	=	-g
endif

# Fsanitize #
ifeq ($(SANITIZE), 1)
	D_FLAG	=	-fsanitize=leak -g
endif


all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(D_FLAG) $(CFLAG) $(SRC_S) $(LIBFT) $(INC) -o $(SERVER)
	@printf "server ready.\n"

$(CLIENT): $(LIBFT)
	@ $(CC) $(D_FLAG) $(CFLAG) $(SRC_C) $(LIBFT) $(INC) -o $(CLIENT)
	@printf "client ready.\n"


$(LIBFT):
	@ $(MAKE) DEBUG=$(DEBUG) -C ./libft

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

fclean:
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "client removed.\n"
	@printf "server removed.\n"

re: fclean all

mandatory:	$(CLIENT) $(SERVER)
bonus:		mandatory

m : mandatory
b : bonus

.PHONY: all clean fclean re mandatory m bonus b