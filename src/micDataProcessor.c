#include "main.h"

void processSample(MicData *micData)
{
  size_t allowedToRead = readSamples(micData);
  if (allowedToRead == 0)
    return;

  floatsToPcm(micData->buf, micData->pcmBuf, allowedToRead);
  bytesToBase64((int8_t *)micData->pcmBuf, micData->base64Buf, allowedToRead * sizeof(int16_t));
  printf("sending string: %s\n", micData->base64Buf);
}

void floatsToPcm(float *in, int16_t *out, size_t amount)
{
  for (int i = 0; i < amount; i++)
  {
    float s = in[i];
    if (s >= 1.0f)
      out[i] = 32767;
    else if (s <= -1.0f)
      out[i] = -32768;
    else
      out[i] = (int16_t)(s * 32767.0f);
  }
}

/**
 * assumes the system is little endian
 */
void bytesToBase64(int8_t *in, char *out, size_t bytesToProcess)
{
  const char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";
  int8_t byteGroup[3] = {0};
  size_t charsProcessed = 0;
  for (size_t i = 0; i < bytesToProcess; i++)
  {
    byteGroup[i % 3] = in[i];
    if (i % 3 == 2)
    {
      int8_t ch1 = byteGroup[0] >> 2 & 0b111111;
      int8_t ch2 = (byteGroup[0] & 0b11) << 4 | (byteGroup[1] >> 4 & 0b1111);
      int8_t ch3 = (byteGroup[1] & 0b1111) << 2 | (byteGroup[2] >> 6 & 0b11);
      int8_t ch4 = byteGroup[2] & 0b111111;
      out[charsProcessed++] = alphabet[ch1];
      out[charsProcessed++] = alphabet[ch2];
      out[charsProcessed++] = alphabet[ch3];
      out[charsProcessed++] = alphabet[ch4];
    }
  }

  size_t paddingNeeded = (3 - (bytesToProcess % 3)) % 3;
  if (paddingNeeded == 1)
  {
    int8_t ch1 = byteGroup[0] >> 2 & 0b111111;
    int8_t ch2 = (byteGroup[0] & 0b11) << 4 | (byteGroup[1] >> 4 & 0b1111);
    int8_t ch3 = (byteGroup[1] & 0b1111) << 2 | 0;
    out[charsProcessed++] = alphabet[ch1];
    out[charsProcessed++] = alphabet[ch2];
    out[charsProcessed++] = alphabet[ch3];
    out[charsProcessed++] = '=';
  }
  else if (paddingNeeded == 2)
  {
    int8_t ch1 = byteGroup[0] >> 2 & 0b111111;
    int8_t ch2 = (byteGroup[0] & 0b11) << 4 | 0;
    out[charsProcessed++] = alphabet[ch1];
    out[charsProcessed++] = alphabet[ch2];
    out[charsProcessed++] = '=';
    out[charsProcessed++] = '=';
  }
  out[charsProcessed++] = '\0';
}

// // buffer
// // [x][x][x][x][x][0][0][0]
// //  r              w

// // samples:
// // [x][x][x]
