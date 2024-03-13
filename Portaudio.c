#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define SAMPLE_RATE 58000
#define RECORDING_DURATION 4.5 // in seconds
#define NUM_CHANNELS 1
#define FRAMES_PER_BUFFER 512

typedef float SAMPLE;

static int recordCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    FILE *file = (FILE *)userData;
    const SAMPLE *input = (const SAMPLE *)inputBuffer;
    fwrite(input, sizeof(SAMPLE), framesPerBuffer, file);
    return paContinue;
}

int main()
{
    PaError err;
    PaStream *stream;
    FILE *outputFile;
    unsigned long totalFrames;
    unsigned long numFrames = SAMPLE_RATE * RECORDING_DURATION;

    err = Pa_Initialize();
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        return 1;
    }

    outputFile = fopen("recorded_sound.raw", "wb");
    if (!outputFile) {
        fprintf(stderr, "Error opening output file.\n");
        Pa_Terminate();
        return 1;
    }

    err = Pa_OpenDefaultStream(&stream, NUM_CHANNELS, 0, paFloat32, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, recordCallback, outputFile);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        fclose(outputFile);
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        fclose(outputFile);
        Pa_Terminate();
        return 1;
    }

    printf("Recording...\n");
    Pa_Sleep(RECORDING_DURATION * 1000);

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        fclose(outputFile);
        Pa_Terminate();
        return 1;
    }

    Pa_CloseStream(stream);
    fclose(outputFile);
    Pa_Terminate();

    printf("Recording saved to 'recorded_sound.raw'.\n");

    return 0;
}
