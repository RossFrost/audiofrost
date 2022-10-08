enum WRITE_STATUS writeWav(
                            char *path,
                            tempFolder source,
                            tracklist tracks,
                            char channel
) {



    char **files = getTempFiles(source);
    for (int track = 0; track != tracks.numTracks; ++track) {
        char *out = malloc(sizeof(char) * 50);
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
                    .data = "data",
                    .subChunk2Size = 0,
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
            
        fclose(output);
        char *raw = malloc(sizeof(char) * 50);
        sprintf(raw, "%s/%s", source.location, files[track]);
        printf("Getting source %s ... \n", raw);

        FILE *audio = fopen(raw, "rb");


        fflush(audio);

        if (audio == NULL) {
            perror("OH FUCK");
            abort();
        }

        fseek(audio, 0L, SEEK_END);
        long fileSize = ftell(audio);
        printf("Size is %lu \n", fileSize);
        rewind(audio);
        fclose(audio);

        output = fopen(out, "ab");
        fwrite(&fileSize, 4, 1, output);
        fclose(output);

        audio = fopen(raw, "ab");

        printf("Writing raw audio to %s ... \n", out);
  
        long byte = 0;
        while (byte < fileSize) {
            char* buffer = malloc(sizeof(char) * CD_DEFAULT_FRAME_SIZE);

            fseek(audio, CD_DEFAULT_FRAME_SIZE, SEEK_CUR);
            fread(buffer, CD_DEFAULT_FRAME_SIZE, 1, audio);
            byte += CD_DEFAULT_FRAME_SIZE;
            fclose(audio);
            output = fopen(out, "ab");
            fwrite(buffer, CD_DEFAULT_FRAME_SIZE, 1, output);
            fclose(output);
            fflush(output);
            free(buffer);
            fopen(raw, "ab");
        }


        free(out);
        free(raw);
    }
}