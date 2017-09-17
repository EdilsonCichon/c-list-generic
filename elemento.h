/* 
 * File:   elemento.h
 * Author: Edilson Cichon
 *
 * Created on September 16, 2017, 8:50 PM
 */

#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "cidade.h"

typedef struct tipoElemento {
    Cidade *conteudo;
    tipoElemento *anterior;
    tipoElemento *proximo;
} Elemento;

Elemento * newElemento(Cidade *conteudo, Elemento *anterior, Elemento *proximo);

Elemento * newElemento(Cidade *conteudo, Elemento *anterior, Elemento *proximo) {
    Elemento *elemento = (Elemento*) malloc(sizeof(Elemento));
    elemento->conteudo = conteudo;
    elemento->anterior = anterior;
    elemento->proximo  = proximo;
    return elemento;
}

#endif /* ELEMENTO_H */

