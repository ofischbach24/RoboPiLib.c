# RoboPiLib.c
This is an experimental C wrapper for RoboPiLib.py for the RoboPi from Mikronauts, USE WITH CAUTION!!!!!

Please read the documentation provided by Mikronauts before use, make sure to have read through the original RoboPiLib.py file. 

This should be able to be included with

  #include <RoboPiLib.h>

To use this code navigate to RoboPiLib.c and compile it using 

gcc -shared -o libRoboPiLib.so -fPIC RoboPiLib.c -lpython3.7m
