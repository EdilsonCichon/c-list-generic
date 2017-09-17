/* 
 * File:   util.h
 * Author: Edilson Cichon
 *
 * Created on September 8, 2017, 10:47 AM
 */

#ifndef UTIL_H
#define UTIL_H

#include "stdlib.h"
#include "string.h"
#include "global.h"

int  * lerInt(int * paramInt);
char * newString(char * string);
char * lerString();
void   carregando(int t);
void   pauseScreen();
void   limparPrompt();

int  * lerInt(int * paramInt) {
    int valor;
    scanf("%d", paramInt);
    return paramInt;
}

char * newString(char * string) {
    int tamanho = 0;
    while (string[tamanho] != STRING_EOF)
        tamanho++;
    char * str;
    str = (char*) malloc (tamanho*sizeof(char));
    strcpy(str, string);
    free(string);
    return str;
}

char * lerString() {
    char * string = (char *) malloc(STRSIZE * sizeof (char));
    fflush(stdin);
    fgets(string, STRSIZE, stdin);
    string[strlen(string) - 1] = '\0';

    return string;
}

void limparPrompt() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}

void carregando(int t) {
    for (int i = 0; i < t; i++) {
        sleep(1);
        printf(".");
    }
}

#endif /* UTIL_H */
