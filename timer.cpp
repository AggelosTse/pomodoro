#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "timer.hpp"

using namespace std;

timer::timer(int x,int y,int z,int s)
{
  workdur = x;
  breakdur = y;
  sessionsCompleted = z;
  totalWorkTime = s;
}
string timer::menouepilogis()
{
    string answer;
    cout << "Press 1 to change working duration. Default working duration: 25 minutes."<< endl;
    cout << "Press 2 to change break duration. Default break duration: 5 minutes." << endl;
    cout << "Press 3 to start with default settings. (Work:25 minutes, Break: 5 minutes)" << endl;
    cout << "Press 4 to change both working duration and break duration." << endl;
    cout << "Press 5 to display statistics." << endl;
    cout << "Press 6 to exit the program." << endl;
    
    cin >> answer;
    while(answer != "1" && answer != "2" && answer != "3" && answer != "4" && answer != "5" && answer != "6")
      {
          cout << "Invalid input. Try Again" << endl;
          cin >> answer;
      }
    return answer;
}

void timer::clearscreen()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void timer::set_work(int wd)
{
    workdur = wd;
}

void timer::set_break(int bd)
{
    breakdur = bd;
}

void timer::getStatistics()
{
  cout << sessionsCompleted << endl;
  cout << totalWorkTime << endl;
}

void timer::startsession()
{
  ifstream destfile("Statistics.txt");
  if(!destfile.is_open())
  {
    cout << "There was a problem opening this text file." << endl;
    return;
  }
  destfile >> sessionsCompleted >> totalWorkTime; 
  destfile.close();
  cout << workdur << endl;
  cout << totalWorkTime << endl;
  
  totalWorkTime = totalWorkTime + workdur;
  int seconds = 0;
  int lepta = workdur;
  clearscreen();
  cout << "Work Time Remaining: " << endl;
  while(seconds >= 0 && lepta >= 0)
     { 
       cout<< "\r" << (lepta < 10 ? "0" : "") << lepta << ":" << (seconds < 10 ? "0" : "") << seconds;
       cout.flush();
      // sleep(1);
       if(seconds == 0) 
          {
            lepta--;
            seconds = 59;
          } 
        else 
          {
            seconds--; 
          }
     }
  cout << endl << "End of work session." << endl;
  sessionsCompleted++;
  sleep(1.4);
   clearscreen();
   sleep(3);
   cout << "Break Time Remaining:" << endl;
   
   while(seconds >= 0 && breakdur >= 0)
       { 
          cout << "\r" << (breakdur < 10 ? "0" : "") << breakdur << ":" << (seconds < 10 ? "0" : "") << seconds;
          //sleep(1);
          if (seconds == 0) 
            {
              breakdur--;
              seconds = 59;
            } 
          else 
            {
              seconds--;
            }
        }
  clearscreen();
  cout << "End of break session." << endl;
}

void timer::endsession()
{ 
  ofstream destfile("Statistics.txt");
  if(!destfile.is_open())
  {
    cout << "There was a problem opening this text file." << endl;
    return;
  }
  destfile << sessionsCompleted << endl;
  destfile << totalWorkTime;
  destfile.close();
}
