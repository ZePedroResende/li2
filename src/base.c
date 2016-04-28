#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

/* Transforma um estado numa string do url. */
char* estado2str(ESTADO e){
    static char str[10240];
    sprintf(str, FORMATO, e.mao[0], e.mao[1], e.mao[2], e.mao[3], e.highlight, e.cartas[0], e.cartas[1], e.cartas[2], e.cartas[3], e.play, e.pass, e.card,e.ultimo_jogador, e.ultima_jogada, e.actual_jogador, e.cartas_bots[0], e.cartas_bots[1], e.cartas_bots[2], e.cartas_bots[3], e.layout,e.start);
    
    return str;
}

/* Transforma a string do url num estado novo. */
ESTADO str2estado(char* str){
    ESTADO e;
    sscanf(str, FORMATO, &e.mao[0], &e.mao[1], &e.mao[2], &e.mao[3], &e.highlight, &e.cartas[0], &e.cartas[1], &e.cartas[2], &e.cartas[3], &e.play, &e.pass, &e.card,&e.ultimo_jogador, &e.ultima_jogada, &e.actual_jogador, &e.cartas_bots[0], &e.cartas_bots[1], &e.cartas_bots[2], &e.cartas_bots[3], &e.layout,&e.start);
    
    return e;
}


/** brief Devolve o índice da carta
@param naipe O naipe da carta (inteiro entre 0 e 3)
@param valor O valor da carta (inteiro entre 0 e 12)
@return O índice correspondente à carta
*/
int indice(int naipe, int valor) {
    return naipe * 13 + valor;
}

/** brief Adiciona uma carta ao estado
@param ESTADO O estado atual
@param naipe O naipe da carta (inteiro entre 0 e 3)
@param valor O valor da carta (inteiro entre 0 e 12)
@return O novo estado
*/
long long int add_carta(long long int ESTADO, int naipe, int valor) {
    int idx = indice(naipe, valor);
    return ESTADO | ((long long int) 1 << idx);
}

/** brief Remove uma carta do estado
@param ESTADO O estado atual
@param naipe O naipe da carta (inteiro entre 0 e 3)
@param valor O valor da carta (inteiro entre 0 e 12)
@return O novo estado
*/
long long int rem_carta(long long int ESTADO, int naipe, int valor) {
    int idx = indice(naipe, valor);
    return ESTADO & ~((long long int) 1 << idx);
}

/** brief Verifica se uma carta pertence ao estado
@param ESTADO O estado atual
@param naipe O naipe da carta (inteiro entre 0 e 3)
@param valor O valor da carta (inteiro entre 0 e 12)
@return 1 se a carta existe e 0 caso contrário
*/
int carta_existe(long long int ESTADO, int naipe, int valor) {
    int idx = indice(naipe, valor);
    return (ESTADO >> idx) & 1;
}