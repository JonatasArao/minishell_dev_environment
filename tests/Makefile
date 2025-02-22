# Executable name
NAME = minishell_tests

# Compiler and compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MOCK_DIR) -lmocks -lreadline

# Command to remove files
RM = rm -rf

# Directories and files for the minishell project
MSH_DIR = ../minishell
LIBFT_DIR = $(MSH_DIR)/libft
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
				expand/env_vars_list.c \
				expand/envp_manager.c \
				expand/extract_vars.c \
				expand/expand_token.c \
				expand/expand_commands.c
MSH_SRC = $(addprefix $(MSH_SRC_DIR)/, $(MSH_SRC_FILES))
MSH_OBJS_DIR = minishell_objs
MSH_OBJS = $(addprefix $(MSH_OBJS_DIR)/, $(subst /,-, $(MSH_SRC_FILES:.c=.o)))

# Determine the shared library extension and flags based on the operating system
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
 SHARED_LIB_EXT = dylib
 SHARED_LIB_FLAGS = -dynamiclib
 LIBRARY_PATH_VAR = DYLD_LIBRARY_PATH
else ifeq ($(UNAME_S), Linux)
 SHARED_LIB_EXT = so
 SHARED_LIB_FLAGS = -shared
 LIBRARY_PATH_VAR = LD_LIBRARY_PATH
endif
MOCK_DIR = ../mocks
MOCK_LIB = $(MOCK_DIR)/libmocks.$(SHARED_LIB_EXT)
MOCK_HEADER_DIR = $(MOCK_DIR)/inc

# Directories and files for the tests
HEADER_DIR = inc
HEADER = $(HEADER_DIR)/minishell_tests.h
INCLUDES = $(MSH_INCLUDES) -I$(HEADER_DIR) -I$(MOCK_HEADER_DIR)
SRC_DIR = src
SRC_FILES = main.c \
			parse/extract_tokens/test_get_token_end.c \
			parse/extract_tokens/test_get_next_token.c \
			parse/extract_tokens/test_extract_tokens.c \
			parse/token_checks/test_is_heredoc.c \
			parse/token_checks/test_is_input_redirection.c \
			parse/token_checks/test_is_output_redirection.c \
			parse/token_checks/test_is_redirection.c \
			parse/token_checks/test_is_pipe.c \
			parse/token_validation/test_is_valid_quotes.c \
			parse/token_validation/test_is_token_list_valid.c \
			parse/command_cleanup/test_free_redirection.c \
			parse/command_cleanup/test_free_command.c \
			parse/command_list/test_lstadd_str.c \
			parse/command_list/test_lstadd_redir.c \
			parse/extract_commands/test_alloc_command.c \
			parse/extract_commands/test_parse_tokens.c \
			parse/extract_commands/test_extract_commands.c \
			expand/env_vars_list/test_free_env_var.c \
			expand/env_vars_list/test_lstadd_env_var.c \
			expand/env_vars_list/test_get_env_var.c \
			expand/env_vars_list/test_lstset_env_var.c \
			expand/env_vars_list/test_lstrm_env_var.c \
			expand/envp_manager/test_create_env_string.c \
			expand/envp_manager/test_get_envp.c \
			expand/envp_manager/test_extract_env_vars.c \
			expand/extract_vars/test_get_var_end.c \
			expand/extract_vars/test_get_next_var.c \
			expand/extract_vars/test_extract_vars.c \
			expand/expand_token/test_get_var_value.c \
			expand/expand_token/test_concat_vars.c \
			expand/expand_token/test_expand_quotes.c \
			expand/expand_token/test_expand_var.c \
			expand/expand_token/test_expand_token.c \
			expand/expand_commands/test_is_ambiguous_redirect.c \
			expand/expand_commands/test_expand_redir.c \
			expand/expand_commands/test_expand_arguments.c \
			expand/expand_commands/test_expand_commands.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(subst /,-, $(SRC_FILES:.c=.o)))

# Default target: build the executable
all: $(NAME)

# Run the tests
run: all
	@$(LIBRARY_PATH_VAR)=$(MOCK_DIR) ./$(NAME)

# Clean object files
clean:
	$(RM) $(MSH_OBJS) $(MSH_OBJS_DIR) $(OBJS) $(OBJS_DIR)
	@make clean -C $(MOCK_DIR)
	@make clean -C $(LIBFT_DIR)

# Full clean: clean object files and the executable
fclean: clean
	$(RM) $(NAME) $(MOCK_LIB) $(LIBFT_LIB)

# Full rebuild: clean and build everything
re: fclean all

# Create the executable
$(NAME): $(LIBFT_LIB) $(MOCK_LIB) $(MSH_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(MSH_OBJS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Build the libft library
$(LIBFT_LIB):
	@make debug -C $(LIBFT_DIR)

# Build the mocks library
$(MOCK_LIB):
	@make -C $(MOCK_DIR)

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

# Create the object directory for test objects
$(OBJS_DIR):
	mkdir -p $@

# Compilation rules for test object files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-extract_tokens-%.o: $(SRC_DIR)/parse/extract_tokens/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-token_checks-%.o: $(SRC_DIR)/parse/token_checks/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-token_validation-%.o: $(SRC_DIR)/parse/token_validation/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-command_cleanup-%.o: $(SRC_DIR)/parse/command_cleanup/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-command_list-%.o: $(SRC_DIR)/parse/command_list/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-extract_commands-%.o: $(SRC_DIR)/parse/extract_commands/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/expand-env_vars_list-%.o: $(SRC_DIR)/expand/env_vars_list/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/expand-envp_manager-%.o: $(SRC_DIR)/expand/envp_manager/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/expand-extract_vars-%.o: $(SRC_DIR)/expand/extract_vars/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/expand-expand_token-%.o: $(SRC_DIR)/expand/expand_token/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/expand-expand_commands-%.o: $(SRC_DIR)/expand/expand_commands/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# Targets that do not correspond to files
.PHONY: all clean fclean re
