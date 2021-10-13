#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"

int main (void) {

// Initialisation de l?oscillateur
    
    InitOscillator();
    InitTimer23();
    InitTimer1();

// Configuration de séentres s o r t i e s

InitIO();
LED_BLANCHE = 0 ;
LED_BLEUE = 0 ;
LED_ORANGE = 0 ;

// Boucle P r i n c i p a l e

while ( 1 ) {
} // f i n main
}