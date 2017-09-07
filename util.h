#include <cstdlib>
#include <cstring>
#include "global.h"

int    menu();
void   limparPrompt();
void   pauseScreen();
char * alocarString(char * string_temp);
char * desalocarString(char * endereco);
int  * lerInt(int * paramInt);
char * lerString();
void   carregando(int t);

void limparPrompt() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}

char * alocarString(char * string_temp) {
    int tamanho = 0;
    while (string_temp[tamanho] != STRING_EOF)
        tamanho++;
    char * str;
    str = (char*)malloc(tamanho*sizeof(char));
    strcpy(str, string_temp);
    string_temp[0] = '\0';
    return str;
}

char * desalocarString(char * endereco) {
    //TODO Pesquisar como desalocar espaços de memória.
}

void carregando(int t) {
    for (int i = 0; i < t; i++) {
        sleep(1);
        printf(".");
    }
}

char * lerString() {
    char * string = (char *) malloc(STRSIZE * sizeof (char));
    fflush(stdin);
    fgets(string, STRSIZE, stdin);
    string[strlen(string) - 1] = '\0';

    return string;
}

int * lerInt(int * paramInt) {
    int valor;
    scanf("%d", paramInt);
    return paramInt;
}

int menu() {
    int opcao;
    limparPrompt();
    printf("\n\n\n\t\t=====| MENU AGENDA |=====\n\n");
    printf("\t 0 - SAIR\n\n");
    printf("\t 1 - CADASTRAR DISCO\n");
    printf("\t 2 - ALTERAR DISCO \n");
    printf("\t 3 - LISTAR DISCOS\n");
    printf("\t 4 - CONSULTAR DISCO \n");
    printf("\t 5 - EXCLUIR DISCO (NAO FEITO)\n");
    printf("\t 6 - ORDENAR DISCO ORDEM CRESCENTE\n");
    printf("\t 7 - ORDENAR DISCO ORDEM DECRESCENTE\n");
    printf("\t 8 - CADASTRAR ARTISTA EM DISCO \n");
    printf("\t 9 - LISTAR ARTISTA EM DISCOS\n");
    printf("\t10 - EXCLUIR ARTISTA DE DISCO (NAO FEITO)\n");
    printf("\t11 - INSERIR FAIXA ARTISTA/DISCO\n");
    printf("\t12 - LISTAR FAIXAS DE DISCO\n");
    printf("\t13 - LISTAR FAIXAS DE ARTISTA EM DISCOS\n");
    printf("\t14 - TOTAL DE FAIXAS POR DISCO\n");
    printf("\t15 - TOTAL DE FAIXAS POR ARTISTA\n");
    printf("\t16 - LISTA ARTISTAS FAIXA ESPECIFICA\n");

    do {
        printf("\t\tInforme a OPCAO desejada: ");
        scanf("%d", &opcao);

        if (opcao > 16) 
            printf("\n\nERRO: Opcao INVALIDA !!!\n\n");
    } while (opcao > 16);

    return opcao;
}