# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baavril <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 10:37:50 by baavril           #+#    #+#              #
#    Updated: 2019/03/13 21:45:53 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-g3 -Wall -Werror -Wextra

NAME		=	ft_ls

LIB_PATH	=	libft
LIB			=	libft.a

LIB_LIST_PTH=	list_lib
LIB_LIST	=	list_lib.a

LIBS 		=	 $(LIB_LIST_PTH)/$(LIB_LIST) $(LIB_PATH)/$(LIB)

DIR_O		=   temporary

SRC_PATH	=	.
SOURCES 	=	ft_ls.c \
				recursive_call.c \
				get_padding_size.c \
				parsing.c \
				parse_display.c\
				display.c \
				extract_data.c \
				ft_long_display.c \
				read_and_stock_ls.c \
				sort.c \

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

$(LIB_LIST)  :
	@make -C $(LIB_LIST_PTH)

$(NAME) : $(LIB) $(LIB_LIST) $(OBJS) $(HDR) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "ft_ls has been successfully created."

$(DIR_O)/%.o: $(SRC_PATH)/%.c
	@mkdir -p temporary
	@$(CC) $(CFLAGS) -I $(HDR_PATH) -o $@ -c $<

clean   :
	@$(RM) $(OBJS)
	@rm -Rf $(DIR_O)
	@make clean -C $(LIB_PATH)
	@make clean -C $(LIB_LIST_PTH)
	@echo "All .o files have been deleted."

fclean  :   clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(LIB_LIST_PTH)
	@echo "ft_ls and libft.a have been deleted."

re      :   fclean all

.PHONY: all clean fclean re
