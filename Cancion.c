#include <ao/ao.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Structures.h"
#include <string.h>
#define BITS 16

void *Play(void *arg) {
  PlayArgs *args = (PlayArgs *)arg;
  char cancion[20];
  strcpy(cancion,args->path);
  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;
  int err;
  int channels, encoding;
  long driver,rate;
  ao_device *dev;
  ao_initialize();

  /* set up options to decode the entire file */
  mpg123_init();
  mh = mpg123_new(NULL, &err);
  buffer_size = mpg123_outblock(mh);
  buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  /* open the file and get the decoding format */
  mpg123_open(mh, cancion);
  mpg123_getformat(mh, &rate, &channels, &encoding);

  /* set up the device */
  ao_sample_format format;
  format.bits = BITS;
  format.channels = channels;
  format.rate = rate;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  driver = ao_default_driver_id();
  dev = ao_open_live(driver, &format, NULL);

  /* decode and play */
  while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
    ao_play(dev, buffer, done);
  }

  /* clean up */
  free(buffer);
  ao_close(dev);
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();
  ao_shutdown();
  pthread_exit(NULL);
}


