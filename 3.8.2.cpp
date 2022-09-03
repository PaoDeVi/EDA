#include <iostream>

using namespace std;

typedef float (*lpfnOperation)(float, float);

float Addition(float a, float b){
  return a+b;
}

float Subtraction(float a, float b){
  return a-b;
}

float Multiplication(float a, float b){
  return a*b;
}

float Division(float a, float b){
  return a/b;
}

int main(){
  lpfnOperation vpf[4] = {&::Addition, &::Subtraction,
&::Multiplication, &::Division};

float a, b, c;
int opt;

cin>>a>> b;

cin>>opt;

c = (*vpf[opt])(a, b);

cout<<c<<endl;
}