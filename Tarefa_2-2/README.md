# Assignment 2.2 - Process Priority

### Description of the assignment

Create a program that generates two children processes. Thus, making a total of 3 processes: parent, children 1, and children 2. The parent process has its priority set to 0 and must read from two analog inputs of the BeagleBone (AD1 and AD2) at each interval of 500ms.
If AD1 has a voltage greater than 1V, set the priority of children 1 to 19. Otherwise, set it to 5.
If AD2 has a voltage greater than 1V, set the priority of children 2 to 19. Otherwise, set it to 5.
Both processes children 1 and 2 must run an infinite loop which executes a load() function. This function should take approximately 1s. 
When there is an even iteration, both children processes should light up its respective LED.
When there is an odd iteration, both children processes should turn off its respective LED.

**Material needed**
- 02 LEDs
- 02 Potenciometers
- 02 Resistors
- BeagleBone Black rev-C kit


### Our implementation

You can check it out the implementation completely functional in the following YouTube video:https://youtu.be/EkfnhGqGNaw

And, of course, the source code is here inside this folder.
