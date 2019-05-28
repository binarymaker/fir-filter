
/**
 ******************************************************************************
 * ______  _                             ___  ___        _
 * | ___ \(_)                            |  \/  |       | |
 * | |_/ / _  _ __    __ _  _ __  _   _  | .  . |  __ _ | | __ ___  _ __
 * | ___ \| || '_ \  / _` || '__|| | | | | |\/| | / _` || |/ // _ \| '__|
 * | |_/ /| || | | || (_| || |   | |_| | | |  | || (_| ||   <|  __/| |
 * \____/ |_||_| |_| \__,_||_|    \__, | \_|  |_/ \__,_||_|\_\\___||_|
 *                                 __/ |
 *                                |___/
 *
 * Copyright (C) 2019 Binary Maker - All Rights Reserved
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution.
 * Written by Binary Maker <https://github.com/binarymaker>
 ******************************************************************************
 */

#include "fir.h"
#include "fir-cfg.h"
#include "stdlib.h"

#include "stm32f0xx_hal.h"

void
fir_create(fir_t *context,
           float *filter_coeff,
           uint16_t filter_size,
           float gain,
           uint16_t sample_time)
{
  context->size = filter_size;
  context->gain = gain;
  free(context->tab);
  context->tab = (int16_t*)malloc(filter_size * sizeof(int16_t));
  context->coeff = filter_coeff;
  context->index = 0;
  context->filtered = 0;
  context->sample_time = sample_time;
  context->last_time = 0;
}

void
fir_filter(fir_t *context,
           int16_t input)
{
  if ((TICK_TIMER - context->last_time) > context->sample_time)
  {
    context->last_time = TICK_TIMER;
    int32_t sum = 0;

    context->tab[context->index] = input;

    for (int i = 0; i < context->size; i++)
    {
      sum += context->coeff[i] *
             context->tab[(i + context->index) % context->size];
    }

    context->index = (context->index + 1) % context->size;
    context->filtered = (int16_t)(sum * context->gain);
  }
}
