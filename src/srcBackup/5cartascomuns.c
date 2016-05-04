#include "big2.h"

/** 
No caso dos straight e straight flush, os ases podiam tomar dois valores diferentes, e o 2 era uma carta baixa, e não a mais alta do jogo. Para isso, criamos um array com 14 posições.
Conforme a validação do que é selecionado pelo utilizador, vemos que "valor" é que toma os ases e o 2 (quando são selecionados), estando estes codificados.
Para usarmos esses valores em comparações ou em qualquer outro processo, temos de os descodificar, para tudo funcionar corretamente. A função descodifica_straight faz exatamente isso, retorna o "verdadeiro" valor da carta (não codificado).
@param maiorCarta O valor da maior carta codificado.
@returns O valor da maior carta descodificado.
*/
int descodifica_straight (int maiorCarta) {
    int v;
    v = maiorCarta;
    switch (v) {
        case 0: { v = 11; } break;
        case 1: { v = 12; } break;
        default: { v -= 2; } break;
    }
    return v;
}

/**
Esta função faz o contrário da função descodifica_straight. Pega nos valores normais do jogo, e codifica-os de forma a serem trabalhados em validações de straight e straight flush.
@param v O valor da maior carta descodificado.
@returns O valor da maior carta codificado.
*/
int codifica(int v){
    switch (v) {
        case 11: return 13; break;
        case 12: return 1; break;
        default:{v=v+2; return v;} break;
    }
}

/**
A função validacao_5cartas identifica qual tipo de combinação é que vai ser analisada. Conforme os returns de 1,2,3,4,5, o programa sabe qual combinação avaliar.
@param m A mão de um jogador.
@returns Um inteiro correspondente a uma sequência.
*/
int validacao_5cartas (MAO m) {
    
    if ((maior_carta_straightflush_bots(m)) != -1) {
        return 5;
    }
    else {
        if ((valida_straight(m)) == 1) {
            return 1;
        }
        else {
            if ((valida_flush(m)) != -1) {
                return 2;
            }
            else {
                if ((valida_fullhouse(m)) != -1) {
                    return 3;
                }
                else {
                    if ((maior_carta_fourkind(m)) != -1) {
                        return 4;
                    }
                }
            }
        }
    }
    return -1;
}
