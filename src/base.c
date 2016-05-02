#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

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