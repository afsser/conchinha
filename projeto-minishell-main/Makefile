NAME = minishell
FLAGS = -Wextra -Wall -Werror -g3
LIBFT = ./libs/libft
HEADERS = ./includes/
BIN= ./bin/
SRC_D= ./src/
CC = cc
LIBS = $(LIBFT)/libft.a -lreadline

SRC= minishell.c \
	 tokenizer/tokenizer.c \
	 tokenizer/token_list.c \
	 tokenizer/token_status_1.c \
	 tokenizer/token_status_2.c \
	 tokenizer/token_validation.c \
	 parser/parser.c \
	 parser/parser_utils.c \
	 parser/get_env.c \
	 parser/expansion.c \
	 parser/expansion_utils.c \
	 parser/expansion_process.c \
	 parser/expansion_quotes.c \
	 parser/pre_parser.c \
	 ast/binary_tree.c \
	 ast/binary_tree_utils.c \
	 ast/tree_printer.c \
	 utils/mini_utils.c \
	 utils/checkers.c \
	 utils/cleaners.c \
	 utils/tools.c \
	 utils/signals.c \
	 builtin/cd.c \
	 builtin/echo.c \
	 builtin/pwd.c \
	 builtin/export.c \
	 builtin/export_utils.c \
	 builtin/unset.c \
	 builtin/env.c \
	 builtin/exit.c \
	 builtin/builtin_utils.c \
	 execution/execution.c \
	 execution/exec_path.c \
	 execution/exec_utils.c \
	 execution/redirects.c \
	 execution/heredoc.c \
	 execution/heredoc_aux.c \
	 execution/heredoc_utils.c \
	 execution/heredoc_history.c \
	 execution/fds.c \
	 debug.c \

SRC:= $(addprefix $(SRC_D),$(SRC))

INCLUDES= -I includes -I $(LIBFT)/ -I $(LIBFT)/ft_printf/includes -I $(LIBFT)/gnl/includes
OBJS= $(patsubst $(SRC)%.c, $(BIN)%.o, $(SRC))

RED     = \033[2;31m
GREEN   = \033[0;32m
BGREEN  = \033[0;41m
YELLOW  = \033[2;33m
BLUE    = \033[2;34m
MAGEN   = \033[0;35m
CYAN    = \033[1;36m
RESET   = \033[0m

all: libft $(NAME)
	@echo "${YELLOW}    --    Compiled Program >>> ${GREEN}./$(NAME)${YELLOW}    --${RESET}"

libft:
	@make -C $(LIBFT)/ --no-print-directory

$(BIN)%.o: $(SRC_D)%.c
	@mkdir -p $(BIN)
	@$(CC) $(FLAGS) -o $@ -c $< && echo "${YELLOW}Compiling:${RESET} $(notdir $<)"

$(NAME): $(OBJS)
	@echo " "
	@echo "Creating file $(NAME) ..."
	@echo " "
	@$(CC) $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBS)

clean:
	@make clean -C $(LIBFT)/ --no-print-directory
	@if ls $(BIN) 1> /dev/null 2>&1; then \
	echo "${RED}Deleting objects...${RESET}"; \
		rm -rf $(BIN); \
		echo "${YELLOW}Done."; \
	else \
		echo "${YELLOW}No objects to delete."; \
	fi \

fclean: clean
	@make fclean -C $(LIBFT)/ --no-print-directory
	@echo "${RED}Removing executable..."
	@rm -rf $(NAME)
	@echo " "
	@echo " ${RED}    --    Program Removed ✔️    --${RESET}"
	@echo " "

gdb:	all
	gdb --tui -ex 'set follow-fork-mode child' -ex 'b main' -ex 'b m_get_new_token' -ex 'run' ./$(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft
