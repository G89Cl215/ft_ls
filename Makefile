# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baavril <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 10:37:50 by baavril           #+#    #+#              #
#    Updated: 2019/03/20 00:21:18 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

NAME		=	ft_ls

LIB_PATH	=	libft
LIB			=	libft.a

LIB_LIST_PTH=	list_lib
LIB_LIST	=	list_lib.a

LIBS 		=	 $(addprefix $(LIB_PATH)/,$(LIB)) \
				 $(addprefix $(LIB_LIST_PTH)/,$(LIB_LIST))

DIR_O		=   obj

SRC_PATH	=	.
SOURCES 	=	ft_ls.c \
				recursive_call.c \
				get_padding_size.c \
				parsing.c \
				parse_display.c\
				display.c \
				display_tools.c \
				extract_data.c \
				ft_long_display.c \
				read_and_stock_ls.c \
				sort.c \

SRCS    	=   $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS    	=   $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))


HDR			=	libft/option.h \
				libft/libft.h \
				list_lib/ls_list.h \
				ft_ls.h

HDR_FLAG	=	-I libft \
				-I list_lib

RM			=   rm -f

CLEAN		=   clean

all : $(NAME)

lib_msg :
	@echo "Compiling Libft"

$(LIB_PATH)/$(LIB) :
	@echo "Compiling Libft"
	@make -C $(LIB_PATH)

lis_msg :
	@echo "Compiling List Library"

$(LIB_LIST_PTH)/$(LIB_LIST) : 
	@echo "Compiling List Library"
	@make -C $(LIB_LIST_PTH)

$(NAME) : $(LIBS) $(OBJS) $(HDR) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(HDR_FLAG)
	@echo "ft_ls has been successfully created."

$(DIR_O) :
	@mkdir -p $(DIR_O)

$(DIR_O)/%.o : $(SRC_PATH)/%.c | $(DIR_O)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HDR_FLAG)
	@echo " \t \t \t \t \t \t \t \t [OK]  \r $^  \r "

clean :
	@$(RM) $(OBJS)
	@rm -Rf $(DIR_O)
	@make clean -C $(LIB_PATH)
	@make clean -C $(LIB_LIST_PTH)
	@echo "All .o files have been deleted."

fclean :   clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(LIB_LIST_PTH)
	@echo "ft_ls and libft.a have been deleted."

re  :   fclean all

.PHONY: all clean fclean re lib_msg lis_msg
