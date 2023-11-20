#include <unistd.h>
#include <iostream>
#include <fstream>
#include "timer.hpp"
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <string>
#include <limits>   


using std::cin,std::cout,std::endl,std::string;


timer::timer(int x,int y,int z,int s)   //constructor function, when the object is created, it gives the starting values in the class member variables.
{
  workdur = x;    // workdur = 25
  breakdur = y;   //breakdur = 5
  sessionsCompleted = z;  //sessionscompleted = 0
  totalWorkTime = s;      //totalworktime = 0
}
timer::~timer()
{

}


void timer::menouepilogis()  //this function, is the "hub" of the program. It controls all the functions,
{
    string answer;
    cout << "Press 1 to start with the default settings." << endl;
    cout << "Press 2 to open duration settings." << endl;
    cout << "Press 3 to print statistics." << endl;
    cout << "Press 4 to exit the program" << endl;
    
    cin >> answer;
    while(answer != "1" && answer != "2" && answer != "3" && answer != "4") //making sure the input is valid.
      {
          cout << "Invalid input. Try Again" << endl;
          cin >> answer;
      }
      clearscreen();
    if(answer == "1")       //if the answer is 1, it starts session with the default settings, 25 minutes work and 5 minutes break.
    {
        startsession();     //starts session.
    }
    else if(answer == "2")    //if the answer is 2, it gives you the opportunity to change them both, but also each one separately.
    {
        cout << "Press b to go back to menu" << endl << endl;
        cout << "Press 1 to change work duration only." << endl;
        cout << "Press 2 to change break duration only." << endl;
        cout << "Press 3 to change both work and break duration." << endl;
        

        string s;
        cin >> s;
        while(s != "1" && s != "2" && s != "3" && s != "b" && s != "B") //checking for valid input
        {
          cout << "Invalid inpput, try again" << endl;
          cin >> s;
          
        }
        if(s == "b" || s == "B")    //calls functions, depending on users choise.
        {
          clearscreen();
          menouepilogis();
        }
        else if(s == "1")
        {
          getworkdur();
          clearscreen();
          startsession();
        }
        else if(s == "2")
        {
          getbreakdur();
          clearscreen();
          startsession();
        }
        else
        {
          getworkdur();
          clearscreen();
          getbreakdur();
          clearscreen();
          startsession();
        }
    }
    else if(answer == "3")  //if answer is 3, it prints the statistics from the moment the user opened the app.
    {
      getStatistics();
    }
    else if(answer == "4")    //if answer is 4, it clears old data and closes the app.
    {
      clearscreen();
      cout << "Thanks for using this app." << endl;
      return;
    }
}

void timer::getworkdur()  //gets the work time and checks for valid input.
{
  clearscreen();
  int lepta;
  cout << "How many minutes of work do you want?" << endl;
  cin >> lepta;
  while(lepta < 1 || lepta > 59)
     {
      cin.clear();       
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid Input, try again." << endl;
      cin >> lepta;
      
     }
  workdur = lepta;  //after the value is stored in "lepta", im assigning it in workdur. (Workdur gets user's input).
}

void timer::getbreakdur()   //gets the break time and checks for valid input.
{
  int lepta;      //the variable "lepta" is local, which means it can only be accessed in this function. Thats how i can use it in getworkdur too without any problem.
  cout << "How many minutes of break do you want?" << endl;
  cin >> lepta;
  while(lepta < 1 || lepta > 59)
     {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid Input, try again." << endl;
      cin >> lepta;
     }
  breakdur = lepta;  //after the value is stored in "lepta", im assigning it in breakdur. (breakdur gets user's input).
}

void timer::startsession()  //startsession checks if a txt file named statistics.txt exists. If not, it creates one.
{
  ifstream destfile("Statistics.txt");
  if(!destfile.is_open())
  {
    cout << "There was a problem opening this text file." << endl;
    return;
  }
  destfile >> sessionsCompleted >> totalWorkTime;     //reads values into sessionscompleted and totalworktime. (starts with 0).
  destfile.close();                                   //closes the file.
  
  totalWorkTime = totalWorkTime + workdur;            //adds up the work time user chose.

  workcounting();   //starts session.
  
}


void timer::workcounting()
{
    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled
    noecho(); // Don't echo any keypresses
    keypad(stdscr, TRUE); // Enable the keypad
    nodelay(stdscr, TRUE); 
  int seconds = 0;
  int lepta = workdur;      //copies the workdur variable in another, so that i can make changes to it for the timer.
  bool paused = false;
 printw("Work Time Remaining: \n\n");
  while(lepta >= 0)
     { 
      int ch = getch();
        if (ch == 'p') {
            paused = !paused; //pause/unpause with the 'p' key.
        }

       if (!paused) {
            printw("\r        ");
            printw("\r%02d:%02d", lepta, seconds);    //displays the timer.
            refresh();

            if (seconds == 0) {
                lepta--;          //uses a extra variable named seconds, counts down until both workdur and seconds are 0.
                seconds = 59;
            } else {
                seconds--;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));   //waits for 1 second until it loops again.
        } 
        else 
        {
            printw("\rPAUSED");   //displays "PAUSED" until the user presses p again.
            refresh();
        }
     }
     endwin();                    //closes ncurses.
     cout << "End of work session." << endl;
  
  sessionsCompleted++;    //if it reaches this line of code, it means that timer was finished, so it adds 1 on sessionscompleted.
  sleep(2);     //waits for 2 seconds and calls the breakcounting function.
  breakcounting();
}

void timer::breakcounting()
{
  initscr();       // Initialize ncurses.
  cbreak(); // Line buffering disabled
  noecho(); // Don't echo any keypresses
  keypad(stdscr, TRUE); // Enable the keypad
  nodelay(stdscr, TRUE); 
  clear();         // clear old data from ncurses.
  int seconds = 0;
  printw("Break Time Remaining: \n\n");
   bool paused = false;
   while(seconds >= 0 && breakdur >= 0)
       { 
        int ch = getch();
        if (ch == 'p') {
            paused = !paused; // you can pause/unpause with the 'p' key.
        }

         if (!paused) {
            printw("\r        ");
            printw("\r%02d:%02d", breakdur, seconds);     //displays the timer.
            refresh();

            if (seconds == 0) {
                breakdur--;             //uses a extra variable named seconds, counts down until both breakdur and seconds are 0.
                seconds = 59;
            } else {
                seconds--;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));     //waits for 1 second until it loops again.
        } else {
            printw("\rPAUSED  ");
            refresh();
        }
        }
         cout << "End of break session." << endl;
        endwin();                               //ends ncurses.
 clearscreen();                                 //clears the screen.
 endsession();                                  //calls the endsession, to save statistics in the file.
  menouepilogis();                              //goes back to menu.
}

void timer::getStatistics()
{
  cout << "Press b to go back to menu" << endl << endl;
  cout << sessionsCompleted << endl;                      //this function prints 2 class member variables (statistics).
  cout << totalWorkTime << endl;
  string a;
  cin >> a;
  while(a != "b" && a != "B")                             //gets you back to menu by pressing "b".
  {
      cout << "Invalid input, try again." << endl;
      cin >> a;
  }
  clearscreen();
  menouepilogis();      //clears older data from screen and goes back to menu
}


void timer::endsession()    
{ 
  ofstream destfile("Statistics.txt");  
  if(!destfile.is_open())           //opens the file.
  {
    cout << "There was a problem opening this text file." << endl;
    return;
  }
  destfile << sessionsCompleted << endl;      //puts the statistics in the file.
  destfile << totalWorkTime;
  destfile.close();                           //closes the file.
}


void timer::clearscreen()  
{
  #ifdef _WIN32     //checks if the program is running from a Windows operating system.
    system("cls");  //if it does, it runs this command, which clears old data from the screen (runs only on windows).
  #else
    system("clear");  //if it is running from unix or macOS, it runs this command that does the same thing.
  #endif
}