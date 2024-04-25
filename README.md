# operating_syst_sp24
Operating System Homework Assignment #2 Banker's Algorithm

*Coded on XCode

To measure whether or not a system of processes goes into deadlock, we can use the Banker's Algorithm to asses resources and processes. This main.cpp reads in a file table of processes with their numbers of allocation, max, and the available resources at time zero. After reading in the table, three respective vectors will be made in additon to a int need, int work, bool finish, and a vector of the completed processes in order. 

The Banker's Algorithm will loop through the number of processes and verify if the process has been finished. If the process has not been finished, the amount of each resource needed for the process to be completed is compared to the amount of each resource available in the available vector. If there is enough resources available for the process to run, the work vector will be updated with the now "completed" process' resources. Then the process number will be pushed back into the completed vector sequence and will be updated to true for the finish vector. Finally, if we get to the end of the loop and the bool variable found is false, that means no safe sequence was found. If no safe sequence is found, the system entered deadlock.


