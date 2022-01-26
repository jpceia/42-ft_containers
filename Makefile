# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 19:07:05 by jceia             #+#    #+#              #
#    Updated: 2022/01/26 10:45:17 by jpceia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = ft_containers

INC_DIR     = headers
SRC_DIR     = tests
BIN_DIR     = bin
LOG_DIR		= logs

SRCS        = $(shell find $(SRC_DIR) -name "*.cpp" -type f)
BINS        = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

CXX          = clang++
RM           = rm -f

BRED		= \033[1;31m
BGREEN		= \033[1;32m
BWHITE		= \033[1;37m
RESET		= \033[0m


OS          = $(shell uname)

FLAGS_WARN  = -Wall -Werror -Wextra -pedantic-errors
FLAGS_INC   = -I$(INC_DIR)
FLAGS_DEBUG = -g -fsanitize=address -DDEBUG
FLAGS_OPT   = -O3

CXXFLAGS    = $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) -std=c++98

# Building
$(BIN_DIR)/%:    $(SRC_DIR)/%.cpp
	$(eval FNAME=$(shell basename $@))
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $< -o $@_ft
	@$(CXX) $(CXXFLAGS) -DUSE_STL $< -o $@_std
	@mkdir -p $(LOG_DIR)
	@./$@_ft > $(BIN_DIR)/$(FNAME)_ft.log
	@./$@_std > $(BIN_DIR)/$(FNAME)_std.log
	@echo
	@diff $(BIN_DIR)/$(FNAME)_ft.log $(BIN_DIR)/$(FNAME)_std.log && printf "${BWHITE}${FNAME}${RESET}\t${BGREEN}OK${RESET}\n" || printf "${BWHITE}${FNAME}${RESET}\t${BRED}FAIL${RESET}\n" 

$(NAME): $(BINS)

all: $(NAME)

# Cleaning
clean:
	$(RM) -rf $(LOG_DIR)

fclean: clean
	$(RM) -rf $(BIN_DIR)

# Rebuild
re: fclean all

.PHONY:     all clean fclean re
