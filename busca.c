#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

int encontreiRegistro(char * buffer, int tam, char * chave, int numRegister, int binaryAtual){
    char *pt;
    char registro[tam];
    if(strcmp(buffer, "") == 0){
        return binaryAtual+1;
    }
    memset(registro, 0, tam);
    pt = strtok(buffer, DELIM_STR);
    char * chaveAtual = pt;

    for (int i = 0; i < 4; i++){    
        strcat(registro, pt);
        strcat(registro, DELIM_STR);
        pt = strtok(NULL, DELIM_STR);
    }

    // Lista todos os candidatos
    // printf("\n%s (RRN = %d - byte-offset %d)", registro, numRegister, (numRegister*TAM_MAX_REG)+4);
    
    // //Lista o candidato caso a chave seja a mesma que está sendo buscada
    if(strcmp(chave, chaveAtual) == 0){
        printf("\n%s (RRN = %d - byte-offset %d)\n", registro, numRegister, (numRegister*TAM_MAX_REG)+4);
        return 0;
    }

    return strlen(registro);
}

int buscaPorChave(char* chave){

    printf("\n-> Busca por chave: %s", chave);

    FILE *dadosBinarios;
    if( (dadosBinarios = fopen("dados.dat","rb") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo dados.dat");
        return 0;
        exit(EXIT_FAILURE);
    }

    int proxRegistro = 0;
    char reg[TAM_MAX_REG];
    int existeReg = 1;
    int numRegistro = 0;
    int registroBuscado = 1;
    int encontrouAlgum = 0;

    while (existeReg == 1 && encontrouAlgum == 0){

        fseek(dadosBinarios, numRegistro * TAM_MAX_REG + sizeof(int), SEEK_SET);
        if(fread(&reg, sizeof(reg), 1, dadosBinarios) == 0){
            existeReg = 0;
        }else{
            registroBuscado = encontreiRegistro(&reg, TAM_MAX_REG, chave, numRegistro, proxRegistro);

            if(registroBuscado == 0){
                encontrouAlgum = 1;
            }
            proxRegistro += registroBuscado;
            numRegistro++;
        }

    }

    if(encontrouAlgum == 0){
        printf("\nNenhum registro compativel com a chave %s\n", chave);
    }

    fclose(dadosBinarios);

    return 0;
}