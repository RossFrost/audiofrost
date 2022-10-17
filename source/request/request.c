#include <cdrip.h>
#include <util.h>
#include <string.h>
#include <stdio.h>
#include <request.h>
#include <stdlib.h>
#include <assert.h>

#include <discid/discid.h>

#define XA_INTERVAL		((60 + 90 + 2) * 75)
#define DATA_TRACK		0x04


void get_metabrainz_discid(char *device_number, tracklist tracks, char output[]) {
    puts("works");
	DiscId *disc_id = discid_new();
    discid_read(disc_id, device_number);
    char *id = discid_get_id(disc_id);
    memcpy(output, id, strlen(output));
    free(disc_id);
}

char *get_metabrainz_xml_request(cdio_t_array devices, tracklist *tracks) {
    char *musicbrainz_url_query_base = "https://musicbrainz.org/ws/2/discid/";
    char disc_id[30];
    get_metabrainz_discid(devices.device_names[0], tracks[0], disc_id);
    printf("%s", disc_id);
    strcat(musicbrainz_url_query_base, disc_id);
    return musicbrainz_url_query_base;
}