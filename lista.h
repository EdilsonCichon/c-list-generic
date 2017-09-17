/* 
 * File:   lista.h
 * Author: Edilson Cichon
 *
 * Created on September 8, 2017, 10:47 AM
 */

#ifndef LISTA_H
#define LISTA_H

#include "string.h"
#include "stdlib.h"

#include "util.h"
#include "cidade.h"
#include "elemento.h"

typedef struct tipoLista {
    Elemento *primeiro;
    Elemento *ultimo;
    int total;
} Lista;

void inicializar(Lista *lista);
void inserir(Lista *lista, Elemento *elemento);
void inserirOrdenadoNome(Lista *lista, Elemento *elemento);
void inserirOrdenadoCodigo(Lista *lista, Elemento *elemento);
Elemento* remover(Lista *lista, Elemento *el);
Lista * clonar(Lista *lista);
Lista * ordenarCodigo(Lista *lista);
Lista * ordenarNome(Lista *lista);
Lista * newLista();
void listar(Lista *lista);


void inicializar(Lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->total = 0;
}

void inserir(Lista *lista, Elemento *elemento) {
    if (lista->primeiro == VAZIO) {
        lista->primeiro = elemento;
        lista->ultimo   = elemento;
        lista->total    = 1;
    } else {
        //inseri no final
        lista->ultimo->proximo = elemento;
        elemento->anterior     = lista->ultimo;
        lista->ultimo          = elemento;
        lista->total++;
    }
}

void inserirOrdenadoCodigo(Lista *lista, Elemento *elemento) {
    int inserido = 0;
    Elemento *atual,
             *anterior = VAZIO;
    if (lista->primeiro == VAZIO) {
        lista->primeiro = elemento;
        lista->ultimo   = elemento;
        lista->total    = 1;
    } else {
        atual = lista->primeiro;

        while (atual != VAZIO) {
            if (atual->conteudo->codigo > elemento->conteudo->codigo) {
                elemento->proximo = atual;
                atual->anterior   = elemento;
                
                if (atual == lista->primeiro)
                    lista->primeiro = elemento;
                else {
                    elemento->anterior = anterior;
                    anterior->proximo  = elemento;
                }
                inserido = 1; break;
            }
            //movimentando os ponteiros
            anterior = atual;
            atual    = atual->proximo;
        }
        if (!inserido) {
            anterior->proximo  = elemento;
            elemento->anterior = anterior;
            lista->ultimo      = elemento;
        }
        lista->total++;
    }
}

void inserirOrdenadoNome(Lista *lista, Elemento *elemento) {
    int inserido = 0;
    Elemento *atual,
             *anterior = VAZIO;
    if (lista->primeiro == VAZIO) {
        lista->primeiro = elemento;
        lista->ultimo   = elemento;
        lista->total    = 1;
    } else {
        atual = lista->primeiro;

        while (atual != VAZIO) {
            if (strcmp(atual->conteudo->nome, elemento->conteudo->nome) == 1) {
                elemento->proximo = atual;
                atual->anterior   = elemento;
                
                if (atual == lista->primeiro)
                    lista->primeiro = elemento;
                else {
                    elemento->anterior = anterior;
                    anterior->proximo  = elemento;
                }
                inserido = 1; break;
            }
            //movimentando os ponteiros
            anterior = atual;
            atual    = atual->proximo;
        }
        if (!inserido) {
            anterior->proximo  = elemento;
            elemento->anterior = anterior;
            lista->ultimo      = elemento;
        }
        lista->total++;
    }
}

Elemento* remover(Lista *lista, Elemento *el) {
    Elemento *elAtual = lista->primeiro;
    while (elAtual != NULL) {
        if (elAtual->conteudo == el->conteudo) {
            if (elAtual == lista->primeiro) {
                lista->primeiro  = elAtual->proximo;
                elAtual->proximo = NULL;
                lista->total--;
                return elAtual;
            }
            if (elAtual == lista->ultimo) {
                lista->ultimo = elAtual->anterior;
                elAtual->anterior->proximo = NULL;
                lista->total--;
                return elAtual;
            }
            //está no meio da lista
            
            elAtual->anterior->proximo = elAtual->proximo;
            elAtual->proximo->anterior = elAtual->anterior;
            
            elAtual->anterior = NULL;
            elAtual->proximo  = NULL;
            lista->total--;
            return elAtual;
        }
        elAtual = elAtual->proximo;
    }
    return NULL;
}

Lista * clonar(Lista *lista) {
    Lista *nova = newLista();
    inicializar(nova);
    Elemento *atual = lista->primeiro;
    
    while (atual->proximo != VAZIO) {
        inserir(nova, newElemento(atual->conteudo, NULL, NULL));
        atual = atual->proximo;
    }
    
    return nova;
}

Lista * ordenarCodigo(Lista *lista) {
    Lista *nova = newLista();
    inicializar(nova);
    Elemento *atual = lista->primeiro;
    
    while (atual != VAZIO) {
        inserirOrdenadoCodigo(nova, newElemento(atual->conteudo, NULL, NULL));
        atual = atual->proximo;
    }
    nova->total = lista->total;
    return nova;
}

Lista * ordenarNome(Lista *lista) {
    Lista *nova = newLista();
    inicializar(nova);
    Elemento *atual = lista->primeiro;
    
    while (atual != VAZIO) {
        inserirOrdenadoNome(nova, newElemento(atual->conteudo, NULL, NULL));
        atual = atual->proximo;
    }
    
    nova->total = lista->total;
    return nova;
}

void listar(Lista *lista) {
    Elemento *elemento = lista->primeiro;
    int cont = 0;
    while (elemento != VAZIO) {
        printf("%d | %s | %d  \n\n", 
                elemento->conteudo->codigo, 
                elemento->conteudo->nome, 
                elemento->conteudo->populacao);
        cont++;
        elemento = elemento->proximo;
    }
    
    printf("QUANTIDADE: %d\n\n", lista->total);
}

Lista * newLista() {
    return (Lista*) malloc(sizeof(Lista));
}

#endif /* LISTA_H */
