#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "busca.c"
#include "remocao.c"
#include "insercao.c"

int execucaoMenu(char* arq){
    FILE *commands;
    if( (commands = fopen(arq,"r") ) == NULL ){
        printf("\nAlgo deu errado na leitura do arquivo commands.txt");
        return 0;
        exit(EXIT_FAILURE);
    }
    
    char comando[TAM_MAX_REG+2];
    int fim = fgets(comando, TAM_MAX_REG+2, commands);

    while(fim != 0){
        // printf("\n%s", comando);
  
        if(strncmp(comando, "b", 1) == 0){
            printf("\n--> Entrei no modo de busca");

            char chave[TAM_MAX_REG];
            memcpy(chave, &comando[2], sizeof(chave));
            chave[6] = '\0';
            
            int error = buscaPorChave(chave);

        }else if(strncmp(comando, "i", 1) == 0){
            printf("\n--> Entrei no modo de insercao");

            char registro[TAM_MAX_REG];
            memcpy(registro, &comando[2], sizeof(registro));
            registro[TAM_MAX_REG] = '\0';
            
            int error = insercaoRegistro(registro);
            
        }else if(strncmp(comando, "r", 1) == 0){
            printf("\n--> Entrei no modo de remocao");

            char chave[TAM_MAX_REG];
            memcpy(chave, &comando[2], sizeof(chave));
            chave[6] = '\0';
            
            int error = remocaoPorChave(chave);
            
        }else{
            if(strncmp(comando, "0", 1) != 0){
                printf("\nOpcao nao existe, escolha uma das opcoes do menu\n");
            }
        }

        fim = fgets(comando, TAM_MAX_REG, commands);
    }

    fclose(commands);

    printf("\nMetodo de execucao finalizado");

    return 0;
}