#include <iostream>
#include <math.h>
#include <chrono>

typedef long long ll ; 

using namespace std;

ll distancia_euclideana(ll x,ll y,ll z,ll x1,ll y1,ll z1){
  ll distancia = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z-z1)*(z-z1));
  return distancia;
}

int main() {
  const int dimension = 10; 
  //1000
  auto start = std::chrono::system_clock::now();
  for(int i=1;i<dimension;i++){
    for(int j=1;j<dimension;j++){
      for(int k=1;k<dimension;k++){
          distancia_euclideana(0,0,0,i,j,k);
      }
    }
  }
  auto end = std::chrono::system_clock::now();
  
  chrono::duration<float,std::milli> duration = end - start;
  
  cout << duration.count() << " segundos " << endl;
  //10000
  const int dimension2 = 10; 
  auto start2 = std::chrono::system_clock::now();
  for(int i=1;i<dimension;i++){
    for(int j=1;j<dimension;j++){
      for(int k=1;k<dimension2;k++){
          distancia_euclideana(0,0,0,i,j,k);
      }
    }
  }
  auto end2 = std::chrono::system_clock::now();
  
  chrono::duration<float,std::milli> duration2 = end2 - start2;
  cout << duration2.count() << " segundos " << endl;
  //50000
  const int dimension3 = 50; 
  auto start3 = std::chrono::system_clock::now();
  for(int i=1;i<dimension;i++){
    for(int j=1;j<dimension;j++){
      for(int k=1;k<dimension3;k++){
          distancia_euclideana(0,0,0,i,j,k);
      }
    }
  }
  auto end3 = std::chrono::system_clock::now();
  
  chrono::duration<float,std::milli> duration3 = end3 - start3;
  cout << duration3.count() << " segundos " << endl;
}




