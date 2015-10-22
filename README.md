# ies
Self-adaptive examination system
The project was group effort to develop a prototype for an intelligent examination system to assess test takers’ knowledge. The intelligence is deduced from a self-adaptive algorithm (implemented in C++) that picks a question from a sorted repository based on current performance of the test taker. The system simulates a smart instructor by changing difficulty level of questions based on the correctness of answered questions, thereby enabling dynamic examination environment and scrutinizing test takers’ knowledge thoroughly.
Note: This is not working prototype at this moment. Some of the files are created and modified by the program internally and should not be moved/renamed/deleted by user.
About files used:
instructions.txt -> used by main.cpp to print necessary instructions before every test
pro_information.txt -> used by main.cpp to print proficiency score information after every test
mean.txt -> used by main.cpp to manage mean proficiency score of test taker
login.dat -> used by main.cpp to manage login credentials
