#include <cdrip.h>
#include <request.h>

char *get_metabrainz_discid(tracklist tracks) {
    SHA_INFO sha;
    SHA_BYTE *buffer;
    SHA_LONG size;

    sprintf(buffer, "%02X", tracks.tracks_offset);
    sha_update(&sha, buffer, strlen(buffer));
    sprintf(&buffer, "%02X", tracks.tracks);
    sha_update(&sha, buffer, strlen(buffer));

    for (unsigned char i_track = 0; i_track != MAX_TRACKS + 1; ++i_track) {
        sprintf(buffer, "%08X", tracks.track_LBAs[i_track]);
        sha_update(&sha, buffer, strlen(buffer));
    }

    unsigned char digest[20];
    sha_final(digest, &sha);

    rfc822_binary(digest, sizeof(digest), &size);

    return digest;
}

char *get_metabrainz_xml_request(tracklist tracks) {
    char *disc_id = get_metabrainz_discid(tracks);
    printf("%s", disc_id);
}