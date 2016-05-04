#include <stdio.h>
#include <string.h>
#include "big2.h"

/** 
Transforma um estado numa string do url, e retorna essa string. 
@param e O estado actual.
@returns Uma string com o estado.
*/
char* estado2str(ESTADO e){
    static char str[10240];
    sprintf(str, FORMATO, e.mao[0], e.mao[1], e.mao[2], e.mao[3], e.highlight, e.cartas[0], e.cartas[1], e.cartas[2], e.cartas[3], e.play, e.pass, e.card,e.ultimo_jogador, e.ultima_jogada, e.actual_jogador, e.cartas_bots[0], e.cartas_bots[1], e.cartas_bots[2], e.cartas_bots[3], e.layout,e.start);
    
    return str;
}

/** 
Transforma a string do url num estado novo, e retorna esse estado. 
@param str Uma string com o estado.
@returns O novo estado.
*/
ESTADO str2estado(char* str){
    ESTADO e;
    sscanf(str, FORMATO, &e.mao[0], &e.mao[1], &e.mao[2], &e.mao[3], &e.highlight, &e.cartas[0], &e.cartas[1], &e.cartas[2], &e.cartas[3], &e.play, &e.pass, &e.card,&e.ultimo_jogador, &e.ultima_jogada, &e.actual_jogador, &e.cartas_bots[0], &e.cartas_bots[1], &e.cartas_bots[2], &e.cartas_bots[3], &e.layout,&e.start);
    
    return e;
}

