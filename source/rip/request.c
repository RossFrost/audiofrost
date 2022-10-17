#include <cdrip.h>
#include <util.h>
#include <stdio.h>
#include <string.h>

void *get_metabrainz_discid(tracklist tracks) {
    lba_t *offsets = malloc(sizeof(lba_t) * tracks.tracks + 4);
    char buffer[20];
    char *final_string = malloc(sizeof(char) * 250);

    offsets[0] = tracks.last_sectors[tracks.tracks - 1] + 151;
    for (unsigned char i_track = 0; i_track != tracks.tracks; ++i_track) {
        offsets[i_track + 1] = tracks.track_LBAs[i_track];
    }

    final_string[0] = '\0';
    sprintf(buffer, "%i", tracks.tracks_offset);
    strcat(final_string, buffer);
    sprintf(buffer, "+%i", tracks.tracks);
    strcat(final_string, buffer);

    for (lba_t lba = 0; lba != tracks.tracks + 1; ++lba) {
        sprintf(buffer, "+%lu\0", offsets[lba]);
        strcat(final_string, buffer);
    }

    return final_string;
}

char *get_metabrainz_xml_request(tracklist tracks, output_directory directory) {
    char get[1000] = "\0";
    char *disc_id = get_metabrainz_discid(tracks);

    char connect_exe[_MAX_PATH];
    full_path("connect.exe", connect_exe);

    sprintf(get, " \"https://musicbrainz.org/ws/2/discid/-?toc=%s&inc=artist-credits%c20aliases\" \"%s\\output.xml\"", disc_id, 37, directory.directory);
    strcat(connect_exe, get);
    system(connect_exe);

    memset(get, '\0', sizeof(get));
    strcpy(get, directory.directory);
    strcat(get, "output.xml");

    #if DEBUG == true
        printf("%s \n", connect_exe);
        printf("Args: %s \n", get);
    #endif

    free(disc_id);

    char *return_get = malloc(sizeof(char) * strlen(get) + 1);
    strcpy(return_get, get);

    return return_get;
}