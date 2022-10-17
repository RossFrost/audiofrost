#include <cdrip.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <util.h>
#include <inttypes.h>

output_directory *create_tree(tracklist *tracks, int num_devices) {
    output_directory *directory[num_devices];
    char current_dir[PATH_MAX];
    getcwd(current_dir, sizeof(current_dir));


    for (char i_device = 0; i_device != num_devices; ++i_device) {
        char device_directory_name[sizeof(current_dir) + strlen(OUTPUT_DIRECTORY_PATH) + 10];
        sprintf(device_directory_name, "%s/%sdevice%02d", current_dir, OUTPUT_DIRECTORY_PATH, i_device);
        mkdir(device_directory_name);

        directory[i_device] = malloc(sizeof(output_directory));
        directory[i_device]->file_names = malloc((sizeof(device_directory_name) + sizeof("track.wav") + 3) * tracks[i_device].tracks);
        directory[i_device]->directory = device_directory_name;
        

        for (char i_track = 0; i_track != tracks[i_device].tracks; ++i_track) {
            char track_temp_name[sizeof(device_directory_name) + sizeof("track.wav") + 3];
            sprintf(track_temp_name, "%s/track%02d.wav", device_directory_name, i_track);

            FILE *track = fopen(track_temp_name , "a+");

            if (track == NULL) {
                printf("Couldn't create file \n");
            }

            fclose(track);

            directory[i_device]->file_names[i_track] = malloc((sizeof(device_directory_name) + sizeof("track.wav") + 3));
            strcpy(directory[i_device]->file_names[i_track], track_temp_name);
            printf("%s \n",directory[i_device]->file_names[i_track]);
        }
    }
    return *directory;
} 


tracklist *get_tracks(cdio_t_array cdio_array) {
    tracklist *tracks = malloc(sizeof(tracklist) * cdio_array.num_devices);
    

    for (unsigned char i_device = 0; i_device != cdio_array.num_devices; ++i_device) {
        tracks[i_device].tracks = cdio_get_last_track_num(cdio_array.devices[i_device]);
        tracks[i_device].tracks_offset = cdio_get_first_track_num(cdio_array.devices[i_device]);
        tracks[i_device].device_number = cdio_array.device_names[i_device];

        tracks[i_device].first_sectors = malloc(sizeof(int) * (tracks[i_device].tracks - 1));
        tracks[i_device].last_sectors = malloc(sizeof(int) * (tracks[i_device].tracks - 1));
        tracks[i_device].track_LBAs = malloc(sizeof(int) * (tracks[i_device].tracks - 1));

        for (track_t i_track = tracks[i_device].tracks_offset; i_track != tracks[i_device].tracks + 1; ++i_track) {
            tracks[i_device].first_sectors[i_track - tracks[i_device].tracks_offset] = cdio_get_track_lsn(cdio_array.devices[i_device], i_track );
            tracks[i_device].last_sectors[i_track - tracks[i_device].tracks_offset] = cdio_get_track_last_lsn(cdio_array.devices[i_device], i_track);
            tracks[i_device].track_LBAs[i_track - tracks[i_device].tracks_offset] = cdio_get_track_lba(cdio_array.devices[i_device], i_track);
        } 
    }

    return tracks;
}


cdio_t_array get_devices() {
   unsigned char init = cdio_init();

   if (init == 0) {
        printf("Could not initiate...\n");
        abort();
   }

    cdio_t_array cdio_array;
    driver_id_t driver_id;
    cdio_array.num_devices = 0;

    #ifdef _WIN32
        driver_id = DRIVER_WIN32;
    #elif __linux__
        driver_id = DRIVER_LINUX;
    #else
        printf("No compatible OS");
        abort();
    #endif

    char **device_names = cdio_get_devices(driver_id);

    for (char iteration = 0; device_names[iteration] != NULL; ++iteration) {
        char *device = device_names[iteration];
        cdio_array.devices[iteration] = cdio_open(device_names[iteration], driver_id);
        cdio_array.device_names[iteration] = device_names[iteration];

        ++cdio_array.num_devices;

    }
    return cdio_array;
}

tracklist *cd_rip_init(enum AUDIO_OUTPUT_OPTIONS audio_option, int musicbrainz_enabled) {
    cdio_t_array devices = get_devices();
    tracklist *tracks = get_tracks(devices);
    /**output_directory *output_dir = create_tree(tracks, devices.num_devices);

    switch (audio_option) {
        case WAV: write_to_wav(devices, tracks, output_dir);
    }


    free(output_dir);
    **/

    if (musicbrainz_enabled == true) {
        get_metabrainz_xml_request(devices, tracks);
    }   
    return tracks;
}
