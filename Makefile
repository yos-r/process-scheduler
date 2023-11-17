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
# $(MAIN): main.c
# 	$(CC) $(CFLAGS) main.c -o $(MAIN) -ldl


#make run that acknowledges gtk
# gcc -Wno-format -o main main.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
$(MAIN): main.c
	$(CC) -Wno-format $(CFLAGS) main.c -o $(MAIN) -ldl -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

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
#copy the prototype file into usr/local/lib
	sudo cp prototype.glade /usr/local/lib/
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	./$(MAIN)

install: $(LIB_DIR) main
# install the main executable
	sudo install main $(INSTALL_DIR)
#create algos/ inside usr/local/lib if it doesn't exist
# sudo mkdir -p $(LIB_DIR)
# install dynamic libraries from algos/
	sudo install algos/*.so $(LIB_DIR)/
	sudo apt-get update
	sudo apt-get install libgtk-3-0
	sudo apt-get install libgtk-3-dev
	sudo apt-get install pkg-config
# sudo install prototype.glade $(LIB_DIR)

# rule to clean up the generated files
clean:
	rm -f $(LIB_FILES) $(MAIN)

uninstall:
# remove the main executable
	sudo rm $(INSTALL_DIR)/main
# remove dynamic libraries from algos/
	sudo rm -rf $(LIB_DIR)
# remove glade file
	sudo rm -f /usr/local/lib/prototype.glade

# .DEFAULT_GOAL := main