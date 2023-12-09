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

$(LIB_DIR)/%.so: $(SRC_DIR)/%.c
	$(CC) -shared -fPIC $(CFLAGS) $< -o $@


$(LIB_DIR):
	sudo mkdir -p $(LIB_DIR)

run: $(MAIN) 
	sudo mkdir -p $(LIB_DIR)
	sudo cp prototype.glade /usr/local/lib/
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	./$(MAIN) 2>/dev/null

install: 
	sudo mkdir -p $(LIB_DIR)
	sudo cp prototype.glade /usr/local/lib/
	sudo cp $(SRC_DIR)/*.so $(LIB_DIR)
	sudo install process-scheduler $(INSTALL_DIR)
	
clean:
	rm -f $(LIB_FILES) $(MAIN)

uninstall:
	sudo rm $(INSTALL_DIR)/process-scheduler
	sudo rm -rf $(LIB_DIR)
	sudo rm -f /usr/local/lib/prototype.glade

