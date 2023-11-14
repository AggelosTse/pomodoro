#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "timer.hpp"
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <string>
#include <limits>

using namespace std;


timer::timer(int x,int y,int z,int s)
{
  workdur = x;
  breakdur = y;
  sessionsCompleted = z;
  totalWorkTime = s;

  initscr(); // Initialize ncurses
  

}
timer::~timer()
{
  endwin();
}


void timer::menouepilogis()
{
    string answer;
    printw("Press 1 to start with the default settings. \n");
    printw("Press 2 to open duration settings. \n");
    printw("Press 3 to print statistics. \n");
    printw("Press 4 to exit the program \n");
    
    cin >> answer;
    while(answer != "1" && answer != "2" && answer != "3" && answer != "4")
      {
          printw("Invalid input. Try Again \n");
          cin >> answer;
      }
    if(answer == "1")
    {
        startsession();
    }
    else if(answer == "2")
    {
        clearscreen();
        printw("Press 1 to change work duration only. \n");
        printw("Press 2 to change break duration only. \n");
        printw("Press 3 to change both work and break duration. \n");
        string s;
        cin >> s;
        while(s != "1" && s != "2" && s != "3")
        {
          clearscreen();
          printw("Invalid inpput, try again \n");
          cin >> s;
        }
        if(s == "1")
        {
          getworkdur();
          startsession();
        }
        else if(s == "2")
        {
          getbreakdur();
          startsession();
        }
        else
        {
          getworkdur();
          getbreakdur();
          startsession();
        }
    }
    else if(answer == "3")
    {
      clearscreen();
      getStatistics();
    }
    else
    {
      clearscreen();
      endsession();
      printw("Thanks for using this app. \n");
      return;
    }
}


void timer::getworkdur()
{
  clearscreen();
  int lepta;
  printw("How many minutes of work do you want? \n");
  cin >> lepta;
  while(lepta < 1 || lepta > 59)
     {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      printw("Invalid Input, try again. \n");
      cin >> lepta;
     }
  workdur = lepta;
  clearscreen();
}


void timer::getbreakdur()
{
  clearscreen();
  int lepta;
  printw("How many minutes of break do you want? \n");
  cin >> lepta;
  while(lepta < 1 || lepta > 59)
     {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      printw("Invalid Input, try again. \n");
      cin >> lepta;
     }
  breakdur = lepta;
  clearscreen();
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
  
  printw("%d \n", workdur);
  printw("%d \n", totalWorkTime);

  printw("Press b to return to menu. \n");
  string a;
  cin >> a;
  while(a != "b" && a != "B")
  {
      printw("Invalid input, try again. \n");
      cin >> a;
  }
  clearscreen();
  menouepilogis();
}


void timer::workcounting()
{
    
  int seconds = 0;
  int lepta = workdur;
  bool paused = false;
  printw("Work Time Remaining: \n\n");
  while(seconds >= 0 && lepta >= 0)
     { 
      int ch = getch();
        if (ch == 'p') {
            paused = !paused; // Toggle pause/unpause with the 'p' key
        }

       if (!paused) {
            printw("\r        ");
            printw("\r%02d:%02d", lepta, seconds);
            refresh();

            if (seconds == 0) {
                lepta--;
                seconds = 59;
            } else {
                seconds--;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            printw("\rPAUSED  ");
            refresh();
        }
     }
     
  printw("End of work session.");
  sessionsCompleted++;
  clearscreen();
  sleep(1.4);
  breakcounting();
}


void timer::breakcounting()
{

  int seconds = 0;
   printw("Break Time Remaining: \n\n");
   bool paused = false;
   while(seconds >= 0 && breakdur >= 0)
       { 
        int ch = getch();
        if (ch == 'p') {
            paused = !paused; // Toggle pause/unpause with the 'p' key
        }

         if (!paused) {
            printw("\r        ");
            printw("\r%02d:%02d", breakdur, seconds);
            refresh();

            if (seconds == 0) {
                breakdur--;
                seconds = 59;
            } else {
                seconds--;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            printw("\rPAUSED  ");
            refresh();
        }
        }
        
  printw("End of break session.\n");
  clearscreen();
  menouepilogis();
}


void timer::startsession()
{
  clearscreen();
  ifstream destfile("Statistics.txt");
  if(!destfile.is_open())
  {
    printw("There was a problem opening this text file. \n");
    return;
  }
  destfile >> sessionsCompleted >> totalWorkTime; 
  destfile.close();
  printw("%d \n", workdur);
  printw("%d \n", totalWorkTime);
  
  totalWorkTime = totalWorkTime + workdur;
  clearscreen();
  workcounting();
}


void timer::endsession()
{ 
  ofstream destfile("Statistics.txt");
  if(!destfile.is_open())
  {
    printw("There was a problem opening this text file. \n");
    return;
  }
  destfile << sessionsCompleted << endl;
  destfile << totalWorkTime;
  destfile.close();
  clearscreen();
}
