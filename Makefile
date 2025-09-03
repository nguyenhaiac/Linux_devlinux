PWD_DIR = .
INC_DIR = ./inc
SRC_DIR = ./src
LIB_DIR = ./lib
OBJ_DIR = ./obj

compile:
	gcc $(SRC_DIR)/main.c $(SRC_DIR)/strutils.c -o main.exe -I $(INC_DIR)

create_shared_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/strutils.c -o $(OBJ_DIR)/strutils.o -I $(INC_DIR)

create_static_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c	$(SRC_DIR)/strutils.c -o $(OBJ_DIR)/strutils.o -I $(INC_DIR)

create_shared_lib: create_shared_obj
	gcc -shared $(OBJ_DIR)/strutils.o -o $(LIB_DIR)/shared/libstrutils.so -I $(INC_DIR)

create_static_lib: create_static_obj
	ar rcs $(LIB_DIR)/static/libstrutils.a $(OBJ_DIR)/strutils.o

link_shared: create_shared_obj create_shared_lib
	gcc $(OBJ_DIR)/main.o -L./lib/shared/ -lstrutils -o main

link_static: create_static_obj create_static_lib
	gcc $(OBJ_DIR)/main.o -L./lib/static/ -lstrutils -o main

clean:
	rm $(OBJ_DIR)/*.o
	rm $(LIB_DIR)/shared/*.so
	rm main
