#include <stdlib.h>
#include <stdio.h>
#include "sources/headers/calc.h"
#include <dlfcn.h>

#define up_count 4

float p(float, float);

int count_so = 0;//количество библиотек

int main(){
  char library_name[80];//используется для ввода из терминала
  float (**fn)(float, float) = NULL;//массив с указателями на функции библиотек
  void **descriptors = NULL;//дескрипторы библиотек
  printf("Please, input  names of libraries one-by-one.\nTo break input 0 or empty line:\n\n");
  while(1){
    printf("?> ");
    fgets(library_name, 80, stdin);
    if((library_name[0] == '0' && library_name[1] == '\n') || library_name[0] == '\n')//пока не пустая строка или не ввел ноль
      break;
    if(count_so % up_count == 0)//добавляем по up_count элементов
      descriptors = realloc(descriptors, (count_so + up_count) * sizeof(void*));
    //чтобы убрать в конце перенос на новую строку для коректной передачи пути файла:
    for(int i = 0; library_name[i] != '\0'; i++){
      if(library_name[i] == '\n'){
        library_name[i] = '\0';
        break;
      }
    }

    descriptors[count_so++] = dlopen(library_name, RTLD_NOW);
  }
  //обработка ошибок open
  for(int i = 0; i < count_so; i++){
    if(!descriptors[i]){
      printf("Error with %d\n", i);
      fprintf(stderr,"dlopen() error: %s\n", dlerror());
 	   exit(1);
    }
  }

  char** all_names_func = NULL;//массив имен всех функций для вывода на экран
  int count_all_operators = 0;//число всех функций
  for(int i = 0; i < count_so; i++){
    int* count_func = (int*)dlsym(descriptors[i], "count_func");//количество функций в этой библиотеке
    char** names = (char**)dlsym(descriptors[i], "names");
    count_all_operators += *count_func;
    all_names_func = (char**)realloc(all_names_func, count_all_operators);
    fn = (typeof(fn))realloc(fn, count_all_operators);
    for(int j = 0; j < *count_func; j++){
      printf("%s\n", names[j]);
      all_names_func[count_all_operators - *count_func + j] = names[j];
  printf("checked\n");
      fn[count_all_operators - *count_func + j] = dlsym(descriptors[i], names[j]);
    }
    free(names);
    free(count_func);
  }

  char chosen_char[2];
  int chosen = 0;
  char operand1_char[11];
  char operand2_char[11];
  float operand1 = 0;
  float operand2 = 0;

  while(1){
    //меню:
    for(int i = 0; i < count_all_operators; i++)
      printf("%d) %s\n", i+1, all_names_func[i]);  
    printf("%d) Quit\n\n", count_all_operators + 1);

    fgets(chosen_char, 2, stdin);
    chosen = atoi(chosen_char);
    if(chosen == count_all_operators + 1)
      return 0;

    printf("\nPlease, input operands:\n");
    while(getchar() != '\n');
    printf("?> ");
    fgets(operand1_char, 11, stdin);
    printf("?> ");
    fgets(operand2_char, 11, stdin);
    operand1 = atof(operand1_char);
    operand2 = atof(operand2_char);
    //проверка на ввод
    if(chosen > count_all_operators || chosen < 1){
      printf("!>Missing range error. Try again.\n");
      continue;
    }
    else
      printf("->%f\n", fn[chosen - 1](operand1, operand2));
  }

  return 0;
}