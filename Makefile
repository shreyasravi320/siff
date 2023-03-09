SRC = src
INC = $(SRC)/include
BIN = bin

CXX      = clang++
CXXFLAGS = -g3 -Ofast -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Werror
LDFLAGS  = -g3 -Wc
#  -fsanitize=address -fsanitize=undefined
IFLAGS = -I$(INC)


INCLUDES = $(shell echo $(INC)/*.h)
SOURCES = $(shell echo $(SRC)/*.cpp)

OBJECTS = $(SOURCES:$(SRC)/%.cpp=$(BIN)/%.o)

build: siff

clean:
	@echo Cleaning binaries
	@rm -rf bin
	@echo Cleaning executable
	@rm siff

siff: $(OBJECTS)
	@echo Generating executable
	@$(CXX) $(LDFLAGS) -o $@ $^

$(OBJECTS): $(BIN)/%.o: $(SRC)/%.cpp $(INCLUDES)
	@mkdir -p $(@D)
	@echo Compiling $< to $@
	@$(CXX) $(CXXFLAGS) -c $< -o $@
