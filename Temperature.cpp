/*
   Author: Garrett Wolfe
   Title: "Temperature Converter"
   Description: This program reads
     an integer value from the user and calls
     an assembly function that converts the
     input to celsius.

 * Data Abstraction:

   The following variables are initialized:
    - 3 ints, num0, num1, num2

 * Input:

   The user is prompted to enter a temperature
     in degrees fahrenheit.

 * Process:

   The assembly function convertTemp is called
      to convert the input to celsius, through
      a common formula. Using floating point
      operations in the stack, the appropriate
      calculations are performed and stored
      to the original variable.

 * Output:

   The program outputs the converted temperature
      to the user screen.

 * Assumptions:

   - It is assumed the user only will input one temperature.
   - It is assumed the user wants to convert Fahrenheit to Celsius.
   - It is assumed the user will correctly input the
      data.
 */

#include <iostream>
#include <iomanip>

using namespace std;

int num0 = 32, num1 = 5, num2 = 9;

void __declspec(naked) convertTemp(float scale, float&)
{
  __asm
  {
  START:
      push  ebp         //push ebp to stack
      mov   ebp, esp   //point esp to base pointer
      push  ebx       //push ebx to stack 

      mov   ebx, [ebp + 8]  //est. ebx to float addr
      
      finit                  //initialize FPU
      fld  DWORD PTR [ebx]  //push temp to front of stack
      fild  num0           //push 32.0 to front of stack
      fsub                //subtract temp - 32.0

      fild  num1         //push 5.0 to front of stack
      fild  num2        //push 9.0 to front of stack
      fdiv             //divide 5.0/9.0
      fmul            //multiply (temp-32.0) with 5.0/9.0

  DONE:
      fstp DWORD PTR [ebx] //store celsius to var in mem.
      pop  ebx            //pop ebx from stack
      pop  ebp           //pop ebp from stack
      ret               //return to calling code
  }
}

int main()
{
  cout << setprecision(1) << fixed;

  //Data Abstraction
  float process;

  //Input
  cout << "Please enter temperature in degrees Fahrenheit: ";
  cin >> process;
  cout << process;
  cout << " " << endl;

  //Process
  convertTemp(process);

  //Output
  cout << "The corresponding temperature in degrees Celsius is ";
  cout << process << endl;
  cout << " " << endl;

  return 0;
}