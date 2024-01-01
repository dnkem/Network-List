Name: Danielle Nkem Ebende
Student #: 101218592
Course: COMP 2404 - Fall
Assignment: #3

List of Files Provided: 
    Cellphone.cc & Cellphone.h
    Control.cc & Control.h
    defs.h
    Entity.cc & Entity.h
    List.cc & List.h
    Location.cc && Location.h
    main.cc
    Makefile
    Message.cc & Message.h
    Network.cc & Network.h
    test.cc
    TestControl.cc & TestControl.h
    Tester.h & Tester.cc
    Tower.cc & Tower.h
    View.cc & View.h
    README.txt
    2404 - A3 UML Diagram

Program Description: 
    Here I implemented an application for a CellPhone carrier. This tracks CellPhones and the Towers that they connect and send Messages through. We specifically track Messages & conversations between customers via Towers. There's also the ability to change the location of a CellPhone user.

Compilation and Execution Instructions:
    Compiling is all done by the Makefile. To use it, type "make" into your terminal at the "a2"
    folder level. There you will get an executable. Next, type in "./a2" to test the Control.cc that I made, or
    type "./a2test" to use the given inputs to test. There you can test any of the features by entering a number, 1 through 7 for "./a2",
    and 1 through 9 for "./a2test" and exit via entering 0.
    EXTRA: To clear your .o files to late compile freshly, enter "make clean".

TO CHECK:
    - check mem leaks