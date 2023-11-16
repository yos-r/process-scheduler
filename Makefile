# Define the  directory w/ shared libs
SRC_DIR = algos

# Get a list of all C source files in the source directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Generate a list of corresponding dynamic library files
LIB_FILES = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(SRC_FILES))

$(LIB_FILES): $(SRC_FILES)
	$(foreach file,$(SRC_FILES), \
    	$(CC) -shared -fPIC $(file) -o $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(file)); \
	)


MAIN = main
$(MAIN): main.c
	$(CC) main.c -o $(MAIN)

# Rule to run the main program
run: $(MAIN)
	./$(MAIN)

# Rule to clean up the generated files
clean:
	rm -f $(LIB_FILES) $(MAIN)