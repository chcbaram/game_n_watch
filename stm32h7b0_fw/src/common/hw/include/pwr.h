/*
 * pwr.h
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */

#ifndef SRC_COMMON_HW_INCLUDE_PWR_H_
#define SRC_COMMON_HW_INCLUDE_PWR_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "hw_def.h"

#ifdef _USE_HW_PWR



bool pwrInit(void);
void pwrEnterDeepSleep(void);
bool pwrUpdate(void);

#endif



#ifdef __cplusplus
}
#endif


#endif /* SRC_COMMON_HW_INCLUDE_PWR_H_ */
