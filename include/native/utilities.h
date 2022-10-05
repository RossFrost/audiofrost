char **getTempFiles(tempFolder directory) {
    DIR *dir = opendir(directory.location);
    struct dirent *readDirectory;

    size_t allocation = 20;
    char **filenames = malloc((allocation));

    if (dir) {
        int i = 0;
        while ((readDirectory = readdir(dir)) != NULL) {
            filenames[i] = readDirectory->d_name;
            ++i;
            allocation += 20;
            filenames = realloc(filenames, allocation);

        }
        closedir(dir);
    }

    return filenames;
}


unsigned int getNumLength(unsigned int number) {
    unsigned int comparative = 10;
    unsigned int numLength = 1;

    while (number < comparative) {
        ++numLength;
        comparative *= 10;
    }

    return numLength;
}


unsigned long *getListOfRandomNumbers(unsigned amount, unsigned maxInt, int option) {
    unsigned long *list = malloc(sizeof(unsigned) * amount);

    for (unsigned int iteration = 0; iteration != amount; ++iteration) {
        time_t timmy;
        srand((unsigned)time(&timmy));

        unsigned int intialNumber = rand() % maxInt;

        if (option == 0) {
            list[iteration] == intialNumber;
            continue;
        } else if (option == 1) {
            int maxIntLength = getNumLength(maxInt);
            int intialNumberLength = getNumLength(intialNumber);
            unsigned int difference = maxIntLength - intialNumberLength;

            if (difference != 0) {
                while (difference != 0) {
                    srand((unsigned)time(&timmy));
                    char* buffer = malloc(sizeof(char) * maxIntLength + 1);
                    unsigned int attachment = rand() % (difference * 10);
                    sprintf(buffer, "%i%i", intialNumber, attachment);

                    unsigned long newNumber = atoi(buffer);
                    difference = maxIntLength - getNumLength(newNumber);
                    intialNumber = newNumber;
                    free(buffer);
                    if (difference == 0) {
                        list[iteration] = intialNumber;
                    }
                }
            }
            
        }
    }

    return list;
}

int checkDirectory(const char* directory) {
    DIR *dir = opendir(directory);

    if (dir) {
        closedir(dir);
        return 1;
    }

    return 0;
}


FILE *createTempFile(tempFolder directory, const char* mode) {
    unsigned long* name = getListOfRandomNumbers(1, 100000, 1);
    char *location = malloc(sizeof(char) * 20 + sizeof(directory.location));
    sprintf(
        location,        
        "%s/aud%lu",
        directory.location, name
    );

    printf("%s \n", location);

    FILE* file = fopen(location, mode);
    return file;
}


tempFolder createTempFolder(char *parentDirectory) {
    unsigned long n1, n2;
    unsigned long* nValues = getListOfRandomNumbers(2, 1000, 1);

    n1 = nValues[0];
    n2 = nValues[1];

    char *localDirectory = malloc(sizeof(parentDirectory) + sizeof(n1) + sizeof(n2) + 2);
    char *name = malloc(sizeof(n1) + sizeof(n2));

    sprintf(
        name,
        "%lu%lu",
        n1, n2
    );

    sprintf(
        localDirectory,
        "%s%lu%lu",
        parentDirectory, n1, n2
    );

    printf("Creating temp folder %s ...\n", localDirectory);

    tempFolder tempfolder;
    tempfolder.name = name;
    tempfolder.location = localDirectory;
    mkdir(localDirectory);
    free(nValues);

    return tempfolder;
}

