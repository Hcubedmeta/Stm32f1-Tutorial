/*
 SimpleKalmanFilter - a Kalman Filter implementation for single variable models.
 Created by Denys Sene, January, 1, 2017.
 Released under MIT License - see LICENSE file for details.
 */ 
 #ifndef _KALMAN_H_
 #define _KALMAN_H_
 #include "stm32f10x.h"
 #include "math.h"
 #include "stdint.h"
 
static float _err_measure;
static float _err_estimate;
static float _q;
static float _current_estimate;
static float _last_estimate = 0.0;
static float _kalman_gain;
 // class SimpleKalmanFilter
void SimpleKalmanFilter(float mea_e, float est_e, float q);
float updateEstimate(float mea);
void setMeasurementError(float mea_e);
void setEstimateError(float est_e);
void setProcessNoise(float q);
float getKalmanGain(void);
float getEstimateError(void);
 #endif