/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "PhysicsEngine.h"
#include "ansi.h"
#include "joystick.h"
#include "led.h"
#include "lookup.h"
#include "potmeter.h"
#include "timers.h"
#include "levels.h"

loadLevel(int * levelSelect, uint32_t * currentLevel){
    switch(* levelSelect){
        case 1 :
            currentLevel = level1;
            break;
        default :
            currentLevel = default_level;
    }
}



int main(void)
{

    //Initializing hardware setup
    // is initialized in Main
    initializeJoystick();
    initializeLed();
    initPot();
    init_usb_uart(9600);
    init_spi_lcd();
    startTimer1(100);

    //Initialize game variables
    // 18.14 values
    int striker0 = 0;
    int striker1 = 0;
    uint8_t activeBalls = 0x00;
    ball_t balls[8];
    uint32_t bricks[8];
    uint8_t speed = 1;
    int score = 0x0000;
    uint8_t lives = 0x33;
    int renderCount = 0;
    int physicsCount = 0;

    // striker initial position
    loadLevel(0, &bricks);//0: default
    //Initiate ball 1

    // Rendering initial positions


    while(1)
    {

        // Check if the timer have had an interrupt since last call
        if(timerflag){
            physicsCount++;
            renderCount++;
            timerflag = 0;
        }

        if(physicsCount > 10000-speed*10){
            updatePhysics();
            physicsCount = 0;
        }

        if(renderCount > 10000){
            renderAll(balls, bricks, striker0, striker1);
            //updateRender();
            renderCount = 0;
        }
        // INSERT lives equal 0 gives return


    }
}
