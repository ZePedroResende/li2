#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

/* Esta função tem como objetivo imprimir as cartas no tabuleiro.
Se a carta a apresentar se encontre na mao do jogador (mao tomar o valor de 0 e o actual_jogador no estado for igual a 0),
e caso a carta seja selecionada e entao adicionada ao highlight , se ja se encontrar no highlight, entao é removida do highlight .
Caso contrario , se a carta encontra-se na mao de um bot logo e imprimido o verso de uma carta caso contrario a carta
ja foi jogada por um bot logo e mostrada a carta correspondente.
*/
void imprime_carta(char *path, int x, int y, ESTADO e, int mao, int naipe, int valor) {
    char *suit = NAIPES;
    char *rank = VALORES;
    char script[10240];
    ESTADO novo = e;
    novo.card = 1;
    
    if (mao == 0 && e.actual_jogador == 0) {
        if (carta_existe (novo.highlight, naipe, valor)) {
            novo.highlight = rem_carta(novo.highlight, naipe, valor);
        }
        
        else {
            novo.highlight = add_carta(novo.highlight, naipe, valor);
        }
        
        sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
        printf("<a xlink:href = \"%s\"><image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" /></a>\n", script, x, y, path, rank[valor], suit[naipe]);  
    }
    
    else {
        if (carta_existe(e.mao[1],naipe,valor) || carta_existe(e.mao[2],naipe,valor) || carta_existe(e.mao[3],naipe,valor))
            printf("<image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/11C.png\" />\n", x, y, path);
        else printf("<image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" />\n", x, y, path, rank[valor], suit[naipe]);
    }
}

/*
    Função auxiliar que recebe parametros da função imprime. Aqui é vista a forma de como as cartas são apresentadas.
*/
void imprime_aux_valor (ESTADO e, int m, int bx1, int by1, int bx2, int by2, int bx3, int by3, int x, int y, char *path) {
    
    int n,v;

    for (v = 0; v < 13; v++) {
        for (n = 0; n < 4; n++){
            if (m == 1 && carta_existe(e.cartas_bots[1],n,v)) {
                imprime_carta(path, bx1, by1, e, m, n, v);
                by1+=20;
            }
            if (m == 2 && carta_existe(e.cartas_bots[2],n,v)) {
                imprime_carta(path, bx2, by2, e, m, n, v);
                bx2+=20;
            }
            if (m == 3 && carta_existe(e.cartas_bots[3],n,v)) {
                imprime_carta(path,bx3, by3, e, m, n, v);
                by3 += 20;
            }
            if (carta_existe(e.mao[m], n, v)) {
                if (m % 2 == 0) {
                    x += 30;
                }
                else {
                    y += 30;
                }
                if (m == 0 && carta_existe(e.highlight, n, v)) {
                    imprime_carta(path, x, (y - 20), e, m, n, v);
                }
                else {
                    imprime_carta(path, x, y, e, m, n, v);
                }
            }
        }
    }
}

void imprime_aux_naipe (ESTADO e, int m, int bx1, int by1, int bx2, int by2, int bx3, int by3, int x, int y, char *path) {

    int n,v;

    for (n = 0; n < 4; n++){
        for (v = 0; v < 13; v++) {
            if (m == 1 && carta_existe(e.cartas_bots[1],n,v)) {
                imprime_carta(path, bx1, by1, e, m, n, v);
                by1+=20;
            }
            if (m == 2 && carta_existe(e.cartas_bots[2],n,v)) {
                imprime_carta(path, bx2, by2, e, m, n, v);
                bx2+=20;
            }
            if (m == 3 && carta_existe(e.cartas_bots[3],n,v)) {
                imprime_carta(path,bx3, by3, e, m, n, v);
                by3 += 20;
            }
            if (carta_existe(e.mao[m], n, v)) {
                if (m % 2 == 0) {
                    x += 30;
                }
                else {
                    y += 30;
                }
                if (m == 0 && carta_existe(e.highlight, n, v)) {
                    imprime_carta(path, x, (y - 20), e, m, n, v);
                }
                else {
                    imprime_carta(path, x, y, e, m, n, v);
                }
            }
        }
    }
}

/*
Apresenta as cartas no tabuleiro nas respetivas coordenadas.
*/
void imprime (char *path, ESTADO e) {
    
    int m, bx1= 820 , by1 = 250 , bx2=570 , by2 = 150 , bx3= 395 , by3 = 250;
    int X[4] = {405, 1190, 405, 10};
    int Y[4] = {595, 100, 15, 100};
    
    for(m = 0; m < 4; m++) {
        int x = X[m], y = Y[m];
        if (e.layout == 1) {
            imprime_aux_valor(e, m, bx1, by1, bx2, by2, bx3, by3, x, y, path);
        }
        else{
            imprime_aux_naipe(e, m, bx1, by1, bx2, by2, bx3, by3, x, y, path);
        }
    }
}