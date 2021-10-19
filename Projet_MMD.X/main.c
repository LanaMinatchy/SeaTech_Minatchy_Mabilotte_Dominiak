#include "PWM.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"

int main(void) {

    // Initialisation de l'oscillateur
    InitOscillator();

    // Configuration de entrées s o r t i e s
    InitIO();
    LED_BLANCHE = 1;
    LED_BLEUE = 0;
    LED_ORANGE = 0;


    InitPWM();
    PWMSetSpeed(30, MOTEUR_GAUCHE);
    PWMSetSpeed(30, MOTEUR_DROIT);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           InitTimer23();
    InitTimer1();

    // Boucle P r i n c i p a l e

    while (1) {
    } // f i n main
}
