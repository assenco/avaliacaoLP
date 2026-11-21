#include <stdio.h>
#include <stdlib.h>
#include "despesas.h"

//Carrega os dados gravados no arquivo
void carregar(Despesa *vetor[]) {

    //Abre o arquivo ja existente
    FILE *fp = fopen("dados.txt", "r");

    char linha[200];
    int i = 0;

    //Se o arquivo nao existir sai da funcao
    if (fp == NULL) {
        return;
    }

    //Executa enquanto houver espaco no vetor e existirem linhas para ler no arquivo
    while (i < MAX && fgets(linha, 200, fp) != NULL) {

        //Reserva a memoria
        vetor[i] = malloc(sizeof(Despesa));

        //Verifica se a memoria foi reservada
        if (vetor[i] == NULL) {
            printf("Sem memoria!\n");
            break;
        }

        //Adequa os campos da linha lida seguindo a formatacao e preenche os campos da struct
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%f", &vetor[i]->codigo, vetor[i]->categoria, vetor[i]->descricao, vetor[i]->mes, &vetor[i]->valor);

        i++;
    }

    //Fecha o arquivo
    fclose(fp);
}

//Salva todos os registros no arquivo
void salvar(Despesa *vetor[]) {

    //Abre o arquivo no modo de escrita
    FILE *fp = fopen("dados.txt", "w");

    int i;

    //Verifica se o arquivo foi barrado ao abrir
    if (fp == NULL) {
        printf("Erro ao salvar!\n");
        return;
    }

    //Percorre o vetor nas posicoes preenchidas
    for (i = 0; i < MAX; i++) {
        if (vetor[i] != NULL) {

            //Grava os dados formatados no arquivo
            fprintf(fp, "%d;%s;%s;%s;%.2f\n", vetor[i]->codigo, vetor[i]->categoria, vetor[i]->descricao, vetor[i]->mes, vetor[i]->valor);

        }
    }

    //Fecha o arquivo
    fclose(fp);
}

//Cadastra novas despesas
void cadastrar(Despesa *vetor[]) {

    int i = 0;

    //Procura a primeira posicao vazia
    while (i < MAX && vetor[i] != NULL) {
        i++;
    }

    //Verifica se e a ultima posicao (vetor cheio)
    if (i == MAX) {
        printf("Vetor cheio!\n");
        return;
    }

    //Reserva espaco na memoria para gravar
    vetor[i] = malloc(sizeof(Despesa));

    //Verifica se o espaco foi reservado
    if (vetor[i] == NULL) {
        printf("Sem memoria!\n");
        return;
    }

    //Registra dados
    printf("Codigo: ");
    scanf("%d", &vetor[i]->codigo);
    printf("Categoria: ");
    scanf(" %[^\n]", vetor[i]->categoria);
    printf("Descricao: ");
    scanf(" %[^\n]", vetor[i]->descricao);
    printf("Mes (MM/AAAA): ");
    scanf(" %s", vetor[i]->mes);
    printf("Valor: ");
    scanf("%f", &vetor[i]->valor);
}

//Lista as despesas existentes
void listar(Despesa *vetor[]) {

    int i;

    //Percorre o vetor
    for (i = 0; i < MAX; i++) {

        //Se a posicao no vetor nao estiver vazia imprime os dados
        if (vetor[i] != NULL) {
            printf("%d | %s | %s | %s | R$ %.2f\n", vetor[i]->codigo, vetor[i]->categoria, vetor[i]->descricao, vetor[i]->mes, vetor[i]->valor);
        }
    }
}

//Buscar por despesas
void buscar(Despesa *vetor[]) {

    int codigo, i;

    //Pede o codigo da despesa pro usuario
    printf("Codigo: ");
    scanf("%d", &codigo);

    //Busca no vetor o codigo, imprime e sai da funcao
    for (i = 0; i < MAX; i++) {
        if (vetor[i] != NULL && vetor[i]->codigo == codigo) {
            printf("Categoria: %s\n", vetor[i]->categoria);
            printf("Descricao: %s\n", vetor[i]->descricao);
            printf("Mes: %s\n", vetor[i]->mes);
            printf("Valor: R$ %.2f\n", vetor[i]->valor);
            return;
        }
    }

    //Se nao encontrado imprime mensagem
    printf("Nao encontrado.\n");
}

//Gerar relatorio com total de despesas e maior valor
void relatorio(Despesa *vetor[]) {

    float total = 0;
    float maiorValor = 0;
    Despesa *maisCara = NULL;
    int i;

    //Percorre o vetor procurando posicoes preenchidas
    for (i = 0; i < MAX; i++) {
        if (vetor[i] != NULL) {

            //Total recebe a soma com valor da posicao
            total = total + vetor[i]->valor;

            //Se o valor da posicao atual for maior que a registrada, recebe o valor e registra a despesa referente
            if (vetor[i]->valor > maiorValor) {
                maiorValor = vetor[i]->valor;
                maisCara = vetor[i];
            }
        }
    }

    //Caso nao tenha despesas imprime a mensagem
    if (maisCara == NULL) {
        printf("Nenhuma despesa cadastrada.\n");
        return;
    }

    //Imprime os resultados
    printf("Custo total: R$ %.2f\n", total);
    printf("Maior despesa: %s - R$ %.2f\n", maisCara->descricao, maisCara->valor);
}

//Libera a memoria restante na RAM
void liberar(Despesa *vetor[]) {

    int i;

    //Verifica as posicoes do vetor, se nao estiverem vazias libera os espacos para a RAM
    for (i = 0; i < MAX; i++) {
        if (vetor[i] != NULL) {
            free(vetor[i]);
        }
    }
}
