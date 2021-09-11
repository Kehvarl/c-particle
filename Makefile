SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/particles
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Generate header dependencies automatically
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS := -g -Wall

# Out output file isn't named all, so we need a PHONY declaration
.PHONY: all clean

# Build output file
all : $(EXE)

# Link out Object files and output an executable (Create BIN dir if needed)
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ -o $@

# Compile our src files into intermediate Objects  (Create OBJ dir if needed)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Make sure out output directoies exist for OBJ and BIN
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up anything we've had to build
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

# Handle automatic dependency generation
-include $(OB:.o=.d)