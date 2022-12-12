#include <iostream>
#include <chrono>
#include <stdlib.h>    
#include <thread>
#include <vector>
#include "PQ.h"


using namespace std;

int main() {
   
    PQueue P;
    auto start = std::chrono::system_clock::now();
    P.minsert(10);
    auto end = std::chrono::system_clock::now();
    chrono::duration<float, std::milli> duration = end - start;
    cout << "Tiempo para insertar numeros " << duration.count() << " segundos " << endl;
    //P.print() ;
}
