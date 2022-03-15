#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

int insercaoRegistro (char *buffer){
    char *pt;
    char registro[TAM_MAX_REG];
    memset(registro, 0, TAM_MAX_REG);
    pt = strtok(buffer, DELIM_STR);
    printf("\n-> Insercao do registro de chave: %s", pt);
    for (int i = 0; i < 4; i++){    
        strcat(registro, pt);
        strcat(registro, DELIM_STR);
        pt = strtok(NULL, DELIM_STR);
    }

    FILE *dadosBinarios;
    if( (dadosBinarios = fopen("dados.dat","r+b") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo dados.dat");
        return 0;
        exit(EXIT_FAILURE);
    }

    char topo[sizeof(int)];
    fseek(dadosBinarios, 0, SEEK_SET);
    fread(topo, sizeof(int), 1, dadosBinarios);


    if(topo[0] == '-'){
        fseek(dadosBinarios, 0, SEEK_END);
        fwrite(registro, TAM_MAX_REG, 1, dadosBinarios);
        printf("\nLocal: fim do arquivo\n");
    }else{
        int topoInt = atoi(topo);
        fseek(dadosBinarios, topoInt * TAM_MAX_REG + sizeof(int), SEEK_SET);
        fread(topo, sizeof(int), 1, dadosBinarios);

        fseek(dadosBinarios, topoInt * TAM_MAX_REG + sizeof(int), SEEK_SET);
        fwrite(registro, TAM_MAX_REG, 1, dadosBinarios);
        printf("\nLocal: RRN = %d (byte-offset %d) [reutilizado]\n", topoInt, topoInt * TAM_MAX_REG + sizeof(int));

        fseek(dadosBinarios, 0, SEEK_SET);
        fwrite(topo, sizeof(int), 1, dadosBinarios);
    }

    fclose(dadosBinarios);

    return 0;
}