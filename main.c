//Author: Lucas Beluomini
//RA: 120111
//Data: 20/10/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "importacao.c"
#include "execucao.c"
#include "imprimePed.c"

int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
        int error_log = importacao(argv[2]);
        if(error_log == 1){
            printf("\nImportacao concluida com sucesso !!!");
        }
        

    }else if(argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("---> Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        execucaoMenu(argv[2]);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {

        printf("Modo de impressao da PED ativado ...\n");
        imprimePed();

    } else {

        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e|-p) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    return 0;
}