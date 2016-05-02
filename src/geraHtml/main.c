#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "big2.h"

/** brief Trata os argumentos da CGI
Esta função recebe a query que é passada à cgi-bin e trata-a.
Neste momento, a query contém o estado que é um inteiro que representa um conjunto de cartas.
Cada carta corresponde a um bit que está a 1 se essa carta está no conjunto e a 0 caso contrário.
Caso não seja passado nada à cgi-bin, ela assume que todas as cartas estão presentes.
@param query A query que é passada à cgi-bin
*/

void parse (char *query) {
    
    ESTADO e;
    
    int a;
    
    if (query != NULL && strlen(query) != 0) {
       
        e = str2estado(query);
        
        if (e.card) e.card = 0;
        if (e.play) e = jogar(e);
        if (e.pass) e = passar(e); 
    }
    
    else {
    
        e = bots1(baralhar());
        
        while(e.actual_jogador != 0){
            e = bots2(e);
        }
        
        a=e.mao[0];
        printf("%dn", a);
    }
    
    if (e.start == 1) {
        imprime_botao_start(e);
    }

    else{
        
        if (e.cartas[0] == 0 || e.cartas[1] == 0 || e.cartas[2] == 0 || e.cartas[3] == 0) {
            imprime_botao_trofeu(e);
            imprime_botao_reset(e);
        }

        else {
            imprime(BARALHO, e);
            imprime_botao_jogar(e);
            imprime_botao_passar(e);
            imprime_botao_layout(e);
            imprime_botao_clear(e);
            imprime_botao_sugestao(e);
            imprime_botao_exit(e); 
        }
    }
}

/** brief Função principal
Função principal do programa que imprime os cabeçalhos necessários e depois disso invoca
a função que vai imprimir o código html para desenhar as cartas
*/


int main() {
/*
 * Cabeçalhos necessários numa CGI
 */

    srand(time(NULL));
    printf("Content-Type: text/html; charset=utf-8\n\n");
    printf("<header><title>Big2wo</title></header>\n");
    printf("<body>\n");
/*  printf("<h1>Big2wo</h1>\n");*/
    printf("<svg height = \"1000\" width = \"1280\">\n");
/*  printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");*/
    printf("<image x = \"0\" y = \"0\" height = \"720\" width = \"1280\" xlink:href = \"http://localhost/cards/tabfinal.png\" /></a>\n");
    printf("<image x = \"0\" y = \"719\" height = \"80\" width = \"1280\" xlink:href = \"http://localhost/cards/barra.png\" /></a>\n");
    printf("<image x = \"1250\" y = \"15\" height = \"10\" width = \"20\" xlink:href = \"http://localhost/cards/easteregg.gif\" /></a>\n");
/*
 * Ler os valores passados à cgi que estão na variável ambiente e passá-los ao programa
 */

    parse(getenv("QUERY_STRING"));
    printf("</svg>\n");
    printf("</body>\n");
    return 0;
}