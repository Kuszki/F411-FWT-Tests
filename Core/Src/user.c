#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "gpio.h"
#include "crc.h"

#include "arm_wt_f32.h"
#include "arm_mal_f32.h"

void SystemClock_Config(void);

#define data_len 1024
#define coef_len 16

float32_t coef_C[coef_len];
float32_t coef_B[coef_len];

uint32_t adc_buff[data_len];

float32_t in_buff[data_len + coef_len];
float32_t out_buff[data_len];

//const float32_t mat[data_len * data_len];

int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CRC_Init();

	HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, 1);
	HAL_GPIO_WritePin(DEBUG_0_OUT_GPIO_Port, DEBUG_0_OUT_Pin, 0);
	HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 0);

	// fwt_adc_scale_ext(adc_buff, in_buff, data_len, coef_len, 0.004882813f);
	// fwt_malat_ext_par(in_buff, out_buff, data_len, dec_len, coef_C, coef_B, coef_len);

//	arm_matrix_instance_f32 mat_A;
//	arm_mat_init_f32(&mat_A, data_len, data_len, mat);
//
//	arm_matrix_instance_f32 mat_X;
//	arm_mat_init_f32(&mat_X, data_len, 1, in_buff);
//
//	arm_matrix_instance_f32 mat_Y;
//	arm_mat_init_f32(&mat_Y, data_len, 1, out_buff);

	//	arm_q31_to_float((q31_t*) V, X, N);
	//	arm_mat_scale_f32(&mat_X, 1.0f, &mat_X);
	//	arm_mat_mult_f32(&mat_A, &mat_X, &mat_Y);

	while (1)
	{
		HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, 0);
		HAL_GPIO_WritePin(DEBUG_0_OUT_GPIO_Port, DEBUG_0_OUT_Pin, 1);

//		for (size_t dec = 1; dec <= 5; ++dec)
//		{
//			arm_wt_f32_instance fwt = {
//					.c = coef_C,
//					.b = coef_B,
//					.c_len = coef_len,
//					.n_len = data_len,
//					.n_dec = dec,
//					.scale = 1.0f,
//					.shift = 0.0f,
//			};
//
//			arm_wt_status s = arm_fwt_f32_init(&fwt);
//
//			if (s != WT_STATUS_SUCCESS) break;
//
//			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 1);
//			for (size_t i = 0; i < 1000; ++i) arm_wt_f32_run(&fwt, adc_buff);
//			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 0);
//
//			arm_wt_f32_free(&fwt);
//		}

//		for (size_t dec = 1; dec <= 5; ++dec)
//		{
//			if ((data_len >> (dec-1)) < coef_len) break;
//
//			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 1);
//			for (size_t i = 0; i < 1000; ++i) arm_wt_f32_mallat(in_buff, out_buff, data_len, dec, coef_C, coef_B, coef_len);
//			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 0);
//		}

		for (size_t dec = 1; dec <= 5; ++dec)
		{
			if ((data_len >> (dec-1)) < coef_len) break;

			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 1);
			for (size_t i = 0; i < 1000; ++i) fwt_malat(in_buff, out_buff, data_len, dec, coef_C, coef_B, coef_len);
			HAL_GPIO_WritePin(DEBUG_1_OUT_GPIO_Port, DEBUG_1_OUT_Pin, 0);
		}

//		for (size_t i = 0; i < 1000; ++i) fwt_malat
//		{
//			arm_q31_to_float(adc_buff, in_buff, data_len);
//			arm_mat_scale_f32(&mat_X, 1.0f, &mat_X);
//			arm_mat_mult_f32(&mat_A, &mat_X, &mat_Y);
//		}

		HAL_GPIO_WritePin(DEBUG_0_OUT_GPIO_Port, DEBUG_0_OUT_Pin, 0);
		HAL_GPIO_WritePin(LED_OUT_GPIO_Port, LED_OUT_Pin, 1);

		HAL_Delay(1000);
	}
}
