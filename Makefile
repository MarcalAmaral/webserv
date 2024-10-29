NAME = webserv

CXX = c++
CXXFLAGS = -g -Wall -Werror -Wextra -std=c++98

BUILD = build

SRC_PATH = src src/Master src/utils src/master/parser src/logger

SOURCE += $(foreach path, $(SRC_PATH), $(wildcard $(addprefix $(path)/, *.cpp)))

OBJECT = $(SOURCE:%.cpp=$(BUILD)/%.o)

INCLUDE = -I./src -I./include

MACRO = $(MACROS)

define makedir
	@mkdir -p $(dir $@)
endef

define compile_objects
	$(CXX) -c $(CXXFLAGS) $(MACRO) $(INCLUDE) -o $@ $<
endef

define compile_executable
	$(CXX) $(CXXFLAGS) $(MACRO) $(INCLUDE) -o $@ $^
endef

define clean_objects
	@rm -rf $(BUILD)
endef

define clean_executable
	@rm -f $(NAME)
endef

all: $(NAME)

$(NAME): $(OBJECT)
	$(call compile_executable)

$(BUILD)/%.o: %.cpp
	$(call makedir)
	$(call compile_objects)

clean:
	$(call clean_objects)

fclean: clean
	$(call clean_executable)

re: fclean all

debug: $(NAME_DEBUG)

.PHONY: all clean fclean re Makefile
.DEFAULT_GOAL: all