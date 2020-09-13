SRC_DIR := src
OBJ_DIR := obj
HEADER_DIR := src/headers
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CCOMPILER := g++
CPPFLAGS := -Wall -Werror -std=c++14 -O

azul: $(OBJ_FILES)
	$(CCOMPILER) -I $(HEADER_DIR) $(CPPFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CCOMPILER) -I $(HEADER_DIR) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJ_FILES) *.o azul