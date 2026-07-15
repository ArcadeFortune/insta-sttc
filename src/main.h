#ifndef MAIN_H
#define MAIN_H

#if __has_include("env.h")
#include "env.h" //contains #define OPENAI_API_KEY "Bearer sk-proj-xxx"
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <portaudio.h>
#include <libwebsockets.h>
#include <stdatomic.h>

#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOKANJI
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#include <windows.h>

#define SAMPLE_RATE (24000)
#define FRAMES_PER_BUFFER (2400)
#define MIC_DATA_BUFFER_SIZE (16384) // has to be power of 2
typedef struct
{
  float *buf;
  int16_t *pcmBuf;
  char *base64Buf;
  size_t writeIndex;
  size_t readIndex;
} MicData;

extern atomic_bool isRecording;

int startListen(MicData *micData, PaStream **stream);
struct lws_context *startWebsocketClient();
int stopListen(PaStream *stream);
int stopWebsocketClient(struct lws_context *context);

DWORD WINAPI keyboardThread(void *arg);
void storeSamples(MicData *micData, const float *samples, size_t amount);
size_t readSamples(MicData *micData);

void processSample(MicData *micData);
void floatsToPcm(float *in, int16_t *out, size_t amount);
void bytesToBase64(int8_t *in, char *out, size_t amount);

#endif
