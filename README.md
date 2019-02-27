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

  For question 1, to resolve the race condition between the two threads, I added
  a mutex that would ensure that only one thread could be in the critical region
  at a time.  This was a simple matter of creating a mutex and then locking and
  unlocking it at the appropriate time.  You will also notice that the printing 
  for both happens after all the updating is done.  I intentionally left the 
  print statements out of the mutex as these are not areas that are not parts
  of the the critical regions of the threads.  It does make the output a little
  strange though in that the printing happens after the updates are done for 
  both threads.

  The biggest decision I made in terms of design for this program was making use
  of a struct to hold all of my threads different data and pass around the
  threads themselves using this struct.  This allowed me to be able to answer
  questions 1 and 2 from the homework using the same threads, just with
  different attributes.  While I wish I could say I thought of this, I have to
  admit that I relied heavily on the examples in the pthread man pages, which
  almost walked me through the whole thing. 
  
  I only had my threads update the totals 10 times each in order to maintain
  readability but this can be easily changed by updating line 18 of thread.c,
  and changing the value of MAX to whatever amount you would prefer.
