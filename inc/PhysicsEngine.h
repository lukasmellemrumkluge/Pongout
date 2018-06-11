
#ifndef _PHYSICSENGINE_H_
#define _PHYSICSENGINE_H_

/* PhysicsEngine.h
 * contains ball and frame struct, and prototypes for the physics functions.
 */
 
 //Ball struct containing position and velocity
typedef struct {
    int xpos;
    int ypos;
    int xv;
    int yv;
    int lastStriker;
} ball_t;

//Frame struct containing coordinates of upper left and bottom right corner.
typedef struct {
    int TLx;
    int TLy;
    int BRx;
    int BRy;
} frame_t;

//function declarations
void reflect(int * pos_p, int wall, int * v_p);
void updateBall(ball_t * ball_p, frame_t * frame_p);

#endif /* _PHYSICSENGINE_H_ */
