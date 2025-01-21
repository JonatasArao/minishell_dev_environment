
CC   = cc
CFLAGS  = -Wall -Wextra -Werror -g
RM   = rm -rf

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
 SHARED_LIB_EXT = dylib
 SHARED_LIB_FLAGS = -dynamiclib
else ifeq ($(UNAME_S), Linux)
 SHARED_LIB_EXT = so
 SHARED_LIB_FLAGS = -shared
endif

NAME = libmocks.$(SHARED_LIB_EXT)

HEADER_DIR = inc
HEADER = $(HEADER_DIR)/mock.h
INCLUDES = -I$(HEADER_DIR)

SRC_DIR = src
FUNC =	malloc \
		free
FUNC_FILES = $(addsuffix .c, $(addprefix mock_, $(FUNC)))
SRCS	=	$(addprefix $(SRC_DIR)/, $(FUNC_FILES))

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(FUNC_FILES:.c=.o))

all: $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SHARED_LIB_FLAGS) -o $@ $^ -ldl

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -fPIC $(INCLUDES) -c -o $@ $<

.PHONY: all clean fclean re
