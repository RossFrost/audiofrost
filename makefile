EXE_NAME := "output.exe"
INCLUDE = "include"
LIB_DIRECTORY = "."

all: compile
compile:
	echo "Compiling"
	gcc main.c  -I $(INCLUDE) -L $(LIB_DIRECTORY) -l "cdio" -l "libFLAC" -o $(EXE_NAME) -W 

