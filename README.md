# CS_VO
# Wssel_Task

### To use this project you will need the following requirments

---
## Requirements

For development, you will only need g++ and a ncurses package in your environement.

### g++
- #### g++ installation on Windows

  Just go on (https://www3.cs.stonybrook.edu/~alee/g++/g++.html) and download the installer.

- #### g++ installation on Ubuntu

  You can install nodejs and npm easily with apt install, just run the following commands.

      $ sudo apt install g++

If the installation was successful, you should be able to run the following command.

    $ g++ --version
    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

###

## Install

    $ git clone https://github.com/Youssef11khaled99/Wssel_Task.git
    $ cd CS_VO

## Running the project

    $ g++ main.cpp -lncurses
    $ ./a.out sjf_dust2.txt // or any map path
    
   
## Debugging the project 

    $ g++ main.cpp -lncurses
    $ gdb ./a.out core
    (gdb) r sjf_dust2.txt // or any map path


