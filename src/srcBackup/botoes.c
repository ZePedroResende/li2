#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

/** 
Esta função trata de imprimir o botão "SUBMIT" na página HTML. Aqui, usamos a função posso_jogar.
Se for possível jogar, o botão é clicável, sendo primitida a jogada. Caso contrário, o botão fica mais escuro, não sendo clicável. 
@param e O estado actual.
*/
void imprime_botao_jogar(ESTADO e) {
    
    char script[10240];
    ESTADO novo = e;
    
    if (posso_jogar(e) && e.highlight != 0) {
        novo.ultima_jogada = e.highlight;
        novo.cartas[0] = e.cartas[0] - (numero_de_cartas(novo.ultima_jogada));
        novo.actual_jogador = incrementa_jogador(e);
        novo.play = 1;
        novo.ultimo_jogador = 0;
        sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
        printf("<a xlink:href = \"%s\"><image x = \"510\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/SubmitLI2.png\" /></a>\n", script); 
    }
    
    else {
        printf("<image x = \"510\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/SubmitLI2out.png\" />\n"); 
    }
}

/** 
Esta função trata de imprimir o botão "PASS" na página HTML. Quando o utilizador não tem nenhuma combinação válida possível
em relação a última jogada, é possível usar o botão "PASS". O utilizador pode usar sempre o botão "PASS",
excepto quando é o primeiro a jogar (3 de ouros) ou quando todos passam a jogada e este foi o ultimo a jogar uma carta/combinaçao 
@param e O estado actual.
*/
void imprime_botao_passar(ESTADO e) {
    
    char script[10240];
    ESTADO novo = e;
    
    if (e.actual_jogador == 0 && e.ultima_jogada != -1 && e.ultimo_jogador != 0) {
        novo.ultima_jogada = e.ultima_jogada;
        novo.highlight = 0;
        novo.actual_jogador = incrementa_jogador(e);
        novo.pass = 1;
        sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
        printf("<a xlink:href = \"%s\"><image x = \"610\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/PassLI2.png\" /></a>\n", script); 
    }
    
    else {
        printf("<image x = \"610\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/PassLI2out.png\" />\n");
    }
}



/**
A função imprime_botao_clear imprime o botão clear para o browser, o qual vai limpar as cartas do highlight, e retorná-las à nossa mão.
@param e O estado actual.
*/
void imprime_botao_clear(ESTADO e) {
    
    char script[10240];
    
    e = clear(e);
    sprintf(script, "%s?%s", SCRIPT, estado2str(e));
    printf("<a xlink:href = \"%s\"><image x = \"710\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/ClearLI2.png\" /></a>\n", script);
}

/**
A função imprime_botao_sugestao imprime o botão de sugestão para o browser.
@param e O estado actual.
*/
void imprime_botao_sugestao(ESTADO e) {
    
    char script[10240];
    
    e = clear(e);
    
    if (e.ultima_jogada == -1) e = sugestao1(e);
    else{
        e = sugestao2(e);
        if (e.highlight == 0){
            e.ultima_jogada = e.ultima_jogada;
            e.actual_jogador = incrementa_jogador(e);
            e.pass = 1;
        }
    }
    sprintf(script, "%s?%s", SCRIPT, estado2str(e));
    printf("<a xlink:href = \"%s\"><image x = \"40\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/sugestaostallman.gif\" /></a>\n", script);
}


/**
A função imprime_botao_start imprime o botão de start do menu inicial para o browser.
@param e O estado actual.
*/
void imprime_botao_start(ESTADO e) {
    
    char script[10240];
    
    if (e.start == 1){
        e = bots1(baralhar());
        
        while(e.actual_jogador != 0){
            e = bots2(e);
        }
        
        e.start=0;
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"1280\" style = \"fill:#000000\"/>\n");
        printf("<image x = \"0\" y = \"0\" height = \"800\" width = \"1280\" xlink:href = \"http://localhost/cards/bg.png\" /></a>\n");
        printf("<a xlink:href = \"%s\"><image x = \"1080\" y = \"650\" height = \"110\" width = \"150\" xlink:href = \"http://localhost/cards/StartLI2.png\" /></a>\n", script);
    }
}

/**
A função imprime_botao_exit imprime o botão de exit para o browser, de forma a ser possível recomeçar o jogo, voltando ao menu inicial com o botão start.
@param e O estado actual.
*/
void imprime_botao_exit(ESTADO e) {
    
    char script[10240];
    
    if (e.start == 0){
        e = bots1(baralhar());
        
        while(e.actual_jogador != 0){
            e = bots2(e);
        }
        
        e.start=1;
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"1140\" y = \"603\" height = \"80\" width = \"100\" xlink:href = \"http://localhost/cards/ExitLI2.png\" /></a>\n", script);   
    }
}


/**
A função imprime_botao_reset imprime um botão que quando algum dos jogadores ganha a ronda, ou seja, acabam as cartas da sua mão.
@param e O estado actual.
*/
void imprime_botao_reset(ESTADO e) {
    
    char script[10240];
    
    if (e.cartas[0] != 0 && e.cartas[1] != 0 && e.cartas[2] != 0 && e.cartas[3] != 0) {
        
    }
    else {
        e = bots1(baralhar());
        
        while(e.actual_jogador != 0) {
            e = bots2(e);
        }
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"850\" y = \"530\" height = \"220\" width = \"200\" xlink:href = \"http://localhost/cards/playagain.png\" /></a>\n", script);
    }
}


/*
A função imprime_botao_layout imprime um botão que muda a organização inicial das cartas (de naipe para valor).
@param e O estado actual.
*/ 
void imprime_botao_layout(ESTADO e) {
    
    char script[10240];
    
    if (e.layout == 0) {
        e.layout = 1;
    }
    else {
        e.layout = 0;
    }
    
    sprintf(script, "%s?%s", SCRIPT, estado2str(e));
    printf("<a xlink:href = \"%s\"><image x = \"1140\" y = \"710\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/Reset.png\" /></a>\n", script);
}


/*
A função imprime_botao_trofeu imprime uma imagem com um trofeu correspondente ao vencedor do jogo no final do mesmo.
@param e O estado actual.
*/
void imprime_botao_trofeu(ESTADO e) {
    
    char script[10240];
    
    if (e.cartas[0] == 0) {
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"260\" y = \"50\" height = \"750\" width = \"750\" xlink:href = \"http://localhost/cards/trofeu.png\" /></a>\n", script);
    }
    
    if (e.cartas[1] == 0) {
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"260\" y = \"50\" height = \"750\" width = \"750\" xlink:href = \"http://localhost/cards/trofeu2.png\" /></a>\n", script);
    }
    
    if (e.cartas[2] == 0) {
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"260\" y = \"50\" height = \"750\" width = \"750\" xlink:href = \"http://localhost/cards/trofeu3.png\" /></a>\n", script);
    }
    
    if (e.cartas[3] == 0){
        sprintf(script, "%s?%s", SCRIPT, estado2str(e));
        printf("<a xlink:href = \"%s\"><image x = \"260\" y = \"50\" height = \"750\" width = \"750\" xlink:href = \"http://localhost/cards/trofeu4.png\" /></a>\n", script);
    } 
}