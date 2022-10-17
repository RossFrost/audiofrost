#include <cdrip.h>
#include <stdio.h>
#include <stdlib.h>


void write_raw_sectors_to_wav(char *file_name, CdIo_t *device, lsn_t first_sector, lsn_t last_sector) {
    FILE *file = fopen(file_name, "ab");
    for (lsn_t current_sector = first_sector; current_sector < last_sector + 1; ++current_sector) {
        void *buffer = malloc(sizeof(char) * SECTOR_SIZE_BYTES);
        cdio_read_audio_sector(device, buffer, current_sector);
        fwrite(buffer, SECTOR_SIZE_BYTES, 1, file);
        free(buffer);
        fflush(file);
    }
    fclose(file);
}


void write_wav_header(char *file_name, lsn_t sectors, enum AUDIO_CHANNEL channel) {
    FILE *file = fopen(file_name, "ab");

    int file_size = (44 + sectors * SECTOR_SIZE_BYTES - 8);
    int subchunk1_size = 16;
    short pcm_format = 1;
    int sample_rate = SAMPLE_RATE; 
    int byte_rate = SAMPLE_RATE * channel * 16 / 8;
    short block_align = (channel * 16 / 8);
    short bits_per_sample = 16;
    int raw_audio_size = (sectors * SECTOR_SIZE_BYTES);
    char *RIFF = "RIFF";
    char *WAVE = "WAVE";
    char *FMT  = "fmt ";
    char *data = "data";



    fwrite(RIFF,                4, 1, file); // RIFF FILE
    fwrite(&file_size,          4, 1, file); // TOTAL FILE SIZE
    fwrite(WAVE,                4, 1, file); // WAVE FILE
    fwrite(FMT,                 4, 1, file); // FORMAT SUBHEADER
    fwrite(&subchunk1_size,     4, 1, file); // SUBCHUNK SIZE
    fwrite(&pcm_format,         2, 1, file); // PCM FORMAT
    fwrite(&channel,            2, 1, file); // CHANNEL
    fwrite(&sample_rate,        4, 1, file); // SAMPLE RATE
    fwrite(&byte_rate,          4, 1, file); // BYTE RATE
    fwrite(&block_align,        2, 1, file); // BLOCK ALIGN
    fwrite(&bits_per_sample,    2, 1, file); // BITS PER SAMLE
    fwrite( data,               4, 1, file); // DATA SUBHEADER
    fwrite(&raw_audio_size,     4, 1, file); // RAW AUDIO DATA SIZE
    
    fflush(file);
    fclose(file);
}


char *write_to_wav(cdio_t_array devices, tracklist *tracks, output_directory *output) {
    for (unsigned char i_device = 0; i_device != devices.num_devices; ++i_device) {
        for (unsigned char i_track = 0; i_track != tracks[i_device].tracks; ++i_track) {
            printf("%i", i_track);
             write_wav_header(
                output[i_device].file_names[i_track],
                tracks[i_device].last_sectors[i_track] - tracks[i_device].first_sectors[i_track],
                STERO
             );
             write_raw_sectors_to_wav(
                output[i_device].file_names[i_track],
                devices.devices[i_device],
                tracks[i_device].first_sectors[i_track],
                tracks[i_device].last_sectors[i_track]
             );
        }
    }    
}