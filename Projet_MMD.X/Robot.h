#ifndef ROBOT_H
#define ROBOT_H

typedef struct robotstateBITS{
    
    union {
        struct {
            unsigned char taskEnCours;
            
            float vitesseGaucheConsigne;
            float vitesseGaucheCommandeCourante;
            float vitesseDroiteConsigne;
            float vitesseDroiteCommandeCourante;
        };
    };
}ROBOT_STATE_BITS;
extern volatile ROBOT_STATE_BITS robotState;
#endif 