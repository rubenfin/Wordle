CPP = c++ -std=c++17
CPPFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -fsanitize=address
SRC_DIR = src
SRC :=  $(wildcard $(SRC_DIR)/*.cpp) \

OBJS_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)
NAME = wordle
INCL_DIRS := $(shell find . -type f -name "*.hpp" -exec dirname {} + | uniq)
INCLUDE_FLAG = $(INCL_DIRS:%=-I%)

.PHONY: all clean fclean re
all: $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf $(LOG_DIR)
	@echo "$(YELLOW)Removed all objects!$(DEFAULT)"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
	@echo "$(RED)Removed executables!$(DEFAULT)"

re:
	$(MAKE) fclean
	$(MAKE) all

$(NAME): $(OBJS_DIR) $(OBJ)
	$(CPP) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(GREEN)Compiled wordle!$(DEFAULT)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_FLAG)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m