
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

#ifndef BM_003e77f8_7ba6_11e9_a31d_c8ff28b6c6d9
#define BM_003e77f8_7ba6_11e9_a31d_c8ff28b6c6d9

/**
 * @file fir.h
 * @author binary maker <https://github.com/binarymaker>
 * @brief Finite impulse responce filter 
 * @date 2019-05-28 
 */

#include "stdint.h"

typedef struct fir_s
{
  int16_t *tab;         /**< Tab buffer pointer */
  float *coeff;         /**< Filter co-efficient buffer */
  float gain;           /**< Filter gain factor */
  uint16_t size;        /**< Size of filter tab buffer */
  uint16_t index;       /**< Current location of tab buffer */
  int16_t filtered;     /**< Filter output */
  uint16_t sample_time; /**< Data sampling time interval */
  uint32_t last_time;   /**< Last sampled time */
} fir_t;

/**
 * @brief FIR filter object Initialization 
 * 
 * @param context [in] Instance of filter object
 * @param filter_coeff [in] Filter co-efficient external array pointer
 * @param filter_size [in] Size of filter tab
 * @param gain [in] Gain factor of filter
 *                  Gain = cumulative of coefficient value
 * @param sample_time [in] filter sampling time
 */
void fir_create(fir_t *context, float *filter_coeff,
                uint16_t filter_size, float gain, uint16_t sample_time);

/**
 * @brief Filter process function
 * 
 * @param context [in] Instance of filter object
 * @param input in] Data sample to filter
 */
void fir_filter(fir_t *context, int16_t input);

#endif // BM_003e77f8_7ba6_11e9_a31d_c8ff28b6c6d9
