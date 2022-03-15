#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h" 

int readRegister(char * buffer, int tam, FILE* binaryData){
    char *pt;
    char registro[tam];
    memset(registro, 0, tam);
    pt = strtok(buffer, DELIM_STR);
    for (int i = 0; i < 4; i++){    
        strcat(registro, pt);
        strcat(registro, DELIM_STR);
        pt = strtok(NULL, DELIM_STR);
    }
    // printf("\nescrevendo: %s", registro);
    fwrite(registro , 1 , sizeof(registro) , binaryData);
    return strlen(registro);
}

int verificaVazio(char* dados){
    FILE* dadosTxt;
    if( (dadosTxt = fopen(dados, "r") ) == NULL ){
        printf("Algo deu errado na leitura do arquivo %s", dados);
        return 0;
        exit(EXIT_FAILURE);
    }

    char reg[TAM_MAX_REG];
    if(fread(&reg, sizeof(reg), 1, dadosTxt) != 1){
        // acabou os registros
        return 0;
    }

    fclose(dadosTxt);
    return 1;
}

int importacao(char* dados){

    int vazio = verificaVazio(dados);
    if(vazio == 0){
        printf("\nArquivo de registros esta vazio");
        return 0;
    }

    FILE* dadosTxt;
    if( (dadosTxt = fopen(dados, "r") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo %s", dados);
        return 0;
        exit(EXIT_FAILURE);
    }

    FILE *dadosBinarios;
    if( (dadosBinarios = fopen("dados.dat","w+b") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo dados.dat");
        return 0;
        exit(EXIT_FAILURE);
    }

    int proxRegistro = 0;
    char reg[TAM_MAX_REG];
    int existeReg = 1;

    char *cabecalho[sizeof(int)];

    strcpy(cabecalho, "-1..");

    fwrite(cabecalho , 1 , sizeof(int) , dadosBinarios);

    while (existeReg == 1){
        fread(&reg, sizeof(reg), 1, dadosTxt);
        fseek(dadosTxt, proxRegistro * sizeof (char), SEEK_SET);
        if(fread(&reg, sizeof(reg), 1, dadosTxt) != 1){
            // acabou os registros
            existeReg = 0;
        }
        //move o ponteiro de leitura para o prox registro (somatorio dos bytes lidos ate agora)
        proxRegistro += readRegister(&reg, TAM_MAX_REG, dadosBinarios);
    }

    fclose(dadosTxt);
    fclose(dadosBinarios);
    return 1;
}