# COVID-Care-Campus-Managing-Testing-Confinement
Program for managing COVID-19 diagnostic tests and confinement of an academic community.

Project developed in the Code::Blocks IDE using the Windows API.

Project not portable to Unix-like systems.

NOTE: Rebuild the project to run properly.

## PROJECT OBJECTIVE
The aim is to develop a program to assist in managing COVID-19 diagnostic tests and confinement of members of the academic community affiliated with a particular course. It is assumed that this community will have a maximum of 200 members.

The program should record information regarding the members of the academic community, scheduled diagnostic tests, and their respective results. Tests can only be scheduled for members of the academic community who are registered in the program. When scheduling, the type of test (PCR or antigen) to be performed should be identified.
After conducting a previously scheduled test, the respective result should be recorded. If the result is inconclusive, a PCR test should be scheduled. The same should occur for positive results obtained from antigen tests.
A member of the academic community should be immediately placed in prophylactic isolation when obtaining a positive test result. If the test result is inconclusive, the member of the community should be placed in quarantine.
Members of the academic community may also be placed in isolation due to close contact with an infected individual. These cases are recorded by the user.

## FUNCTIONALITIES
• Display the following information in the main menu: number of community members, number of scheduled tests, number of tests conducted, and number of vaccinated members.

• Insert and list information regarding the members of the community. For each member, the number of tests conducted and information (type of test, date) of scheduled tests should also be listed.

• Record/update the vaccination status of a community member.

• Record/update the confinement status of a community member.

• Schedule a test, considering that a maximum of 15 PCR tests can be conducted in a single day.

• List data for all tests. For each test conducted, the result, time of testing, and duration should also be shown.

• Change the scheduled date for a test.

• Record the result of a previously scheduled test. All test information, along with the name and vaccination status of the community member who took the test, should be added to a log in a text file.

• Store (and read) information regarding the members of the academic community and scheduled tests in binary file(s).

• Display information for a selected test, including the following information about the respective member of the academic community: name, member type, and number of positive tests.

• Present the following statistical data: number of each type of member of the academic community, average duration of each conducted test, percentage of inconclusive tests, member(s) of the academic community with the fewest tests conducted, and most recent test(s) conducted.

• Present a list of confinement cases containing the following information: member of the academic community, type of confinement (quarantine or prophylactic isolation), date of confinement, and duration (in days).
