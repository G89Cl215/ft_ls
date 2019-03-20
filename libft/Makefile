# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 22:11:12 by tgouedar          #+#    #+#              #
#    Updated: 2019/03/20 00:21:20 by tgouedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRCFILE	= ft_swap.c\
		  ft_btw.c\
		  ft_bzero.c\
		  ft_memset.c\
		  ft_memcpy.c\
		  ft_memccpy.c\
		  ft_memmove.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_strlen.c\
		  ft_strdup.c\
		  ft_strndup.c\
		  ft_strcpy.c\
		  ft_strncpy.c\
		  ft_strcat.c\
		  ft_strncat.c\
		  ft_strlcat.c\
		  ft_strchr.c\
		  ft_strrchr.c\
		  ft_strstr.c\
		  ft_strnstr.c\
		  ft_strspn.c\
		  ft_strcspn.c\
		  ft_strcmp.c\
		  ft_strncmp.c\
		  ft_atoi.c\
		  ft_unsigned_itoa_base.c\
		  ft_itoa.c\
		  ft_pow.c\
		  ft_isalpha.c\
		  ft_islower.c\
		  ft_isdigit.c\
		  ft_isalnum.c\
		  ft_isascii.c\
		  ft_isprint.c\
		  ft_isin.c\
		  ft_indice.c\
		  ft_toupper.c\
		  ft_tolower.c\
		  ft_memalloc.c\
		  ft_memdel.c\
		  ft_strnew.c\
		  ft_strdel.c\
		  ft_strclr.c\
		  ft_striter.c\
		  ft_striteri.c\
		  ft_strmap.c\
		  ft_strmapi.c\
		  ft_strequ.c\
		  ft_strnequ.c\
		  ft_strsub.c\
		  ft_strjoin.c\
		  ft_strappend.c\
		  ft_strappend_back.c\
		  ft_strtrim.c\
		  ft_strrev.c\
		  ft_strupper.c\
		  ft_strsplit.c\
		  ft_putchar.c\
		  ft_putchar_fd.c\
		  ft_putstr.c\
		  ft_putstr_fd.c\
		  ft_putlpadstr.c\
		  ft_putrpadstr.c\
		  ft_putendl.c\
		  ft_print_nods.c\
		  ft_putendl_fd.c\
		  ft_putnbr.c\
		  ft_putnbr_fd.c\
		  ft_putnbr_base.c\
		  ft_lstadd.c\
		  ft_lstdel.c\
		  ft_lstdelone.c\
		  ft_lstfree.c\
		  ft_lstfreeone.c\
		  ft_lstnew.c\
		  ft_lstmap.c\
		  ft_lstiter.c\
		  ft_integer_len.c\
		  ft_lstadd_back.c\
		  get_next_line.c\
		  option.c\
		  match.c

FTPRINTF =	conv_char_printf.c\
			conv_float1_printf.c\
			conv_float2_printf.c\
			conv_int_printf.c\
			conv_ubase_printf.c\
			conv_unicode_printf.c\
			crisis_room.c\
			display_result.c\
			extract_from_pattern.c\
			float_conv_tools.c\
			ft_printf.c\
			gestion_t_pattern.c\
			padding_flags.c\
			padding_floats.c\
			padding_negativ.c\
			padding_positiv.c\
			padding_positiv2.c\
			padding_prec.c\
			padding_prefix.c\
			padding_prefix2.c\
			padding_spaces.c\
			padding_types.c\
			padding_zero.c\
			padding_zero2.c\
			parsing_conv.c\
			parsing_extract_pattern.c\
			parsing_pattern_detect.c\
			parsing_pos1.c\
			parsing_pos2.c

SRCDIR	= ./
SRC		= $(addprefix $(SRCDIR),$(SRCFILE))
HDR 	= .
OBJFILE	= $(SRCFILE:.c=.o)
OBJDIR	= obj
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))

FTPRINTFPATH	=	./ft_printf
FTPRINTF_C		=	$(addprefix $(FTPRINTFPATH)/,$(FTPRINTF))
FTPRINTF_O		=	$(FTPRINTF:.c=.o)
FTPRINTF_DEP	=	$(addprefix $(FTPRINTFPATH)/,$(FTPRINTF_O))

NAME 	= libft.a

.PHONY: all re clean fclean obj_process printf_process

all : $(NAME)

$(NAME) : $(OBJ) $(FTPRINTF_DEP) Makefile
	@ar rc $(NAME) $(OBJ) $(FTPRINTF_DEP)
	@echo "Your LIBFT is ready for use."

$(FTPRINTFPATH)/%.o : $(FTPRINTFPATH)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $^
	@echo " \t \t \t \t \t \t \t \t [OK]  \r $^  \r "

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $^ -I $(HDR)
	@echo " \t \t \t \t \t \t \t \t [OK]  \r $^  \r "

$(OBJDIR) :
	@/bin/mkdir $(OBJDIR)

clean :
	@/bin/rm $(OBJ) 2>/dev/null || true
	@/bin/rm $(FTPRINTF_DEP) 2>/dev/null || true
	@/bin/rm -R $(OBJDIR) 2>/dev/null || true

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all
