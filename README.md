# CS485 Assignment 3 - Threads
 - Author: Chris Humphreys
 - File: README.md
 - Date: 02/02/19

## Description
  This is my submission for assignment 3 in CS485.  This program consists of two
  distinct but separate modes that correspond with the questions posed in the 
  assignment.  For example, mode 1 meets the requirements of the first question
  while mode 2 is met by running the program in 2 mode.  Additionally, I have
  included two different files 1.txt and 2.txt which are sample outputs of each
  of these separate modes.
  
  Both of the modes demonstrate the creation of threads, their usage, and then
  their destruction after they are done being used.  In mode 2 mutual exclusion 
  is used as well.

## File List
 - Required:
   - main.c - Main driver of program.  Determines Mode to run in.
   - threads.c - Function definitions and implementations for demonstrating the 
               use of multi-threaded programs.
   - threads.h - Function declarations for threads.c.
   - Makefile - Instructions for building executable.
   - README.md - This file
 - Optional:
   - 1.txt - Sample output from running in mode 1.
   - 2.txt - Sample output from running in mode 2.
 
## Usage
 - To build:
   1. Download all Required files from above list.
   2. From command line navigate to folder containing above files.
   3. With all files in the same directory run `make`.
 - To run:
   1. For question 1 from homework run `./threads -1`.
   2. For question 2 from homework fun `./threads -2`.
   
## Design Decisions
  The biggest decision I made in terms of design for this program was making use
  of a struct to hold all of my threads different data and pass around the
  threads themselves using this struct.  This allowed me to be able to answer
  questions 1 and 2 from the homework using the same threads, just with
  different attributes. 
