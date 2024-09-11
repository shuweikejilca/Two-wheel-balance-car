#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"                  // Device header
void Encoder_Init(void);
int16_t Encoder1_Get(void);
int16_t Encoder2_Get(void);
#endif
