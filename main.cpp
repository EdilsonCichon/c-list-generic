/**
 * 1º Trabalho - Lista de elementos 
 * para ser utilizada no decorrer das aulas.
 * 
 * Data: 06-08-2017
 * Aluno: Edilson Cichon
 * Professor: Victório
 * Disciplina: TPA
 * Curso: Sistemas de Informação - 6º Semestre
 */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <ctype.h>

#include "global.h"
#include "util.h"
#include "structures.h"

void acoesMenu(ListaDisco *discos);

int main() {
    ListaDisco discos;
    
    inicializa(&discos);

    acoesMenu(&discos);
}

void acoesMenu(ListaDisco *discos) {
    int operacao;
    do {
        operacao = menu();

        switch (operacao) {
            case 1: insereDisco(discos, NULL, NULL);
                break;
            case 2: alterarDisco(discos);
            limparPrompt();
                break;
            case 3: listarDiscos(discos);
                break;
            case 4: consultarDisco(discos);
                break;
            case 5: excluirDisco(discos, NULL);
                break;
            case 6: ordenarDiscoUP(discos);
                break;
            case 7: ordenarDiscoDOWN(discos);
                break;
            case 8: insereArtista(discos);
                break;
            case 9: listaArtistas(discos);
                break;
            case 10: break;
            case 11: inserirFaixa(discos);
                break;
            case 12: listaFaixasDisco(discos);
                break;
            case 13: listaFaixasArtista(discos);
                break;
            case 14: listaTotalFaixasDisco(discos);
                break;
            case 15: listaTotalFaixasArtista(discos);
                break;
            case 16: listaArtistasFaixaEspecifica(discos);
                break;
        }

    } while (operacao != 0);
}