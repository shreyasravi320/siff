CXX      = clang++
CXXFLAGS = -g3 -Ofast -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Werror
LDFLAGS  = -g3 -Wc -fsanitize=address -fsanitize=undefined

SRC = src
INC = src/include
BIN = bin
OBJ = $(BIN)/obj

SOURCE_FILES  = siff.cpp main.cpp

OBJECT_FILES  = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

build: siff

clean:
	@echo Cleaning binaries
	@rm -rf bin
	@echo Cleaning executable
	@rm siff

siff: $(OBJECT_FILES)
	@echo Generating executable
	@$(CXX) $(LDFLAGS) -o $@ $^

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.cpp $(INC)/array.h $(INC)/%.h
	@mkdir -p $(@D)
	@echo Compiling $< to $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

