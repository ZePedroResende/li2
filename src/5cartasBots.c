#include "big2.h"


/*
O estado fazjogada é aquele que verifica se o bot pode jogar uma combinação de 5 cartas.
Através de todas as validações das diferentes combinações, e comparando sempre com a última jogada, o bot vê qual a próxima combinação que vai jogar (a menor possível).
Se não tiver nada válido para jogar, o bot passa a jogada.
Este estado recebe o pŕoprio estado e o int 'v', o qual representa qual a combinação a ser analisada, de forma a ver um conjunto mais amplo de jogadas possíveis.
Exemplo:
-> v = 1: Straight;
-> v = 2: Flush;
-> etc....
*/

ESTADO fazjogada (ESTADO e, int v) {
    if (v == 1) {
        if (maior_carta_straight_bots(e.mao[e.actual_jogador]) > maior_carta_straight_bots(e.ultima_jogada)) {
            e = joga_straight(e);
            return e;
        }
        else {
            if ((maior_carta_straight_bots(e.mao[e.actual_jogador])) == (maior_carta_straight_bots(e.ultima_jogada)) && ((maior_naipe_straight_bots(e.mao[e.actual_jogador], (maior_carta_straight_bots(e.mao[e.actual_jogador])))) > (maior_naipe_straight(e.ultima_jogada, (maior_carta_straight_bots(e.ultima_jogada)))))) {
                e = joga_straight(e);
                return e;
            }
            else{
                if (valida_flush(e.mao[e.actual_jogador]) != -1){
                    e = joga_flush(e);
                    return e;
                }
                else {
                    if (valida_fullhouse(e.mao[e.actual_jogador]) != -1) {
                        e = joga_fullhouse(e);
                        return e;
                    }
                    else {
                        if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                            e = joga_fourkind(e);
                            return e;
                        }
                        else {
                            if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                                e = joga_straightflush(e);
                                return e;
                            }
                            else {
                                e.cartas_bots[e.actual_jogador] = 0;
                                e.actual_jogador = incrementa_jogador(e);
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
            e = joga_flush(e);
            return e;
        }
        else {
            if ((valida_flush(e.mao[e.actual_jogador])) == (valida_flush(e.ultima_jogada))) {
                if ((maior_carta_flush_bots(e.mao[e.actual_jogador], (valida_flush(e.mao[e.actual_jogador])))) > (maior_carta_flush_bots(e.ultima_jogada, (valida_flush(e.ultima_jogada))))) {
                    e = joga_flush(e);
                    return e;
                }
            }
            else {
                if (valida_fullhouse(e.mao[e.actual_jogador]) != -1) {
                    e = joga_fullhouse(e);
                    return e;
                }
                else {
                    if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                        e = joga_fourkind(e);
                        return e;
                    }
                    else {
                        if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                            e = joga_straightflush(e);
                            return e;
                        }
                        else {
                            e.cartas_bots[e.actual_jogador] = 0;
                            e.actual_jogador = incrementa_jogador(e);
                            return e;
                        }
                    }
                }
            }
        }
    }
    
    if (v == 3) {
        if (valida_fullhouse(e.mao[e.actual_jogador]) > valida_fullhouse(e.ultima_jogada) && (valida_fullhouse(e.mao[e.actual_jogador] != -1))) {
            e = joga_fullhouse(e);
            return e;
        }
        else {
            if (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1) {
                e = joga_fourkind(e);
                return e;
            }
            else {
                if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1) {
                    e = joga_straightflush(e);
                    return e;
                }
                else {
                    e.cartas_bots[e.actual_jogador] = 0;
                    e.actual_jogador = incrementa_jogador(e);
                    return e;
                }
            }
        }
    }
    
    if (v == 4) {
        if ((maior_carta_fourkind(e.mao[e.actual_jogador])) > (maior_carta_fourkind(e.ultima_jogada)) && (maior_carta_fourkind(e.mao[e.actual_jogador]) != -1)) {
            e = joga_fourkind(e);
            return e;
        }
        else {
            if (maior_carta_straightflush_bots(e.mao[e.actual_jogador]) != -1){
                e = joga_straightflush(e);
                return e;
            }
            else {
                e.cartas_bots[e.actual_jogador] = 0;
                e.actual_jogador = incrementa_jogador(e);
                return e;
            }
        }
    }
    
    if (v == 5) {
        if((maior_carta_straightflush_bots(e.mao[e.actual_jogador]) == -1)) {
            e.cartas_bots[e.actual_jogador] = 0;
            e.actual_jogador = incrementa_jogador(e);
            return e;
        }
        else {
            if (codifica(maior_carta_straightflush_bots(e.mao[e.actual_jogador])) > codifica(maior_carta_straightflush_bots(e.ultima_jogada))) {
                e = joga_straightflush(e);
                return e;
            }
            else {
                if ((codifica(maior_carta_straightflush_bots(e.mao[e.actual_jogador])) == (codifica(maior_carta_straightflush_bots(e.ultima_jogada)))) && (maior_naipeCarta_straightflush_bots(e.mao[e.actual_jogador])) > (maior_naipeCarta_straightflush_bots(e.ultima_jogada))) {
                    e = joga_straightflush(e);
                    return e;
                }
            }
        }
    }
    
    e = passabot(e);
    return e;
}

/*
O estado pbot executa a função validao_5cartas, de forma a verificar qual a combinação da ultima jogada, de forma a avaliar com a combinação que vai ser jogada.
Posto isto, é chamado o esatdo fazjogada, para verificar se, e comparando com a jogada anterior, o bot tem uma combinação válida para ser jogada.
*/
ESTADO pbot(ESTADO e){
    int v;
    v = 0;
    v = validacao_5cartas(e.ultima_jogada);
    e = (fazjogada (e, v));
    return e;
}





/*
Nas cartas selecionadas pelo utilizador (neste caso um straight flush), determina o valor da maior carta desse, para mais tarde comparar, se necessário, com as ultimas jogadas, de forma a avaliar a jogada.
Esta função foi usada para avaliar a mão do utilizador, pois seguia o mesmo precedimento.
*/
int maior_carta_straight_bots(MAO m){
    /* USAMOS MAIOR_CARTA_STRAIGHT_BOTS PARA AVALIAR A MAIOR CARTA DE UM STRAIGHT FLUSH, POIS ERA O MESMO PROCEDIMENTO */
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
    
    if (contaValores[1] != 0) {
        j = 12;
        while ((j-4) >= 0) {
            if ((contaValores[j] != 0) && (contaValores[j-1] != 0) && (contaValores[j-3] != 0) && (contaValores[j-4] != 0)) {
                switch (j) {
                    case 0: { j = 11; } break;
                    case 1: { j = 12; } break;
                    default: { j -= 2; } break;
                }
                return j;
            }
            j--;
        }
    }
    else {
        j = 13;
        while ((j-4) >= 1) {
            if ((contaValores[j] != 0) && (contaValores[j-1] != 0) && (contaValores[j-3] != 0) && (contaValores[j-4] != 0)) {
                switch (j) {
                    case 0: { j = 11; } break;
                    case 1: { j = 12; } break;
                    default: { j -= 2; } break;
                }
                return j;
            }
            j--;
        }
    }
    
    return -1;
}


/*
Depois de ser validada um straight na mão de um dos bots, esta função determina o naipe da maior carta nesse straight, para se for necessário comparar com valores iguais.
*/
int maior_naipe_straight_bots (MAO m, int maiorCarta) {
    int i,n;
    i = 0;
    for (n = 3; n >= 0; --n) {
        if (carta_existe(m,n,maiorCarta)) i = n;
    }
    return i;
}


/*
Depois de ser validada um flush na mão de um dos bots, esta função determina o valor da maior carta nesse flush, para se for necessário comparar com valores iguais.
*/
int maior_carta_flush_bots (MAO m, int n1) {
    int i,v,flag;
    i = 0;
    flag = 0;
    for (v = 12; (v >= 0) && (flag != 1); --v) {
        if (carta_existe(m,n1,v)) {
            flag = 1;
            i = v;
        }
    }
    return i;
}


/*
Para a formação de um four of a kind, é necessário quatro cartas com o mesmo valor mais uma carta qualquer existente na mão.
Esta função escolhe essa carta, verificando primeiro se existe na mão. A primeira que for encontrada, é adicionada ao four of a kind.
*/
int da_carta_fourkind (MAO m) {
    
    int v,i,n,j,var=0,flag;
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
    
    flag = 0;
    for (j = 0; (j < 13) && (flag != 1); j++) {
        if (contaValores[j] == 1) {
            var = j;
            flag = 1;
        }
    }
    
    return var;
}



/*
Esta função procura na mão um par válido para ser usado num full house. Se existir um par, é retornado o valor desse.
*/
int maior_carta_par_fullhouse (MAO m) {
    
    int v,i,n,j,var,flag;
    
    int contaValores[13];
    
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
    
    flag = 0;
    for (j = 0; (j < 14) && (flag != 1); j++) {
        if (contaValores[j] == 2) {
            var = j;
            flag = 1;
        }
    }
    
    return var;
}





/*
Função para determinar a maior carta de um straight flush na mão de um bot, de forma a validar para ser jogado. Esta função retorna a maior carta desse straight flush para usarmos na validação e comparação com as outras jogadas.
Esta função foi também usada para o highlight do utilizado, visto que funciona para os dois casos.
*/
int maior_carta_straightflush_bots (MAO m) {
    
    int x,v,i,n,j,p0,p1,p2,p3,p4;
    
    int contaValores1[14];
    int contaNaipes1[4];
    int maioresCartasStraightsPossiveis1[8];
    
    x = p0 = p1 = p2 = p3 = p4 = 0;
    
    for (i = 0; i < 14; i++) {
        contaValores1[i] = 0;
    }
    
    for (i = 0; i < 4; i++) {
        contaNaipes1[i] = 0;
    }
    
    for (i = 0; i < 4; i++) {
        maioresCartasStraightsPossiveis1[i] = -1;
    }
    
    i = 2;
    for (v = 0; v < 14; v++) {
        for(n = 0; n < 4; n++) {
            switch (v) {
                case 11: if (carta_existe(m,n,v)) { contaValores1[0]++; contaValores1[13]++; } break;
                case 12: if (carta_existe(m,n,v)) { contaValores1[1]++; } break;
                default: if (carta_existe(m,n,v)) { contaValores1[i]++; } break;
            }
        }
        i++;
    }
    
    for (v = 0; v < 14; v++) {
        for(n = 0; n < 4; n++) {
            switch(n) {
                case 0: if (carta_existe(m,n,v)) { contaNaipes1[0]++; } break;
                case 1: if (carta_existe(m,n,v)) { contaNaipes1[1]++; } break;
                case 2: if (carta_existe(m,n,v)) { contaNaipes1[2]++; } break;
                case 3: if (carta_existe(m,n,v)) { contaNaipes1[3]++; } break;
            }
        }
    }
    
    for (i = 13, j = 0; (i - 4) >= 0; --i) {
        if ((contaValores1[i] != 0) && (contaValores1[i-1] != 0) && (contaValores1[i-2] != 0) && (contaValores1[i-3] != 0) && (contaValores1[i-4] != 0)) {
            maioresCartasStraightsPossiveis1[j] = i;
            j++;
        }
    }
    
    for (i = 0; i < 8; i++) {
        if (maioresCartasStraightsPossiveis1[i] != -1) {
            x = maioresCartasStraightsPossiveis1[i];
            p0 = descodifica_straight(x);
            p1 = descodifica_straight(x-1);
            p2 = descodifica_straight(x-2);
            p3 = descodifica_straight(x-3);
            p4 = descodifica_straight(x-4);
            
            for (n = 3; n >= 0; --n) {
                if ((carta_existe(m,n,p0)) && (carta_existe(m,n,p1)) && (carta_existe(m,n,p2)) && (carta_existe(m,n,p3)) && (carta_existe(m,n,p4))) {
                    return p0;
                }
            }
        }
    }
    return -1;
}


/*
Função para determinar o naipe da maior carta de um straight flush na mão de um bot. Esta função tem o intuito de se na ultima jogada for jogado um straight flush com o mesmo valor
do que o que vai ser jogado agora, temos de analisar o naipe para ver se a jogada é válida.
*/
int maior_naipeCarta_straightflush_bots (MAO m) {
    
    int v,i,n,j,x,p0,p1,p2,p3,p4;
    int contaValores[14];
    int contaNaipes[4];
    int maioresCartasStraightsPossiveis[8];
    
    x = p0 = p1 = p2 = p3 = p4 = 0;
    
    for (i = 0; i < 14; i++) {
        contaValores[i] = 0;
    }
    
    for (i = 0; i < 4; i++) {
        contaNaipes[i] = 0;
    }
    
    for (i = 0; i < 4; i++) {
        maioresCartasStraightsPossiveis[i] = -1;
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
    
    for (i = 13, j = 0; (i - 4) >= 0; --i) {
        if ((contaValores[i] != 0) && (contaValores[i-1] != 0) && (contaValores[i-2] != 0) && (contaValores[i-3] != 0) && (contaValores[i-4] != 0)) {
            maioresCartasStraightsPossiveis[j] = i;
            j++;
        }
    }
    
    for (i = 0; i < 8; i++) {
        if (maioresCartasStraightsPossiveis[i] != -1) {
            x = maioresCartasStraightsPossiveis[i];
            p0 = descodifica_straight(x);
            p1 = descodifica_straight(x-1);
            p2 = descodifica_straight(x-2);
            p3 = descodifica_straight(x-3);
            p4 = descodifica_straight(x-4);
            
            for (n = 3; n >= 0; --n) {
                if ((carta_existe(m,n,p0)) && (carta_existe(m,n,p1)) && (carta_existe(m,n,p2)) && (carta_existe(m,n,p3)) && (carta_existe(m,n,p4))) {
                    return n;
                }
            }
        }
    }
    return -1;
}