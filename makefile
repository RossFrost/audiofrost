INCLUDE_DIRECOTRY = include

REQUEST_NAME = request
REQUEST_DLL = $(REQUEST_NAME).dll
REQUEST_DIR = source/request

CD_RIP_NAME = cdrip
CD_RIP_DLL = $(CD_RIP_NAME).dll
CD_RIP_DIR = source/rip

OUTPUT_DIRECTORY = output
ASSESTS_DIRECTORY = assests

MAIN = main.c
EXE_NAME = audiofrost.exe
OUT = compiled/


all: clean libs directories executable

clean:
	rmdir /s /q "$(OUT)"
	mkdir "$(OUT)"
	copy "cdio.dll" "$(OUT)"

libs: 
	gcc -fpic -shared "$(REQUEST_DIR)/base64.c" "$(REQUEST_DIR)/sha1.c" "$(REQUEST_DIR)/request.c" "$(REQUEST_DIR)/disc_win32.c" "$(REQUEST_DIR)/disc.c" "$(REQUEST_DIR)/toc.c" -I "$(INCLUDE_DIRECOTRY)" -o "$(OUT)$(REQUEST_DLL)"
	gcc -fpic -shared "$(CD_RIP_DIR)/cdrip.c" "$(CD_RIP_DIR)/wav.c" -L "$(OUT)" -l "cdio" -I "$(INCLUDE_DIRECOTRY)" -L "$(OUT)" -l "$(REQUEST_NAME)" -o "$(OUT)$(CD_RIP_DLL)"

directories:
	mkdir "$(OUT)$(OUTPUT_DIRECTORY)"
	mkdir "$(OUT)$(ASSESTS_DIRECTORY)"

executable:
	gcc "$(MAIN)" -I "$(INCLUDE_DIRECOTRY)" -L "$(OUT)" -l "$(REQUEST_NAME)" -l "$(CD_RIP_NAME)" -o "$(OUT)$(EXE_NAME)" 

