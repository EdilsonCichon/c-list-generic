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
void ordenarNome(Lista *lista, Lista *listaOrdenada);
void ordenarCodigo(Lista *lista, Lista *listaOrdenada);
Elemento* remover(Lista *lista, Elemento *el);
Lista * clonar(Lista *lista);
Lista * clonarOrdenadoCodigo(Lista *lista);
Lista * clonarOrdenadoNome(Lista *lista);
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

void ordenarNome(Lista *lista) {
    if (lista->total < 2)
        return;
    int moveu_elemento = 0;
    int ordenado = 0;

    Elemento * atual   = NULL;
    Elemento * proximo = NULL;

    while (ordenado != 1) {
        atual   = lista->primeiro;
        proximo = atual->proximo;

        while (proximo != NULL) {
            moveu_elemento = 0;
            if (strcmp(atual->conteudo->nome, proximo->conteudo->nome) == 1) {
                proximo->anterior = atual->anterior;
                atual->proximo    = proximo->proximo;

                if (proximo->proximo != NULL) {
                    proximo->proximo->anterior = atual;
                }
                if (atual->anterior != NULL) {
                    atual->anterior->proximo = proximo;
                }
                proximo->proximo = atual;
                atual->anterior  = proximo;

                if (atual == lista->primeiro)
                    lista->primeiro = proximo;
                if (proximo == lista->ultimo)
                    lista->ultimo = atual;
                moveu_elemento = 1;
            }
            if (moveu_elemento) {
                atual   = lista->primeiro;
                proximo = atual->proximo;
            } else {
                atual   = proximo;
                proximo = proximo->proximo;
            }
        }
        if (moveu_elemento == 0)
            ordenado = 1;
        else
            moveu_elemento = 0;
    }
}

void ordenarCodigo(Lista *lista) {
    if (lista->total < 2)
        return;
    int moveu_elemento = 0;
    int ordenado = 0;

    Elemento * atual   = NULL;
    Elemento * proximo = NULL;

    while (ordenado != 1) {
        atual   = lista->primeiro;
        proximo = atual->proximo;

        while (proximo != NULL) {
            moveu_elemento = 0;
            
            if (atual->conteudo->codigo > proximo->conteudo->codigo) {
                proximo->anterior = atual->anterior;
                atual->proximo    = proximo->proximo;

                if (proximo->proximo != NULL) {
                    proximo->proximo->anterior = atual;
                }
                if (atual->anterior != NULL) {
                    atual->anterior->proximo = proximo;
                }
                proximo->proximo = atual;
                atual->anterior  = proximo;

                if (atual == lista->primeiro)
                    lista->primeiro = proximo;
                if (proximo == lista->ultimo)
                    lista->ultimo = atual;
                moveu_elemento = 1;
            }
            
            if (moveu_elemento) {
                atual   = lista->primeiro;
                proximo = atual->proximo;
            } else {
                atual   = proximo;
                proximo = proximo->proximo;
            }
        }
        
        if (moveu_elemento == 0)
            ordenado = 1;
        else
            moveu_elemento = 0;
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

Lista * clonarOrdenadoCodigo(Lista *lista) {
    Lista *nova = newLista();
    inicializar(nova);
    Elemento *atual = lista->primeiro;
    
    while (atual->proximo != VAZIO) {
        inserirOrdenadoCodigo(nova, newElemento(atual->conteudo, NULL, NULL));
        atual = atual->proximo;
    }
    nova->total = lista->total;
    return nova;
}

Lista * clonarOrdenadoNome(Lista *lista) {
    Lista *nova = newLista();
    inicializar(nova);
    Elemento *atual = lista->primeiro;
    
    while (atual->proximo != VAZIO) {
        inserirOrdenadoNome(nova, newElemento(atual->conteudo, NULL, NULL));
        atual = atual->proximo;
    }
    
    nova->total = lista->total;
    return nova;
}

Lista * newLista() {
    return (Lista*) malloc(sizeof(Lista));
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

#endif /* LISTA_H */
