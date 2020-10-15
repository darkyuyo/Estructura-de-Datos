#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funcion que descomprime el string que se almacena en un archivo binario y lo retorna
char * descomprimir (char *nbreArchivo){
    //Declaramos variables (contadores, string, etc)
    int n,contador1,contador2;
    int pos=0;
    int largoString=0;
    char *Stringgg;

    //declaramos el fichero de archivo y abrimos el archivo binario en forma de lectura
    FILE *fp;
    fp=fopen(nbreArchivo,"rb");
    if (fp==NULL){
        return("Archivo no existe") ;
    }
    fread(&n, sizeof(int), 1, fp); //lee el primer entero del archivo binario y la guarda en la variable n
    unsigned int rep[n]; //ahora que tenemos el valor de n podemos definir estas listas de largo n
    unsigned char letras[n];
    fread(&rep, sizeof(unsigned int), n, fp); //lee los siguientes n enteros y los almacena en la lista rep
    fread(&letras, sizeof(unsigned int), n, fp);//lee los siguientes n caracteres y los almacena en la lista letras
    fclose(fp); //cerramos el archivo, dado que ya lo leimos y no lo necesitamos

    //En este for calculamos el largo del String que retornaremos, para a continuacion poder pedir la memoria
    for (int i=0;i<n;i++){
        largoString=largoString+rep[i];
    }
    Stringgg=(char*)malloc(sizeof(char)*largoString); //ahora que sabemos el largo del string, pedimos la memoria correspondiente

    //Dentro de este for basicamente escribimos los char dependiendo de sus repeticiones y los unimos en un mismo string que retornaremos
    for(contador1=0;n>contador1;contador1++){
        for(contador2=0;rep[contador1]>contador2;contador2++){
                Stringgg[pos]=letras[contador1];
                pos++;
        }
    }
    return Stringgg; //retorna el string descomprimido
}
int main(){
    char nArch[100]; //definimos un arreglo de 100 caracteres donde iremos almacenando los nombres de archivo que leeremos del archivo de entrada
    FILE *fp2,*fp3;
    fp2=fopen("input-strings.txt","r"); //abrimos el archivo de entrada en modo lectura
    fp3=fopen("strings-descomprimidos.txt","w"); //escribimos el archivo de salida
    if (fp2==NULL){
        exit(1);
    }
    while (!feof(fp2)){ //esto hace que lo que este dentro del while se repita mientras no hallamos llegado al termino del archivo guardado en fp2
        fgets(nArch,100,fp2); //lee una linea del archivo y guarda en nArch el string de maximo 100 char
        nArch[strlen(nArch)-1]='\0'; //strlen entrega el largo del string, por lo que le restamos 1 debido a que el primer char empieza en la posicion 0, por lo que el n-eseimo char estara en la posicion n-1, por lo que en la ultima posicion del arreglo de char guarda \0 que denota el fin del string
        if (feof(fp2)){
            break;
        }
        fprintf(fp3,"%s\n",descomprimir(nArch));
    }
    fclose(fp2);
    fclose(fp3);
    return 0;
}
