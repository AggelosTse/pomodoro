# Pomodoro CLI App (c++)

A lightweight, **Terminal-Based** productivity timer developed as a project for the **Department of Informatics and Telecommunications (DIT), University of Ioannina**. 

This is a pure Command Line Interface (CLI) application designed for developers and students who prefer staying in the terminal while working.

---

## Terminal Features

* **CLI Timer:** A real-time countdown clock rendered directly in your terminal.
* **Custom Durations:** Configure your work/break intervals via terminal prompts.
* **Persistent Logs:** Automated session tracking saved to `statistics.txt`.
* **Flow Control:** Support for **Pause/Unpause** functionality during active sessions.
* **Zero Dependencies:** Pure C++ logic—no heavy GUI libraries required.

---

## Installation & Compilation

1)Clone the repository with this command:

  'git clone https://github.com/AggelosTse/pomodoro.git'
  
2)navigate into the project's directory:

  cd pomodoro
  
3)Compile it with this command:

  g++ main.cpp timer.cpp -lcurses -o hello
  
4)Run it:
  if you have linux or macOS, write this command: ./hello
  
  if you have windows, write this command: hello.exe
