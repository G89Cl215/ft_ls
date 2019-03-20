# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 22:11:12 by tgouedar          #+#    #+#              #
#    Updated: 2019/03/20 00:20:59 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRCFILE	= ft_flstadd.c\
		  ft_flstadd_back.c\
		  ft_reclistadd.c\
		  ft_newdir_nod.c\
		  ft_lstnew.c\
		  ft_lstfree.c\
		  ft_lstfreeone.c\
		  ft_free_reclist.c\
		  ft_relink.c\
		  ft_revrelink.c\
		  parse_sort.c\
		  ft_recmerge_sort.c\
		  ft_fmerge_sort.c\
		  ft_ascii_cmp.c\
		  ft_time_cmp.c\

SRCDIR	= ./
SRC		= $(addprefix $(SRCDIR),$(SRCFILE))
HDR 	= .
OBJFILE	= $(SRCFILE:.c=.o)
OBJDIR	= obj
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))

NAME 	= list_lib.a

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "Your list_lib.a is ready"

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $^ -I $(HDR)
	@echo " \t \t \t \t \t \t \t \t [OK]  \r $^  \r "


$(OBJDIR) :
	@/bin/mkdir $(OBJDIR)

clean :
	@/bin/rm $(OBJ) 2>/dev/null || true
	@/bin/rm -R $(OBJDIR) 2>/dev/null || true

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all
