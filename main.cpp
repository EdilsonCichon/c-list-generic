/* 
 * File:   main.cpp
 * Author: Edilson Cichon
 * Data: 06-08-2017
 * Professor: Victório Carvalho
 * Disciplina: TPA
 * Curso: Sistemas de Informação - 6º Semestre (IFES)
 * 
 * 1º Trabalho - Lista de elementos 
 * para ser utilizada no decorrer das aulas.
 *
 * Created on September 16, 2017, 8:50 PM
 */

#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h"

#include "global.h"
#include "util.h"
#include "lista.h"
#include "cidade.h"

int  menu();
void executarMenu();
void * lerArquivo(Lista *lista, char * caminho);
void medirTempos(Lista *lista, Lista *ordCodigo, Lista *ordNome);

int main() {
    Lista *baseDados = newLista();
    Lista listaOrdenadaNome;
    Lista listaOrdenadaCodigo;
    inicializar(baseDados);
    
    printf("\n\n Lendo cidades... \n");
    lerArquivo(baseDados, newString("base_dados/entrada_100000.txt"));
    
    medirTempos(baseDados, &listaOrdenadaCodigo, &listaOrdenadaNome);
    
    return (EXIT_SUCCESS);
}

void executarMenu() {
    int operacao;
    do {
        operacao = menu();

        switch (operacao) {
            case 1: 
                break;
            default:
                printf("IMPLEMENTAR ACOES MENU!!!");
        }

    } while (operacao != 0);
}

int menu() {
    int opcao;
    limparPrompt();
    printf("\n\n\n\t\t=====| MENU AGENDA |=====\n\n");
    printf("\t 0 - SAIR\n\n");
    printf("\t 1 - INSERIR ELEMENTO\n");
    printf("\t 2 - REMOVER ELEMENTO\n");
    printf("\t 3 - LISTAR LISTA\n");

    do {
        printf("\t\tInforme a OPCAO desejada: ");
        scanf("%d", &opcao);

        if (opcao > 3) 
            printf("\n\nERRO: Opcao INVALIDA !!!\n\n");
    } while (opcao > 3);

    return opcao;
}

void * lerArquivo(Lista *lista, char * caminho) {
    char linha[100];
    char *parte;
    char delimitador[2] = ";";
    
    char *nome;
    int  codigo;
    int  populacao;
    Cidade   *cidade   = NULL;
    Elemento *elemento = NULL;
    int contador = 0;
    FILE * arquivo = fopen(caminho, "r");
    
    if (!arquivo) {
        printf("\n\nErro: nao foi possivel abrir o arquivo!\n\n");
        pauseScreen();
    } else {
        while (!feof(arquivo)) {
            fscanf(arquivo, "%s\n", linha);
            
            //formato esperado: '%d;%s;%d' que eh o mesmo de 'INTEIRO;STRING;INTEIRO'
            parte  = strtok(linha, delimitador); 
            codigo = atoi(parte);
            parte = strtok(NULL, delimitador);
            nome  = parte;
            parte = strtok(NULL, delimitador);
            populacao = atoi(parte);
            
            cidade   = newCidade(codigo, nome, populacao);
            elemento = newElemento(cidade, NULL, NULL);
            inserir(lista, elemento);
            contador++;
        }
    }
    fclose(arquivo);
    return NULL;
}

void medirTempos(Lista *baseDados, Lista *ltOrdenadaCod, Lista *ltOrdenadaNome) {
    clock_t clockInicio, clockFim;
    double tempo;
    //TEMPO ORDENAÇÃO POR CÓDIGO
    clockInicio   = clock();
    ltOrdenadaCod = ordenarCodigo(baseDados);
    clockFim      = clock();
    tempo         = (double)(clockFim - clockInicio) / CLOCKS_PER_SEC;
    printf("\n\nTEMPO CODIGO: %f \n", tempo);
    
    //TEMPO ORDENAÇÃO POR NOME
    clockInicio = clock();
    ltOrdenadaNome = ordenarNome(baseDados);
    clockFim = clock();
    tempo = (double)(clockFim - clockInicio) / CLOCKS_PER_SEC;
    printf("\n\nTEMPO NOME: %f \n\n\n", tempo);
}
