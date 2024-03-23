# calculator-in-Assembly
this is a calculator I wrote in Assembly and C to practice interactions between C and Assembly. 

The calculator works, and can handle rather simple equations such as 20+20. It can only handle somewhat more complex equiations like multiplication with decimals (10x0.1) and division with decimals. It also follows PEDMAS, so asking it to solve for e.g: 10x(10+10) will work.  

In assembly, I use xmm registers instead of integers to handle the decimals, and also storing data in xmm0 to return.

In C, the code looks quite complex, but it is easy if you break it down. Some of the functions are solely there just to handle user input and and PEDMAS system. The _Shunting Yard Algorithm_ and the _stack-based RPN evaluator_ takes up a lot of code in C, this can be found in the void infixToPostfix. 

Creating a program like this goes far beyond the point of assembly but I still found it very educational. If you would like to test this I suggest you download the files and make sure to change everything in C and assembly to your correct prefix. Then compiling it using GCC, like this:
```
gcc -c Calculator.s -o Calculator.o
gcc main.c Calculator.o -o calculator
```
