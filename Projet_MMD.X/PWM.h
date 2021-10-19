/* 
 * File:   PWM.h
 * Author: GEII Robot
 *
 * Created on 19 octobre 2021, 13:49
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1
void InitPWM(void);
void PWMSetSpeed(float,int);
void PWMUpdateSpeed(void);

#endif	/* PWM_H */

