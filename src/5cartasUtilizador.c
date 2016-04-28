#include "big2.h"



/*
O estado passabot permite que o bot passe uma jogada, se não tiver qualquer tipo de combinação válida para ser jogada.
*/
ESTADO passabot(ESTADO e) {
    e.cartas_bots[e.actual_jogador] = 0;
    e.actual_jogador = incrementa_jogador(e);
    return e;
}


/*
Ao receber o highlight do utilizador (neste caso um straight), confirma se este é válido para ser efetuada uma jogada.
*/
int valida_straight (MAO m) {
    
    int v,i,n,j;
    
    int contaValores[14];
    
    for (i = 0; i < 14; i++) {
        contaValores[i] = 0;
    }
    
    i = 2;
    for (v = 0; v <= 13; v++) {
        for(n = 0; n < 4; n++) {
            switch (v) {
                case 11: if (carta_existe(m,n,v)) { contaValores[0]++; contaValores[13]++; } break;
                case 12: if (carta_existe(m,n,v)) { contaValores[1]++; } break;
                default: if (carta_existe(m,n,v)) { contaValores[i]++; } break;
            }
        }
        i++;
    }
    
    j = 0;
    while ((j + 4) < 14) {
        if ((contaValores[j] != 0) && (contaValores[j+1] != 0) && (contaValores[j+2] != 0) && (contaValores[j+3] != 0) && (contaValores[j+4] != 0)) {
            return 1;
        }
        j++;
    }
    
    return -1;
}

/*
Nas cartas selecionadas pelo utilizador (neste caso um straight), determina o valor da maior carta desse, para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
*/
int maior_carta_straight (MAO m) {
    
    int v,i,n,j;
    
    int contaValores[14];
    
    for (i = 0; i < 14; i++) {
        contaValores[i] = 0;
    }
    
    i = 2;
    for (v = 0; v < 13; v++) {
        for(n = 0; n < 4; n++) {
            switch (v) {
                case 11: if (carta_existe(m,n,v)) { contaValores[0]++; contaValores[13]++; } break;
                case 12: if (carta_existe(m,n,v)) { contaValores[1]++; } break;
                default: if (carta_existe(m,n,v)) { contaValores[i]++; } break;
            }
        }
        i++;
    }
    
    if ((contaValores[1] != 0)) {
        for (j = 12; j >= 0; j--) {
            if (contaValores[j] != 0) {
                return (contaValores[j]);
            }
        }
    }
    
    else {
        for (j = 13; j > 0; j--) {
            if (contaValores[j] != 0) {
                return contaValores[j];
            }
        }
    }
    return 0; /* TER CUIDADO COM ISTO, FOI ADICIONADO PARA RESOLVER PROBLEMAS DE COMPILAÇÃO */
}


/*
Nas cartas selecionadas pelo utilizador (neste caso um straight), determina o naipe da maior carta desse, para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
*/
int maior_naipe_straight (MAO m, int maiorCarta) {
    
    int i, n, v;
    i = 0;
    v = maiorCarta;
    
    switch (v) {
        case 0: { v = 11; } break;
        case 1: { v = 12; } break;
        default: { v -= 2; } break;
    }
    
    for (n = 0; n < 4; n++) {
        if (carta_existe(m,n,v)) i = n;
    }
    
    return i;
}

/*
Ao receber o highlight do utilizador (neste caso um flush), confirma se este é válido para ser efetuada uma jogada.
*/
int valida_flush (MAO m) {
    
    int v, n, i;
    
    int contaNaipes[4];
    
    for (i = 0; i < 4; i++) {
        contaNaipes[i] = 0;
    }
    
    for (v = 0; v < 13; v++)
    for(n = 0; n < 4; n++) {
        switch(n) {
            case 0: if (carta_existe(m,n,v)) { contaNaipes[0]++; } break;
            case 1: if (carta_existe(m,n,v)) { contaNaipes[1]++; } break;
            case 2: if (carta_existe(m,n,v)) { contaNaipes[2]++; } break;
            case 3: if (carta_existe(m,n,v)) { contaNaipes[3]++; } break;
        }
    }
    
    
    if (contaNaipes[0] >= 5) return 0;
    
    else {
        if (contaNaipes[1] >= 5) return 1;
        
        else {
            if (contaNaipes[2] >= 5) return 2;
            
            else {
                if (contaNaipes[3] >= 5) return 3;
                else return -1;
            }
        }
    }
}


/*
Nas cartas selecionadas pelo utilizador (neste caso um flush), determina o valor da maior carta desse, para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
*/
int maior_carta_flush (MAO m) {
    
    int i, n, v;
    i = 0;
    for (v = 0; v < 13; v++) {
        for (n = 0; n < 4; n++) {
            if (carta_existe(m,n,v)) i = v;
        }
    }
    
    return i;
}


/*
Ao receber o highlight do utilizador (neste caso um fullhouse), confirma se este é válido para ser efetuada uma jogada.
*/
int valida_fullhouse (MAO m) {
    
    int v,i,n,j,p,flag;
    int contaValores[13];
    
    p=-1;
    flag=0;
    
    for (i = 0; i < 13; i++) {
        contaValores[i] = 0;
    }
    
    i = 0;
    for (v = 0; v < 13; v++) {
        for(n = 0; n < 4; n++) {
            if (carta_existe(m,n,v)) {
                contaValores[i]++;
            }
        }
        i++;
    }
    
    for (i = 0; i < 13 && flag != 1; i++) {;
        if (contaValores[i] >= 3 && flag != 1) {
            for (j = 0; j < 13 && flag != 1; j++) {
                if ((contaValores[j] >= 2) && j != i && flag != 1) {
                    p = i;
                    flag = 1;
                    return p;
                }
            }
        }
    }
    return p;
}


/*
Nas cartas selecionadas pelo utilizador (neste caso um fullhouse), determina o valor da maior carta do trio desse, para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
*/
int maior_carta_trio_fullhouse (MAO m) {
    
    int v,i,n,j,var;
    int contaValores[14];
    var = 0;
    
    for (i = 0; i < 14; i++) {
        contaValores[i] = 0;
    }
    
    i = 0;
    for (v = 0; v < 13; v++) {
        for(n = 0; n < 4; n++) {
            if (carta_existe(m,n,v)) {
                contaValores[i]++;
            }
        }
        i++;
    }
    
    for (j = 0; j < 13; j++) {
        if (contaValores[j] == 3) {
            var = j;
        }
    }
    
    return var;
}


/*
Ao receber o highlight do utilizador (neste caso um four of a kind), confirma se este é válido para ser efetuada uma jogada.
*/
int valida_fourkind (MAO m) {
    
    int v,i,n,j;
    
    int contaValores[13];
    
    for (i = 0; i < 13; i++) {
        contaValores[i] = 0;
    }
    
    i = 0;
    for (v = 0; v < 13; v++) {
        for(n = 0; n < 4; n++) {
            if ((carta_existe(m,n,v))) {
                contaValores[i]++;
            }
        }
        i++;
    }
    
    for (j = 0; j < 13; j++) {
        if (contaValores[j] == 4) {
            
            return 1;
        }
    }
    
    return 0;
}


/*
Nas cartas selecionadas pelo utilizador (neste caso um four of a kind), determina o valor da maior carta de entre as quatro cartas com o mesmo valor,
para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
*/
int maior_carta_fourkind (MAO m) {
    
    int v,i,x,n,j,var,flag;
    int contaValores[13];
    
    var = -1;
    
    for (i = 0; i < 13; i++) {
        contaValores[i] = 0;
    }
    
    x = 0;
    for (v = 0; v < 13; v++) {
        for(n = 0; n < 4; n++) {
            if (carta_existe(m,n,v)) {
                contaValores[x]++;
            }
        }
        x++;
    }
    
    flag = 0;
    for (j = 12; j >= 0 && flag != 1; --j) {
        if ((contaValores[j]) == 4) {
            var = j;
            flag = 1;
        }
    }
    return var;
}


/*
Ao receber o highlight do utilizador (neste caso um straight flush), confirma se este é válido para ser efetuada uma jogada.
*/
int valida_straightflush (MAO m) {
    
    int v,i,n,j,var,flag;
    
    int contaValores[14];
    int contaNaipes[4];
    
    for (i = 0; i < 14; i++) {
        contaValores[i] = 0;
    }
    
    for (i = 0; i < 4; i++) {
        contaNaipes[i] = 0;
    }
    
    i = 2;
    for (v = 0; v < 14; v++) {
        for(n = 0; n < 4; n++) {
            switch (v) {
                case 11: if (carta_existe(m,n,v)) { contaValores[0]++; contaValores[13]++; } break;
                case 12: if (carta_existe(m,n,v)) { contaValores[1]++; } break;
                default: if (carta_existe(m,n,v)) { contaValores[i]++; } break;
            }
        }
        i++;
    }
    
    for (v = 0; v < 14; v++) {
        for(n = 0; n < 4; n++) {
            switch(n) {
                case 0: if (carta_existe(m,n,v)) { contaNaipes[0]++; } break;
                case 1: if (carta_existe(m,n,v)) { contaNaipes[1]++; } break;
                case 2: if (carta_existe(m,n,v)) { contaNaipes[2]++; } break;
                case 3: if (carta_existe(m,n,v)) { contaNaipes[3]++; } break;
            }
        }
    }
    
    j = 0;
    flag = 1;
    var = 0;
    while ((j + 4) < 14) {
        if ((contaValores[j] != 0) && (contaValores[j+1] != 0) && (contaValores[j+2] != 0) && (contaValores[j+3] != 0) && (contaValores[j+4] != 0)) {
            while(flag != 0) {
                for (v = 0; v < 14; v++) {
                    for (n = 0; n < 4; n++) {
                        if (carta_existe(m,n,v)) {
                            var = n;
                            flag = 0;
                        }
                    }
                }
            }
            for (v = 0; v < 14; v++) {
                for (n = 0; n < 4; n++) {
                    if ((carta_existe(m,n,v)) && (var != n)) {
                        return -1;
                    }
                }
            }
            return 1;
        }
        j++;
    }
    
    return -1;
}