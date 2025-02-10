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
				parse/token_checks.c
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
			parse/test_get_token_end.c \
			parse/test_get_next_token.c \
			parse/test_is_valid_quotes.c \
			parse/test_extract_tokens.c \
			parse/test_is_redirection.c \
			parse/test_is_pipe.c \
			parse/test_is_token_list_valid.c \
			parse/test_free_redirection.c \
			parse/test_free_command.c
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

# Create the object directory for test objects
$(OBJS_DIR):
	mkdir -p $@

# Compilation rules for test object files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/parse-%.o: $(SRC_DIR)/parse/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Targets that do not correspond to files
.PHONY: all clean fclean re
