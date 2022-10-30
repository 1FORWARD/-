#include "line_walking.h"
#include "control.h"

#define stand_x 130
#define P      35
#define P_N    40

int judge_line(uint8_t w,uint8_t h)
{
    if(h != 0 && w <= 25)
    {
        Go_Forward(45000);

        return 1;
    }
    else
    {
        Stop();

        return 0;
    }
}

void P_control(uint16_t x)
{
    int16_t error;
    error = stand_x - x;

    if(error < 0)
    {
       setpwm(5,9,200000,14222 + P_N*error);
    }
    else
     {
       setpwm(5,9,200000,14222 + (P*error) );
     }
        
}


