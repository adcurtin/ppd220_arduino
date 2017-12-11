# ppd220 display testing

this probably works with most alpha signs. I used the ASCII format, since I used a dump from alphanet 3 and that's what it used, and it's a little easier once you see how it works.
the code has comments explaining most commands

hardware was real simple, just a max232 between the micros serial and the ppd220
I don't read anything from the display, so I don't hook up the RX line of the micro (it also can interfere with programming)

