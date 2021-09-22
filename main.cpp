/*

RASPII clock

Dey - 2021

Based on an older ASCII project:

https://deybacsi.github.io/asciiclock/
https://github.com/Deybacsi/asciiclock

*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <sys/timeb.h>
#include <math.h>
#define PI 3.14159265

using namespace std;


#include "inc/common.h"
#include "inc/screen.h"
#include "inc/3d.h"
#include "inc/math.h"
#include "inc/clock_digits.h"

#include "inc/clock_digital.cpp"
#include "inc/clock_analog.cpp"

#include "inc/backg_snow.cpp"
#include "inc/backg_starfield.cpp"
#include "inc/backg_starfield3d.cpp"
#include "inc/backg_plasma.cpp"
#include "inc/backg_matrix.cpp"
#include "inc/backg_fire.cpp"
#include "inc/backg_obj3d.cpp"



// define the effects
typedef void (*myfunctions)();


/* array with effects

   0 - init function
   1 - calc next frame func
   2 - draw actual frame to layers

*/
myfunctions background[][3] = {
    { init_bg_snow, calc_bg_snow, draw_bg_snow},            // snow
    { init_bg_star, calc_bg_star, draw_bg_star},            // starfield
    { init_bg_star3d, calc_bg_star3d, draw_bg_star3d},      // starfield 3d
    { init_bg_plasma, calc_bg_plasma, draw_bg_plasma},      // plasma
    { init_bg_matrix, calc_bg_matrix, draw_bg_matrix},      // matrix
    { init_bg_fire, calc_bg_fire, draw_bg_fire},             // fire
    { init_bg_obj3d, calc_bg_obj3d, draw_bg_obj3d},         // 3d
 
};


// number of our effects 
// why don't we use length()?
const int   BG_EFFECTNO=7;


int         ACT_BG_EFFECT=0;
            




// init all thingies
void init_all() {
    int i;
    initscreen();
    clear();
    clearalllayer(CLEARCHAR);

    // get a random background effect
    ACT_BG_EFFECT = rand() % BG_EFFECTNO;

    // to setup a constant effect
    //ACT_BG_EFFECT=0;

    // initialize background & foreground effects
    background[ACT_BG_EFFECT][0]();


    clocky=float((SCREENY/2 - DIGITDESIGNS[ACTDIGITDESIGN].y) /2);
    clockx=float((SCREENX - DIGITDESIGNS[ACTDIGITDESIGN].x * 5) /2);

    pricey=float((SCREENY/2 - DIGITDESIGNS[ACTDIGITDESIGN].y) /2 + SCREENY/2);
    //pricex=float((SCREENX - DIGITDESIGNS[ACTDIGITDESIGN].x * btcprice.length()+10) /2);
    pricex=float((SCREENX - DIGITDESIGNS[ACTDIGITDESIGN].x *(btcprice.length()+1)) /2);

}

void get_price(){
    // get btc price
    string line;
    ifstream myfile ("price.txt");
    if (myfile.is_open())
    {
        getline (myfile,btcprice);
        myfile.close();
    }
}

int main(){
    system("stty raw -echo");
    hideCursor();
    // to store pressed keys
    char ch=0;


    srand(GetMilliCount());

    // elapsed time counter in msec
    int nTimeElapsed =0;
    get_price();
    init_clock_digital();
    init_all();
    

    checktime();
    LAST_MINSTR[0] = ACT_MINSTR[0];
    
    while(ch!=27 && ch!=113 && ch!=120) {
        // current millisec for proper FPS counting
        int nTimeStart = GetMilliCount();

        checktime();
        // if minute changed, reinit everything
        if (LAST_MINSTR[0] != ACT_MINSTR[0]) {
            get_price();
            init_clock_digital();
            init_all();
            
        }
     
        // calculate next background frame
        background[ACT_BG_EFFECT][1]();

        // put background frame to layers
        background[ACT_BG_EFFECT][2]();


        // draw the clock
        draw_clock_digital(clockx ,clocky);

        // write out btc price

        draw_price(pricex , pricey, btcprice);

        // merge all layers and draw to screen
        mergelayers();
        printscreen();

        // check pressed keys
        if (keyPressed()) {
            ch=getchar();
            switch (ch) {
                case 27:
                    getchar(); ch=getchar();
                    switch (ch) {
                        case 27:
                            cout << endl << "ESC" << ch << endl; 
                            exit(0);
                            break;
                        case 68:
                            cout << "Left";
                            break;
                        case 67:
                            cout << "Right";
                            break;
                    }
                    break;

            }
        }

        // save current minute
        LAST_MINSTR[0]=ACT_MINSTR[0];

        // get elapsed time in ms
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    }	
    // restore terminal
    system("stty cooked echo");
    textReset();
    showCursor();
	return 0;
}
