#ifndef DESPESA_H
#define DESPESA_H

#define MAX 100

//Cria um struct para cada despesa
typedef struct {
    int codigo;
    char categoria[30];
    char descricao[50];
    char mes[10];
    float valor;
} Despesa;

//Prototipo das funcoes
void carregar(Despesa *vetor[]);
void salvar(Despesa *vetor[]);
void cadastrar(Despesa *vetor[]);
void listar(Despesa *vetor[]);
void buscar(Despesa *vetor[]);
void relatorio(Despesa *vetor[]);
void liberar(Despesa *vetor[]);

#endif