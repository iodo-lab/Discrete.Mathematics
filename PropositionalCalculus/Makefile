INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CC = g++
CFLAGS = -Wall -std=c++14 -I$(INC_DIR)
LFLAGS = -Wall -lm -I$(INC_DIR)
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.hpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


TARGET = pcalculus

all: makeDirs $(TARGET)
 
makeDirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)	

$(TARGET): $(OBJS)     	
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJS)
	
$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(LFLAGS) -c $< -o $@
	@echo 'Compiled '$<' successfully' 
clean :
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	@echo 'Clean successfully'


