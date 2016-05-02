#include "big2.h"

/*
O estado sugestao_straightflush faz parte do botão sugestão.
Neste caso, sugere ao utilizador um possível straight flush a ser jogado na sua vez.
*/
ESTADO sugestao_straightflush(ESTADO e) {
    
    long long int m=0;
    
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
    
    e.highlight = m;
    return e;
}



/*
O estado sugestao_fourkind faz parte do botão sugestão.
Neste caso, sugere ao utilizador um possível four of a kind a ser jogado na sua vez.
*/
ESTADO sugestao_fourkind(ESTADO e) {
    
    long long int m=0;
    
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
    
    e.highlight = m;
    return e;
}



/*
O estado sugestao_fullhouse faz parte do botão sugestão.
Neste caso, sugere ao utilizador um possível full housr a ser jogado na sua vez.
*/
ESTADO sugestao_fullhouse(ESTADO e) {
    
    long long int m=0, n=0;
    
    int v1=0,n3=0,n2=0,n1=0,p=0,p1=0,p2=0,p3=0,np1=0,np2=0,flag,flag1,flag2,flag3,flag4;
    
    v1 = valida_fullhouse(e.mao[e.actual_jogador]);
    
    p = maior_carta_par_fullhouse(e.mao[e.actual_jogador]); /* valor do par */
    
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
    
    e.highlight = m;
    return e;
}




/*
O estado sugestao_flush faz parte do botão sugestão.
Neste caso, sugere ao utilizador um possível flush a ser jogado na sua vez.
*/
ESTADO sugestao_flush(ESTADO e) {
    
    long long int m=0;
    
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
    
    e.highlight = m;
    
    return e;
}


/*
O estado sugestao_straight faz parte do botão sugestão.
Neste caso, sugere ao utilizador um possível straight a ser jogado na sua vez.
*/
ESTADO sugestao_straight(ESTADO e) {
    
    long long int m=0;
    
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
    
    
    e.highlight = m;
    return e;
}


/*
O estado fazsugestao é aquele que efetivamente valida a sugestão a ser feita.
Com um funcionamento e estrutura identicos ao estado "fazjogada", este estado "escolhe" qual a sugestão a ser feita, comparando com a última jogada.
Conforme a mão do utilizador, o estado fazsugestao ve a menor combinação possível a ser jogada na ronda o utilizador.
*/
ESTADO fazsugestao (ESTADO e, int v) {
    if (v == 1) {
        if (maior_carta_straight_bots(e.mao[e.actual_jogador]) > maior_carta_straight_bots(e.ultima_jogada)) {
            e = sugestao_straight(e);
            return e;
        }
        else {
            if ((maior_carta_straight_bots(e.mao[e.actual_jogador])) == (maior_carta_straight_bots(e.ultima_jogada)) && ((maior_naipe_straight_bots(e.mao[e.actual_jogador], (maior_carta_straight_bots(e.mao[e.actual_jogador])))) > (maior_naipe_straight(e.ultima_jogada, (maior_carta_straight(e.ultima_jogada)))))) {
                e = sugestao_straight(e);
                return e;
            }
            else{
                if (valida_flush(e.mao[e.actual_jogador]) != -1){
                    e = sugestao_flush(e);
                    return e;
                }
                else {
                    if (valida_fullhouse(e.mao[e.actual_jogador]) != -1) {
                        e = sugestao_fullhouse(e);
                        return e;
                    }
                    else {
                        if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                            e = sugestao_fourkind(e);
                            return e;
                        }
                        else {
                            if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                                e = sugestao_straightflush(e);
                                return e;
                            }
                            else {
                                return e;
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (v == 2) {
        if ((valida_flush(e.mao[e.actual_jogador])) > (valida_flush(e.ultima_jogada))) {
            e = sugestao_flush(e);
            return e;
        }
        else {
            if ((valida_flush(e.mao[e.actual_jogador])) == (valida_flush(e.ultima_jogada))) {
                if ((maior_carta_flush_bots(e.mao[e.actual_jogador], (valida_flush(e.mao[e.actual_jogador])))) > (maior_carta_flush_bots(e.ultima_jogada, (valida_flush(e.ultima_jogada))))) {
                    e = sugestao_flush(e);
                    return e;
                }
            }
            else {
                if (valida_fullhouse(e.mao[e.actual_jogador]) != -1) {
                    e = sugestao_fullhouse(e);
                    return e;
                }
                else {
                    if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                        e = sugestao_fourkind(e);
                        return e;
                    }
                    else {
                        if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                            e = sugestao_straightflush(e);
                            return e;
                        }
                        else {
                            return e;
                        }
                    }
                }
            }
        }
    }
    
    if (v == 3) {
        if (valida_fullhouse(e.mao[e.actual_jogador]) > valida_fullhouse(e.ultima_jogada) && (valida_fullhouse(e.mao[e.actual_jogador] != -1))) {
            e = sugestao_fullhouse(e);
            return e;
        }
        else {
            if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                e = sugestao_fourkind(e);
                return e;
            }
            else {
                if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1) {
                    e = sugestao_straightflush(e);
                    return e;
                }
                else {
                    return e;
                }
            }
        }
    }
    
    if (v == 4) {
        if ((maior_carta_fourkind(e.mao[e.actual_jogador])) > (maior_carta_fourkind(e.ultima_jogada)) && (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1)) {
            e = sugestao_fourkind(e);
            return e;
        }
        else {
            if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                e = sugestao_straightflush(e);
                return e;
            }
            else {
                return e;
            }
        }
    }
    
    if (v == 5) {
        if((maior_carta_straightflush_bots(e.mao[e.actual_jogador]) == -1)) {
            return e;
        }
        else {
            if (codifica(maior_carta_straightflush_bots(e.mao[e.actual_jogador])) > codifica(maior_carta_straightflush_bots(e.ultima_jogada))) {
                e = sugestao_straightflush(e);
                return e;
            }
            else {
                if ((codifica(maior_carta_straightflush_bots(e.mao[e.actual_jogador])) == (codifica(maior_carta_straightflush_bots(e.ultima_jogada)))) && (maior_naipeCarta_straightflush_bots(e.mao[e.actual_jogador])) > (maior_naipeCarta_straightflush_bots(e.ultima_jogada))) {
                    e = sugestao_straightflush(e);
                    return e;
                }
            }
        }
    }
    
    return e;
}


/*
O estado cartas5sugestao executa a função validao_5cartas, de forma a verificar qual a combinação da ultima jogada, com o intuito de avaliar a combinação que vai ser escolhida.
Posto isto, é chamado o estado fazsugestao, para verificar se, e comparando com a jogada anterior, o utilizador tem uma combinação válida para ser escolhida.
*/
ESTADO cartas5sugestao (ESTADO e){
    int v;
    v = 0;
    v = validacao_5cartas(e.ultima_jogada);
    e = (fazsugestao (e, v));
    return e;
}


/*
O estado sugestao1 é usado no inicio da ronda do nosso utilizador, quando este tem o 3 de ouros.
A primeira sugestão será, portanto, o 3 de ouros, pois é a menor combinação que pode ser jogada.
*/
ESTADO sugestao1(ESTADO e){
    long long int m;
    m = 0;
    if (e.ultima_jogada == -1 && e.actual_jogador == 0 ){
        e.highlight= add_carta(m,0,0);
        return e;
    }
    
    return e;
}

/*
O estado sugestao2 é aquele que escolhe as cartas que efetivamente passam para o highlight (cartas essas já validadas).
Assim, e com a sugestão já concluída, o utilizador pode escolher se quer jogar essa sugestão.
Se não existir qualquer tipo de combinação válida para ser "escolhida", este estado passa a jogada, pois não existe qualquer jogada possível.
*/
ESTADO sugestao2(ESTADO e){
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
                        e.highlight= m;
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
                        e.highlight= m;
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
                        e.highlight= m;
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
                                e.highlight= p;
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
                        e.highlight= m;
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
                                        e.highlight= p;
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
                        e.highlight= m;
                        return e;
                    }
                }
            }
        }
        else {
            e = cartas5sugestao(e);
            return e;
        }
    }
    
    return e;
}
