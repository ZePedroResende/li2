#include "big2.h"


/*
Conta o número de cartas que se encontra numa mao numa dada altura
*/
int numero_de_cartas(MAO m) {
    
    int n, v, contaCartas=0;
    
    for (n = 0; n < 4; n++) {
        for (v = 0; v < 13; v++)
        if (carta_existe(m, n, v)) contaCartas++;
    }
    
    return contaCartas;
}


/* Confirma se a mão que é recebida (o highlight), tem uma, duas ou três cartas */
int combinacao_valida(MAO m) {
    
    if ((numero_de_cartas (m)) > 3) {
        return 0;
    }
    
    else return 1;
}

/* Compara o tamanha entre duas mãos, ou seja, ve o tamanho da ultima jogada, e compara o tamanho com a jogada actual,
e vê se a combinação tem o mesmo tamanho */

int compara_tamanho(MAO m1, MAO m2){
    if (numero_de_cartas(m1) == numero_de_cartas(m2)) {
        return 1;
    }
    
    return 0;
}

/*numa jogada de 1,2 e 3 cartas esta funçao e utilizada para comparar o valor entre a ultima jogada e a efetua pelo atual jogador*/
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

/* Esta função obtém o maior naipe dentro de uma mão, de forma a ser usado para avaliar a maior jogada. */

int da_maior_naipe (MAO m){
    int n, v, maior=0;
    
    for (n = 0; n < 4; n++) {
        
        for (v = 0; v < 13; v++)
        
        if (carta_existe(m, n, v)) { if (n > maior) maior =n;}
    }
    
    return maior;
}


/* Aqui, é verificado se a jogada actual é maior que a jogada anterior. Conforme o retorno da função dá valor, a jogada
actual é possível ser realizada ou não. Ao comparar, de os retornos das duas funções forem iguais, ou seja, se os maiores
valores de cada mão forem iguais, comparamos o naipe, assim identificando qual a maior jogada */

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


/*
É nesta função que a jogada do utilizador é verificada. Se esta for possível, é permitido ao utilizador colocar as cartas
no meio do tabuleiro, registando assim a sua jogada. Caso contrário, ou o utilizador passa, ou tenta arranjar outro tipo de combinação.
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
                            }
                            
                            else {
                                if ((validacao_5cartas(e.highlight)) == 2) {
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
                                }
                                if ((validacao_5cartas(e.highlight)) == 3) {
                                    if (valida_fullhouse(e.highlight) == -1 || (valida_fullhouse(e.highlight) < valida_fullhouse(e.ultima_jogada))) {
                                        return 0;
                                    }
                                    else {
                                        return 1;
                                    }
                                }
                                if ((validacao_5cartas(e.highlight)) == 4) {
                                    if (maior_carta_fourkind(e.highlight) > maior_carta_fourkind(e.ultima_jogada) && maior_carta_fourkind(e.highlight) != -1 ) {
                                        return 1;
                                    }
                                    else {
                                        return 0;
                                    }
                                }
                                if ((validacao_5cartas(e.highlight)) == 5) {
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
}