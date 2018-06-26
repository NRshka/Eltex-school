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
  int chosen = 0;
  float operand1 = 0;
  float operand2 = 0;
  while(1){
    printf("1)Add\n2)Deduct\n3)Multiply\n4)Divide\n5)Quit\n\n?>");
    scanf("%d", &chosen);

    if(chosen == Quit)
      return 0;

    printf("\nPlease, input operands:\n");
    switch (chosen) {
      case Add:{
        scanf("%f%f", &operand1, &operand2);
        printf("\n%f\n\n", add(operand1, operand2));
        break;
      }
      case Deduct:{
        scanf("%f%f", &operand1, &operand2);
        printf("\n%f\n\n", deduct(operand1, operand2));
        break;
      }
      case Multiply:{
        scanf("%f%f", &operand1, &operand2);
        printf("\n%f\n\n", multiply(operand1, operand2));
        break;
      }
      case Divide:{
        scanf("%f%f", &operand1, &operand2);
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
