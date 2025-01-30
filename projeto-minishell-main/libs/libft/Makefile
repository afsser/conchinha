# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 19:06:53 by lilmende          #+#    #+#              #
#    Updated: 2024/11/05 23:58:59 by lilmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADERS = ./

CC = cc
FLAGS = -Wextra -Wall -Werror
AR = ar rcs
RM = rm -f

SRC = ./src/ft_memset.c \
		./src/ft_bzero.c \
		./src/ft_memcpy.c \
		./src/ft_memmove.c \
		./src/ft_memchar.c \
		./src/ft_memcmp.c \
		./src/ft_strlen.c \
		./src/ft_strlcpy.c \
		./src/ft_strlcat.c \
		./src/ft_strdup.c \
		./src/ft_calloc.c \
		./src/ft_isalpha.c \
		./src/ft_isdigit.c \
		./src/ft_isalnum.c \
		./src/ft_isascii.c \
		./src/ft_isprint.c \
		./src/ft_putchar_fd.c \
		./src/ft_putstr_fd.c \
		./src/ft_putendl_fd.c \
		./src/ft_toupper.c \
		./src/ft_putnbr_fd.c \
		./src/ft_tolower.c \
		./src/ft_strchr.c \
		./src/ft_strrchr.c \
		./src/ft_strncmp.c \
		./src/ft_strnstr.c \
		./src/ft_atoi.c \
		./src/ft_substr.c \
		./src/ft_itoa.c \
		./src/ft_strjoin.c \
		./src/ft_strtrim.c \
		./src/ft_striteri.c \
		./src/ft_split.c \
		./src/ft_strmapi.c \
		./src/ft_lstnew.c \
		./src/ft_lstadd_front.c \
		./src/ft_lstadd_back.c \
		./src/ft_lstsize.c \
		./src/ft_lstlast.c \
		./src/ft_lstdelone.c \
		./src/ft_lstclear.c \
		./src/ft_lstiter.c \
		./src/ft_lstmap.c \
		./src/ft_abs.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		./ft_printf/ft_printf.c \
		./ft_printf/ft_printf_utils.c \
		./ft_printf/ft_printf_utils_2.c \
		./src/ft_atol.c \
		./src/ft_isspace.c \
		./src/ft_free_split.c \
		./src/ft_strcmp.c \

OBJS = ${SRC:%.c=%.o}

all: $(NAME)
	@echo "${YELLOW}Libft Compiled."
	
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ -I $(HEADERS)
	@ar rcs ${NAME} $@

$(NAME): $(OBJS)
	@echo "${YELLOW}Compiling Libft files..."
	
clean:
	@if ls $(OBJS) 1> /dev/null 2>&1; then \
		echo "${RED}Deleting objects...${RESET}"; \
		$(RM) $(OBJS); \
		echo "${YELLOW}Done."; \
	else \
		echo "${YELLOW}No objects to delete."; \
	fi

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}Libft.a removed."
	
re: fclean all

RED     = \033[2;31m
GREEN   = \033[0;32m
BGREEN  = \033[0;41m
YELLOW  = \033[2;33m
BLUE    = \033[2;34m
MAGEN   = \033[0;35m
CYAN    = \033[1;36m
RESET   = \033[0m

.PHONY: all, clean, fclean, re