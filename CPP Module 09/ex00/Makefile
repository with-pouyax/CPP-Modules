# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: student <student@42.fr>                    +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/01/01 00:00:00 by student          #+#    #+#             #
#    Updated: 2024/01/01 00:00:00 by student         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCDIR = src
INCDIR = include
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/BitcoinExchange.cpp $(SRCDIR)/Date.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re 