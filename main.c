#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>

#include <cdio/cdio.h>

#include <FLAC/all.h>

#include <native/define.h>
#include <native/utilities.h>
#include <native/opticaldrive.h>
#include <native/encode.h>


int main() {
    const char* drive = getDefaultDrive();
    tracklist data = getTracks(drive);
    tempFolder folder = readCompactDisk(drive, data, 1);
    writeWav(OUTPUT_PATH, folder, data, STERO); 
    return 0;
}