#include <iostream>
#include <fstream>

using namespace std;

int width=0,height=0;
int ** R;
int** G;
int** B;

void inicializar(int** M,int h,int w){
  M=new int*[h];
  for(int i=0;i<h;i++){
    M[i]=new int[w];
  }
}

unsigned char* ReadBMP(char* filename){
  
    FILE* f = fopen(filename, "rb");
    if(f == NULL) cout<<"Archivo no especificado";
      
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, f); 
    width = *(int*)&header[18];
    height = *(int*)&header[22];

    int completar_fila = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[completar_fila];
    inicializar(R,height,width);
     inicializar(G,height,width);
     inicializar(B,height,width);
  
    unsigned char tmp;

    for(int i = 0; i < height; i++){
        fread(data, sizeof(unsigned char), completar_fila, f);
        for(int j = 0; j < width*3; j += 3){// Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;
            cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }
    }

    fclose(f);
    return data;
}

int main() {
  std::cout << "Hello World!\n";
  char* filename = "COLOR.bmp";
  ReadBMP(filename);
}
