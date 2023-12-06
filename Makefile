SRC_DIR = algos
CFLAGS = -I.
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

LIB_FILES = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(SRC_FILES))

$(LIB_FILES): $(SRC_FILES)
	$(foreach file,$(SRC_FILES), \
    	$(CC) -shared -fPIC $(CFLAGS) $(file) -o $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.so,$(file)); \
	)

MAIN = process-scheduler

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
	sudo cp prototype.glade /usr/local/lib/
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	./$(MAIN)

install: 
# $(LIB_DIR) main
	sudo mkdir -p $(LIB_DIR)
#copy the prototype file into usr/local/lib
	sudo cp prototype.glade /usr/local/lib/
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	sudo install process-scheduler $(INSTALL_DIR)
#create algos/ inside usr/local/lib if it doesn't exist
# sudo mkdir -p $(LIB_DIR)
# install dynamic libraries from algos/
	

# rule to clean up the generated files
clean:
	rm -f $(LIB_FILES) $(MAIN)

uninstall:
	sudo rm $(INSTALL_DIR)/process-scheduler
	sudo rm -rf $(LIB_DIR)
	sudo rm -f /usr/local/lib/prototype.glade

