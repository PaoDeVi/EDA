#include <iostream>

using namespace std;

class vectorob
{
private:

int *vector, tam=0,mem_max=0, delta_mem; 
void Resize(){
  int* newArr = new int[delta_mem+mem_max];
  for(int i=0;i<mem_max;i++){
    newArr[i] = vector[i];
  }
    delta_mem+=mem_max;
    vector = newArr;
  delete [] newArr;
} 

public:
vectorob(int delta_mem = 10){
  this->delta_mem = delta_mem;
} 

void Insert(int elem){
if( tam == mem_max ) Resize(); 
vector[tam++] = elem; 
}

void print(){
  for(int i=0;i<tam;i++){
    cout<<vector[i]<<" ";
  }
  cout<<endl;
}
};


int main() {
  vectorob tuki;
  tuki.Insert(1);
  tuki.Insert(2);
  tuki.Insert(3);
  tuki.print();
}