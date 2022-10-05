enum WRITE_STATUS writeWav(
                            char *path,
                            tempFolder source,
                            tracklist tracks,
                            char channel
) {



    char **files = getTempFiles(source);
    for (int track = 0; track != tracks.numTracks; ++track) {

        char *out = malloc(sizeof(50));
        char *raw = malloc(sizeof(50));

        sprintf(raw, "%s/%s", source.location, files[track]);
        sprintf(out, "%s%s.wav", path, files[track]);

        printf("Outputting audio file...\n");
        FILE *output = fopen(out, "ab");
        fflush(output);

        if (output == NULL) {
            perror("OH FUCK");
            abort();
        }

        printf("Encoding %s...\n", files[track]);

        printf("Writing header \n");

        WAV_HEADER header = {
                    .chunk = "RIFF",
                    .chunkSize = WAV_DEFAULT_CHUNK_SIZE,
                    .fmt =  "FMT",
                    .subChunk1Size = WAV_DEFAULT_SUBCHUNK1_SIZE,
                    .byteRate = CD_DEFAULT_BYTE_RATE,
                    .bitSample = CD_DEFAULT_BITS_PER_SAMPLE,
                    .audioFormat = WAV_DEFAULT_FORMAT_PCM,
                    .audioChannel = CD_DEFAULT_AUDIO_CHANNEL,
                    .blockAlign =  CD_DEFAULT_BLOCK_ALIGN,
                    .data = "DATA",
                    .subChunk2Size = 8,
                    .sampleRate = CD_DEFAULT_SAMPLE_RATE
            };

        fwrite(header.chunk, 1, 4,           output);
        fwrite(&header.chunkSize, 4, 1,      output);
        fwrite(header.fmt, 1, 4,             output);
        fwrite(&header.subChunk1Size, 4, 1,  output);
        fwrite(&header.audioFormat, 2, 1,    output);
        fwrite(&header.audioChannel, 2, 1,   output);
        fwrite(&header.sampleRate, 4, 1,     output);
        fwrite(&header.sampleRate, 4, 1,     output);
        fwrite(&header.byteRate, 4, 1,       output);
        fwrite(&header.blockAlign, 2, 1,     output);
        fwrite(&header.bitSample, 4, 1,      output);
        fwrite(header.data, 1, 4,            output);
        fwrite(&header.subChunk2Size, 4, 1,  output);

        printf("Writing raw audio... \n");
        printf("%s \n", raw);

        FILE *audio = fopen(raw, "rb");
        fflush(audio);

        if (audio == NULL) {
            perror("OH FUCK");
            abort();
        }

        fseek(audio, 0L, SEEK_END);
        long fileSize = ftell(audio);
        printf("%lu", fileSize);
        fseek(audio, 0L, SEEK_SET);
        
        for (long  byte = 0; byte != fileSize; ++byte) {
            if (byte % 1000 == 0) {
                printf(" %lu bytes out of %lu \n", ftell(audio), fileSize);
            }

            char *buffer = malloc(sizeof(char));
            fread(buffer, 1, 1, audio);
            fseek(audio, byte, SEEK_SET);
            fwrite(buffer, 1, 1, output);
            free(buffer);
        }

        free(out);
        free(raw);
        fclose(audio);
        fclose(output);
    }
}