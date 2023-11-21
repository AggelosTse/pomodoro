#include "timer.hpp"    

int main()
{
    timer t(25,5,0,0);  //using a constructor to initialize timer's variables (work time, break time, totalwork, sessionscompleted)
    t.menouepilogis();  //calling the menu function. (It controlls the flow of the app)
    return 0;           
} 



