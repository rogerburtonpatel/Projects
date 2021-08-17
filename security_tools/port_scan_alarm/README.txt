Roger A. Burtonpatel 
6/21/2021 
README.txt for alarm.py 

ASSIGNMENT PROGRESS//PROGRAM CHANGELOG
6.14.2021 
          Began alarm.py planning and early implementation. Much online 
          research and Piazza consultation begins. Installed and updated
          python3, scapy, etc. 
6.19.2021 
          Discussed alarm.py with Steven Fugelsang, who shared some parts 
          of his implementation with me. Full credit to him for base64 
          decoding and general python help. Created a rough shell of the 
          program with flag reading and message printing. Still very messy, 
          and scapy wasn't working well on Linux. 
6.21.2021
          Implemented most of alarm.py with help from Ming Chow and Steven. 
          Some debugging with my girlfrend, Evelyn. Decided to re-install 
          scapy on Windows instead of fighting with low-level bugs on my 
          WSL and was met with success. 
6.22.2021 
          Final changes before submission included reading variations of 
          "Nikto" from a list using a built-in python command, distinguishing
          (critically) between FIN flags and XMAS flags, and removing old 
          test functions. Program submitted with README at 
          04:21 EST, 6.22.2021. 
    
6.29.2021 
          Deleted an extra space that was causing program to not read 
          plain-text username/password due to python line-split. 

README Questions

0. Identify what aspects of the work have been correctly implemented and what 
    have not.
        I believe all aspects of the program have been correctly implemented. 
        I have had trouble running the program on an IP address on my device; 
        however, others testing my program on their devices leads me to 
        beleive that this is functional. 

1. Identify anyone with whom you have collaborated or discussed the assignment.
        I talked a good bit with Steven Fugelsang about how to start thinking 
        about the assignment and how to use python. As a return favor, I helped 
        him with Lab 3 Question 6. I hope this type of collaboration is OK 
        in the class; there was no breach of academic integrity and all work 
        has been cited to its proper owner. 

        Professor Ming Chow provided immense insight via Piazza and advance 
        grading. 

        Evelyn Miller-Nuzzo taught me some basics of python indentation rules. 

        Sarah Fomchenko and Candan Iuliano answered some questions on Piazza, 
        as did several other anonymous classmates. 

        Lastly, I consulted a breadth of online documentation for this (and 
        all projects) to lift its wings. 

2. Say approximately how many hours you have spent completing the assignment.
        Not including research, about 5 hours (mostly debugging). 
        Including research, about 15 hours. I understand port scanning much 
        more acutely now. 

3. List any additional dependencies used.

    As stated above, many, many online resources, IBNLT: 
        - python documentation 
        - (sub-par) scapy documentation 
        - Github 
        - S.O. (of course)
        - cnblogs, techbeamers, and many others. 

4. Address the following questions:

a. Are the heuristics used in this assignment to determine incidents 
"even that good"?
    They're OK for finding skiddies and anyone else looking to do a sweep of 
    your system. That said, there are definitely more 'under-the-rug' scanning
    and attacking methods that will not be susceptible to crude technology. At 
    the end of the day, I might use this tool to show off some ability to 
    detect a scan, but defending against one is a different story. 

b. If you have spare time in the future, what would you add to the program 
or do differently with regards to detecting incidents? 

    I might implement a password-cracking detector, which would scan for many 
    attempts at login from another device. It could also be interesting to 
    see the transfer of hashed passwords over a network, at which point we 
    could pipe this tool into a cracking tool or decrypter. Lastly, if there
    were a way to see from where a LIVE attack were happening (not sure if 
    possible but worth exploring), that could be invaluable to locating 
    low-profile scammers and attackers. 