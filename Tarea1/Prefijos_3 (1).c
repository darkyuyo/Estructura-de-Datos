#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Funcion que necesitamos para la utilizacion de qsrot()
int comparetor(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}
//funcion que recibe un conjunto de strings proveniente del archivo de entrada y un entero n que corresponde a la cantidad de strings que posee S
int pCML (char **S, int n){
    FILE *fp;
    char stringg[201];
    int i=0;
    fp=fopen("strings.txt","r");
    //El while siguiente almacena los strings del archivo en el conjunto S
    while (!feof(fp)){
        fgets(stringg, sizeof(char)*201, fp);
        stringg[strcspn(stringg, "\n")] = '\0';
        S[i++] = strdup(stringg);
    }
    int max_prefijo=-1,cont,cont_char;
    //qsort va a ordenar nuestro conjunto de strings por orden alfabetico
    qsort (S,n, sizeof(char*), comparetor);
    //recorreremos el conunto de strings S
    for(cont=0;cont<n-1;cont++){
        //con este for  gracias a que esta ordenado alfabeticamente podemos ir comparando los string con el siguiente y hallar mas facilmente los prefijos comunes
        for(cont_char=0;S[cont][cont_char]==S[cont+1][cont_char];cont_char++){
            //este if en caso de que el prefijo comparado es mayor al mas largo guardado actualmente, guarda este como el mas largo, y la segunda condicion del if hace que al momento de comparar no cuente el caracter de fin de string como una letra mas
            if(cont_char>max_prefijo && S[cont][cont_char]!='\0'){
                max_prefijo=cont_char;
            }
        }
    }
    return max_prefijo+1;
}

int main(){
    int n=0;
    FILE *fp2,*fpn;
    char **S;
    char stringg[201];
    fpn=fopen("strings.txt","r");
    if (fpn==NULL)
        return -1;
    //con este while calcularemos la cantidad de strings presentes en el archivo que leemos
    while (fgets(stringg,sizeof(char)*201,fpn)!=NULL){
        n++;
    }
    fclose(fpn);
    //una vez teniendo el valor de n, podemos pedir memoria y declarar el conjunto de strings S
    char *arregloAux[n];
    S=arregloAux;
    //abrimos otro archivo en modo de escritura, lo que escribira un nuevo archivo de salida
    fp2=fopen("salida-1.txt","w");
    fprintf(fp2,"%d",pCML(S,n));
    fclose(fp2);
    return 0;
}
