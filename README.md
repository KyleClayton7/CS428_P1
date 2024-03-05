# Binghamton University, Spring 2024

## CS428 Project-1: Web Server

### SUMMARY

Webserver1 works as expected, handling requests one by one, and providing the correct file
Webserver2 handles a significant load (up to 20000 requests with 5 concurrent users)
To quit both servers, type quit (read in through cin)#

### NOTES, KNOWN BUGS, AND/OR INCOMPLETE PARTS

Webserver 2 will eventaully segfault under heavy load

### REFERENCES

https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html
https://www.geeksforgeeks.org/multithreading-in-cpp/ #

### INSTRUCTIONS

"g++ <webserver1or2> -o webserver" will compile both files, but the -std=c++11 option is required for std::thread compatibility in webserver2#

### SUBMISSION

I have done this assignment completely on my own. I have not copied it, nor have I given my solution to anyone else. I understand that if I am involved in plagiarism or cheating I will have to sign an official form that I have cheated and that this form will be stored in my official university record. I also understand that I will receive a grade of "0" for the involved assignment and my grade will be reduced by one level (e.g., from "A" to "A-" or from "B+" to "B") for my first offense, and that I will receive a grade of "F" for the course for any additional offense of any kind.

By signing my name below and submitting the project, I confirm the above statement is true and that I have followed the course guidelines and policies.

Submission date: 3/4/24

Team member 1 name: Jacob Helhoski

Team member 2 name (N/A, if not applicable): Kyle Clayton