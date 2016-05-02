#include "big2.h"

/* Em cada jogada, o jogador é incrementado, tomando assim o controlo do jogador que está em jogo.
Como estes variam entre 0 e 3 (4 jogadores), enquanto ele for diferente de 3, vai incrementar para um próximo jogador, e uma próxima jogada. */
int incrementa_jogador (ESTADO e){
    if (e.actual_jogador != 3) return (e.actual_jogador += 1);
    else return 0;
}


/*
A função jogar vai ser invocada pela função parse, e vai retirar as cartas da mão do jogador caso esta exista no highlight,
colocando-a na posição do tabuleiro correspondete a jogada do utilizador, ou seja, vai ser a função executada quando carregamos no botao jogar para um dado highlight.
Esta função também convoca as funções dos bots que executam as suas jogadas enquanto não for a vez do utilizador jogar.
*/
ESTADO jogar (ESTADO e) {
    
    int n, v, x, y;
    
    x = 551;
    y = 450;
    
    e.play = 0;
    if(e.layout == 1){
        for (v = 0; v < 13; v++) {
            for (n = 0; n < 4; n++) {
                if (carta_existe((e.highlight), n, v)) {
                    e.mao[0] = rem_carta(e.mao[0], n, v);
                    x += 20;
                    imprime_carta(BARALHO, x, y, e, 4, n , v);
                }
            }
        }
    }
    else{
        for (n = 0; n < 4; n++) {
            for (v = 0; v < 13; v++) {
                if (carta_existe((e.highlight), n, v)) {
                    e.mao[0] = rem_carta(e.mao[0], n, v);
                    x += 20;
                    imprime_carta(BARALHO, x, y, e, 4, n , v);
                }
            }
        }
        
    }
    
    e = bots2(e);
    while(e.actual_jogador != 0 && e.cartas[0] != 0 && e.cartas[1] != 0 && e.cartas[2] != 0 && e.cartas[3] != 0){
        e = bots2(e);
    }
    
    e.actual_jogador = 0;
    e.highlight = 0;
    return e;
    
}

/*
Função invocada na parse, que vai ser executada quando carregamos no botao passar, e que só incrementa o jogador e mantém o resto do estado.
Esta função também convoca as funções dos bots que executam as suas jogadas enquanto não for a vez do utilizador jogar.
*/
ESTADO passar (ESTADO e) {
    
    e.pass = 0;
    e = bots2(e);
    
    while(e.actual_jogador != 0){
        e = bots2(e);
    }
    
    
    e.highlight = 0;
    return e;
}


/*
O estado clear permite-nos após termos diferentes cartas no highlight, removê-las do mesmo, e colocando-as de novo na nossa mão, melhorando assim a jogabilidade.
*/
ESTADO clear(ESTADO e){
    int n,v;
    n=0;
    v=0;
    
    for (n = 0; n <= 3; n++)
    for (v = 0; v <= 12; v++) {
        if(carta_existe(e.highlight,n,v)){
            e.highlight = rem_carta(e.highlight,n,v);
        }
    }
    return e;
}
