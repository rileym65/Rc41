This is a command line simulation of the HP-41CV calculator.  Note that this
is a functional simulation and not an emulation.  This does not emulate the
Nut processor nor does it use the HP-41cv OS.

This interprets the HP-41CV byte code table and will in theory perform the
same functions as the original calculator, including synthetic functions.
The internal memory and registers mimic the real calculator and operations
should produce the same effects in memory/registers as the real calculator.

This project is in very early development, most all functionality of the base
calculator as well as many functions from the HP-82143A printer and the
HP-82104A card reader have been implemented.

When using this simulation, you do need to think in terms of the operations
on the calculator, for example if you wanted to add 4 and 5 on the HP-41CV
you would hit these keys:

  <4> <ENTER^> <5> <+>

In this simulation you would enter this as:

  4 enter^ 5 +

All commands are available without needed XEQ for unkeyable commands (HMS for
example).  All commands can be used directly. so for instance you can do

  4.58 hms

As this is a command line simulation, 'user' mode does not exist, as there
are no keys to press.  Although I may add a keyboard simulation that would
allow for ASN'd keys, but for now this does not exist.

There is also no direct alpha mode,  merely entering a string in quotes will
place characters into the alpha register, for example:

  "HP-41CV"

Will place that string into the alpha register.

While the real calculator uses set input lengths for some functions, for
example STO requires 2 characters, that is not necessary here.  If you want
to store a value in registor 2, for example, you can do just:

  sto 2

Multiple commands can be done on a single line:

  rcl 3 rcl 4 * sto 5

While functions use RPN for arguments, function parameters always appear after
the function name.

Program mode is done simpley by typing:

  prgm

The prompt will change when in programming mode.  To exit programming mode
just type 'prgm' again.

