#include <cdio/cdio.h>

#define DEBUG true

#ifndef CDRIP_H_INCLUDED
#define CDRIP_H_INCLUDED
    enum DEFAULTS {
        MAX_TRACKS = 99,
        MAX_DEVICES = 10,
        WAV_HEADER_SIZE = 44,
        SECTOR_SIZE_BYTES = 2352,
        SAMPLE_RATE = 44100
    };


    enum AUDIO_OUTPUT_OPTIONS {
        WAV,
        FLAC,
        OGG,
        PCM
    };


    enum AUDIO_CHANNEL {
        MONO = 1,
        STERO = 2
    };


    typedef struct {;
        unsigned char tracks;
        unsigned char tracks_offset;
        lsn_t *first_sectors;
        lsn_t *last_sectors;
        lba_t *track_LBAs;
        
    } tracklist;


    typedef struct {
        CdIo_t *devices[MAX_DEVICES];
        unsigned char num_devices;
    } cdio_t_array;


    typedef struct {
        char *disc_id;
        tracklist *tracks;
        char **track_names;
        char *artist;
        char *album;
        char *album_cover;
        char month;
        char day;
        unsigned short year;
    } disc_attributes;

    typedef struct {
        char *directory;
        char **file_names;
    } output_directory;


    void *cd_rip_init(enum AUDIO_OUTPUT_OPTIONS audio_option);

    char *write_to_wav(cdio_t_array devices, tracklist *tracks, output_directory *output);

    char *get_metabrainz_xml_request(tracklist tracks, output_directory device);

    char *get_album_name(char *xml_file);
    

#endif