#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct pixel {
  unsigned char R;
  unsigned char G;
  unsigned char B;
};

struct img {
  int width = 0, height = 0;
  int rowstep = 0;
  unsigned char *data;
  unsigned char header[54];
  pixel **rgb_data;

  img() {}
  img(char *filename) { ReadBMP(filename); }

  img(pixel **data, int width, int height) {
    this->rgb_data = data;
    this->width = width;
    this->height = height;
    this->rowstep = width * 3;
  }

  void ReadBMP(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
      cout << "Archivo no especificado";

    fread(header, sizeof(unsigned char), 54, f);
    width = *(int *)&header[18];
    height = *(int *)&header[22];

    rowstep = (width * 3 + 3) & (~3);
    unsigned char *data = new unsigned char[rowstep];
    unsigned char tmp;
    rgb_data = new pixel *[height];
    for (int i = 0; i < height; i++) {
      rgb_data[i] = new pixel[width];
    }
    for (int i = 0; i < height; i++) {
      int count = 0;
      fread(data, sizeof(unsigned char), rowstep, f);
      for (int j = 0; j < width * 3; j += 3) { // Convert (B, G, R) to (R, G, B)
        tmp = data[j];
        data[j] = data[j + 2];
        data[j + 2] = tmp;
        rgb_data[i][count].R = data[j];
        rgb_data[i][count].G = data[j + 1];
        rgb_data[i][count].B = data[j + 2];
        count++;
      }
    }
    fclose(f);
  }

  void write() {
    char *filename = "comprimido.bmp";
    FILE *aux = fopen(filename, "w");
    unsigned char *data;
    fwrite(header, sizeof(unsigned char), 54, aux);
    for (int i = 0; i < height; i++) {
      data = (unsigned char *)malloc(sizeof(char) * rowstep);
      for (int j = 0; j < width * 3; j += 3) {
        data[j] = rgb_data[i][j / 3].B;
        data[j + 1] = rgb_data[i][j / 3].G;
        data[j + 2] = rgb_data[i][j / 3].R;
      }
      fwrite(data, sizeof(unsigned char), rowstep, aux);
      free(data);
    }
    fclose(aux);
  }
};

struct quadtree_node {
  img value;
  quadtree_node *hijos[4];
  int ini_h = 0, fin_h = 0;
  int ini_w = 0, fin_w = 0;
  int w = 0, h = 0;
  // inicializar raiz
  quadtree_node(img filename) {
    value = filename;
    fin_w = value.width;
    fin_h = value.height;
    w = value.width;
    h = value.height;
  }
  quadtree_node(img padre, int ih, int fh, int iw, int fw, int wi, int he) {
    value = padre;
    ini_h = ih;
    ini_w = iw;
    fin_h = fh;
    fin_w = fw;
    w = wi;
    h = he;
  }

  pixel promedio() {
    int pr = 0, pg = 0, pb = 0;
    for (int i = ini_h; i < fin_h; i++) {
      for (int j = ini_w; j < fin_w; j++) {
        pr += (int)(value.rgb_data[i][j].R);
        pg += (int)(value.rgb_data[i][j].G);
        pb += (int)(value.rgb_data[i][j].B);
      }
    }
    pixel aux;
    aux.R = (unsigned char)(pr / (w * h));
    aux.G = (unsigned char)(pg / (w * h));
    aux.B = (unsigned char)(pb / (w * h));
    
    return aux;
  }

  pixel DE() {
    pixel prom = promedio();
    int pr = 0, pg = 0, pb = 0;
    for (int i = ini_h; i < fin_h; i++) {
      for (int j = ini_w; j < fin_w; j++) {
        pr += ((int)(value.rgb_data[i][j].R) - (int)prom.R) *
              ((int)(value.rgb_data[i][j].R) - (int)prom.R);
        pg += ((int)(value.rgb_data[i][j].G) - (int)prom.G) *
              ((int)(value.rgb_data[i][j].G) - (int)prom.G);
        pb += ((int)(value.rgb_data[i][j].B) - (int)prom.B) *
              ((int)(value.rgb_data[i][j].B) - (int)prom.B);
      }
    }
    pixel ruido;
    ruido.R = sqrt(pr / (w * h));
    ruido.G = sqrt(pg / (w * h));
    ruido.B = sqrt(pb / (w * h));
    return ruido;
  }
  void compresion() {
    pixel ruido = DE();
    pixel prom = promedio();
    for (int i = ini_h; i < fin_h; i++) {
      for (int j = ini_w; j < fin_w; j++) {
        int dR = abs((int)value.rgb_data[i][j].R - (int)prom.R);
        int dG = abs((int)value.rgb_data[i][j].G - (int)prom.G);
        int dB = abs((int)value.rgb_data[i][j].B - (int)prom.B);
        if (dR >= (int)ruido.R && dG >= (int)ruido.G && dB >= (int)ruido.B) {
          value.rgb_data[i][j].R = prom.R;
          value.rgb_data[i][j].G = prom.G;
          value.rgb_data[i][j].B = prom.B;
        }
      }
    }
  }
  bool quad() {
    if (w / 2 > 1 && h / 2 > 1) {
      hijos[0] = new quadtree_node(value, ini_h, (fin_h + ini_h) / 2, ini_w,
                                   fin_w / 2 + ini_w, w / 2, h / 2);
      hijos[1] = new quadtree_node(value, ini_h, (fin_h + ini_h) / 2, ini_w,
                                   fin_w / 2, w / 2, h / 2);
      hijos[2] = new quadtree_node(value, fin_h / 2 + ini_h / 2, fin_h, ini_w,
                                   fin_w / 2 + ini_w, w / 2, h / 2);
      hijos[3] = new quadtree_node(value, fin_h / 2 + ini_h / 2, fin_h, ini_w,
                                   fin_w / 2, w / 2, h / 2);
      hijos[0]->quad();
      hijos[1]->quad();
      hijos[2]->quad();
      hijos[3]->quad();
      hijos[0]->compresion();
      hijos[1]->compresion();
      hijos[2]->compresion();
      hijos[3]->compresion();
    }
    return true;
  }

  bool quad2(int deR, int deG, int deB) {
    pixel ruido = DE();
    if ((int)ruido.R > deR || (int)ruido.G > deG || (int)ruido.B > deB) {
      if (w / 2 > 1 && h / 2 > 1) {
        hijos[0] = new quadtree_node(value, ini_h, (fin_h + ini_h) / 2, ini_w,
                                     fin_w / 2 + ini_w, w / 2, h / 2);
        hijos[1] = new quadtree_node(value, ini_h, (fin_h + ini_h) / 2, ini_w,
                                     fin_w / 2, w / 2, h / 2);
        hijos[2] = new quadtree_node(value, fin_h / 2 + ini_h / 2, fin_h, ini_w,
                                     fin_w / 2 + ini_w, w / 2, h / 2);
        hijos[3] = new quadtree_node(value, fin_h / 2 + ini_h / 2, fin_h, ini_w,
                                     fin_w / 2, w / 2, h / 2);
        hijos[0]->quad2(deR, deG, deB);
        hijos[1]->quad2(deR, deG, deB);
        hijos[2]->quad2(deR, deG, deB);
        hijos[3]->quad2(deR, deG, deB);
        hijos[0]->compresion();
        hijos[1]->compresion();
        hijos[2]->compresion();
        hijos[3]->compresion();
      }
    }
    return true;
  }

  void dimensiones() {
    cout << "altura: " << fin_h - ini_h << endl;
    cout << "anchura: " << fin_w - ini_w << endl;
  }
};

struct quadtree {
  quadtree_node *root;

  quadtree(img filename) {
    root = new quadtree_node(filename);
    root->quad2(50, 50, 50);
    root->value.write();
  }
};

int main() {
  std::cout << "Hello World!\n";
  char *filename = "picture_compress.bmp";
  img mario(filename);
  quadtree Imagen(mario);
}
