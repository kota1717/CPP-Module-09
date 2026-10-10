TARGET := PmergeMe

CXX := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98
RMDIR := rm -rf

OBJ_DIR := obj

SRCS := main.cpp \
				PmergeMe.cpp

OBJS := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RMDIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=reachable --track-origins=yes ./$(TARGET)

re: fclean all

.PHONY: all clean fclean re valgrind
