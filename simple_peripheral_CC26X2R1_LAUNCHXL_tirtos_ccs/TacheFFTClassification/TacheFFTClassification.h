/*
 * TacheFFTClassification.h
 *
 *  Created on: 16 janv. 2023
 *      Author: GEII Robot
 */

#ifndef TACHEFFTCLASSIFICATION_TACHEFFTCLASSIFICATION_H_
#define TACHEFFTCLASSIFICATION_TACHEFFTCLASSIFICATION_H_

static void TacheFFTClassification_taskFxn(UArg a0, UArg a1);
void TacheFFTClassification_CreateTask(void);

void FFTClassificationTrigger(float serie[]);


#endif /* TACHEFFTCLASSIFICATION_TACHEFFTCLASSIFICATION_H_ */
