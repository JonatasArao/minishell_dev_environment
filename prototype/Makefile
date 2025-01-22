CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
LIBFT_DIR = ../minishell/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

%.out: %.c $(LIBFT_LIB) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) $< $(LDFLAGS) -o $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)
