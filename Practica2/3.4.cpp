#include <iostream>

using namespace std;

template < typename T > class vectorob
{
private:
T *vector;
int tam=0,mem_max=0, delta_mem; 
void Resize(){
  T* newArr = new T[delta_mem+mem_max];
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

void print(){
  for(int i=0;i<tam;i++){
    cout<<vector[i]<<" ";
  }
  cout<<endl;
}
void Insert(T elem){
if( tam == mem_max ) Resize(); 
vector[tam++] = elem; 
}

};

int main() {
  vectorob<float> tuki;
  tuki.Insert(1.523);
  tuki.Insert(2);
  tuki.Insert(3);
  tuki.print();
}
