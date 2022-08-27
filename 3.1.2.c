#include <stdio.h>
#include <stdlib.h>

const int aux_mem=16;

//3.1.2//
int *vector2 = NULL; 
int tam2 = 0; 
int mem_size = 0; 

void resize(){
  vector2 = realloc(vector2, sizeof(int) * (mem_size + aux_mem));
  mem_size += aux_mem; 
}

void dynamic_insert(int elem){
  if(tam2==mem_size){
    resize();
  }
  vector2[tam2++] = elem;
}

void print(){
  for(int i=0;i<tam2;i++){
    printf("%d ",vector2[i]);
  }
  printf("\n");
}
int main(void) {
  dynamic_insert(4);
  dynamic_insert(5);
  dynamic_insert(6);
  dynamic_insert(7);
  print();
  
  return 0;
}