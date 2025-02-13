CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
RM = rm -rf
MSH_DIR = ../minishell
LIBFT_DIR = ../minishell/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MSH_HEADER_DIR = $(MSH_DIR)/inc
MSH_HEADER = $(MSH_HEADER_DIR)/minishell.h
MSH_INCLUDES = -I$(MSH_HEADER_DIR) -I$(LIBFT_DIR)
MSH_SRC_DIR = $(MSH_DIR)/src
MSH_SRC_FILES = main.c \
				parse/extract_tokens.c \
				parse/extract_commands.c \
				parse/command_cleanup.c \
				parse/token_validation.c \
				parse/command_list.c \
				parse/token_checks.c \
				expand/env_vars_list.c
MSH_SRC = $(addprefix $(MSH_SRC_DIR)/, $(MSH_SRC_FILES))
MSH_OBJS_DIR = minishell_objs
MSH_OBJS = $(addprefix $(MSH_OBJS_DIR)/, $(subst /,-, $(MSH_SRC_FILES:.c=.o)))
INCLUDES = $(MSH_INCLUDES)

# Default target to build the project
all: $(LIBFT_LIB) $(MSH_OBJS_DIR) $(MSH_OBJS)

clean:
	$(RM) $(MSH_OBJS) $(MSH_OBJS_DIR)
	@make clean -C $(LIBFT_DIR)

# Full clean: clean object files and the executable
fclean: clean
	$(RM) *.out

# Full rebuild: clean and build everything
re: fclean all

%.out: %.c $(LIBFT_LIB) $(MSH_OBJS)
	$(CC) $(CFLAGS) $(MSH_OBJS) $(INCLUDES) $< $(LDFLAGS) -o $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# Create the object directory for minishell objects
$(MSH_OBJS_DIR):
	mkdir -p $@

# Compilation rules for minishell object files
$(MSH_OBJS_DIR)/main.o: $(MSH_SRC_DIR)/main.c $(MSH_HEADER) | $(MSH_OBJS_DIR)
	$(CC) $(CFLAGS) $(MSH_INCLUDES) -Dmain=program_main -c $< -o $@

$(MSH_OBJS_DIR)/%.o: $(MSH_SRC_DIR)/%.c $(MSH_HEADER) | $(MSH_OBJS_DIR)
	$(CC) $(CFLAGS) $(MSH_INCLUDES) -c $< -o $@

$(MSH_OBJS_DIR)/parse-%.o: $(MSH_SRC_DIR)/parse/%.c $(MSH_HEADER) | $(MSH_OBJS_DIR)
	$(CC) $(CFLAGS) $(MSH_INCLUDES) -c $< -o $@

$(MSH_OBJS_DIR)/expand-%.o: $(MSH_SRC_DIR)/expand/%.c $(MSH_HEADER) | $(MSH_OBJS_DIR)
	$(CC) $(CFLAGS) $(MSH_INCLUDES) -c $< -o $@

.PHONY: clean fclean re all
