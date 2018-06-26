#include <stdlib.h>
#include <stdio.h>
#include "sources/headers/calc.h"

/*
extern float add(float, float);
extern float deduct(float, float);
extern float multiply(float, float);
extern float divide(float, float);
*/

enum{
  Add = 1,
  Deduct, Multiply, Divide, Quit
};

int main(){
  char chosen_char[2];
  int chosen = 0;
  char operand1_char[11];
  char operand2_char[11];
  float operand1 = 0;
  float operand2 = 0;

  while(1){
    printf("1)Add\n2)Deduct\n3)Multiply\n4)Divide\n5)Quit\n\n?>");
    fgets(chosen_char, 2, stdin);
    chosen = atoi(chosen_char);
    if(chosen == Quit)
      return 0;

    printf("\nPlease, input operands:\n");
    while(getchar() != '\n');
    fgets(operand1_char, 11, stdin);
    fgets(operand2_char, 11, stdin);
    printf("op2ch: %s\n", operand2_char);
    //while(getchar() != '\n');
    operand1 = atof(operand1_char);
    operand2 = atof(operand2_char);
    printf("op2: %f\n", operand2);
    switch (chosen) {
      case Add:{
        printf("\n%f\n\n", add(operand1, operand2));
        break;
      }
      case Deduct:{
        printf("\n%f\n\n", deduct(operand1, operand2));
        break;
      }
      case Multiply:{
        printf("\n%f\n\n", multiply(operand1, operand2));
        break;
      }
      case Divide:{
        if(operand2 == 0.0)
          printf("Can't divide by zero\n\n");
        else
          printf("\n%f\n\n", divide(operand1, operand2));
        break;
      }
      default:{
        printf("Unknown command\n\n");
        break;
      }
    }
  }

  return 0;
}
