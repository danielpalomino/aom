/*
 * Copyright (c) 2018, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

/* Sum the difference between every corresponding element of the buffers. */

#include "config/aom_config.h"
#include "config/aom_dsp_rtcd.h"

#include "aom/aom_integer.h"

//DANIEL BEGIN
extern int intra_mode;
extern int intra_angle_delta;
//DANIEL END

int64_t aom_sse_c(const uint8_t *a, int a_stride, const uint8_t *b,
                  int b_stride, int width, int height) {
  int y, x;
  int64_t sse = 0;

  //DANIEL BEGIN
  switch(intra_mode) {
          case DC_PRED: fprintf(stdout,"\nblock %dx%d",width,height);
          fprintf(stdout,"\n\t\tCalculating SSE for intra mode DC_PRED %d",intra_angle_delta);
                        break;
          case V_PRED:  fprintf(stdout,"\n\t\tCalculating SSE for intra mode V_PRED %d",intra_angle_delta);
                        break;
          case H_PRED:  fprintf(stdout,"\n\t\tCalculating SSE for intra mode H_PRED %d",intra_angle_delta);
                        break;
          case D45_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode D45_PRED %d",intra_angle_delta);
                            break;
          case D135_PRED:   fprintf(stdout,"\n\t\tCalculating SSE for intra mode D135_PRED %d",intra_angle_delta);
                            break;
          case D113_PRED:   fprintf(stdout,"\n\t\tCalculating SSE for intra mode D113_PRED %d",intra_angle_delta);
                            break;
          case D157_PRED:   fprintf(stdout,"\n\t\tCalculating SSE for intra mode D157_PRED %d",intra_angle_delta);
                            break;
          case D203_PRED:   fprintf(stdout,"\n\t\tCalculating SSE for intra mode D203_PRED %d",intra_angle_delta);
                            break;
          case D67_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode D67_PRED %d",intra_angle_delta);
                            break;
          case SMOOTH_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode SMOOTH_PRED %d",intra_angle_delta);
                            break;
          case SMOOTH_V_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode SMOOTH_V_PRED %d",intra_angle_delta);
                            break;
          case SMOOTH_H_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode SMOOTH_H_PRED %d",intra_angle_delta);
                            break;                            
          case PAETH_PRED:    fprintf(stdout,"\n\t\tCalculating SSE for intra mode PAETH_PRED %d",intra_angle_delta);
                            break;
          default: fprintf(stdout,"\n\t\tOTHER MODE");
      }
  //DANIEL END
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      const int32_t diff = abs(a[x] - b[x]);
      sse += diff * diff;
    }

    a += a_stride;
    b += b_stride;
  }
  return sse;
}

#if CONFIG_AV1_HIGHBITDEPTH
int64_t aom_highbd_sse_c(const uint8_t *a8, int a_stride, const uint8_t *b8,
                         int b_stride, int width, int height) {
  int y, x;
  int64_t sse = 0;
  uint16_t *a = CONVERT_TO_SHORTPTR(a8);
  uint16_t *b = CONVERT_TO_SHORTPTR(b8);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      const int32_t diff = (int32_t)(a[x]) - (int32_t)(b[x]);
      sse += diff * diff;
    }

    a += a_stride;
    b += b_stride;
  }
  return sse;
}
#endif
