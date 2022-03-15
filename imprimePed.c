#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

int imprimePed (){
    FILE *dadosBinarios;
    if( (dadosBinarios = fopen("dados.dat","rb") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo dados.dat");
        return 0;
        exit(EXIT_FAILURE);
    }

    int espacosVazios = 0;
    char reg[TAM_MAX_REG];
    int existeReg = 1;
    int numRegistro = 0;
    int registroBuscado = 1;
    int encontrouAlgum = 0;

    char topo[sizeof(int)];
    fseek(dadosBinarios, 0, SEEK_SET);
    fread(topo, sizeof(int), 1, dadosBinarios);


    if(topo[0] == '-'){
        printf("\nPED: %s\nEspacos vazios: %d\n", topo, espacosVazios);
    }else{
        printf("\nPED: %s\n", topo);
        printf("RRNs disponiveis:");
        while(topo[0]!='-'){
            int topoInt = atoi(topo);

            printf(" %s", topo);

            fseek(dadosBinarios, topoInt * TAM_MAX_REG + sizeof(int), SEEK_SET);
            fread(topo, sizeof(int), 1, dadosBinarios);

            espacosVazios+=1;
        }
        printf("\nEspacos vazios: %d\n", espacosVazios);
    }

    fclose(dadosBinarios);

    return 0;
}