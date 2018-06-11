//.c file for all internal 'physics' functions and structs in the program
#include "PhysicsEngine.h"

// Uses 18.14 fixed-point integers

// general one-dimensional reflect function taking moving object position and
// velocity plus statical object position.
void reflect(int * pos_p, int wall, int * v_p){
    //This function assumes good input.
    //All checks must be made before calling it.

    *pos_p = (wall << 1) - *v_p - *pos_p;

    *v_p *= -1;
}

//Checks for collisions on walls and updates ball accordingly
uint8_t wallCollision(ball_t * ball_p) {
    if (ball_p->xpos + ball_p->xv < (1 << 14)) {
        reflect(&ball_p->xpos, (1 << 14), &ball_p->xv);
        return 1;
    } else if (ball_p->xpos + ball_p->xv > (31 << 14)) {
        reflect(&ball_p->xpos, (31 << 14), &ball_p->xv);
        return 1;
    } else{
        return 0;
    }
}
    
uint8_t endCollision(ball_t * ball_p, uint8_t * player0lives_p, uint8_t * player1lives_p) {
    if (ball_p->ypos + ball_p->yv < (7 << 14)) {
        *player0lives_p--;
        return 1;
    } else if (ball_p->ypos + ball_p->yv > (121 << 14)) {
        *player1lives_p--;
        return 1;
    } else{
        return 0;
    }
}

uint8_t strikerCollision(ball_t * ball_p, uint32_t * striker0, uint32_t * striker1) {
    int nextX = ball_p->xpos + ball_p->xv;
    int nextY = ball_p->ypos + ball_p->yv;
    if (nextX < (9 << 14)) {
        if (nextY > striker0 && nextY <= striker0 - (1 << 14)) {
            reflect(ball_p);
            ball_p->angle = ball_p->angle + ((127 - ball_p->angle) >> 1);
        }
        else if (nextY > striker0 - (1 << 14)) {
        }
        ball_p->xv = FIX14MULT(ball_p->v, cos(ball_p->angle));
        ball_p->yv = FIX14MULT(ball_p->v, sin(ball_p->angle));
    }      
    //not finished
}
