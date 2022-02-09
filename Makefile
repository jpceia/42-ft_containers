# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 19:07:05 by jceia             #+#    #+#              #
#    Updated: 2022/02/09 01:38:19 by jpceia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = ft_containers

INC_DIR     = headers
SRC_DIR		= src
TEST_DIR    = tests
BIN_DIR     = bin
LOG_DIR		= logs

TEST_SRCS	= $(shell (find $(TEST_DIR) -name "*.cpp" -type f | sort -z ))
TEST_BINS	= $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BIN_DIR)/%)

SRCS		= $(shell (find $(SRC_DIR) -name "*.cpp" -type f | sort -z ))
BINS		= $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)

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

FT_CXXFLAGS = $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) -std=c++98 -fsanitize=address
STD_CXXFLAGS= $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) -std=c++11 -DUSE_STL

all: $(NAME)

$(NAME): $(BINS)

test:	$(TEST_BINS)

# Building - Tests
$(BIN_DIR)/%:    $(TEST_DIR)/%.cpp
	$(eval FNAME=$(shell basename $@))
	@mkdir -p $(dir $@)
	@mkdir -p $(LOG_DIR)
	@($(CXX) $(FT_CXXFLAGS) $< -o $@_ft  && \
		$(CXX) $(STD_CXXFLAGS) $< -o $@_std ) && \
		((./$@_ft > $(LOG_DIR)/$(FNAME)_ft.log && \
		 ./$@_std > $(LOG_DIR)/$(FNAME)_std.log) && \
		(diff $(LOG_DIR)/$(FNAME)_ft.log $(LOG_DIR)/$(FNAME)_std.log && \
			printf "$(BWHITE)$(FNAME)$(RESET)\t$(BGREEN)OK$(RESET)\n" || \
			printf "$(BWHITE)$(FNAME)$(RESET)\t$(BRED)FAIL$(RESET)\n") || \
		printf "$(BWHITE)$(FNAME)$(RESET) $(BRED)runtime error${RESET}\n") || \
		printf "$(BWHITE)$(FNAME)$(RESET) $(BRED)compilation error${RESET}\n"

# Building - Sources
$(BIN_DIR)/%:	$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(FT_CXXFLAGS) $< -o $@

# Cleaning
clean:
	$(RM) -rf $(LOG_DIR)

fclean: clean
	$(RM) -rf $(BIN_DIR)

# Rebuild
re: fclean all

FORCE:

.PHONY:     all clean fclean re
