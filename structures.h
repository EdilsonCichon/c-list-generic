#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <ctype.h>
#include "global.h"

typedef struct tipoFaixa {
    char * titulo;
    int aoVivo;
    int instrumental;
    tipoFaixa *prox;
} Faixa;

typedef struct tipoArtista {
    char nome[45];
    Faixa *faixas;
    tipoArtista *prox;
} Artista;

typedef struct tipoDisco {
    char titulo[45];
    char ano[4];
    Artista *participacao;
    tipoDisco *ante, *prox;
} Disco;

typedef struct tipoListaDisco {
    Disco *inicio, *fim;
    int total;
} ListaDisco;

// ASSINATURA FUNÇÕES

void inicializa(ListaDisco *discos);
//Faixa
void inserirFaixa(ListaDisco *discos);
void listaFaixas(ListaDisco *discos);
void artistasFaixa(ListaDisco *discos, char *tituloFaixa);
void listaArtistasFaixaEspecifica(ListaDisco *discos);

//Artista
void insereArtista(ListaDisco *discos);
void listaArtistas(ListaDisco *discos);
Artista* selectArtista(Disco *disco, char *titulo);
void infoArtistas(ListaDisco *discos, Artista *artista);
void infoFaixasArtistas(ListaDisco *discos, Artista *artista);
void listaFaixasArtista(ListaDisco *discos);
void faixasArtista(Artista *artista);
void listaTotalFaixasArtista(ListaDisco *discos);

//Disco
void popularDiscos(ListaDisco *discos);
void insereDisco(ListaDisco *discos, char *titulo, char *ano);
void listarDiscos(ListaDisco *discos);
Disco* selecionarDisco(ListaDisco *discos, char *titulo);
void artistasDisco(Disco *disco);
void consultarDisco(ListaDisco *discos);
void alterarDisco(ListaDisco *discos);
void ordenarDiscoUP(ListaDisco * discos);
void ordenarDiscoDOWN(ListaDisco *discos);
void listaFaixasDisco(ListaDisco *discos);
void listaTotalFaixasDisco(ListaDisco *discos);

// IMPLEMENTAÇÃO FUNÇÕES

void excluirDisco(ListaDisco *discos, char *titulo);

void inicializa(ListaDisco *discos) {
    discos->inicio = NULL;
    discos->fim = NULL;
    discos->total = 0;
    popularDiscos(discos); // Para efeito de teste
}

//Faixa
void listaArtistasFaixaEspecifica(ListaDisco *discos) {
    char  * faixaInformada = NULL;
    Faixa * faixaSelect = NULL;
    limparPrompt();
    printf("\n\n\t\t ====| ARTISTAS POR FAIXA ESPECIFICA |====\n\n");
    printf("\t\t ====| LISTA DE FAIXAS |====\n");

    listaFaixas(discos);
    printf("\n\tESCOLHA UMA FAIXA (NOME): ");
    faixaInformada = lerString();


    printf("\t\t ====| ARTISTAS |====\n");
    artistasFaixa(discos, faixaInformada);

    printf("\n\n");
    system("pause");
}

void artistasFaixa(ListaDisco *discos, char *titulo) {
    Disco   * discoAtual   = VAZIO;
    Artista * artistaAtual = VAZIO;
    Faixa   * faixaAtual   = VAZIO;
    
    discoAtual = discos->inicio;
    while (discoAtual != VAZIO) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != VAZIO) {
            int cont = 1;
            faixaAtual = artistaAtual->faixas;
            while (faixaAtual != NULL) {
                if (strcmp(titulo, faixaAtual->titulo) == 0)
                    printf("\n\t\t(%d) %s\n", cont++, artistaAtual->nome);

                faixaAtual = faixaAtual->prox;
            }
            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
}

void listaFaixas(ListaDisco *discos) {
    Disco * discoAtual = NULL;
    Artista * artistaAtual = NULL;
    Faixa * faixaAtual = NULL;

    discoAtual = discos->inicio;
    while (discoAtual != NULL) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != NULL) {
            int cont = 1;
            faixaAtual = artistaAtual->faixas;
            while (faixaAtual != NULL) {

                printf("\n\n\t (%d) %s | AO VIVO [%d] | INSTRUMENTAL [%d] | \n", cont++, faixaAtual->titulo, faixaAtual->aoVivo, faixaAtual->instrumental);

                faixaAtual = faixaAtual->prox;
            }
            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
}

void inserirFaixa(ListaDisco *discos) {
    bool cadastrado = false;
    Disco * disco = NULL;
    Artista * artista = NULL;
    Faixa * novaFaixa = (Faixa*) malloc(sizeof (Faixa));
    Faixa * faixaAtual = NULL;
    Faixa * faixaAnterior = NULL;
    novaFaixa->titulo = NULL;
    novaFaixa->aoVivo = 0;
    novaFaixa->instrumental = 0;
    novaFaixa->prox = NULL;

    listarDiscos(discos);
    printf("\n\n\t\t ===| CADASTRO DE FAIXA |=== \n");
    disco = selecionarDisco(discos, NULL);
    printf("\n\t\t ===| ARTISTAS DESTE DISCO |=== \n");
    artistasDisco(disco);
    artista = selectArtista(disco, NULL);

    if (artista == NULL) {
        printf("\n\t\t >>> ARTISTA NAO ENCONTRADO! <<<\n");
        system("pause");
        return;
    } else {
        // captura dados da faixa
        printf("\n\t\t ===| INFO DA FAIXA |=== \n");
        printf("\n\n\t INFORME O TITULO: ");
        novaFaixa->titulo = lerString();
        printf("\n\n\t MUSICA AO VIVO: ");
        lerInt(&novaFaixa->aoVivo);
        printf("\n\n\t MUSICA INSTRUMENTAL: ");
        lerInt(&novaFaixa->instrumental);
    }

    // Faz a inserção da faixa na lista de faixas do artista...
    if (artista->faixas == NULL) {
        artista->faixas = novaFaixa;
    } else {

        faixaAtual = artista->faixas;
        faixaAnterior = NULL;

        while (faixaAtual != NULL) {
            if (strcmp(faixaAtual->titulo, novaFaixa->titulo) == 1) {
                cadastrado = true;
                novaFaixa->prox = faixaAtual;
                if (faixaAtual == artista->faixas) {
                    artista->faixas = novaFaixa;
                } else {
                    faixaAnterior->prox = novaFaixa;
                }
                break;
            }//if
            //movimentando os ponteiros
            faixaAnterior = faixaAtual;
            faixaAtual = faixaAtual->prox;
        }//while

        if (!cadastrado) {
            faixaAnterior->prox = novaFaixa;
        }
    }
}

//Artista
void insereArtista(ListaDisco *discos) {
    // Inicializa variáveis necessárias..
    int encontrado = 0;
    char discoInformado[45] = "\0";
    Disco *discoSelect = NULL;
    Artista *artistaAtual = NULL;
    Artista *artistaAnterior = NULL;
    Artista *novoArtista = (Artista*) malloc(sizeof (Artista));
    //	novoArtista->nome   = NULL;
    novoArtista->faixas = NULL;
    novoArtista->prox = NULL;

    // Listar os discos pra escolha..
    listarDiscos(discos);
    printf("\n\t\t=====| CADASTRAR ARTISTA EM DISCO |=====\n\n");

    discoSelect = selecionarDisco(discos, NULL);

    if (discoSelect == NULL) {
        printf("\n\n\t DISCO NAO ENCONTRADO!!!");
        system("pause");
        return;
    } else {
        // pega dados do usuário e popula objeto, depois trata a inserção..
        printf("\n\n\t INFORME OS DADOS DO ARTISTA: ");
        printf("\n\n\t NOME: ");
        strcpy(novoArtista->nome, lerString());
        // if for nullo, instânciar um novo e sentar o bambu no cadastro..
        // tratar inserção..
        if (discoSelect->participacao == NULL) {
            discoSelect->participacao = novoArtista;
        } else { // >>> TECHO DO VANDERSON <<<
            int inserido = 0;
            artistaAtual = discoSelect->participacao;
            artistaAnterior = NULL;

            while (artistaAtual != NULL) {
                if (strcmp(artistaAtual->nome, novoArtista->nome) == 1) {
                    inserido = 1;
                    novoArtista->prox = artistaAtual;
                    if (artistaAtual == discoSelect->participacao) {
                        discoSelect->participacao = novoArtista;
                    } else {
                        artistaAnterior->prox = novoArtista;
                    }
                    break;
                }//if
                //movimentando os ponteiros
                artistaAnterior = artistaAtual;
                artistaAtual = artistaAtual->prox;
            }//while

            if (!inserido) {
                artistaAnterior->prox = novoArtista;
            }
        }
        // >>> TECHO DO VANDERSON <<<
    }
}

void faixasArtista(Artista *artista) {
    Faixa *faixa = artista->faixas;
    int cont = 0;

    while (faixa != NULL) {
        printf("\t\t(%d) - %s AOVIVO: %d INSTRUM.: %d \n", ++cont, faixa->titulo, faixa->aoVivo, faixa->instrumental);
        faixa = faixa->prox;
    }
}

void listaArtistas(ListaDisco *discos) {
    limparPrompt();
    Artista *artista = NULL;
    int cont = 0, encontrado = 0;
    char discoInformado[45];
    Disco *discoAtual = NULL;

    // Listar os discos pra escolha..
    listarDiscos(discos);
    printf("\n\n\t INFORME O NOME DO DISCO: ");

    // Armazenar o disco selecionado..
    strcpy(discoInformado, lerString());

    // Buscar e Pegar o ponteiro pra Artista do disco selecionado..
    discoAtual = discos->inicio;

    while (discoAtual != NULL) {
        if (strcmp(discoAtual->titulo, discoInformado) == 0) { // Disco escolhido!
            encontrado = 1;
            break;
        } else {
            discoAtual = discoAtual->prox;
        }
    }

    if (encontrado != 1) {
        printf("\n\n\n\t\tDISCO NAO ENCONTRADO!!!\n\n");
    } else {
        artista = discoAtual->participacao;
        printf("\n\n\n\t\t=====| ARTISTAS DO DISCO |=====\n\n");

        artistasDisco(discoAtual);
    }
    system("pause");
}

Artista* selectArtista(Disco *disco, char * nome) {

    char artistaInformado[45];
    Artista *artistaAtual = NULL;

    printf("\n\n\t INFORME O NOME DO ARTISTA: ");
    // Armazenar o artista selecionado..
    strcpy(artistaInformado, lerString());
    // Buscar e Pegar o ponteiro pra Artista do disco selecionado..
    artistaAtual = disco->participacao;

    while (artistaAtual != NULL) {
        if (strcmp(artistaAtual->nome, artistaInformado) == 0) { // Artista escolhido!
            return artistaAtual;
        } else {
            artistaAtual = artistaAtual->prox;
        }
    }
    return NULL;
}

void listaFaixasArtista(ListaDisco *discos) {
    Disco * discoAtual = NULL;
    Artista * artistaAtual = NULL;
    Faixa * faixaAtual = NULL;
    int cont = 0;

    limparPrompt();
    printf("\n\n\t ===| LISTA FAIXAS DE ARTISTA EM DISCOS: |===");

    discoAtual = discos->inicio;
    while (discoAtual != NULL) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != NULL) {
            printf("\n\n ARTISTA: [%s]\n", artistaAtual->nome);

            infoFaixasArtistas(discos, artistaAtual);

            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
    printf("\n\n");
    system("pause");
}

void listaTotalFaixasArtista(ListaDisco *discos) {
    Disco * discoAtual = NULL;
    Artista * artistaAtual = NULL;
    Faixa * faixaAtual = NULL;
    int cont = 0;
    limparPrompt();
    printf("\n\n\t ===| QUANT. FAIXAS POR ARTISTA: |===");

    discoAtual = discos->inicio;
    while (discoAtual != NULL) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != NULL) {
            printf("\n\n\t [%s]\n", artistaAtual->nome);
            infoArtistas(discos, artistaAtual);

            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
    printf("\n\n");
    system("pause");
}

void infoFaixasArtistas(ListaDisco *discos, Artista *artistaPesquisado) {
    Disco   * discoAtual   = VAZIO;
    Artista * artistaAtual = VAZIO;
    Faixa   * faixaAtual   = VAZIO;
    int cont = 0;

    discoAtual = discos->inicio;
    while (discoAtual != NULL) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != NULL) {

            if (strcmp(artistaPesquisado->nome, artistaAtual->nome) == 0) {
                //					printf("\n>>>strcmp<<<\n");
                //					system("pause");
                printf("\n\n\t DISCO: %s", discoAtual->titulo);
                faixaAtual = artistaAtual->faixas;
                while (faixaAtual != NULL) {
                    //						printf("\n>>>faixa<<<\n");
                    //						system("pause");
                    printf("\n\n\t\t(%d) FAIXA: %s | AO VIVO [%d] | INSTRUMENTAL [%d]", cont++, faixaAtual->titulo,
                            faixaAtual->aoVivo, faixaAtual->instrumental);
                    faixaAtual = faixaAtual->prox;
                }
            }
            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
}

void infoArtistas(ListaDisco *discos, Artista *artistaPesquisado) {
    Disco   * discoAtual   = VAZIO;
    Artista * artistaAtual = VAZIO;
    Faixa   * faixaAtual   = VAZIO;
    int cont = 0;

    discoAtual = discos->inicio;
    while (discoAtual != NULL) {
        artistaAtual = discoAtual->participacao;
        while (artistaAtual != NULL) {

            if (strcmp(artistaPesquisado->nome, artistaAtual->nome) == 0) {
                faixaAtual = artistaAtual->faixas;
                while (faixaAtual != NULL) {
                    cont++;
                    faixaAtual = faixaAtual->prox;
                }
            }
            artistaAtual = artistaAtual->prox;
        }
        discoAtual = discoAtual->prox;
    }
    printf("\n\n\t QUANTIDADE FAIXAS: %d", cont);
}

//Disco
void popularDiscos(ListaDisco *discos) {
    insereDisco(discos, "vanderson", "2000");
    insereDisco(discos, "edilson", "2000");
    insereDisco(discos, "erick", "2000");
}

void insereDisco(ListaDisco *discos, char *titulo, char *ano) {
    Disco *novo = (Disco *) malloc(sizeof (Disco));
    Disco *anterior, *atual = VAZIO;
    bool inserido = false;

    if (titulo == NULL) {
        printf("\n\n\n\t\t=====| CADASTRO DISCO |=====\n\n");
        printf("\tInforme TITULO: ");
        strcpy(novo->titulo, lerString());
        printf("\n\tANO: ");
        strcpy(novo->ano, lerString());
    } else {
        strcpy(novo->titulo, titulo);
        strcpy(novo->ano, ano);
        novo->participacao = NULL;
    }

    novo->prox = NULL;
    novo->ante = NULL;

    if (discos->inicio == NULL) {
        //Lista VAZIA
        discos->inicio = novo;
        discos->fim = novo;
        discos->total = 1;
    } else {
        atual = discos->inicio;
        anterior = NULL;

        while (atual != NULL) {
            if (strcmp(atual->titulo, novo->titulo) == 1) {
                inserido = true;
                novo->prox = atual;
                atual->ante = novo;
                if (atual == discos->inicio) {
                    discos->inicio = novo;
                } else {
                    novo->ante = anterior;
                    anterior->prox = novo;
                }
                break;
            }
            //movimentando os ponteiros
            anterior = atual;
            atual = atual->prox;
        }
        if (!inserido) {
            anterior->prox = novo;
            novo->ante = anterior;
            discos->fim = novo;
        }
        discos->total++;
    }
}

void listarDiscos(ListaDisco *discos) {
    limparPrompt();
    Disco *atual = discos->inicio;
    int cont = 0;

    printf("\n\n\n\t\t=====| LISTA DE DISCOS |=====\n\n");

    while (atual != NULL) {
        printf("\t(%d) - %s [%s]\n", ++cont, atual->titulo, atual->ano);
        atual = atual->prox;
    }//while
    system("pause");
}

Disco* selecionarDisco(ListaDisco *discos, char *titulo) {
    Artista *artista = NULL;
    char discoInformado[45];
    Disco *discoAtual = NULL;

    if (titulo != NULL) {
        strcpy(discoInformado, titulo);
    } else {
        printf("\n\n\t INFORME O NOME DO DISCO: ");
        // Armazenar o disco selecionado..
        strcpy(discoInformado, lerString());
    }

    // Buscar e Pegar o ponteiro pra Artista do disco selecionado..
    discoAtual = discos->inicio;

    while (discoAtual != NULL) {
        if (strcmp(discoAtual->titulo, discoInformado) == 0) { // Disco escolhido!
            return discoAtual;
        } else {
            discoAtual = discoAtual->prox;
        }
    }
    return NULL;
}

void artistasDisco(Disco *disco) {
    Artista *atual = disco->participacao;
    int cont = 0;

    while (atual != NULL) {
        printf("\t\t(%d) - %s \n", ++cont, atual->nome);
        atual = atual->prox;
    }
}

void consultarDisco(ListaDisco *discos) {
    limparPrompt();
    Artista *artista = NULL;
    int cont, encontrado = 0;
    Disco *discoSelect = NULL;

    // Listar os discos pra escolha...
    listarDiscos(discos);
    printf("\n\t\t=====| CONSULTAR DISCO |=====\n\n");

    discoSelect = selecionarDisco(discos, NULL);
    limparPrompt();

    if (discoSelect == NULL) {
        printf("\n\t\tDISCO NAO ENCONTRADO!!!\n\n");
    } else {
        artista = discoSelect->participacao;

        printf("\n\n\n\t\t=====| INFO DO DISCO |=====\n\n");

        printf("\n\t TITULO: %s", discoSelect->titulo);
        printf("\n\t ANO: %s", discoSelect->ano);
        printf("\n\t DISCO ANTERIOR: %s", discoSelect->ante->titulo);
        printf("\n\t DISCO PROXIMO: %s", discoSelect->prox->titulo);
        // Exibe artistas do Disco selecionado.
        printf("\n\n\t PARTICICOES: %s\n", discoSelect->participacao->nome);
        artistasDisco(discoSelect);

        Artista * artistaAtual = discoSelect->participacao;

        printf("\n\n\t\t=====| FAIXAS |=====\n\n");

        while (artistaAtual != NULL) {

            printf("\t ARTISTA %s\n", artistaAtual->nome);

            //LISTA AS FAIXAS DO ARTISTA..
            faixasArtista(artistaAtual);

            artistaAtual = artistaAtual->prox;
        }
    }
    system("pause");
}

void alterarDisco(ListaDisco *discos) {
    Artista * artista = NULL;
    // INFORMAR O DISCO A SER ALTERADO..
    Disco *discoSelect = NULL;

    // Listar os discos pra escolha..
    listarDiscos(discos);
    printf("\n\t\t=====| ALTERAR DISCO |=====\n\n");

    // CAPTURAR O DISCO..
    discoSelect = selecionarDisco(discos, NULL);
    limparPrompt();

    if (discoSelect == NULL) {
        printf("\n\t\tDISCO NAO ENCONTRADO!!!\n\n");
    } else {
        artista = discoSelect->participacao;
        // LISTAR OS CAMPOS INDIVIDUALMENTE.. (se nÃ£o informar nada, Ã± alterar)	
        printf("\n\n\n\t\t=====| INFO ATUAL DO DISCO |=====\n");

        printf("\n\t\t TITULO: %s", discoSelect->titulo);
        printf("\n\t\t ANO: %s", discoSelect->ano);

        printf("\n\t\t=====| NOVAS INFO DO DISCO |=====\n");

        printf("\n\t\t NOVO TITULO: ");
        strcpy(discoSelect->titulo, lerString());
        printf("\n\t\t NOVO ANO: ");
        strcpy(discoSelect->ano, lerString());
        printf("\n\t\t Alterando.");
        carregando(5);
        printf("\n\t\t DISCO ALTERADO COM SUCESSO!\n\n");
        printf("\n\t\t=================================\n\n");
    }
    system("pause");
}

void ordenarDiscoUP(ListaDisco *discos) {

    if (discos->total < 2) {
        printf("\n\n\t Nao eh necessario ordenar a lista!\n\n");
        system("pause");
        return;
    }

    int moveu_elemento = 0;
    int ordenado = 0;

    Disco * atual = NULL;
    Disco * proximo = NULL;

    while (ordenado != 1) {
        atual = discos->inicio;
        proximo = atual->prox;

        while (proximo != NULL) {
            moveu_elemento = 0;

            if (strcmp(atual->titulo, proximo->titulo) == 1) {

                proximo->ante = atual->ante;
                atual->prox = proximo->prox;

                if (proximo->prox != NULL) {
                    proximo->prox->ante = atual;
                }
                if (atual->ante != NULL) {
                    atual->ante->prox = proximo;
                }
                proximo->prox = atual;
                atual->ante = proximo;

                if (atual == discos->inicio)
                    discos->inicio = proximo;
                if (proximo == discos->fim)
                    discos->fim = atual;

                moveu_elemento = 1;
            }
            if (moveu_elemento) {
                atual = discos->inicio; // pula pro prÃ³ximo.
                proximo = atual->prox; // pula pro prÃ³ximo.
            } else {
                atual = proximo;
                proximo = proximo->prox;
            }
        }

        if (moveu_elemento == 0) // Passou a lista toda e nÃ£o moveu.
            ordenado = 1;
        else
            moveu_elemento = 0;
    }//while
    printf("\n\n\t Ordenacao Concluida!\n\n");
    //    _system("timeout 100");
    system("pause");
}

void ordenarDiscoDOWN(ListaDisco *discos) {

    if (discos->total < 2) {
        printf("\n\n\t Nao eh necessario ordenar a lista!\n\n");
        system("pause");
        return;
    }

    int moveu_elemento = 0;
    int ordenado = 0;

    Disco * atual = NULL;
    Disco * proximo = NULL;

    while (ordenado != 1) {
        atual = discos->inicio;
        proximo = atual->prox;

        while (proximo != NULL) {
            moveu_elemento = 0;

            if (strcmp(atual->titulo, proximo->titulo) == -1) {

                proximo->ante = atual->ante;
                atual->prox = proximo->prox;

                if (proximo->prox != NULL) {
                    proximo->prox->ante = atual;
                }
                if (atual->ante != NULL) {
                    atual->ante->prox = proximo;
                }
                proximo->prox = atual;
                atual->ante = proximo;

                if (atual == discos->inicio)
                    discos->inicio = proximo;
                if (proximo == discos->fim)
                    discos->fim = atual;

                moveu_elemento = 1;
            }
            if (moveu_elemento) {
                atual = discos->inicio; // pula pro prÃ³ximo.
                proximo = atual->prox; // pula pro prÃ³ximo.
            } else {
                atual = proximo;
                proximo = proximo->prox;
            }
        }

        if (moveu_elemento == 0) // Passou a lista toda e não moveu.
            ordenado = 1;
        else
            moveu_elemento = 0;
    }//while
    printf("\n\n\t Ordenacao Concluida!\n\n");
    system("pause");
}

void listaFaixasDisco(ListaDisco *discos) {
    limparPrompt();
    Artista *artistaAtual = NULL;
    int cont = 0, encontrado = 0;
    char discoInformado[45];
    Disco *discoAtual = NULL;
    Faixa *faixaAtual = NULL;

    //LISTA OS DISCOS DA LISTA..
    listarDiscos(discos);
    //SOLICITA O DISCO..
    discoAtual = selecionarDisco(discos, NULL);
    limparPrompt();
    printf("\n\n\t ===| LISTA FAIXAS DE DISCO: |===");

    if (discoAtual == NULL)
        printf("\n\n\n\t\tDISCO NAO ENCONTRADO!!!\n\n");
    else {
        printf("\n\n\t DISCO: %s", discoAtual->titulo);

        artistaAtual = discoAtual->participacao;

        printf("\n\n\t\t=====| FAIXAS |=====\n\n");

        while (artistaAtual != NULL) {

            printf("\t ARTISTA %s\n", artistaAtual->nome);

            //LISTA AS FAIXAS DO ARTISTA..
            faixasArtista(artistaAtual);

            artistaAtual = artistaAtual->prox;
        }
    }
    system("pause");
}

void listaTotalFaixasDisco(ListaDisco *discos) {
    Artista *artistaAtual = NULL;
    int cont = 0;
    Disco *discoAtual = NULL;
    Faixa *faixaAtual = NULL;

    discoAtual = discos->inicio;
    limparPrompt();
    printf("\n\n\t ===| QUANT. FAIXAS POR DISCO |===");

    if (discoAtual == NULL)
        printf("\n\n\n\t\tDISCO NAO ENCONTRADO!!!\n\n");
    else {
        while (discoAtual != NULL) {
            printf("\n\t DISCO SELECIONADO: %s", discoAtual->titulo);

            artistaAtual = discoAtual->participacao;

            while (artistaAtual != NULL) {

                faixaAtual = artistaAtual->faixas;

                // RODA AS FAIXAS DE CADA ARTISTA..
                while (faixaAtual != NULL) {
                    ++cont;
                    faixaAtual = faixaAtual->prox;
                }
                artistaAtual = artistaAtual->prox;
            }
            printf("\n\t\tCarregando, aguarde.");
            carregando(2);
            printf("\n\t QUANTIDADE DE FAIXAS: [%d]\n", cont);
            cont = 0;
            discoAtual = discoAtual->prox;
        }
    }
    system("pause");
}

void excluirDisco(ListaDisco *discos, char *titulo) {
    //Disco *novo = (Disco *) malloc(sizeof (Disco));
    Disco *anterior, *atual;
    int removido = 0;

    if (titulo == NULL) {
        listarDiscos(discos);
        printf("\n\n\n\t\t=====| EXCLUIR DISCO |=====\n\n");
        printf("\tInforme TITULO: ");
        strcpy(titulo, lerString());
    }

    atual = discos->inicio;
    anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            removido = 1;
            
            printf("\n\nIGUAL!\n\n");
            pauseScreen();
            atual->ante->prox = atual->prox;
            atual->prox->ante = atual->ante;
            
            atual = NULL;
            break;
        }
        //movimentando os ponteiros
        anterior = atual;
        atual = atual->prox;
    }
    discos->total--;
}
#endif	// STRUCTURES_H
