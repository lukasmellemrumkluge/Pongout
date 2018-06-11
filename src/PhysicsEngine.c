//.c file for all internal 'physics' functions and structs in the program
#include "PhysicsEngine.h"
#include "stm32f30x_conf.h"

// Uses 18.14 fixed-point integers

// general one-dimensional reflect function taking moving object position and
// velocity plus statical object position.
void reflect(int * pos_p, int wall, int * v_p){
    //This function assumes good input.
    //All checks must be made before calling it.

    *pos_p = (wall << 1) - *v_p - *pos_p;

    *v_p *= -1;
}

void moveBall(ball_t * ball_p){
    ball_p->xpos += ball_p->xv;
    ball_p->ypos += ball_p->yv;
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
    
// TODO: Delete ball from ball-array
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

uint8_t brickCollision(ball_t * ball_p){

    // TODO:
    // Special bricks not implemented
    // Score updating not implemented
    // Placeholder for level-info (bricks).

   /* About bit-shiting in this function:
    *   >>14 - Conversion from 18:14 to int.
    *   >>15 - Conversion and division by two.
    *       Used for calculating x-coordinates for bricks.
    *       Because bricks are two wide
    *   >>16 - Conversion and division by four.
    *       Used for calculating y-coordinates for bricks.
            Because bricks are four tall.
    */

    // Are we even near the bricks?
    if(ball_p->xpos>>14 > 96) return 0;
    if(ball_p->xpos>>14 < 32) return 0;

    // Remembering old positions for double-bouncing.
    // Without these, a ball might end up inside a brick.
    int oldx = ball_p->xpos;
    int oldy = ball_p->ypos;

    //Helper value
    int nextx = oldx+ball_p->xv;

    // Return value.
    // Indicates if a brick has been hit.
    uint8_t retval = 0;

    /* Generally about the collision detection:
     *
     * The block the ball collides with is assumed
     *  to be the one closest to the original position.
     * This not only simplifies detection, but also
     *  speeds it up. Change it if it feels bad.
     * This works best visually, because the physics
     *  is faster and more accurate than the rendering.
     *
     * X and Y are checked separately.
     * This should allow corner bounces.
     */

    // X

    // Are we crossing a whole-numbered coordinate?
    if(oldx>>15 != nextx>>15){

        //Calculate brick index values
        uint32_t decoded_x = 0x00000001<<((nextx-(33<<14))>>15);
        uint8_t iy = oldy>>16;

        // Is the brick we're "hitting" there?
        //currentLevel is a placeholder for the level (brick) data!!!!
        if(currentLevel[iy] & decoded_x){
            if(ball_p->vx > 0) {
                // Hitting left edge of brick:
                reflect(&ball_p->xpos, nextx>>14, &ball_p->xv);
            } else {
                // Hitting right edge of brick:
                reflect(&ball_p->xpos, oldx>>14, &ball_p->xv);
            }
            //Flip the bit
            currentLevel[iy] ^= decoded_x;

            retval = 1;
        }
    } // End x


    // Helper value
    nexty = oldy+ball_p->yv;

    // Y
    if(oldy>>16 != nexty>>16){

        //Calculate brick index values
        uint32_t decoded_x = 0x00000001<<((oldx-33)>>15);
        uint8_t iy = nexty>>16;

        // Is the brick we're "hitting" there?
        //currentLevel is a placeholder for the level (brick) data!!!!
        if(currentLevel[iy] & decoded_x){
            if(ball_p->vy > 0) {
                // Hitting top of brick:
                reflect(&ball_p->ypos, oldy>>14, &ball_p->yv);
            } else {
                // Hitting bottom of brick:
                reflect(&ball_p->ypos, nexty>>14, &ball_p->yv);
            }
            //Flip the bit
            currentLevel[iy] ^= decoded_x;

            retval = 1;
        }
    } // End y
    return retval;
} // End brickCollision

//Checks all collisions, updates accordingly.
// For one ball only.
void updatePhysics(ball_t * ball_p, uint32_t * striker0, uint32_t * striker1m uint8_t * player0lives_p, uint8_t * player1lives_p){
    if(wallCollision(ball_p)){}
    else if(endCollision(ball_p, player0lives_p, player1lives_p)){}
    else if(strikerCollision(ball_p, striker0, striker1)){}
    else if(brickCollision(ball_t * ball_p)){}
    else moveBall(ball_p);
}
