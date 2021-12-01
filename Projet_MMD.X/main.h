/* 
 * File:   main.h
 * Author: GEII Robot
 *
 * Created on 16 novembre 2021, 15:26
 */

#ifndef MAIN_H
#define	MAIN_H

#define FCY 40000000

#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_GAUCHE_DOUCEMENT 6
#define STATE_TOURNE_GAUCHE_DOUCEMENT_EN_COURS 7
#define STATE_TOURNE_DROITE 8
#define STATE_TOURNE_DROITE_EN_COURS 9
#define STATE_TOURNE_DROITE_DOUCEMENT 10
#define STATE_TOURNE_DROITE_DOUCEMENT_EN_COURS 11
#define STATE_TOURNE_SUR_PLACE_GAUCHE 12
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 13
#define STATE_TOURNE_SUR_PLACE_DROITE 14
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 15
#define STATE_ARRET 16
#define STATE_ARRET_EN_COURS 17
#define STATE_RECULE 18
#define STATE_RECULE_EN_COURS 19

#define ATTENTE 0
#define PAS_D_OBSTACLE 1
#define OBSTACLE_EN_FACE 2
#define OBSTACLE_A_GAUCHE 3
#define OBSTACLE_A_GAUCHE_2 4
#define OBSTACLE_A_DROITE 5

#define OBSTACLE_A_DROITE_2 6
#define OBSTACLE_EN_FACE 7

#define ON 0
#define OFF 1

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

