#works for both local and installed versions!

SRC_DIR = algos

#flags are so important!! 
CFLAGS = -I.
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

LIB_FILES = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(SRC_FILES))

$(LIB_FILES): $(SRC_FILES)
	$(foreach file,$(SRC_FILES), \
    	$(CC) -shared -fPIC $(CFLAGS) $(file) -o $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(file)); \
	)

MAIN = main
$(MAIN): main.c
	$(CC) $(CFLAGS) main.c -o $(MAIN) -ldl

INSTALL_DIR = /usr/local/bin
LIB_DIR = /usr/local/lib/algos

libs: $(LIB_FILES)

#v2. building the .so w/ header file misc.h
$(LIB_DIR)/%.so: $(SRC_DIR)/%.c
	$(CC) -shared -fPIC $(CFLAGS) $< -o $@


# rule to create the dest directory if it doesn't exist
$(LIB_DIR):
	sudo mkdir -p $(LIB_DIR)

# rule for running main
run: $(MAIN)
	sudo mkdir -p $(LIB_DIR)
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	./$(MAIN)

install: $(LIB_DIR) main
# install the main executable
	sudo install main $(INSTALL_DIR)
#create algos/ inside usr/local/lib if it doesn't exist
# sudo mkdir -p $(LIB_DIR)
# install dynamic libraries from algos/
	sudo install algos/*.so $(LIB_DIR)/

# rule to clean up the generated files
clean:
	rm -f $(LIB_FILES) $(MAIN)

uninstall:
# remove the main executable
	sudo rm $(INSTALL_DIR)/main
# remove dynamic libraries from algos/
	sudo rm -rf $(LIB_DIR)

# .DEFAULT_GOAL := main