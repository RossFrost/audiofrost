#define OUTPUT_PATH "output/"
#define TEMP_DIRECTORY "temp/"
#define MAX_TRACKS 99
#define TRACK_ALL 255


enum AUDIO_CHANNEL {
    MONO = 1,
    STERO = 2
};

enum WRITE_STATUS {
    OK,
    ERROR,
    FATAL
};


// Red Book Standard
enum CD_DEFAULTS {
    CD_DEFAULT_BITS_PER_SAMPLE = 16,
    CD_DEFAULT_SAMPLE_RATE = 44100, //in 
    CD_DEFAULT_BYTE_DEPTH = 2,
    CD_DEFAULT_BYTE_RATE = 176400,
    CD_DEFAULT_FRAME_SIZE = 2352,
    CD_DEFAULT_BLOCK_ALIGN = 4,
    CD_DEFAULT_AUDIO_CHANNEL = STERO
};


enum WAV_DEFAULTS {
    WAV_DEFAULT_CHUNK_SIZE = 44,
    WAV_DEFAULT_FORMAT_PCM = 1,
    WAV_DEFAULT_SUBCHUNK1_SIZE = 24,
    WAV_DEFAULT_SUBCHUNK2_SIZE = 8
};


typedef struct {
    char            *chunk;
    unsigned int    chunkSize;
    char            format;

    char            *fmt;
    short  subChunk1Size;
    int    byteRate;
    short  bitSample;
    short  audioFormat;
    int    audioChannel;
    short  blockAlign;
    int    sampleRate;

    
    char            *data;
    unsigned int   subChunk2Size;
} WAV_HEADER;


typedef struct {
    unsigned int *sampleRate;
    char *byteDepth;
} AUDIO_PROPERTIES;


typedef struct {
    char text[11][MAX_TRACKS];
    lsn_t sectorBegins[MAX_TRACKS];
    lsn_t sectorEnds[MAX_TRACKS];
    int track[MAX_TRACKS];
    int numTracks;
} tracklist;


typedef struct {
    char* location;
    char* name;
} tempFolder;