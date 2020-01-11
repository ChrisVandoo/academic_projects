-------------------------------------------------------------------------------
    Introduction
-------------------------------------------------------------------------------
    This program was created by Chris VanDoodewaard. It was written to fulfill 
    the specifications outlined in Assignment 2 of CIS 2520 (Data Structures). 
    This program was completed on October 27, 2019. All components of this 
    program are written in the C language.

-------------------------------------------------------------------------------
    Functionality
-------------------------------------------------------------------------------
    -parses a text file into words, using whitespaces and punctuation as word
    deliminators
    -employs a linked list to store each word of the text file as well as any
    punctuation, ensuring that the formatting of the text file is preserved
    -allows a user to search for a specific word in the text file, returning
    any matching values 
    -allows the user to enter a start and end paramter and returns a copy of 
    all text inbetween those two points (picks the first occurence of the 
    start parameter)
    -implements a merge sort algorithm to sort every word in the text file
    -is able to remove all repeated words in the text file, and return this
    list to the user
    -counts the total number of words in the text file, and can also count 
    every unique word in the document

-------------------------------------------------------------------------------
    Other
-------------------------------------------------------------------------------
    This project was graded using an automated testing suite, hence the lack of 
    a main(), and other user interface related functionality.

    Due to time constraints, simplifying assumptions were made about what a word 
    is as well as reproducing the formatting of the text document (this was 
    outlined in the assignment requirements).
