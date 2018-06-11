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


int main(void)
{

    //Initializing hardware setup
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
    uint8_t bricks[128];
    uint8_t level = 1;
    int score = 0x0000;
    uint8_t lives = 0x33;
    int renderCount = 0;
    int physicsCount = 0;

    // Rendering initial positions


    while(1)
    {
        // Check if the timer have had an interrupt since last call
        if(interruptflag()){ // The functioncall resets the flag itself
            physicsCount++;
            renderCount++;
        }

        if(physicsCount > 10000/level){
            updatePhysics();
            physicsCount = 0;
        }

        if(renderCount > 10000){
            updateRender();
            renderCount = 0;
        }
        // INSERT lives equal 0 gives return

    }
}
