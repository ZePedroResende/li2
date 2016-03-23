#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
URL da CGI
*/
#define SCRIPT		"http://127.0.0.1/cgi-bin/cartas"
/**
URL da pasta com as cartas
*/
#define BARALHO		"http://127.0.0.1/cards"

/**
Ordem dos naipes
*/
#define NAIPES		"DCHS"
/**
Ordem das cartas
*/
#define VALORES		"3456789TJQKA2"

/**
	Estado inicial com todas as 52 cartas do baralho
	Cada carta é representada por um bit que está
	a 1 caso ela pertença à mão ou 0 caso contrário
*/

const long long int ESTADO_INICIAL = 0x1FFF;





#define FORMATO "%lld_%lld_%lld_%lld_%lld_%d_%d_%d_%d_%d_%d_%d_%lld_%d"


typedef long long int MAO;
struct estado {
	MAO mao[4];

	MAO highlight;

	int cartas[4];

	int play, pass, card;

	MAO ultima_jogada;
	int ultimo_jogador;
};
	
typedef struct estado ESTADO;
char* estado2str(ESTADO e){
  static char str[10240];
  sprintf(str, FORMATO, e.mao[0], e.mao[1], e.mao[2], e.mao[3], e.highlight, e.cartas[0], e.cartas[1], e.cartas[2], e.cartas[3], e.play, e.pass, e.card, e.ultima_jogada, e.ultimo_jogador);

  return str;
}

ESTADO str2estado(char* str){
  ESTADO e;
  sscanf(str, FORMATO, &e.mao[0], &e.mao[1], &e.mao[2], &e.mao[3], &e.highlight, &e.cartas[0], &e.cartas[1], &e.cartas[2], &e.cartas[3], &e.play, &e.pass, &e.card, &e.ultima_jogada, &e.ultimo_jogador);  

  return e;
}

int carta_existe(long long int ESTADO, int naipe, int valor) ;


int primeiro_jogar(ESTADO e){
int n =0;
  
      if (carta_existe(e.mao[0], 0, 0)){
       n=0;
	 }
	 
      if (carta_existe(e.mao[1], 0, 0)){
       n= 1;
       
   }
      if (carta_existe(e.mao[2], 0, 0)){
       n=  2;
       
      }
      if (carta_existe(e.mao[3], 0, 0)){
       n=  3;
       
      }

return n;
}

long long int add_carta(long long int ESTADO, int naipe, int valor);

ESTADO baralhar () {
	int a=0 , i=0 , j=0 , k=0 , l=0 , n=0 , v=0, jogador;

	long long int player1[13];
	long long int player2[13];
	long long int player3[13];
	long long int player4[13];
	
	ESTADO e = {{0},0,{0},0,0,0,-1,0};

	e.cartas[0] = 13;
	e.cartas[1] = 13;
	e.cartas[2] = 13;
	e.cartas[3] = 13;




	for(a = 0; a <= 12; a++) {
		player1[a] = 0;
		player2[a] = 0;
		player3[a] = 0;
		player4[a] = 0;
	}
	for (n = 0; n <= 3; n++)
		for (v = 0; v <= 12; v++) {
			jogador = (rand() % 4);
			switch (jogador) {
				case 0: if (i == 13) v--; else { player1[i] = (add_carta (0, n, v)); i++; } break;
				case 1: if (j == 13) v--; else { player2[j] = (add_carta (0, n, v)); j++; } break;
				case 2: if (k == 13) v--; else { player3[k] = (add_carta (0, n, v)); k++; } break;
				case 3: if (l == 13) v--; else { player4[l] = (add_carta (0, n, v)); l++; } break;
			}
		}
	for (a = 0; a <= 12; a++) {
		e.mao[0] += player1[a];
	}

	for (a = 0; a <= 12; a++) {
		e.mao[1] += player2[a];
	}

	for (a = 0; a <= 12; a++) {
		e.mao[2] += player3[a];
	}

	for (a = 0; a <= 12; a++) {
		e.mao[3] += player4[a];
	}

	e.ultimo_jogador = primeiro_jogar(e);

	return e;

}




/** \brief Devolve o índice da carta
@param naipe	O naipe da carta (inteiro entre 0 e 3)
@param valor	O valor da carta (inteiro entre 0 e 12)
@return		O índice correspondente à carta
*/
int indice(int naipe, int valor) {
	return naipe * 13 + valor;
}

/** \brief Adiciona uma carta ao estado
@param ESTADO	O estado atual
@param naipe	O naipe da carta (inteiro entre 0 e 3)
@param valor	O valor da carta (inteiro entre 0 e 12)
@return		O novo estado
*/
long long int add_carta(long long int ESTADO, int naipe, int valor) {
	int idx = indice(naipe, valor);
	return ESTADO | ((long long int) 1 << idx);
}

/** \brief Remove uma carta do estado
@param ESTADO	O estado atual
@param naipe	O naipe da carta (inteiro entre 0 e 3)
@param valor	O valor da carta (inteiro entre 0 e 12)
@return		O novo estado
*/
long long int rem_carta(long long int ESTADO, int naipe, int valor) {
	int idx = indice(naipe, valor);
	return ESTADO & ~((long long int) 1 << idx);
}

/** \brief Verifica se uma carta pertence ao estado
@param ESTADO	O estado atual
@param naipe	O naipe da carta (inteiro entre 0 e 3)
@param valor	O valor da carta (inteiro entre 0 e 12)
@return		1 se a carta existe e 0 caso contrário
*/
int carta_existe(long long int ESTADO, int naipe, int valor) {
	int idx = indice(naipe, valor);
	return (ESTADO >> idx) & 1;
}

/** \brief Imprime o html correspondente a uma carta
@param path	o URL correspondente à pasta que contém todas as cartas
@param x A coordenada x da carta
@param y A coordenada y da carta
@param ESTADO	O estado atual
@param naipe	O naipe da carta (inteiro entre 0 e 3)
@param valor	O valor da carta (inteiro entre 0 e 12)
*/




/*
void imprime_carta(char *path, int x, int y, long long int ESTADO, long long int ESTADO1, long long int ESTADO2, long long int ESTADO3 , int naipe, int valor) {
	char *suit = NAIPES;
	char *rank = VALORES;
	char script[10240];
	sprintf(script, "%s?%lld_%lld_%lld_%lld", SCRIPT, rem_carta(ESTADO, naipe, valor), ESTADO1, ESTADO2, ESTADO3);
	printf("<a xlink:href = \"%s\"><image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" /></a>\n", script, x, y, path, rank[valor], suit[naipe]);
}
*/

/** \brief Imprime o estado?5639952667138_4389327735900288_107805827932500_826110870569_4539780431872_13_13_13_13_1_0_0_0_0
Esta função está a imprimir o estado em quatro colunas: uma para cada naipe
@param path	o URL correspondente à pasta que contém todas as cartas
@param ESTADO	O estado atual
*/

void imprime_carta(char *path, int x, int y, ESTADO e, int mao, int naipe, int valor) {
	char *suit = NAIPES;
	char *rank = VALORES;
	char script[10240];
	ESTADO novo = e;
	novo.card = 1; 
   
	if (mao == 0 && e.ultimo_jogador == 0) {
		if (carta_existe (novo.highlight, naipe, valor)) {
			novo.highlight = rem_carta(novo.highlight, naipe, valor); 
		}

		else {
			novo.highlight = add_carta(novo.highlight, naipe, valor); 
		}

		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" /></a>\n", script, x, y, path, rank[valor], suit[naipe]);	
	}

	else {
		printf("<image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" />\n", x, y, path, rank[valor], suit[naipe]);
	}
}




void imprime (char *path, ESTADO e) {

	int n, v, m;
	int X[4] = {200, 600, 200, 10};
	int Y[4] = {550, 200, 10, 200};

	for(m = 0; m < 4; m++) { 

		int x = X[m], y = Y[m];

		for (n = 0; n < 4; n++) {
			
			for (v = 0; v < 13; v++)
				
				if (carta_existe(e.mao[m], n, v)) {
					
					if (m % 2 == 0) { 
						x += 20;
					}

					else {
						y += 20; 
					}

					if (m == 0 && carta_existe(e.highlight, n, v)) {
						imprime_carta(path, x, (y - 20), e, m, n, v); 	
					}
				
					else {
						imprime_carta(path, x, y, e, m, n, v);
					}
			}
		}
	}
}



/*
void imprime(char *path, long long int ESTADO[]) {
	int n, v;
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = 220;
    y2 = 490;
    x3 = 480;
    y4 = 230;

	printf("<svg height = \"800\" width = \"800\">\n");
	printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");

	for(y1 = 670, x2=670, y3= 30, x4 = 30  , n = 0; n < 4; n++) {
		for(v = 0; v < 13; v++)
			
            if(carta_existe(ESTADO[0], n, v)) {
				x1 += 20;
				imprime_carta(path, x1, y1, ESTADO[0],  ESTADO[1],  ESTADO[2],  ESTADO[3], n, v);
			}

            else if(carta_existe(ESTADO[1], n, v)) {
				y2 -= 20 ;
				imprime_carta(path, x2, y2,  ESTADO[0], ESTADO[1],  ESTADO[2],  ESTADO[3], n, v);
			}
			

			else if(carta_existe(ESTADO[2], n, v)) {
				x3 -= 20;
				imprime_carta(path, x3, y3, ESTADO[0],  ESTADO[1],  ESTADO[2],  ESTADO[3], n, v);
			}

			else if(carta_existe(ESTADO[3], n, v)) {
				y4 += 20;
				imprime_carta(path, x4, y4,  ESTADO[0],  ESTADO[1],  ESTADO[2],  ESTADO[3], n, v);
			}
	}
	printf("</svg>\n");
}
*/



int numero_de_cartas(MAO m){
	
	int n, v, contaCartas=0;

	for (n = 0; n < 4; n++) {
			
			for (v = 0; v < 13; v++)
				
				if (carta_existe(m, n, v)) contaCartas++;
	}

	return contaCartas;
}




/*
  funçao int conta_cartas Mao
  2 int da_valor(MAO) que devolve -1 se a mao tem mais do que um valor e o valor caso todas as cartas da mao tenham o mesmo valor
  3 faz um funçao int da_maior_naipe (MAO) que devolve o maior naipe de uma MAO



  isto para a combinaçao maior .
  (1-1/1)
 */

int combinacao_valida(MAO m) { 
	
	if ((numero_de_cartas (m)) > 3) {
	 	return 0;
	}

	else return 1;
}

int compara_tamanho(MAO m1, MAO m2){
	if (numero_de_cartas(m1) == numero_de_cartas(m2)) {
		return 1;
	} 

	return 0;
}

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


int da_maior_naipe (MAO m){
 	int n, v, maior=0;

	for (n = 0; n < 4; n++) {

    for (v = 0; v < 13; v++)

      if (carta_existe(m, n, v)) { if (n > maior) maior =n;}
	}

	return maior;
}



int combinacao_maior (MAO m1, MAO m2) {
  int n =0;
        if ((da_valor(m2)) != -1){
            if (da_valor(m1) < da_valor(m2)) n =1;
            if (da_valor(m1) >  da_valor(m2)) n= 0 ;
            if (da_valor(m1) == da_valor(m2)) {
             if (da_maior_naipe(m1) < da_maior_naipe(m2)) n=1;
             
            }
          }
      

else n= 0;

return n;
}

int posso_jogar (ESTADO e) {
	
	if (e.ultima_jogada == -1){
		if (!combinacao_valida (e.highlight) ) { 
			return 0;
		}
		
		else {
	 	
	 		if (e.ultimo_jogador != 0) {
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
	
	else {	
		if (!combinacao_valida (e.highlight)) { 
			return 0;
		}
		
		else {
	 	
	 		if (e.ultimo_jogador != 0) {
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


	
int incrementa_jogador (ESTADO e){
  if (e.ultimo_jogador != 3) return (e.ultimo_jogador += 1);
  else return 0;
}

ESTADO bots2(ESTADO e);


void imprime_botao_jogar(ESTADO e) {

	char script[10240];
	ESTADO novo = e;

	if (posso_jogar(e)) {
	    novo.ultima_jogada = e.highlight;
        novo.cartas[0] = e.cartas[0] - (numero_de_cartas(novo.ultima_jogada));
      	novo.ultimo_jogador = incrementa_jogador(e);
		novo.play = 1;
		
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"280\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/SubmitLI2.png\" /></a>\n", script); 
	}

	else {
		printf("<image x = \"280\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/SubmitLI2out.png\" />\n"); 
	}
}

void imprime_botao_passar(ESTADO e) {

	char script[10240];
	ESTADO novo = e;

	if(e.ultimo_jogador == 0 && e.ultima_jogada != -1){
		novo.ultima_jogada = e.ultima_jogada;
    novo.highlight = 0;
    novo.ultimo_jogador = incrementa_jogador(e);
    novo.pass = 1;
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"380\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/PassLI2.png\" /></a>\n", script); 
}

	else {
		printf("<image x = \"380\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/PassLI2out.png\" />\n"); 
	}
}



void imprime_botao_incrementa(ESTADO e) {

	char script[10240];
	ESTADO novo = e;

	
    novo.ultimo_jogador = incrementa_jogador(e);
    
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"480\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/PassLI2.png\" /></a>\n", script);


	
}










ESTADO jogar (ESTADO e) {
	
	int n, v, x, y;

	x = 250;
	y = 400;

	e.play = 0;

		for (n = 0; n < 4; n++) {
			for (v = 0; v < 13; v++) {
				if (carta_existe((e.highlight), n, v)) {
					e.mao[0] = rem_carta(e.mao[0], n, v);
					x += 20;
					imprime_carta(BARALHO, x, y, e, 4, n , v);
				}
			}
		}

	e.highlight = 0; 
	
	return e;
}


ESTADO passar (ESTADO e) {
	
	e.pass = 0;
	e.highlight = 0; 
	return e;
}


/*
ESTADO incrementa (ESTADO e) {
	int n, v, x, y, m;
	e.highlight = e.highlight; 
	return e;
}
*/
/*
  Validação Bots:

  - Se bot começar com 3 de ouros, é essa a carta que ele tem de jogar, ou um par, ou um trio com o 3 de ouros

  - Supondo que somos nós a começar. O bot1 tem de jogar uma combinação válida maior que a nossa. Seguidamente, o bot2 uma maior que o bot1, e o bot3 uma maior que o bot2.

  - Objetivo do bot: Procurar na sua mão a menor combinação possível a ser jogada, em relação à anterior. 
  (Se for ele a começar a turno, ele jogará na mesma a menor carta possível em relação à última carta jogada da última ronda).

  - Se ao percorrer a mão do bot, ele não tiver uma combinação maior que a anterior, não joga nada, sendo equivalente a um "PASS".
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

/*ESTADO bots(ESTADO e){
	long long int m=0 ;
	int n,v;

while(e.ultimo_jogador != 0){
if (e.ultima_jogada == -1 && e.ultimo_jogador == 2 ){
 e.cartas[e.ultimo_jogador] = e.cartas[(e.ultimo_jogador)] - 1;
 e.mao[e.ultimo_jogador] = rem_carta(e.mao[(e.ultimo_jogador)],0,0);
 e.ultima_jogada = 1;
 e.ultimo_jogador = incrementa_jogador(e);
 e.card = 0;
 

 
}

else
	for (n = 1; n <= 3; n++)
		for (v = 0; v <= 12; v++) {
			m = add_carta(0,n,v);
			if (carta_existe(e.mao[e.ultimo_jogador],n,v) && valida_bots_jogadas_normais(e,m)){
				e.cartas[e.ultimo_jogador] = e.cartas[(e.ultimo_jogador)] - 1;
				e.mao[e.ultimo_jogador] = rem_carta(e.mao[(e.ultimo_jogador)],n,v);
				e.ultima_jogada = m;
				e.ultimo_jogador = incrementa_jogador(;
				e.card = 0;
            }
        }
    }
}
return e;
}
*/



ESTADO bots1(ESTADO e){



if (e.ultima_jogada == -1 && e.ultimo_jogador == 3 ){
 e.cartas[e.ultimo_jogador] =( e.cartas[(e.ultimo_jogador)]) - 1;
 e.mao[e.ultimo_jogador] = rem_carta(e.mao[(e.ultimo_jogador)],0,0);
 e.ultima_jogada = 1;
 e.ultimo_jogador = incrementa_jogador(e);
 e.card = 0;
 return e;
 }
return e;
}





ESTADO bots2(ESTADO e){
	long long int m=0 ;
	int n,v;

  while(e.ultimo_jogador != 0){
if (e.ultima_jogada != -1  ){
	for (v = 0; v <= 12; v++)
    for (n = 0; n <= 3; n++){
			m = add_carta(0,n,v);
			if (carta_existe(e.mao[e.ultimo_jogador],n,v) && valida_bots_jogadas_normais(e,m)){
				m = add_carta(0,n,v);
				e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
				e.ultima_jogada = m;
				e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
				
				e.ultimo_jogador = incrementa_jogador(e);
				e.card = 0;
            }
        }
 }
  }
    return e;
}



/*
ESTADO jogar (ESTADO e){
  int n, v, x=250, y=400;  
  e.play = 0;
  for(n = 0; n < 4; n++) {
    for(v = 0; v < 13; v++) {
      if(carta_existe(e.highlight, n, v)) {
        e.mao[0]=rem_carta(e.mao[0], n, v);
        x+=20;
        imprime_carta(BARALHO, x, y, e, 4, n, v);
      }
    }
  }    
  e.highlight = 0;
  return e;
}
*/


/** \brief Trata os argumentos da CGI
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
/*a= 	e.ultimo_jogador;
printf("%d\n", a);*/
		if (e.play) e = bots2(jogar(e));
        if (e.pass) e = bots2(passar(e));
       /* if(e.ultimo_jogador != 0) e = incrementa(e);*/
    a=e.mao[0];
    printf("%d\n", a);
   /* if (e.ultimo_jogador != 0){
      e = bots(e);
    }*/
	}


	else {
		
   e = bots1(baralhar());

 a=e.mao[0];
printf("%d\n", a);

	}
	
	imprime(BARALHO, e);
    (imprime_botao_jogar(e));
  	imprime_botao_passar(e);
  	imprime_botao_incrementa(e);
/*  a= 	e.ultimo_jogador;
printf("%d\n", a);*/
}


/** \brief Função principal
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
	printf("<h1>Big2wo</h1>\n");
	printf("<svg height = \"800\" width = \"800\">\n");
	printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");

/*
 * Ler os valores passados à cgi que estão na variável ambiente e passá-los ao programa
 */

	parse(getenv("QUERY_STRING"));
	printf("</svg>\n");
	printf("</body>\n");
	return 0;
}


/*
int main () {
	int x;
	x = baralhar();
	printf("%d \n", x);
	return 0;
}
*/
