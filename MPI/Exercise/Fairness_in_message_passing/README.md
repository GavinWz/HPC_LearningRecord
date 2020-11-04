# Task:

Write a program to test how fair the message passing implementation is. To do this, have all processes except process 0 send 100 messages to process 0. Have process 0 print out the messages as it receives them, using MPI_ANY_SOURCE and MPI_ANY_TAG in MPI_Recv. Is the MPI implementation fair?
