#include "waittime.h"
#include <raylib.h>

WaitTimer::WaitTimer(float seconds){
    float starTime = GetTime();
    while(GetTime() - starTime < seconds);
}