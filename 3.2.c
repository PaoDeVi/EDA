#include <stdio.h>
#include <stdlib.h>

struct vectorma{
  int *vector;
  int tam; 
  int mem_max; 
  int delta_mem;
};

void Resize(struct vectorma *pThis){
pThis->vector = realloc(pThis->vector, sizeof(int) * (pThis->mem_max + pThis->delta_mem));
pThis->mem_max += pThis->delta_mem;
}

void Insert(struct vectorma *pThis, int elem){
if(pThis->tam == pThis->mem_max )
Resize(pThis);
pThis->vector[pThis->tam++] = elem;
}

void print(struct vectorma *pThis){
  for(int i=0;i<pThis->tam;i++){
    printf("%d ",pThis->vector[i]);
  }
}


int main(void) {
  struct vectorma tuki;
  
  tuki.tam = 0;
  tuki.mem_max = 0;
  tuki.delta_mem = 10;
  Insert(&tuki,1);
  
  Insert(&tuki,2);
  Insert(&tuki,4);
  Insert(&tuki,5);
  print(&tuki);
  return 0;
}