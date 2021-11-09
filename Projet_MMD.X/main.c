#include "PWM.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "ADC.h"

unsigned int ADCValue0;
unsigned int ADCValue1;
unsigned int ADCValue2;

int main(void) {

    // Initialisation de l'oscillateur
    InitOscillator();

    // Configuration de entrées s o r t i e s
    InitIO();
    LED_BLANCHE = 1;
    LED_BLEUE = 0;
    LED_ORANGE = 0;

  
    InitPWM();
    //PWMSetSpeed(30, MOTEUR_GAUCHE);
    //PWMSetSpeed(30, MOTEUR_DROIT);
    //PWMSetSpeedConsigne( 37,MOTEUR_DROIT);
    //PWMSetSpeedConsigne(37,MOTEUR_GAUCHE);
 
    InitTimer1();
    InitTimer23();
    InitADC1();
    // Boucle P r i n c i p a l e

    while (1) {
        if (ADCIsConversionFinished()==1){
        ADCClearConversionFinishedFlag();
        unsigned int * result=ADCGetResult();
        ADCValue0=result[0];
        ADCValue1=result[1];
        ADCValue2=result[2];
        }
    } // f i n main
}
