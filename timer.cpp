#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "timer.hpp"

using namespace std;

void timer::getworkdur()
{
  int lepta;
  cout << "How many minutes of work do you want?" << endl;
  cin >> lepta;
  while(lepta <= 0 || lepta > 59)
     {
      if(lepta > 59)
      {
        cout << "Invalid input, give a work duration less than 59" << endl;
      }
      else if(lepta <= 0)
      {
        cout << "Invalid input, give a work duration more than 0" << endl;
      }
       cin >> lepta;
     }
  workdur = lepta;
}

void timer::getbreakdur()
{
  int lepta;
  cout << "How many minutes of break do you want?" << endl;
  cin >> lepta;
  while(lepta <= 0 || lepta > 59)
     {
       if(lepta > 59)
      {
        cout << "Invalid input, give a work duration less than 59" << endl;
      }
      else if(lepta <= 0)
      {
        cout << "Invalid input, give a work duration more than 0" << endl;
      }
       cin >> lepta;
     }
  breakdur = lepta;
}
timer::timer(int x,int y,int z,int s)
{
  workdur = x;
  breakdur = y;
  sessionsCompleted = z;
  totalWorkTime = s;
}
void timer::menouepilogis()
{
    string answer;
    cout << "Press 1 to start with the default settings." << endl;
    cout << "Press 2 to open duration settings." << endl;
    cout << "Press 3 to print statistics." << endl;
    cout << "Press 4 to exit the program" << endl;
    
    cin >> answer;
    while(answer != "1" && answer != "2" && answer != "3" && answer != "4")
      {
          cout << "Invalid input. Try Again" << endl;
          cin >> answer;
      }
    if(answer == "1")
    {
        startsession();
    }
}

void timer::clearscreen()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void timer::getStatistics()
{
  cout << sessionsCompleted << endl;
  cout << totalWorkTime << endl;
}

void timer::workcounting()
{
 int seconds = 0;
  int lepta = workdur;
  clearscreen();
  cout << "Work Time Remaining: " << endl;
  while(seconds >= 0 && lepta >= 0)
     { 
       printf("\r%02d:%02d", lepta, seconds);
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
}

void timer::breakcounting()
{
  int seconds = 0;
  cout << "Break Time Remaining:" << endl;
   
   while(seconds >= 0 && breakdur >= 0)
       { 
          printf("\r%02d:%02d", breakdur, seconds);
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

  workcounting();
  breakcounting();
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
