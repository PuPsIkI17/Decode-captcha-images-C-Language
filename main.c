//Vadim Pislari 313CB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_header.h"
#define N 100

// functie care verifica daca punctul este unul de inceput pentru un numar
int verificare(int pz_h[N], int pz_w[N],int h, int w,int cite){
int i=0;
    for (i = 0; i < cite; i++){
        if(pz_h[i] == h && pz_w[i] == w) return 1;
    }
return 0;
}

int main(){

//se deschide file-ul input.txt
//cifre[N][N] este matricea imaginii formata din 0 e punct incolor iar restul 1
//cifris[N][N] la fel este o matrice modificata pentru task-ul 3
int i = 0, j = 0, k,l, cifre[N][N],cifris[N][N];

//variabile utilizate la determinarea numelui fisierului output
char name[N], out_name[N],out_name_ts2[N],out_name_ts3[N],
     ou_ts1[N] = "_task1.bmp", ou_ts2[N] = "_task2.txt",
     ou_ts3[N] = "_task3.bmp";

int r_foto, g_foto, b_foto;

FILE *input = fopen("input.txt", "r");

if (input == NULL){
    printf("input error");
    return -1;
}

fscanf(input, "%s", name);
fscanf(input, "%d%d%d", &r_foto, &g_foto, &b_foto);

//se citesc numerele excluse pentru task-ul 3
char aux;
int cite_numere=0, numere_excluse[11];

fscanf(input,"%c%c", &aux,&aux);

//verificarea daca exista vreun numar
if (aux!='\n'){

    //cast la primul nr gasit
    numere_excluse[0] = aux - '0';

    cite_numere++;
    fscanf(input,"%c",&aux);
    //citirea tuturor numerelor urmatoare
    while(aux!= '\n'){
            fscanf(input,"%d%c", &numere_excluse[cite_numere], &aux);
            cite_numere++;
            }
    }

char f_bonus[N],bonus[N], ad_bonus[]="_bonus.bmp";
//file-ul binusul
fscanf(input,"%s", f_bonus);

fclose(input);

//se formeaza file-ul cu sfirsitul _task1.bmp pentru task-ul 1
while(name[i] != '.'){
    out_name_ts3[i] = name[i];
    out_name_ts2[i] = name[i];
    out_name[i] = name[i];
    i++;
}

out_name_ts3[i]='\0';
out_name_ts2[i]='\0';
out_name[i]='\0';

i=0;
// se formeaza fileul output pentru bonus
while(f_bonus[i] != '.'){
    bonus[i] = f_bonus[i];
    i++;
}

bonus[i]='\0';

strcat(out_name,ou_ts1);
strcat(out_name_ts2,ou_ts2);
strcat(out_name_ts3,ou_ts3);
strcat(bonus,ad_bonus);

// se deschid imaginile
FILE *in = fopen(name, "rb");
FILE *out = fopen(out_name, "wb");

if(in == NULL) {
        printf("in error");

        return -1;
}

if (out == NULL) {
    printf("out error");
    return -1;
}

FILEHEADER file;
INFOHEADER info;
struct Pix source_pix;
//tak 3 memorizeaza culorile
struct Pix color[N][N];


int padding;

//se citesc datele din input
fread(&file,sizeof(FILEHEADER),1, in);
fread(&info,sizeof(INFOHEADER),1, in);

//se scriu datele catre output
fwrite(&file, sizeof(FILEHEADER), 1, out);
fwrite(&info, sizeof(INFOHEADER), 1, out);


padding =  (4 - (info.width * sizeof(Pix)) % 4) % 4;

// se trece peste linii
for (i = 0; i < info.height; i++){

    // se trece peste coloane
    for (j = 0; j < info.width; j++){

        // se citeste rgb de la fiecare pixel
        fread(&source_pix, sizeof(Pix), 1, in);

        //se modifica fiecare pixel daca nu are culoarea alba
        if( source_pix.B!= 255 && source_pix.G != 255
            && source_pix.R != 255 ){
                color[i][j].B = source_pix.B;
                color[i][j].G = source_pix.G;
                color[i][j].R = source_pix.R;
                source_pix.B = r_foto;
                source_pix.G = g_foto;
                source_pix.R = b_foto;
                cifre[i][j] = 1;
                cifris[i][j] = 1;
        }
        else {
                cifre[i][j]=0;
                cifris[i][j]=0;
        }
        // se scrie pixelul
        fwrite(&source_pix, sizeof(Pix), 1, out);
    }

    // se trece peste padding
    fseek(in, padding, SEEK_CUR);

    // paddingul pe 0
    for ( k = 0; k < padding; k++)
    {
        fputc(0, out);

    }
}

fclose(out);
fclose(in);

// se verifica cifra 1 si daca se gasete se translateaza
//cu 4 casute pentru  a se forma
// 1 0 0 0 0
// 1 0 0 0 0
// 1 0 0 0 0
// 1 0 0 0 0
// 1 0 0 0 0

for(i = 0; i != info.height; i++){
    for(j = 0; j != info.width; j++){
        //verificarea daca e cifra 1
        if(cifre[i][j] == 1 && cifre[i + 1][j] == 1 && cifre[i + 2][j] == 1  &&
        cifre[i + 3][j] == 1 &&  cifre[i + 4][j] == 1 && cifre[i][j + 1] == 0
        && cifre[i][j - 1] == 0 && cifre[i + 2][j - 1] == 0 &&
        cifre[i + 4][j - 1] == 0){

            //mutarea la prima matrice
            cifre[i][j] = 0;
            cifre[i + 1][j] = 0 ;
            cifre[i + 2][j] = 0;
            cifre[i + 3][j] = 0;
            cifre[i][j - 4] = 1;
            cifre[i + 1][j - 4] = 1;
            cifre[i + 2][j - 4] = 1;
            cifre[i + 3][j - 4] = 1;
            cifre[i + 4][j - 4] = 1;

            //mutarea la 2 matrice
            cifris[i][j] = 0;
            cifris[i + 1][j] = 0 ;
            cifris[i + 2][j] = 0;
            cifris[i + 3][j] = 0;
            cifris[i][j - 4] = 1;
            cifris[i + 1][j - 4] = 1;
            cifris[i + 2][j - 4] = 1;
            cifris[i + 3][j - 4] = 1;
            cifris[i + 4][j - 4] = 1;

        }
    }
}

//se seteaza indicele de unde incep cifrele
// se utilizeaza pentru determinarea cuorii
int poz_color_w[N], poz_color_h[N],v=0;
for(j = 0; j != info.width; j++){
    for(i = info.height-1; i >=0; i--){
        if(cifris[i][j]==1){
                if( cifris[i-1][j] == 1 && cifris[i-2][j] == 1  && cifris[i - 3][j] == 1 &&
                cifris[i - 4][j] == 1 && cifris[i][j + 1] == 0 && cifris[i][j - 1] == 0 &&
                cifris[i - 2][j - 1] == 0 && cifris[i - 4][j - 1] == 0){
                    printf("da ");
                    poz_color_h[v]=i;
                    poz_color_w[v]=j+4;
                }
                else{
                    poz_color_h[v]=i;
                    poz_color_w[v]=j;
                }
                v++;
                for(k = 0;k != 5; k++)
                    for(l = 0; l != 5; l++){
                            cifris[i - k][j + l]=0;
                        }
                }
        }
}

v=0;

//se creaza o mini matrice numar in care se vor copia toate numerele
int numar[N][5][5],z = 0;

int poz_w[N], poz_h[N];
//pentru taskul 3 memorizeaza pozitia
for(i = 0; i != info.width; i++){

    for(j = info.height; j >= 0; j--){

        if(cifre[j][i] == 1 ) {

            // copierea numerelor
            poz_h[v]=j;
            poz_w[v]=i;
            v++;
                for(k = 0; k != 5; k++){
                    for(l = 0; l != 5; l++){
                        numar[z][k][l] = cifre[j - k][i + l];
                        cifre[j - k][i + l]=0;

                    }
                }
            z++;
        }
    }
}


FILE *txt=fopen(out_name_ts2,"w");

int scr_nr[N];
k=0;
//se gaseste cifra necesara
for(i = 0; i != z; i++){

    //0
    if(numar[i][1][0] == 1 && numar[i][4][0] == 1 &&
       numar[i][0][3] == 1 && numar[i][2][2] == 0)
        scr_nr[k]=0;

    //1
    if(numar[i][1][0] == 1 && numar[i][4][0] == 1 && numar[i][0][1] == 0)
        scr_nr[k]=1;

    //2
    if(numar[i][1][0] == 0  && numar[i][3][4] == 0 && numar[i][0][1] == 1)
        scr_nr[k]=2;

    //3
    if(numar[i][1][0] == 0  && numar[i][3][4] == 1 &&
       numar[i][2][0] == 1 && numar[i][0][1] == 1)
        scr_nr[k]=3;

    //4
    if(numar[i][1][0] == 1  && numar[i][4][0] == 0 && numar[i][0][1] == 0)
        scr_nr[k]=4;

    //5
    if(numar[i][1][0] == 1  && numar[i][3][0] == 0 &&
       numar[i][1][4] == 0 && numar[i][2][0] == 1 && numar[i][0][1] == 1)
        scr_nr[k]=5;

    //6
    if(numar[i][1][0] == 1  && numar[i][3][0] == 1 &&
       numar[i][1][4] == 0 && numar[i][2][0] == 1 && numar[i][0][1] == 1)
        scr_nr[k]=6;

    //7
    if(numar[i][1][0] == 0  && numar[i][3][4] == 1 &&
       numar[i][2][0] == 0 && numar[i][0][1] == 1)
        scr_nr[k]=7;

    //8
    if(numar[i][1][0] == 1 && numar[i][4][0] == 1 &&
       numar[i][0][3] == 1 && numar[i][2][2] == 1 &&
       numar[i][3][0] == 1 && numar[i][1][4] == 1)
        scr_nr[k]=8;

    //9
    if(numar[i][1][0] == 1  && numar[i][3][0] == 0 &&
       numar[i][1][4] == 1 && numar[i][2][0] == 1 && numar[i][0][1] == 1)
        scr_nr[k]=9;
    k++;
}

//scrierea in fisier
for(i = 0; i != k; i++){
    fprintf(txt,"%d",scr_nr[i]);
}

//mutarea inapoi a cifrei 1 care s-a facut anterior
for(i = 0; i != k; i++){
    if (scr_nr[i] == 1){
        for(l = 0; l != 5; l++){
            numar[i][l][0]=0;
            numar[i][l][4]=1;
        }
    }
}

//taskul 3;
int ordinea[N];

for(i = 0; i != 100; i++){
    ordinea[i] = i;
}

//eliminarea numerelor excluse
for(j = 0; j!= cite_numere; j++)
    for(i = 0; i != k; i++){
        if(scr_nr[i] == numere_excluse[j]){

        for(l = i; l != k; l++)
                scr_nr[l]=scr_nr[l+1];

        for(l = i; l != 100; l++)
                ordinea[l]=ordinea[l+1];

        //eliminarea indicilor numerelor excluse
        for(z = i; z != k; z++)
            for(l = 0; l != 5; l++){
                for(v = 0; v != 5; v++){
                    numar[z][l][v]=numar[z+1][l][v];
                }
            }
        k--;
        i--;
        }
}

int cite_cifre=k;

FILE *out_ts3 = fopen(out_name_ts3, "wb");
FILE *ini = fopen(name, "rb");
struct Pix pixeli[N][N];

if (out_ts3 == NULL) {
    printf("out_ts3 error");
    return -1;
}

if (ini == NULL) {
    printf("out_ts3 error");
    return -1;
}

//citirea si scrierea a fisierului 3
fread(&file,sizeof(FILEHEADER),1, ini);
fread(&info,sizeof(INFOHEADER),1, ini);

fwrite(&file, sizeof(FILEHEADER), 1, out_ts3);
fwrite(&info, sizeof(INFOHEADER), 1, out_ts3);


//crearea unei noi imagini albe
for (i = 0; i < info.height; i++){

    for (j = 0; j < info.width; j++){
            pixeli[i][j].R = 255;
            pixeli[i][j].G = 255;
            pixeli[i][j].B = 255;
    }
}
z = 0;

//setarea culorilor numerelor care vor fi printate
for (i = 0; i != info.width; i++){
    for (j = 0; j != info.height; j++){
        if(verificare(poz_h,poz_w,j,i,cite_cifre)){

                //crearea ariei de 5 corespunzatoare numeror
                for(k = 0; k != 5; k++){
                    for(l = 0; l != 5; l++){
                        if(numar[z][k][l] == 1) {
                                v=ordinea[z];
                                int aux = poz_color_h[v];
                                int aux1 = poz_color_w[v];
                                pixeli[j - k][i + l].B = color[aux][aux1].B;
                                pixeli[j - k][i + l].G = color[aux][aux1].G;
                                pixeli[j - k][i + l].R = color[aux][aux1].R;

                        }
                    }
                }
            z++;
        }
    }
}

//printarea cifrelor in fisieru3
for (i = 0; i < info.height; i++){
    for (j = 0; j < info.width; j++){
        fwrite(&pixeli[i][j], sizeof(Pix), 1, out_ts3);
    }
     for ( k = 0; k < padding; k++)
    {
        fputc(0, out_ts3);
    }
}
fclose(ini);
fclose(out_ts3);
fclose(txt);

// BONU
FILE *bon=fopen(bonus,"w"),*f_bon=fopen(f_bonus,"r");
if(bon == NULL) {
    printf("bon error");
    return -1;
}

if (f_bon == NULL) {
    printf("f_bon error");
    return -1;
}

FILEHEADER b_file;
INFOHEADER b_info;
struct Pix b_color[N][N];

//se citesc datele din input
fread(&b_file,sizeof(FILEHEADER),1, f_bon);
fread(&b_info,sizeof(INFOHEADER),1, f_bon);

//se scriu datele catre output
fwrite(&b_file, sizeof(FILEHEADER), 1, bon);
fwrite(&b_info, sizeof(INFOHEADER), 1, bon);


padding =  (4 - (b_info.width * sizeof(Pix)) % 4) % 4;

// se trece peste linii
for (i = 0; i < b_info.height; i++){

    // se trece peste coloane
    for (j = 0; j < b_info.width; j++){

        // se citeste rgb de la fiecare pixel
        fread(&b_color[i][j], sizeof(Pix), 1, f_bon);
    }

    // se trece peste padding
    fseek(f_bon, padding, SEEK_CUR);
}

//se modifica culoarea
for (i = 0; i < b_info.height; i++){

    for (j = 0; j < b_info.width; j++){

        //se verifica daca e color
        if( b_color[i][j].B!= 255 && b_color[i][j].G != 255
            && b_color[i][j].R != 255 ){

            // se verifica daca nu e un singur punct
            if ( ( (b_color[i + 1][j].B == 255 && b_color[i + 1][j].G == 255 && b_color[i + 1][j].R == 255) || i == b_info.height-1 )
            && ( (b_color[i - 1][j].B == 255 && b_color[i - 1][j].G == 255 && b_color[i - 1][j].R == 255) || i == 0 )
            && ( (b_color[i][j + 1].B == 255 && b_color[i][j + 1].G == 255 && b_color[i][j + 1].R == 255) || j == b_info.width-1 )
            && ( (b_color[i][j - 1].B == 255 && b_color[i][j - 1].G == 255 && b_color[i][j - 1].R == 255) || j== 1) ){
                continue;
            }

        int suma_b = b_color[i][j].B, suma_g = b_color[i][j].G ,suma_r = b_color[i][j].R, nr_s = 1;

                //se creaza raza cercului
                for(l = -7; l <= 7; l++){
                        for(k = -7; k <= 7; k++){
                            if(l == 0 && k == 0) continue;
                            if(l * l + k * k <= 49){

                                //se verifica daca e color
                                if( b_color[i + l][j + k].B!= 255 && b_color[i + l][j + k].G != 255
                                   && b_color[i + l][j + k].R != 255){

                                       //se verifica sa nu se modifice punctele incolore si beculetele
                                        if( b_color[i + l][j + k].B!= 255 && b_color[i + l][j + k].G != 255
                                            && b_color[i + l][j + k].R != 255 && ( (b_color[i + l + 1][j + k].B == 255
                                            && b_color[i + l + 1][j + k].G == 255 && b_color[i + l + 1][j + k].R == 255) || i + l == b_info.height-1 )
                                            && ((b_color[i + l - 1][j + k].B == 255 && b_color[i + l - 1][j + k].G == 255
                                            && b_color[i + l - 1][j + k].R == 255) || i + l == 0 ) && ( (b_color[i + l][j + k + 1].B == 255
                                            && b_color[i + l][j + k + 1].G == 255 && b_color[i + l][j + k + 1].R == 255) || j + k == b_info.width - 1)
                                            && ( (b_color[i + l][j + k - 1].B == 255 && b_color[i + l][j + k - 1].G == 255
                                            && b_color[i + l][j + k - 1].R == 255) || j + k== 1) ) {

                                                    suma_b = suma_b + b_color[i + l][j + k].B;
                                                    suma_g = suma_g + b_color[i + l][j + k].G;
                                                    suma_r = suma_r + b_color[i + l][j + k].R;
                                                    nr_s++;
                                            }
                                }
                            }
                        }
                }
                printf("da");
        b_color[i][j].B = suma_b / nr_s;
        b_color[i][j].G = suma_g / nr_s;
        b_color[i][j].R = suma_r / nr_s;
        }
    }
}

//printarea cifrelor in file
for (i = 0; i < b_info.height; i++){
    for (j = 0; j < b_info.width; j++){

        fwrite(&b_color[i][j], sizeof(Pix), 1, bon);
    }
    // paddingul pe 0
    for ( k = 0; k < padding; k++)
    {
        fputc(0, bon);

    }
}


fclose(f_bon);
fclose(bon);
return 0;
}
