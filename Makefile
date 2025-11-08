# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 16:04:15 by hgamiz-g          #+#    #+#              #
#    Updated: 2025/11/08 16:28:28 by hgamiz-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -pthread -Iincludes
SHOW_MEALS_FLAG = -DSHOW_MEALS=1
RM = rm -f

# Ensure SHOW_MEALS is always defined during compilation
CFLAGS += $(SHOW_MEALS_FLAG)

SRCDIR = SRCS
SOURCES = $(addprefix $(SRCDIR)/, philosophers.c error_checks.c philosophers_aux.c philosophers_aux2.c\
			simulation.c print_status.c sync_utils.c utils.c get_set.c\
			monitoring.c)

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "✅ $(NAME) compiled succesfully!"

%.o: %.c includes/philosophers.h
	@echo "⚙️  Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# (show_meals target removed) SHOW_MEALS is enabled by default via CFLAGS

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJECTS)

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@$(RM) $(NAME)
	@echo "✅ Full clean completed!"

re: fclean all

.PHONY: all clean fclean re

