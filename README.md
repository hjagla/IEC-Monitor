# IEC-Monitor
Commodore IEC Monitor

Here is a simple Commodore IEC Monitor that I created. Not much time has been put into it and it is probably far from perfect and there are probably issues.

I am using an Ardunio Uno for communication and using Pin 4 for ATN, Pin 5 for Clock and Pin 6 for Data lines.

It will monitor the IEC bus for communication and will output HEX values of the data read to the Arduino Serial Port.

Output will appear in the following format:

(28 F0 ) 24
(3F )
(48 60 ) 01 81 40 00 00 90 88 A8 45 53 54 20 20 20 20 20 20 20 20 20 20 20 20 22 20 20 20 20 32 41 00 01 01 98 02 42 4C 4F 43 4B 53 20 46 52 45 45 2E 20 20 20 20 20 20 20 20 20 20 20 20 20 00 00 00
(5F )
(28 E0 3F )

Command sequences are encased in brackets "()" and data will be after.
