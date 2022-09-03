#include <iostream>
using namespace std;

namespace tuki
{
float pi=3.1416;

float area_triangulo(float b, float h) 
{ return (b*h)/2; }

float area_circulo(float r) 
{ return pi*r*r; }

float area_cuadrado(float l) 
{ return l*l; }

template < typename T > class vectorob
{
public:
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
};

int main() {
  tuki::vectorob<int> vectore;
  vectore.Insert(1);
  vectore.Insert(2);
  vectore.Insert(3);vectore.Insert(4);
  vectore.print();
  cout<<tuki::area_circulo(vectore.vector[0])<<endl;
  cout<<tuki::area_cuadrado(vectore.vector[1])<<endl;
  cout<<tuki::area_triangulo(vectore.vector[2],vectore.vector[3])<<endl;
}
