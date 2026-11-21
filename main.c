// Controle de Gastos

#include <stdio.h>
#include <stdlib.h>
#include "despesas.h"

int main() {

    //Faz um vetor de ponteiros para struct
    Despesa *vetor[MAX];
    int opcao, i;

    //Inicia todos os ponteiros vazios
    for (i = 0; i < MAX; i++) {
        vetor[i] = NULL;
    }

    //Executa funcao carregar
    carregar(vetor);

    do {

        //Imprime lista de funcoes do sistema
        printf("\n1 - Cadastrar\n2 - Listar\n3 - Buscar\n4 - Relatorio\n5 - Salvar e sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        //Entra em cada funcao
        switch (opcao) {
            case 1: cadastrar(vetor); break;
            case 2: listar(vetor); break;
            case 3: buscar(vetor); break;
            case 4: relatorio(vetor); break;
            case 5:
                salvar(vetor);
                liberar(vetor);
                break;

            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
