typedef unsigned int UINT32;

float fastsin(UINT32 phase) {
  const float frf3 = -1.0f / 6.0f;
  const float frf5 = 1.0f / 120.0f;
  const float frf7 = -1.0f / 5040.0f;
  const float frf9 = 1.0f / 362880.0f;
  const float f0pi5 = 1.570796327f;
  float x, x2, asin;
  UINT32 tmp = 0x3f800000 | (phase >> 7);
  if (phase & 0x40000000) tmp ^= 0x007fffff;
  x = (*((float*)&tmp) - 1.0f) * f0pi5;
  x2 = x * x;
  asin = ((((frf9 * x2 + frf7) * x2 + frf5) * x2 + frf3) * x2 + 1.0f) * x;
  return (phase & 0x80000000) ? -asin : asin;
}
#include <math.h>
int main() {
  float frequency = 440.0f;
  float sampleRate = 48000.0f;
  float mod = (float)(1L << 32) - .0001;
  UINT32 step = (UINT32)(frequency / sampleRate * mod);

  UINT32 phase = 0;
  // UINT32 step = ((float)(frequency / sampleRate)) * ((float)(1L << 32) -
  // .0001);
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  printf("%u %u\n", phase, step);
  phase = phase + step;
  phase = phase + step;
  printf("%u %u", phase, step);
  printf("%u %u", phase, step);

  phase = phase + step;
  printf("%u %u", phase, step);
  FILE* fd = popen("ffplay -f f32le -i pipe:0 -ac 1 -ar 48000", "w");

  for (int i = 0; i < 480300; i++) {
    phase = phase + step;
    float f = fastsin(phase);
    fwrite(&f, sizeof(float), 1, fd);
  }

  pclose(fd);
}