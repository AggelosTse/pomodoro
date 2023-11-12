#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "timer.hpp"
#include <ncurses.h>

using namespace std;

int getworkdur()
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
  return lepta;
}

int getbreakdur()
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
  return lepta;
}

string apantisi(string text)
{
    while(text != "Y" && text != "N" && text != "y" && text != "n")
       {
           cout << "Invalid input, try again (Y/N)" << endl;
           cin >> text;
       }
    return text;
}

int main()
{
    timer t(25,5,0,0);
    int wo,br,plithosYES = 0;
    string k,ap,s; 
    cout << "Do you want to start a session?  (Y/N)" << endl;
    cin >> s;
    ap = apantisi(s);
    t.clearscreen();
    while(ap == "Y" || ap == "y") 
      {
        plithosYES++;
        k = t.menouepilogis();
        t.clearscreen();
        if(k == "1")
          {
             wo = getworkdur();
             t.set_work(wo);
          }
        else if(k == "2")
          {
             br = getbreakdur();
             t.set_break(br);
          }
        else if(k == "3")
          {
             wo = 25;
             br = 5;
             t.set_work(wo);
             t.set_break(br);
          }
        else if(k == "4")
          {
            wo = getworkdur();
            br = getbreakdur();
            t.set_work(wo);
            t.set_break(br);
          }
        else if(k == "5")
          {
            t.getStatistics();
            t.menouepilogis();
          }
          else
          {
            return 0;
          }
        t.startsession();
        t.endsession();
        cout << "Do you want to start another session?  (Y/N)" << endl;
        cin >> s;
        ap = apantisi(s);
        t.clearscreen();
      }
      if(ap == "N" || ap == "n")
        {
          if(plithosYES > 0)
          {
            cout << "All the statistics are uploaded in a txt file called Statistics.txt" << endl;  
            return 0;
          }
          else
          {
            return 0;
          }  
        }
}



