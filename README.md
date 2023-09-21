# Welcome to rent-a-bike repository

Project of the subject "Programming I" of the Degree in Computer Engineering: Interface for renting bicycles for users
Final grade of the subject: 18/20.

The goal is to develop a program in the C language to assist in the management of bike sharing used for commuting between campuses of the Polytechnic located in Leiria. 

The program records information regarding 15 bicycles, their users, and the loans made. When a user intends to borrow a bicycle, the program indicates the campus that they are at and the campus they want to go to. If there are available bicycles at the origin campus indicated by the user, the loan is immediately processed. Otherwise, the user is placed in a waiting queue. Upon reaching the destination campus, the user returns the bicycle. There are 5 campuses in Leiria: Residences, Campus 1, Campus 2, and Campus 5.

The application, was developed in the C language, and presents the user with a menu of options that provide the following functionalities: 
• Insert, consult, and list bicycle data. The number of loans, the number of malfunctions, and the total distance traveled should also be listed. 
• Insert, modify, consult, and list user data. The number of loans made and the total distance traveled should also be listed. 
• Record, consult, and list loan data and the waiting list. 
• Register the return of a bicycle. 
• Delete a loan request on the waiting list or change its destination campus. 
• Record a malfunction/repair of a bicycle. 
• Register the criteria for assigning bicycles to requests on the waiting list. The user should select one of the following criteria: order of request entry, by user type, or by distance to be traveled (between campuses). 
• List the data of the last bicycle used by a specific user (indicated by the user), as well as the loan history of that user. 
• List users in descending order of the number of loans made. 
• Display quantity quantity 
• Show, for each bicycle, the number of loans made between two dates (indicated by the user), the percentage of loans made by each type of user, the origin campus with the highest number of loans, and the number of users who used a specific bicycle (indicated by the user). 
• Store (and read) all information in binary file(s). 
• Add to a log in a text file the following information regarding each malfunction: bicycle designation, total distance traveled, date and time of the malfunction, and description of the malfunction.
• The program should display warning/error messages whenever necessary.

![P1_screenshoot](https://user-images.githubusercontent.com/64530615/178125951-85c78786-102b-4305-8921-9cae73b37857.jpg)
