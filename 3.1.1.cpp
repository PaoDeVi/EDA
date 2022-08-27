#include <iostream>
#include <stdlib.h>

using namespace std;
//3.1.1//
int vector[100];
int tam=0;

void Insert(int elem){
if(tam < 100 ) 
vector[tam++] = elem; 
}

void print(){
  for(int i=0;i<tam;i++){
    cout<<vector[i]<<" ";
  }
  cout<<endl;
}
///////////////////////////////


int main() {
  Insert(1);
  Insert(2);
  print();
}