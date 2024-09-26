# Project name
NAME := webserv

# Compiler and flags
CXX := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98

# Directories
BUILD := build

# Source files
SOURCE := $(shell find ./ -type f -name "*.cpp")
SOURCE += $(shell find ./ -type f -name "Server/*.cpp")

# Object files
OBJECTS := $(patsubst ./%,$(BUILD)/%,$(SOURCE:.cpp=.o))

# Includes
INCLUDES := -I./

define compile_source
        $(CXX) -c $(CXXFLAGS) $(INCLUDES) -o $@ $<
endef

define create_dir
        @mkdir -p $(dir $@)
endef

define compile_executable
        $(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^
endef

define clean_objs
        rm -rf $(BUILD)
endef

define clean_executable
        rm -f $(NAME)
endef

all: $(NAME)

$(NAME): $(OBJECTS)
        $(call compile_executable)

$(BUILD)/%.o: %.cpp
        $(call create_dir)
        $(call compile_source)

clean:
        $(call clean_objs)

fclean: clean
        $(call clean_executable)

re: fclean all

.PHONY: all clean fclean re Makefile
.DEFAULT_GOAL = all