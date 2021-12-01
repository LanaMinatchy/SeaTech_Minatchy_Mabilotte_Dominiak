#include "PWM.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"

unsigned int ADCValue0; // droit 1
unsigned int ADCValue1; // centre
unsigned int ADCValue2; // gauche 1
unsigned char stateRobot;


void OperatingSystemLoop(void)
{
switch (stateRobot)
{
case STATE_ATTENTE:
timestamp = 0;
PWMSetSpeedConsigne(0, MOTEUR_DROIT);
PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
stateRobot = STATE_ATTENTE_EN_COURS;

case STATE_ATTENTE_EN_COURS:
if (timestamp > 1000)
stateRobot = STATE_AVANCE;
break;

case STATE_AVANCE:
PWMSetSpeedConsigne(45, MOTEUR_DROIT);
PWMSetSpeedConsigne(45, MOTEUR_GAUCHE);
stateRobot = STATE_AVANCE_EN_COURS;
break;
case STATE_AVANCE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_GAUCHE:
PWMSetSpeedConsigne(30, MOTEUR_DROIT);
PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
break;
case STATE_TOURNE_GAUCHE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_GAUCHE_DOUCEMENT:
PWMSetSpeedConsigne(30, MOTEUR_DROIT);
PWMSetSpeedConsigne(12, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_GAUCHE_DOUCEMENT_EN_COURS;
break;
case STATE_TOURNE_GAUCHE_DOUCEMENT_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_DROITE:
PWMSetSpeedConsigne(0, MOTEUR_DROIT);
PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_DROITE_EN_COURS;
break;
case STATE_TOURNE_DROITE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_DROITE_DOUCEMENT:
PWMSetSpeedConsigne(12, MOTEUR_DROIT);
PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_DROITE_DOUCEMENT_EN_COURS;
break;
case STATE_TOURNE_DROITE_DOUCEMENT_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_SUR_PLACE_GAUCHE:
PWMSetSpeedConsigne(20, MOTEUR_DROIT);
PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
break;
case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

case STATE_TOURNE_SUR_PLACE_DROITE:
PWMSetSpeedConsigne(-20, MOTEUR_DROIT);
PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
break;
case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
SetNextRobotStateInAutomaticMode();
break;

default :
stateRobot = STATE_ATTENTE;
break;
}
}

unsigned char nextStateRobot=0;

void SetNextRobotStateInAutomaticMode()
{
    /*
unsigned char positionObstacle = ATTENTE;
int a=30;
int b=30;
//Détermination de la position des obstacles en fonction des télémètres
if(robotState.distanceTelemetreCentre < 20) //Obstacle en face
positionObstacle = OBSTACLE_EN_FACE;
else if ( robotState.distanceTelemetreDroit < a &&
robotState.distanceTelemetreGauche2 < b &&
robotState.distanceTelemetreDroit2 < b &&        
robotState.distanceTelemetreCentre > a &&
robotState.distanceTelemetreGauche > a) //Obstacle à droite
positionObstacle = OBSTACLE_EN_FACE;
else if ( robotState.distanceTelemetreGauche < a &&
robotState.distanceTelemetreGauche2 < b &&
robotState.distanceTelemetreDroit2 < b &&        
robotState.distanceTelemetreCentre > a &&
robotState.distanceTelemetreDroit > a) //Obstacle à droite
positionObstacle = OBSTACLE_EN_FACE;
else if ( robotState.distanceTelemetreDroit < a &&
robotState.distanceTelemetreCentre > a &&
robotState.distanceTelemetreGauche > a) //Obstacle à droite
positionObstacle = OBSTACLE_A_DROITE;
else if(robotState.distanceTelemetreDroit > a &&
robotState.distanceTelemetreCentre > a &&
robotState.distanceTelemetreGauche < a) //Obstacle à gauche
positionObstacle = OBSTACLE_A_GAUCHE;
else if(robotState.distanceTelemetreDroit < a &&
robotState.distanceTelemetreCentre > a &&
robotState.distanceTelemetreGauche < a) //Obstacle à gauche
positionObstacle = OBSTACLE_EN_FACE;
else if ( robotState.distanceTelemetreDroit2 < 10 &&
robotState.distanceTelemetreGauche > a &&
robotState.distanceTelemetreGauche2 > 10 &&
robotState.distanceTelemetreDroit > a &&        
robotState.distanceTelemetreCentre > a)
positionObstacle = OBSTACLE_A_DROITE_2;
else if ( robotState.distanceTelemetreGauche2 < 10 &&
robotState.distanceTelemetreGauche > a &&
robotState.distanceTelemetreDroit2 > 10 &&
robotState.distanceTelemetreDroit > a &&        
robotState.distanceTelemetreCentre > a)//Obstacle à gauche
positionObstacle = OBSTACLE_A_GAUCHE_2;
else 
    positionObstacle = PAS_D_OBSTACLE;
*/

int DD = OFF;
int D = OFF;
int C = OFF;
int G = OFF;
int GG = OFF;        
        
if(robotState.distanceTelemetreDroit2 < 16){
    DD=ON;
    LED_ORANGE = 1;}
else {
    DD=OFF;
    LED_ORANGE = 0;}
if(robotState.distanceTelemetreDroit < 26)
    D=ON;
else 
    D=OFF;
if(robotState.distanceTelemetreCentre < 28){
    C=ON;
    LED_BLEUE = 1;}
else {
    C=OFF;
    LED_BLEUE = 0;}
if(robotState.distanceTelemetreGauche < 26)
    G=ON;
else 
    G=OFF;
if(robotState.distanceTelemetreGauche2 < 16){
    GG=ON;
    LED_BLANCHE = 1;}
else {
    GG=OFF;
    LED_BLANCHE = 0;}
    

//Détermination de l?état à venir du robot
if (C == ON || D == ON && G == ON || DD == ON && GG == ON && D == ON)
nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
else if (DD == ON && GG == ON && G == ON)
nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
else if (G == OFF && C == OFF && D == ON)
nextStateRobot = STATE_TOURNE_GAUCHE;
else if (G == ON && C == OFF && D == OFF)
nextStateRobot = STATE_TOURNE_DROITE;
else if (GG == OFF && G == OFF && C == OFF && D == OFF && DD == ON)
nextStateRobot = STATE_TOURNE_GAUCHE_DOUCEMENT;
else if (GG == ON && G == OFF && C == OFF && D == OFF && DD == OFF)
nextStateRobot = STATE_TOURNE_DROITE_DOUCEMENT;
else 
nextStateRobot = STATE_AVANCE;


//Si l?on n?est pas dans la transition de l?étape en cours
if (nextStateRobot != stateRobot-1)
stateRobot = nextStateRobot;
}

int main(void) {

    // Initialisation de l'oscillateur
    InitOscillator();

    // Configuration de entrées s o r t i e s
    InitIO();
    LED_BLANCHE = 0;
    LED_BLEUE = 0;
    LED_ORANGE = 0;
  
    InitPWM();
    //PWMSetSpeed(30, MOTEUR_GAUCHE);
    //PWMSetSpeed(30, MOTEUR_DROIT);
    //PWMSetSpeedConsigne(37,MOTEUR_DROIT);
    //PWMSetSpeedConsigne(37,MOTEUR_GAUCHE);
 
    InitTimer1();
    InitTimer23();
    //InitTimerPolice();
    InitTimer4();
    InitADC1();
    

    // Boucle P r i n c i p a l e

    while (1) {
        /*
        if (ADCIsConversionFinished()==1){
        ADCClearConversionFinishedFlag();
        unsigned int * result=ADCGetResult();
        ADCValue0=result[0];
        ADCValue1=result[1]; 
        ADCValue2=result[2];
        */
        if (ADCIsConversionFinished() == 1)
        {
            ADCClearConversionFinishedFlag();
            unsigned int * result=ADCGetResult();
            float volts = ((float) result [4])*3.3/4096*3.2;
            robotState.distanceTelemetreGauche = 34 / volts -5;
            volts = ((float) result [2])*3.3/4096*3.2;
            robotState.distanceTelemetreCentre = 34 / volts -5;
            volts = ((float) result [1])*3.3/4096*3.2;
            robotState.distanceTelemetreDroit = 34 / volts -5;
            volts = ((float) result [3])*3.3/4096*3.2;
            robotState.distanceTelemetreGauche2 = 34 / volts -5;
            volts = ((float) result [0])*3.3/4096*3.2;
            robotState.distanceTelemetreDroit2 = 34 / volts -5;
        
        /*
        if (robotState.distanceTelemetreDroit2 <= 32)
            LED_ORANGE = 1;
        else
            LED_ORANGE = 0; 
        if (robotState.distanceTelemetreCentre <= 32)
            LED_BLEUE = 1;
        else
            LED_BLEUE = 0;
        if (robotState.distanceTelemetreGauche2 <= 32)
            LED_BLANCHE = 1;
        else
            LED_BLANCHE = 0;  */  
        }
    } // f i n main
}
