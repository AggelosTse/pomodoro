#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "timer.hpp"
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <string>

using namespace std;

bool timer::checkifnumber(string n)
{
    for (char c : n) {
        if (!isdigit(c)) {
            return false;
        }
}
return true;
}

void timer::getworkdur()
{
  string lepta;
  cout << "How many minutes of work do you want?" << endl;
  cin >> lepta;
  while((lepta <= "1" || lepta > "59") && (!checkifnumber(lepta)))
     {
      cout << "Invalid Input, try again." << endl;
      cin >> lepta;
     }
  workdur = stoi(lepta);
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
    else if(answer == "2")
    {
        cout << "Press 1 to change work duration only." << endl;
        cout << "Press 2 to change break duration only." << endl;
        cout << "Press 3 to change both work and break duration." << endl;
        string s;
        cin >> s;
        while(s != "1" && s != "2" && s != "3")
        {
          cout << "Invalid inpput, try again" << endl;
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
      getStatistics();
    }
    else
    {
      endsession();
      cout << "Thanks for using this app." << endl;
      return;
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

  cout << "Press b to return to menu." << endl;
  string a;
  cin >> a;
  while(a != "b" && a != "B")
  {
      cout << "Invalid input, try again." << endl;
      cin >> a;
  }
  menouepilogis();
}

void timer::workcounting()
{
    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled, Pass on everything to me
    noecho(); // Don't echo any keypresses
    keypad(stdscr, TRUE); // Enable the keypad
    nodelay(stdscr, TRUE); // Set getch() to non-blocking mode
  int seconds = 0;
  int lepta = workdur;
  bool paused = false;
  cout << "Work Time Remaining: " << endl;
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
     endwin();
  cout << endl << "End of work session." << endl;
  sessionsCompleted++;
  sleep(1.4);
}

void timer::breakcounting()
{
  initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled, Pass on everything to me
    noecho(); // Don't echo any keypresses
    keypad(stdscr, TRUE); // Enable the keypad
    nodelay(stdscr, TRUE); // Set getch() to non-blocking mode

  int seconds = 0;
  cout << "Break Time Remaining:" << endl;
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
        endwin();
  cout << "End of break session." << endl;
  menouepilogis();
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
