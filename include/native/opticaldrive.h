tempFolder readCompactDisk(const char* drive, tracklist list, unsigned char readTrack) {
    CdIo_t *disc = cdio_open(drive, DRIVER_DEVICE);
    tempFolder temp = createTempFolder(TEMP_DIRECTORY);

    int readTracks;
    if (readTrack == TRACK_ALL) {
        readTracks = list.numTracks;
    } else if (readTrack <= list.numTracks && readTrack != 0 ) {
        readTracks = readTrack;
    } else {
        printf("WARNING: TRACK CANNOT BE LESS THAN 0");
        return temp;
    }


    for (int track = 0; track != readTracks; ++track) {
        lsn_t sectorBegins = list.sectorBegins[track];
        lsn_t sectorEnds   = list.sectorEnds[track];
        lsn_t observer     = list.sectorBegins[track];

        printf("Creating temp file... \n");
        FILE *tempFile;
        tempFile = createTempFile(temp, "ab");

        printf("Reading %s... \n", list.text[track]);
        long sector = 0;
        for (observer; observer != sectorEnds + 1; ++observer) {
            void *buffer = malloc(sizeof(char) * 2352);
            cdio_read_audio_sector(disc, buffer, observer);
            fwrite(buffer, 2352, 1, tempFile);
            ++sector;

            if (sector % 1000 == 0) {
                printf("%lu read out of %i\n", sector, sectorEnds - sectorBegins);
            }
            free(buffer);
        }
        fflush(tempFile);
        fclose(tempFile);
    }
    return temp;
}


tracklist getTracks(const char *device) {
    CdIo_t *disc = cdio_open(device, DRIVER_DEVICE);

    track_t firstTrack = cdio_get_first_track_num(disc);
    track_t numTracks = cdio_get_num_tracks(disc);

    //track dump
    char *header = "Track ";
    int sects[numTracks];

    tracklist trackList;

    int track = firstTrack;     
    for (int iteration = 0; track < numTracks; ++iteration, ++track) {
        //max tracks is 99

        printf("%s", header);
        lsn_t sectBegins = cdio_get_track_lsn(disc, track);
        lsn_t sectEnds = cdio_get_track_last_lsn(disc, track);
        
        if (sectBegins != CDIO_INVALID_LSN) {
            printf("%d at %06d; ends %06d (OK)\n", track, sectBegins, sectEnds);
        } else {
            printf("%3d has invalid logical sector number (BAD)\n");
            continue;
        }

        char *strOutput = malloc(sizeof(char) * sizeof(header) + sizeof(int) * numTracks);

        snprintf(
                    strOutput, 
                    (size_t)sizeof(strOutput) + 1, 
                    "%s%i", 
                    header, track
                );

        size_t strOutputLength = strnlen(strOutput, 1000) + 1;
        strcpy(trackList.text[iteration], strOutput);

        trackList.sectorBegins[iteration] = sectBegins;
        trackList.sectorEnds[iteration] = sectEnds;
        trackList.track[iteration] = track;

        free(strOutput);
    }
    trackList.numTracks = numTracks;
    return trackList;
}


const char* getDefaultDrive() {
    CdIo_t* opticalDriver = cdio_open(NULL, DRIVER_DEVICE);
    const driver_id_t *driverId;
    
    const char *defaultOpticalDriver;

    if (opticalDriver != NULL) {
        defaultOpticalDriver = cdio_get_default_device(opticalDriver);
        cdio_destroy(opticalDriver);

        printf("Selecting '%s' as drive \n", defaultOpticalDriver);
        return defaultOpticalDriver;
    }

}
