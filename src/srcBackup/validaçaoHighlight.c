#include "big2.h"


/**
Conta o número de cartas que se encontra numa mao numa dada altura.
@param m A mão de um jogador.
@returns O número de cartas.
*/
int numero_de_cartas(MAO m) {
    
    int n, v, contaCartas=0;
    
    for (n = 0; n < 4; n++) {
        for (v = 0; v < 13; v++)
        if (carta_existe(m, n, v)) contaCartas++;
    }
    
    return contaCartas;
}


/** 
Confirma se a mão que é recebida (o highlight), tem uma, duas ou três cartas.
@param m A mão de um jogador.
@returns Um inteiro 0 se tiver mais de três cartas, caso contrário retorna 1. 
*/
int combinacao_valida(MAO m) {
    
    if ((numero_de_cartas (m)) > 3) {
        return 0;
    }
    
    else return 1;
}

/** 
Compara o tamanha entre duas mãos, ou seja, ve o tamanho da ultima jogada, e compara o tamanho com a jogada actual,
e vê se a combinação tem o mesmo tamanho.
@param m1 A mão de um jogador.
@param m2 A mão de outro jogador.
@returns Um inteiro 1 se as mãos tiverem o mesmo tamanha, 0 caso contrário.
*/
int compara_tamanho(MAO m1, MAO m2){
    if (numero_de_cartas(m1) == numero_de_cartas(m2)) {
        return 1;
    }
    
    return 0;
}

/* *
Numa jogada de 1,2 e 3 cartas esta função é utilizada para comparar o valor entre a ultima_jogada e a efetuda pelo atual_jogador. 
@param m A mão de um jogador.
@returns O valor de uma carta.
*/
int da_valor (MAO m){
    
    int n, v, primeiraCarta, flag = 0;
    primeiraCarta = 0;
    
    for (n = 0; n < 4 && flag != 1; n++) {
        
        for (v = 0; v < 13 && flag != 1; v++)
        
        if (carta_existe(m, n, v)){
            primeiraCarta = v ;
            flag = 1;
        }
    }
    
    for (n = 0; n < 4 ; n++) {
        
        for (v = 0; v < 13 ; v++)
        
        if (carta_existe(m, n, v)){
            if (v != primeiraCarta){
                return -1 ;
            }
        }
    }
    return primeiraCarta;
}

/** 
Esta função obtém o maior naipe dentro de uma mão, de forma a ser usado para avaliar a maior jogada. 
@param m A mão de um jogador.
@returns O naipe de uma carta.
*/

int da_maior_naipe (MAO m){
    int n, v, maior=0;
    
    for (n = 0; n < 4; n++) {
        
        for (v = 0; v < 13; v++)
        
        if (carta_existe(m, n, v)) { if (n > maior) maior = n;}
    }
    
    return maior;
}


/** 
Aqui, é verificado se a jogada actual é maior que a jogada anterior. Conforme o retorno da função dá valor, a jogada
actual é possível ser realizada ou não. Ao comparar, de os retornos das duas funções forem iguais, ou seja, se os maiores
valores de cada mão forem iguais, comparamos o naipe, assim identificando qual a maior jogada.
@param m1 A mão de um jogador.
@param m2 A mão de outro jogador.
@returns Um inteiro 1 caso seja possível jogar, 0 caso contrário.
*/

int combinacao_maior (MAO m1, MAO m2) {
    int n =0;
    if ((da_valor(m2)) != -1){
        if (da_valor(m1) < da_valor(m2)) n =1;
        if (da_valor(m1) > da_valor(m2)) n= 0 ;
        if (da_valor(m1) == da_valor(m2)) {
            if (da_maior_naipe(m1) < da_maior_naipe(m2)) n=1;
            
        }
    }
    
    else n= 0;
    
    return n;
}



/**
Função que valida o highlight do jogador, consoante a ultima jogada. 
Neste caso, como a ultima jogada foi um straight, a função valida se as 5 cartas (straight) escolhidas pelo utilizador são válidas de ser jogadas.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_straight (ESTADO e) {
    /*VAI BUSCAR A MAIOR CARTA DAS DUAS*/
    if ((maior_carta_straight(e.highlight)) > (maior_carta_straight(e.ultima_jogada))) {
        return 1;
    }
    else {
        if ((maior_carta_straight(e.highlight)) == (maior_carta_straight(e.ultima_jogada))) {
            if ((maior_naipe_straight(e.highlight, (maior_carta_straight(e.highlight)))) > (maior_naipe_straight(e.ultima_jogada, (maior_carta_straight(e.ultima_jogada))))) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}


/**
Função que valida o highlight do jogador, consoante a ultima jogada. 
Neste caso, como a ultima jogada foi um flush, a função valida se as 5 cartas (flush) escolhidas pelo utilizador são válidas de ser jogadas.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_flush (ESTADO e) {
    /*VAI BUSCAR O NAIPE DAS DUAS, E VE SE O DE O HIGHLIGHT É MAIOR, E SE O NAIPE FOR IGUAL, VAI BUSCAR A MAIOR CARTA*/
    if ((valida_flush(e.highlight)) < (valida_flush(e.ultima_jogada))) {
        return 0;
    }
    else {
        if ((valida_flush(e.highlight)) > (valida_flush(e.ultima_jogada))) {
            return 1;
        }
        else { /*e.highlight == e.ultima_jogada*/
            if ((maior_carta_flush(e.highlight)) < (maior_carta_flush(e.ultima_jogada))) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    return 0;
}



/**
Função que valida o highlight do jogador, consoante a ultima jogada. 
Neste caso, como a ultima jogada foi um full house, a função valida se as 5 cartas (full house) escolhidas pelo utilizador são válidas de ser jogadas.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_fullhouse (ESTADO e) {
    if (valida_fullhouse(e.highlight) == -1 || (valida_fullhouse(e.highlight) < valida_fullhouse(e.ultima_jogada))) {
        return 0;
    }
    return 1;
}


/**
Função que valida o highlight do jogador, consoante a ultima jogada. 
Neste caso, como a ultima jogada foi um four of a kind, a função valida se as 5 cartas (four of a kind) escolhidas pelo utilizador são válidas de ser jogadas.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_fourkind (ESTADO e) {
    if (maior_carta_fourkind(e.highlight) > maior_carta_fourkind(e.ultima_jogada) && maior_carta_fourkind(e.highlight) != -1 ) {
        return 1;
    }
    return 0;
}

/**
Função que valida o highlight do jogador, consoante a ultima jogada. 
Neste caso, como a ultima jogada foi um straight flush, a função valida se as 5 cartas (straight flush) escolhidas pelo utilizador são válidas de ser jogadas.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_straightflush (ESTADO e) {
    if ((maior_carta_straightflush_bots(e.highlight)) == -1) {
        return 0;
    }
    else {
        if (maior_carta_straight(e.highlight) > maior_carta_straight(e.ultima_jogada)) {
            return 1;
        }
        else {
            if (maior_carta_straight(e.highlight) == maior_carta_straight(e.ultima_jogada) && (valida_flush(e.highlight)) > (valida_flush(e.ultima_jogada))) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

/**
Função que valida o highlight do jogador, para 1, 2 ou 3 cartas. Aqui, é permitido ao utilizador jogar uma das 3 combinações.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0.
*/
int utilizador_joga_singles_pares_triplos (ESTADO e) {
    if (e.ultima_jogada == -1) {
        if (!combinacao_valida (e.highlight) ) {
            return 0;
        }
        else {
            if (e.actual_jogador != 0) {
                return 0;
            }
            else {
                if ((da_valor (e.highlight) != -1) && (carta_existe(e.highlight, 0, 0))) {
                    return 1;
                }
                else return 0;
            }
        }
    }
    
    if (e.ultimo_jogador == 0) {
        if (!combinacao_valida (e.highlight) ) {
            return 0;
        }
        else {
            if (e.actual_jogador != 0) {
                return 0;
            }
            else {
                if ((da_valor (e.highlight) != -1) ) {
                    return 1;
                }
                else return 0;
            }
        }
    }
    
    else {
        if (!combinacao_valida (e.highlight)) {
            return 0;
        }
        else {
            if (e.actual_jogador != 0) {
                return 0;
            }
            else {
                if (!compara_tamanho (e.ultima_jogada, e.highlight)) {
                    return 0;
                }
                else {
                    if (!combinacao_maior (e.ultima_jogada, e.highlight)) {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
}



/**
É nesta função que a jogada do utilizador é verificada. Se esta for possível, é permitido ao utilizador colocar as cartas
no meio do tabuleiro, registando assim a sua jogada. Caso contrário, ou o utilizador passa, ou tenta arranjar outro tipo de combinação.
@param e O estado actual.
@returns Um inteiro 1 se for possível jogar, caso contrário retorna 0. 
*/
int posso_jogar (ESTADO e) {
    
    if ((numero_de_cartas(e.highlight)) == 5) {
        if (e.ultima_jogada == -1) {
            if (((validacao_5cartas(e.highlight)) != -1) && (carta_existe(e.highlight, 0, 0)) && (e.actual_jogador == 0)) {
                return 1;
            }
            else {
                return 0;
            }
        }
        if (e.ultimo_jogador == 0 && e.actual_jogador == 0) {
            if ((validacao_5cartas(e.highlight)) != -1) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            if (!compara_tamanho(e.ultima_jogada, e.highlight)) { return 0; }
            else{
                if (e.ultimo_jogador == 0) {
                    if (((validacao_5cartas(e.highlight)) != -1) && (e.actual_jogador == 0)) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                else {   
                    if ((validacao_5cartas(e.highlight)) > (validacao_5cartas(e.ultima_jogada))) {
                        return 1;
                    }
                    else {
                        if ((validacao_5cartas(e.highlight)) < (validacao_5cartas(e.ultima_jogada))) {
                            return 0;
                        }   
                        else {
                            if ((validacao_5cartas(e.highlight)) == 1) {
                                int a = utilizador_joga_straight(e);
                                return a;
                            }   
                            else {
                                if ((validacao_5cartas(e.highlight)) == 2) {
                                    int b = utilizador_joga_flush(e);
                                    return b;
                                }
                                if ((validacao_5cartas(e.highlight)) == 3) {
                                    int c = utilizador_joga_fullhouse(e);
                                    return c;
                                }
                                if ((validacao_5cartas(e.highlight)) == 4) {
                                    int d = utilizador_joga_fourkind(e);
                                    return d;
                                }
                                if ((validacao_5cartas(e.highlight)) == 5) {
                                    int f = utilizador_joga_straightflush(e);
                                    return f;
                                }
                            }
                        }
                    }
                }
                return 0;
            }
        }
    }
    
    else {
        int g = utilizador_joga_singles_pares_triplos(e);
        return g;
    }
}