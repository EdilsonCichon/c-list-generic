/* 
 * File:   cidade.h
 * Author: Edilson Cichon
 *
 * Created on September 8, 2017, 10:56 AM
 */

#ifndef CIDADE_H
#define CIDADE_H

typedef struct tipoCidade {
    int codigo;
    char nome[11];
    int populacao;
} Cidade;

Cidade * newCidade(int codigo, char *nome, int populacao);

Cidade * newCidade(int codigo, char *nome, int populacao) {
    Cidade *cidade = (Cidade*) malloc(sizeof(Cidade));
    cidade->codigo    = codigo;
    cidade->populacao = populacao;
    strcpy(cidade->nome, nome);
    return cidade;
}
#endif /* CIDADE_H */

