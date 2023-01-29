#include "config.h"
#include <xc.h>
#include "io.h"

//porting from 12F675 to 12F1572:
//use these IO defines (in io.h):
//#define ANSEL ANSELA
//#define TRISIO TRISA
//#define GPIO LATA

const unsigned char pattern[]={
//1,4,2,4,5,4,7,4,10,4,9,4,3,4,2,4,6,4,8,4,11,4,12,4      //for Reindeer
//3,2,1,0,4,5,6,7,8,9,0,10,11,12,0                        //for Santa Sleigh
//12,11,10,9,8,7,6,5,4,3,2,1,0,0                          //for Candy Cane
//8,4,2,1,0,9,5,2,1,0,10,6,3,1,11,6,3,1,12,7,3,1,0,1,0    //for Cap
//1,2,3,4,5,6,7,8,9,10,12,11                              //for Bauble
5,2,1,0,8,6,7,0,8,11,12,0,8,9,10,0,8,4,3,0              //for Star
//1,2,3,4,5,6,7,8,9,10,11,12,0,0                          //for Stocking        
//12,11,7,4,2,1, 12,11,8,5,2,1, 12,11,9,5,3,1, 12,11,10,6,3,1, 0,1 //for Tree
    
    /*
//fixed pseudorandom
11,12,5,6,7,1,3,5,10,7,9,12,10,9,11,9,10,4,2,7,7,
11,2,5,11,6,2,3,5,10,4,5,6,4,7,4,11,12,6,2,9,1,
8,2,10,2,8,11,5,6,11,4,12,3,8,5,4,4,12,2,8,12,1,
8,6,5,4,12,3,5,3,2,7,7,6,11,11,1,3,7,2,2,8,3,
12,4,12,2,9,2,12,6,3,2,1,10,10,2,9,9,12,6,9,12,7,
8,3,12,11,3,6,12,3,8,7,12,7,11,5,1,2,11,4,7,6,8,
7,4,9,8,3,3,11,9,8,7,9,9,4,9,10,2,1,12,11,4,7,
11,2,5,3,12,8,9,7,4,2,8,11,7,5,1,4,10,12,9,2,7,
12,9,4,10,9,10,5,12,9,10,8,10,11,1,3,3,10,12,11,11,4,
4,8,3,11,9,8,4,7,4,2,6,1,7,1,6,10,1,8,7,10,12,
5,8,10,2,2,7,7,10,4,5,6,10,1,3,10,9,3,4,8,4,8,
12,4,7,4,5,10,8,8,9,2,11,1,6,8,12,12,1,9,2,11,6    
     //*/
};

//original 12F675 code:

void main(void) {
    unsigned char i;
    CLRWDT();                   //on powerup 12F1572 has 2s WDT timeout
    //OPTION_REGbits.PSA=1;   //PS assigned to WDT 12F675 code not needed as WDT has its own PS
    ioinit();
    while(1){
        for(i=0;i<sizeof(pattern);i++){
            CLRWDT();
            //OPTION_REGbits.PS=0;        //brief on 18ms 12F675 code becomes:
            WDTCONbits.WDTPS=4;            //16ms
            setLED(pattern[i]);            
            SLEEP();            
            NOP();
            CLRWDT();
            //OPTION_REGbits.PS=2;        //longer off 72ms 12F675 code becomes:
            WDTCONbits.WDTPS=6;            //64ms
            setLED(0);
            SLEEP();            
            NOP();
        }        
    }
    return;
}
