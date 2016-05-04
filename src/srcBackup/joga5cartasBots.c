#include "big2.h"

/**
O estado joga_straight é aquele que faz com que o bot jogue um straight. Após todas as validações da sua mão, ele adiciona cartas para jogar, removendo-as da sua mão.
Posto isto, mostra as cartas no tabuleiro, e é a vez de outro jogador.
@param e O estado actual.
@returns O novo estado.
*/
ESTADO joga_straight(ESTADO e) {
    
    long long int m=0, n=0;
    
    int v1,v2,v3,v4,v5,n1,n2,n3,n4,n5,p1,p2,p3,p4,p5;
    
    p1 = maior_carta_straight_bots (e.mao[e.actual_jogador]);
    p2 = codifica((maior_carta_straight_bots(e.mao[e.actual_jogador]))-1);
    p3 = codifica((maior_carta_straight_bots(e.mao[e.actual_jogador]))-2);
    p4 = codifica((maior_carta_straight_bots(e.mao[e.actual_jogador]))-3);
    p5 = codifica((maior_carta_straight_bots(e.mao[e.actual_jogador]))-4);
    
    v1 = p1;
    v2 = descodifica_straight(p2);
    v3 = descodifica_straight(p3);
    v4 = descodifica_straight(p4);
    v5 = descodifica_straight(p5);
    
    n1 = maior_naipe_straight_bots((e.mao[e.actual_jogador]),v1);
    n2 = maior_naipe_straight_bots((e.mao[e.actual_jogador]),v2);
    n3 = maior_naipe_straight_bots((e.mao[e.actual_jogador]),v3);
    n4 = maior_naipe_straight_bots((e.mao[e.actual_jogador]),v4);
    n5 = maior_naipe_straight_bots((e.mao[e.actual_jogador]),v5);
    
    m = add_carta(0,n1,v1);
    m = add_carta(m,n2,v2);
    m = add_carta(m,n3,v3);
    m = add_carta(m,n4,v4);
    m = add_carta(m,n5,v5);
    
    n = rem_carta((e.mao[e.actual_jogador]),n1,v1);
    n = rem_carta(n,n2,v2);
    n = rem_carta(n,n3,v3);
    n = rem_carta(n,n4,v4);
    n = rem_carta(n,n5,v5);
    
    e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 5;
    e.ultima_jogada = m;
    e.cartas_bots[e.actual_jogador] = m;
    e.mao[e.actual_jogador] = n;
    e.ultimo_jogador = e.actual_jogador;
    e.actual_jogador = incrementa_jogador(e);
    e.card = 0;
    return e;
}


/**
O estado joga_flush é aquele que faz com que o bot jogue um flush. Após todas as validações da sua mão, ele adiciona cartas para jogar, removendo-as da sua mão.
Posto isto, mostra as cartas no tabuleiro, e é a vez de outro jogador.
@param e O estado actual.
@returns O novo estado.
*/
ESTADO joga_flush(ESTADO e) {
    
    long long int m=0, n=0;
    
    int flag1,flag2,flag3,flag4,v1,v2,v3,v4,v5,p1=0,p2=0,p3=0,p4=0,p5=0,n1;
    
    n1 = valida_flush(e.mao[e.actual_jogador]);
    v1 = maior_carta_flush_bots(e.mao[e.actual_jogador], n1);
    
    flag1 = 0;
    p1 = v1;
    for(v2 = (v1 - 1); v2 >= 0 && flag1 != 1; --v2) {
        if (carta_existe(e.mao[e.actual_jogador],n1,v2)) {
            p2 = v2;
            flag1 = 1;
        }
    }
    
    flag2 = 0;
    for (v3 = v2; v3 >= 0 && flag2 != 1; --v3) {
        if (carta_existe(e.mao[e.actual_jogador],n1,v3)) {
            p3 = v3;
            flag2 = 1;
        }
    }
    
    flag3 = 0;
    for (v4 = v3; v4 >= 0 && flag3 != 1; --v4) {
        if (carta_existe(e.mao[e.actual_jogador],n1,v4)) {
            p4 = v4;
            flag3 = 1;
        }
    }
    
    flag4 = 0;
    for (v5 = v4; v5 >= 0 && flag4 != 1; --v5) {
        if (carta_existe(e.mao[e.actual_jogador],n1,v5)) {
            p5 = v5;
            flag4 = 1;
        }
    }
    
    m = add_carta(0,n1,p1);
    m = add_carta(m,n1,p2);
    m = add_carta(m,n1,p3);
    m = add_carta(m,n1,p4);
    m = add_carta(m,n1,p5);
    
    n = rem_carta((e.mao[e.actual_jogador]),n1,p1);
    n = rem_carta(n,n1,p2);
    n = rem_carta(n,n1,p3);
    n = rem_carta(n,n1,p4);
    n = rem_carta(n,n1,p5);
    
    e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 5;
    e.ultima_jogada = m;
    e.cartas_bots[e.actual_jogador] = m;
    e.mao[e.actual_jogador] = n;
    e.ultimo_jogador = e.actual_jogador;
    e.actual_jogador = incrementa_jogador(e);
    e.card = 0;
    return e;
}

/**
O estado joga_fullhouse é aquele que faz com que o bot jogue um full house. Após todas as validações da sua mão, ele adiciona cartas para jogar, removendo-as da sua mão.
Posto isto, mostra as cartas no tabuleiro, e é a vez de outro jogador.
@param e O estado actual.
@returns O novo estado.
*/
ESTADO joga_fullhouse(ESTADO e) {
    
    long long int m=0, f=0;
    
    int v1=0,n=0,n3=0,n2=0,n1=0,p=0,p1=0,p2=0,p3=0,np1=0,np2=0,flag,flag1,flag2,flag3,flag4;
    
    v1 = valida_fullhouse(e.mao[e.actual_jogador]);
    
    flag = 0;
    for (n = 3; n >= 0 && flag != 1; --n) {
        if(carta_existe(e.mao[e.actual_jogador], n, v1)) {
            n1 = n;
            flag = 1;
        }
    }
    
    flag1 = 0;
    p1 = n1-1;
    for (n = p1; n >= 0 && flag1 != 1; --n) {
        if(carta_existe(e.mao[e.actual_jogador], n, v1)) {
            n2 = n;
            flag1 = 1;
        }
    }
    
    flag2 = 0;
    p2 = n2-1;
    for (n = p2; n >= 0 && flag2 != 1; --n) {
        if (carta_existe(e.mao[e.actual_jogador], n, v1)) {
            n3 = n;
            flag2 = 1;
        }
    }


    f = rem_carta((e.mao[e.actual_jogador]),n1,v1);
    f = rem_carta(f,n2,v1);
    f = rem_carta(f,n3,v1);
    p = maior_carta_par_fullhouse(f); /* valor do par */


    flag3 = 0;
    for (n = 3; n >= 0 && flag3 != 1; --n) {
        if (carta_existe(e.mao[e.actual_jogador], n, p)) {
            np1 = n;
            flag3 = 1;
        }
    }
    
    flag4 = 0;
    p3 = n;
    for (n = p3; n >= 0 && flag4 != 1; --n) {
        if (carta_existe(e.mao[e.actual_jogador], n, p)) {
            np2 = n;
            flag4 = 1;
        }
    }
    
    m = add_carta(0,n1,v1);
    m = add_carta(m,n2,v1);
    m = add_carta(m,n3,v1);
    m = add_carta(m,np1,p);
    m = add_carta(m,np2,p);
    
    
    f = rem_carta(f,np1,p);
    f = rem_carta(f,np2,p);
    
    e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 5;
    e.ultima_jogada = m;
    e.cartas_bots[e.actual_jogador] = m;
    e.mao[e.actual_jogador] = f;
    e.ultimo_jogador = e.actual_jogador;
    e.actual_jogador = incrementa_jogador(e);
    e.card = 0;
    return e;
}

/**
O estado joga_fourkind é aquele que faz com que o bot jogue um four of a kind. Após todas as validações da sua mão, ele adiciona cartas para jogar, removendo-as da sua mão.
Posto isto, mostra as cartas no tabuleiro, e é a vez de outro jogador.
@param e O estado actual.
@returns O novo estado.
*/
ESTADO joga_fourkind(ESTADO e) {
    
    long long int m=0, n=0;
    
    int v1=0,n2=0,n1=0,p=0;
    
    v1 = maior_carta_fourkind(e.mao[e.actual_jogador]);
    
    p = da_carta_fourkind(e.mao[e.actual_jogador]);
    
    for (n1 = 3; n1 >= 0; --n1) {
        if (carta_existe(e.mao[e.actual_jogador],n1,p)) {
            n2 = n1;
        }
    }
    
    /* os v's são todos iguais, exceto v5 */
    
    m = add_carta(0,0,v1);
    m = add_carta(m,1,v1);
    m = add_carta(m,2,v1);
    m = add_carta(m,3,v1);
    m = add_carta(m,n2,p);
    
    n = rem_carta((e.mao[e.actual_jogador]),0,v1);
    n = rem_carta(n,1,v1);
    n = rem_carta(n,2,v1);
    n = rem_carta(n,3,v1);
    n = rem_carta(n,n2,p);
    
    e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 5;
    e.ultima_jogada = m;
    e.cartas_bots[e.actual_jogador] = m;
    e.mao[e.actual_jogador] = n;
    e.ultimo_jogador = e.actual_jogador;
    e.actual_jogador = incrementa_jogador(e);
    e.card = 0;
    return e;
}

/**
O estado joga_straightflush é aquele que faz com que o bot jogue um straight flush. Após todas as validações da sua mão, ele adiciona cartas para jogar, removendo-as da sua mão.
Posto isto, mostra as cartas no tabuleiro, e é a vez de outro jogador.
@param e O estado actual.
@returns O novo estado.
*/
ESTADO joga_straightflush(ESTADO e) {
    
    long long int m=0, n=0;
    
    int v1,v2,v3,v4,v5,n1,n2,n3,n4,n5,p2,p3,p4,p5;
    
    v1 = maior_carta_straightflush_bots (e.mao[e.actual_jogador]);
    p2 = codifica ((maior_carta_straightflush_bots(e.mao[e.actual_jogador]))-1);
    p3 = codifica ((maior_carta_straightflush_bots(e.mao[e.actual_jogador]))-2);
    p4 = codifica ((maior_carta_straightflush_bots(e.mao[e.actual_jogador]))-3);
    p5 = codifica ((maior_carta_straightflush_bots(e.mao[e.actual_jogador]))-4);
    
    v2 = descodifica_straight(p2);
    v3 = descodifica_straight(p3);
    v4 = descodifica_straight(p4);
    v5 = descodifica_straight(p5);
    /* os ns sao todos iguais */
    n1 = maior_naipeCarta_straightflush_bots((e.mao[e.actual_jogador]));
    n2 = maior_naipeCarta_straightflush_bots((e.mao[e.actual_jogador]));
    n3 = maior_naipeCarta_straightflush_bots((e.mao[e.actual_jogador]));
    n4 = maior_naipeCarta_straightflush_bots((e.mao[e.actual_jogador]));
    n5 = maior_naipeCarta_straightflush_bots((e.mao[e.actual_jogador]));
    
    m = add_carta(0,n1,v1);
    m = add_carta(m,n2,v2);
    m = add_carta(m,n3,v3);
    m = add_carta(m,n4,v4);
    m = add_carta(m,n5,v5);
    
    n = rem_carta((e.mao[e.actual_jogador]),n1,v1);
    n = rem_carta(n,n2,v2);
    n = rem_carta(n,n3,v3);
    n = rem_carta(n,n4,v4);
    n = rem_carta(n,n5,v5);
    
    e.cartas[e.actual_jogador] = (e.cartas[e.actual_jogador]) - 5;
    e.ultima_jogada = m;
    e.cartas_bots[e.actual_jogador] = m;
    e.mao[e.actual_jogador] = n;
    e.ultimo_jogador = e.actual_jogador;
    e.actual_jogador = incrementa_jogador(e);
    e.card = 0;
    return e;
}


