# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baavril <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 10:37:50 by baavril           #+#    #+#              #
#    Updated: 2019/02/14 08:45:17 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

NAME		=	ft_ls

LIB_PATH	=	libft
LIB			=	$(LIB_PATH)/libft.a

DIR_O		=   temporary

SRC_PATH	=	.
SOURCES 	=	ft_ls.c \
				options_management.c \
				parsing.c \
				read_and_stock_ls.c

SRCS    	=   $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS    	=   $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

HDR_PATH	=	.
HEADERS		=	ft_ls.h
HDR	    	=   $(addprefix $(HDR_PATH)/,$(HEADERS))

RM			=   rm -f

CLEAN		=   clean

all     :   $(NAME)

$(LIB)  :
	@make -C $(LIB_PATH)

$(NAME) : $(LIB) $(OBJS) $(HDR) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
	@echo "ft_ls has been successfully created."

$(DIR_O)/%.o: $(SRC_PATH)/%.c
	@mkdir -p temporary
	@$(CC) $(CFLAGS) -I $(HDR_PATH) -o $@ -c $<

clean   :
	@$(RM) $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIB_PATH)
	@echo "All .o files have been deleted."

fclean  :   clean
	@$(RM) $(NAME) $(LIB)
	@echo "ft_ls and libft.a have been deleted."

re      :   fclean all

.PHONY: all clean fclean re
