#include "big2.h"



/*
A valida_bots_jogadas_normais é a função que vai validar as jogadas dos bots (uma, duas e três cartas).
É retornado 0 se os bots não puderem efetuar a jogada, e 1 caso contrário.
*/
int valida_bots_jogadas_normais (ESTADO e, MAO m) {
    
    if (!combinacao_valida (m)) {
        return 0;
    }
    else {
        if (!compara_tamanho (e.ultima_jogada, m)) {
            return 0;
        }
        else {
            if (!combinacao_maior (e.ultima_jogada, m)) {
                return 0;
            }
        }
    }
    return 1;
}


/*
A função bots1 vai ser executada quando um bot começa a jogar(sendo que este tem o 3 de ouros na sua mão).
E executada na modificação do baralhar na parse.
É retornado o estado do jogo após ser jogado o 3 de ouros.
*/
ESTADO bots1(ESTADO e){
    if (e.ultima_jogada == -1 && e.actual_jogador != 0 ){
        e.cartas[e.actual_jogador] =( e.cartas[(e.actual_jogador)]) - 1;
        e.mao[e.actual_jogador] = rem_carta(e.mao[(e.actual_jogador)],0,0);
        e.ultima_jogada = 1;
        e.actual_jogador = incrementa_jogador(e);
        e.card = 0;
        e.cartas_bots[e.actual_jogador] = 2;
        
        return e;
    }
    
    return e;
}

/*
O estado bots2 é executado quando um bot executa uma jogada que não seja jogar um 3 de ouros, isto inclui jogadas de 1, 2, 3 e 5 cartas.
Se não existir nenhuma combinação válida a ser jogada (comparando com a ultima jogada), o bot passa a jogada.
É retornado o estado actual do jogo após as jogadas dos bots.
*/
ESTADO bots2(ESTADO e){
    long long int m=0;
    long long int z=0;
    long long int p=0;
    long long int g=0;
    int n,v,k,l,ncartas;
    
    ncartas = numero_de_cartas(e.ultima_jogada);
    
    if (ncartas == 1) {
        if (e.ultimo_jogador == e.actual_jogador ){
            for (v = 0; v <= 12; v++){
                for (n = 0; n <= 3; n++){
                    m = add_carta(0,n,v);
                    if (carta_existe(e.mao[e.actual_jogador],n,v)){
                        m = add_carta(0,n,v);
                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) -1 ;
                        e.ultima_jogada = m;
                        e.cartas_bots[e.actual_jogador] = m;
                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador],n,v) ;
                        e.ultimo_jogador = e.actual_jogador;
                        e.actual_jogador = incrementa_jogador(e);
                        e.card = 0;
                        return e;
                    }
                }
            }
        }
        
        else {
            for (v = 0; v <= 12; v++){
                for (n = 0; n <= 3; n++){
                    m = add_carta(0,n,v);
                    if (carta_existe(e.mao[e.actual_jogador],n,v) && valida_bots_jogadas_normais(e,m)){
                        m = add_carta(0,n,v);
                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) -1 ;
                        e.ultima_jogada = m;
                        e.cartas_bots[e.actual_jogador] = m;
                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador],n,v) ;
                        e.ultimo_jogador = e.actual_jogador;
                        e.actual_jogador = incrementa_jogador(e);
                        e.card = 0;
                        return e;
                    }
                }
            }
        }
    }
    
    if (ncartas == 2) {
        
        if (e.ultimo_jogador == e.actual_jogador ){
            for (v = 0; v <= 12; v++){
                for (n = 0; n <= 3; n++){
                    m = add_carta(0,n,v);
                    if (carta_existe(e.mao[e.actual_jogador],n,v)){
                        m = add_carta(0,n,v);
                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) -1 ;
                        e.ultima_jogada = m;
                        e.cartas_bots[e.actual_jogador] = m;
                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador],n,v) ;
                        e.ultimo_jogador = e.actual_jogador;
                        e.actual_jogador = incrementa_jogador(e);
                        e.card = 0;
                        return e;
                    }
                }
            }
        }
        
        else {
            for(v = 0; v <= 12; v++) {
                for(n = 0; n <= 3; n++) {
                    if (carta_existe(e.mao[e.actual_jogador], n, v)) {
                        m = add_carta(0,n,v);
                        for(k = 0; k <= 3; k++) {
                            z = add_carta(0, k, v);
                            m = add_carta(0,n,v);
                            p = add_carta(m,k,v);
                            if (carta_existe(e.mao[e.actual_jogador],k,v) && z != m && valida_bots_jogadas_normais(e,p) ) {
                                m = add_carta(0,n,v);
                                p = add_carta(m, k, v);
                                e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 2;
                                e.ultima_jogada = p;
                                e.cartas_bots[e.actual_jogador] = p;
                                e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador], n, v);
                                e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador], k, v);
                                e.ultimo_jogador = e.actual_jogador;
                                e.actual_jogador = incrementa_jogador(e);
                                e.card = 0;
                                return e;
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (ncartas == 3) {
        
        if (e.ultimo_jogador == e.actual_jogador ){
            for (v = 0; v <= 12; v++){
                for (n = 0; n <= 3; n++){
                    m = add_carta(0,n,v);
                    if (carta_existe(e.mao[e.actual_jogador],n,v)){
                        m = add_carta(0,n,v);
                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) -1 ;
                        e.ultima_jogada = m;
                        e.cartas_bots[e.actual_jogador] = m;
                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador],n,v) ;
                        e.ultimo_jogador = e.actual_jogador;
                        e.actual_jogador = incrementa_jogador(e);
                        e.card = 0;
                        return e;
                    }
                }
            }
        }
        
        else{
            for(v = 0; v <= 12; v++) {
                for(n = 0; n <= 3; n++) {
                    if (carta_existe(e.mao[e.actual_jogador], n, v)) {
                        m = add_carta(0,n,v);
                        for(l = 0; l <= 3; l++) {
                            if (carta_existe(e.mao[e.actual_jogador], l, v)) {
                                g = add_carta(0,l,v);
                                for(k = 0; k <= 3; k++) {
                                    g = add_carta(0,l,v);
                                    z = add_carta(0, k, v);
                                    m = add_carta(0,n,v);
                                    p = add_carta(m,k,v);
                                    p = add_carta(p,l,v);
                                    if (carta_existe(e.mao[e.actual_jogador],k,v) && z != m && g != m && g != z && valida_bots_jogadas_normais(e,p) ) {
                                        m = add_carta(0,n,v);
                                        p = add_carta(m, k, v);
                                        p = add_carta(p,l,v);
                                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 3;
                                        e.ultima_jogada = p;
                                        e.cartas_bots[e.actual_jogador] = p;
                                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador], n, v);
                                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador], k, v);
                                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador], l, v);
                                        e.ultimo_jogador = e.actual_jogador;
                                        e.actual_jogador = incrementa_jogador(e);
                                        e.card = 0;
                                        return e;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (ncartas == 5) {
        if (e.ultimo_jogador == e.actual_jogador){
            for (v = 0; v <= 12; v++){
                for (n = 0; n <= 3; n++){
                    m = add_carta(0,n,v);
                    if (carta_existe(e.mao[e.actual_jogador],n,v)){
                        m = add_carta(0,n,v);
                        e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) -1 ;
                        e.ultima_jogada = m;
                        e.cartas_bots[e.actual_jogador] = m;
                        e.mao[e.actual_jogador] = rem_carta(e.mao[e.actual_jogador],n,v) ;
                        e.ultimo_jogador = e.actual_jogador;
                        e.actual_jogador = incrementa_jogador(e);
                        e.card = 0;
                        return e;
                    }
                }
            }
        }
        else {
            e = pbot(e);
            return e;
        }
    }
    e.cartas_bots[e.actual_jogador] = 0;
    e.actual_jogador = incrementa_jogador(e);
    return e;
}

