# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/09 17:05:50 by mhwangbo          #+#    #+#              #
#    Updated: 2018/05/23 22:38:31 by mhwangbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ls_main.c

OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs
LIBDIR = lib/libft

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
LIBS = $(LIBDIR)/libftprintf.a
HEADER = -I includes -I $(LIBDIR)

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -I includes -I $(LIBDIR)/includes $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS) $(LIBS) -o $@

clean:
	@/bin/rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@rm -f $(LIBDIR)/libftprintf.a

re: fclean all
