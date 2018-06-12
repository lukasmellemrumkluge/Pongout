
#ifndef _PHYSICSENGINE_H_
#define _PHYSICSENGINE_H_

/* PhysicsEngine.h
 * contains ball and frame struct, and prototypes for the physics functions.
 */
 
 //Ball struct containing position and velocity
typedef struct {
    // 18.14
    int xpos;
    int ypos;
    int xv;
    int yv;
    
    uint8_t lastStriker;
    uint8_t angle;
} ball_t;

//Frame struct containing coordinates of upper left and bottom right corner.
typedef struct {
    int TLx;
    int TLy;
    int BRx;
    int BRy;
} frame_t;

//function declarations
void updatePhysics(ball_t * ball_p, uint32_t * striker0, uint32_t * striker1 uint8_t * player0lives_p, uint8_t * player1lives_p);

#endif /* _PHYSICSENGINE_H_ */
