#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lodepng.h"

#define NUM_FILTERS 7 

typedef struct
{
  int radius;			// the radius of the filter
  const double *filter;	// a pointer to the array of matrix
} Filter;

typedef struct
{
  int width;
  int height;
  uint8_t *redChannel;
  uint8_t *blueChannel;
  uint8_t *greenChannel;
  uint8_t *alphaChannel;
} Image;

void encode(const char *filename,Image *encodeImage);
Image *decode(const char *filename);
Filter *initializeFilters(double sigma);
Image *generateOutput(Image *inputImage);
void freeImage(Image *inputImage);
