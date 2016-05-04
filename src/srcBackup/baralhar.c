#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

/** 
Conforme as regras do jogo, a primeiro jogador a jogar é aquele que tem o 3 de ouros na sua mão.
Esta função procura nas mãos de cada jogador o valor e o naipe correspondentes ao 3 de ouros. 
O jogador que tiver essa carta, passará a ser o actual_jogador, dando então prosseguimento. 
@param e O estado actual.
@returns Um inteiro correspondente ao jogador que vai executar primeiro a jogada.
*/

int primeiro_jogar(ESTADO e){
    int n = 0;
    
    if (carta_existe(e.mao[0], 0, 0)) {
        n = 0;
    }
    
    if (carta_existe(e.mao[1], 0, 0)) {
        n = 1;   
    }
    
    if (carta_existe(e.mao[2], 0, 0)) {
        n = 2;
    }
    
    if (carta_existe(e.mao[3], 0, 0)) {
        n = 3;  
    }
    
    return n;
}


/** 
Função que distribui as cartas por todas as mãos, de igual modo (13 para cada).
Através da função "rand", as cartas são distribuidas aleatoriamente. Aqui, são feitas outras tarefas:
O actual_jogador vai tomar o valor da função primeiro_jogador, previamente definida, que indica o jogador que começa o jogo,
da-mos a e.cartas_bots[e.actual_jogador] o valor 1, de maneira que se um bot começar o jogo, este vai apresentar o 3 de ouros no tabuleiro,
e a ultimo_jogador toma o valor do actual_jogador, guardando assim o ultimo jogador que jogou corretamente.
@returns O novo estado.
*/

ESTADO baralhar () {
    int a=0, b=0, i=0, j=0, k=0, l=0, n=0, v=0, jogador;
    ESTADO e = {{0},0,{0},0,0,0,0,-1,0,{0},0,1};

    for (a = 0; a < 4; a++) {
        e.cartas[a] = 13;
    }

    for (b = 0; b < 4; b++) {
        e.cartas_bots[b] = 0;
    }

    for (n = 0; n <= 3; n++)
        for (v = 0; v <= 12; v++) {
            jogador = (rand() % 4);
            switch (jogador) {
                case 0: if (i == 13) v--; else { e.mao[jogador] +=  (add_carta (0, n, v)); i++; } break;
                case 1: if (j == 13) v--; else { e.mao[jogador] +=  (add_carta (0, n, v)); j++; } break;
                case 2: if (k == 13) v--; else { e.mao[jogador] +=  (add_carta (0, n, v)); k++; } break;
                case 3: if (l == 13) v--; else { e.mao[jogador] +=  (add_carta (0, n, v)); l++; } break;
            }
        }
        
    e.actual_jogador = primeiro_jogar(e);
    e.cartas_bots[e.actual_jogador] = 1;
    e.ultimo_jogador = e.actual_jogador;
    e.layout = 0;
    return e;   
}