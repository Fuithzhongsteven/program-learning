/*
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <tinyalsa/asoundlib.h>

#include "dprintf.h"
#include "speecharray.h"

#define RECORD_FILENAME "/sdcard/RecordTest.wav"
#define OUT_FILENAME    "/sdcard/out.pcm"

#define RECORD_CH0_FILENAME "/sdcard/RecordTestCh0.wav"
#define RECORD_CH1_FILENAME "/sdcard/RecordTestCh1.wav"
#define RECORD_CH2_FILENAME "/sdcard/RecordTestCh2.wav"
#define RECORD_CH3_FILENAME "/sdcard/RecordTestCh3.wav"
#define RECORD_CH4_FILENAME "/sdcard/RecordTestCh4.wav"
#define RECORD_CH5_FILENAME "/sdcard/RecordTestCh5.wav"

#define BUFFER_SIZE     4*6*16000/20 // 50ms 19200Bytes
#define SAMPLEBITS      32
#define CHANNEL_COUNT   6
#define CHANNEL_BASE    0

#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT  0x20746d66
#define ID_DATA 0x61746164

#define FORMAT_PCM 1

struct wav_header {
    uint32_t riff_id;
    uint32_t riff_sz;
    uint32_t riff_fmt;
    uint32_t fmt_id;
    uint32_t fmt_sz;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    uint32_t data_id;
    uint32_t data_sz;
};
static int flagexit = 0;
void sigint_handler(int sig __unused){
    DprintfE("sigint_handler %d\n",sig);
    flagexit = 1;
}

int main(int argc, char **argv)
{
    FILE *file;
    struct wav_header header;
    unsigned int card = 0;
    unsigned int device = 0;
    unsigned int channels = 2;
    unsigned int rate = 48000;
    unsigned int bits = 16;
    unsigned int frames;
    unsigned int period_size = 9600;
    unsigned int period_count = 2;
    unsigned int cap_time = 0;
    enum pcm_format format;
    SpeechArrayHandle_t *handle = NULL;
    SpeechArray_t speechconfig;
    struct timespec end;
    struct timespec now;
    char buff[BUFFER_SIZE] = {0};
    int len = 0;
    int size = 0;
    int bytes_write = 0;
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file.wav [-D card] [-d device]"
                " [-c channels] [-r rate] [-b bits] [-p period_size]"
                " [-n n_periods] [-T capture time]\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "wb");
    if (!file) {
        fprintf(stderr, "Unable to create file '%s'\n", argv[1]);
        return 1;
    }

    /* parse command line arguments */
    argv += 2;
    while (*argv) {
        if (strcmp(*argv, "-d") == 0) {
            argv++;
            if (*argv)
                device = atoi(*argv);
        } else if (strcmp(*argv, "-c") == 0) {
            argv++;
            if (*argv)
                channels = atoi(*argv);
        } else if (strcmp(*argv, "-r") == 0) {
            argv++;
            if (*argv)
                rate = atoi(*argv);
        } else if (strcmp(*argv, "-b") == 0) {
            argv++;
            if (*argv)
                bits = atoi(*argv);
        } else if (strcmp(*argv, "-D") == 0) {
            argv++;
            if (*argv)
                card = atoi(*argv);
        } else if (strcmp(*argv, "-p") == 0) {
            argv++;
            if (*argv)
                period_size = atoi(*argv);
        } else if (strcmp(*argv, "-n") == 0) {
            argv++;
            if (*argv)
                period_count = atoi(*argv);
        } else if (strcmp(*argv, "-T") == 0) {
            argv++;
            if (*argv)
                cap_time = atoi(*argv);
        }
        if (*argv)
            argv++;
    }

    header.riff_id = ID_RIFF;
    header.riff_sz = 0;
    header.riff_fmt = ID_WAVE;
    header.fmt_id = ID_FMT;
    header.fmt_sz = 16;
    header.audio_format = FORMAT_PCM;
    header.num_channels = channels;
    header.sample_rate = rate;

    switch (bits) {
    case 32:
        format = PCM_FORMAT_S32_LE;
        break;
    case 24:
        format = PCM_FORMAT_S24_LE;
        break;
    case 16:
        format = PCM_FORMAT_S16_LE;
        break;
    default:
        fprintf(stderr, "%d bits is not supported.\n", bits);
        return 1;
    }

    header.bits_per_sample = pcm_format_to_bits(format);
    header.byte_rate = (header.bits_per_sample / 8) * channels * rate;
    header.block_align = header.num_channels * (header.bits_per_sample / 8);
    header.data_id = ID_DATA;

    /* leave enough room for header */
    fseek(file, sizeof(struct wav_header), SEEK_SET);

    /* install signal handler and begin capturing */
    signal(SIGINT, sigint_handler);
    signal(SIGHUP, sigint_handler);
    signal(SIGTERM, sigint_handler);

    speechconfig.card = card;
    speechconfig.device = device;
    speechconfig.channels = channels;
    speechconfig.rate = rate;
    speechconfig.format = format;
    speechconfig.period_count = period_count;
    speechconfig.period_size = period_size;
    
    speechArrayInit();
    handle = speechArrayOpen(&speechconfig);
    if(handle == NULL){
        printf("speechArrayOpen failed: %p\n",handle);
    }
    clock_gettime(CLOCK_MONOTONIC, &now);
    end.tv_sec = now.tv_sec + cap_time;
    end.tv_nsec = now.tv_nsec;
    size = bits * channels * period_count * period_size / 8;
    while (1) {
        len = SpeechArrayRead(handle, buff, size);
        if(len <= 0){
            printf("SpeechArrayRead error\n");
            break;
        }else{
            printf("SpeechArrayRead %d bytes\n",len);
        }
        if (fwrite(buff, 1, len, file) != len) {
            printf("Error capturing sample\n");
            break;
        }
        bytes_write += len;
        if (cap_time) {
            clock_gettime(CLOCK_MONOTONIC, &now);
            if (now.tv_sec > end.tv_sec ||
                (now.tv_sec == end.tv_sec && now.tv_nsec >= end.tv_nsec))
                break;
        }
        if(flagexit)break;
    }
    speechArrayClose(handle);
    speechArrayUninit();
    frames = bytes_write/12;
    printf("Captured %d frames\n", frames);

    /* write header now all information is known */
    header.data_sz = frames * header.block_align;
    header.riff_sz = header.data_sz + sizeof(header) - 8;
    fseek(file, 0, SEEK_SET);
    fwrite(&header, sizeof(struct wav_header), 1, file);

    fclose(file);

    return 0;
}



