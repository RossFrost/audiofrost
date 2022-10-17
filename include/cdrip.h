#include <cdio/cdio.h>

#define OUTPUT_DIRECTORY_PATH "compiled/output/"
#define TEMP_FILE_LENGTH 20

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
    unsigned char *device_number;
    unsigned char tracks;
    unsigned char tracks_offset;
    lsn_t *first_sectors;
    lsn_t *last_sectors;
    lba_t *track_LBAs;
} tracklist;


typedef struct {
    CdIo_t *devices[MAX_DEVICES];
    unsigned char *device_names[10];
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

#define MB_TOC_STRING_LENGTH (3 + 3 + 100*7)

#define MB_DISC_ID_LENGTH		32

#define MB_ERROR_MSG_LENGTH		255


#define MCN_STR_LENGTH		13

#define ISRC_STR_LENGTH		12

#define MAX_DISC_LENGTH		(90 * 60 * 75)

char *write_to_wav(cdio_t_array devices, tracklist *tracks, output_directory *output);
char *get_metabrainz_xml_request(cdio_t_array devices, tracklist *tracks);
tracklist *cd_rip_init(enum AUDIO_OUTPUT_OPTIONS audio_option, int musicbrainz_enabled);

