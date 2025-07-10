# LibAudacious

Authors:              
===========

Kylie Bogar (k\_bogar2023@coloradocollege.edu)
Madeleine Johnson (m\_johnson2023@coloradocollege.edu)

Summary:
===========

LibAudacious is a library for manipulating functions and libraries before 
they are loaded into the user's program

Overview:
============

The current RTLD-Audit library allows an application the ability to be notified when various dynamic linking events occur and to work inside of these linking events to manipulate libraries and function calls. This program, however, has many known bugs and can be difficult to use. The purpose of LibAudacious is to allow an easier way to manage library loading and function wrapping without the user needing to use the RTLD-Audit code themself.

Usage Instructions:
============

The user must create their own buildfile with a buildinit() function that returns an int (typically 0). All wanted functions must be run in the buildinit function or else they will not be compiled and run until after the program's original libraries and functions are already loaded.  
