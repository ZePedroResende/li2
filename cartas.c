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

const long long int ESTADO_INICIAL = 0xb00a00f000f;



long long int add_carta(long long int ESTADO, int naipe, int valor);


int randomizer() {
   
   time_t t;
   int r;
   srand((unsigned) time(&t));

   r = rand() % 4;
   
   return r;
}


long long int baralhar () {
	int a , i , j , k , l , n , v;
	long long int res; 
    a = i = j = k = l = n = v = res = 0;
	long long int player1[13];
	long long int player2[13];
	long long int player3[13];
	long long int player4[13]; 
	int jogador;
	for(a = 0; a <= 12; a++) {
		player1[a] = 0;
		player2[a] = 0;
		player3[a] = 0;
		player4[a] = 0;
	}
	for (n = 0; n <= 3; n++)
		for (v = 0; v <= 12; v++) {
			jogador = randomizer();
			switch (jogador) {
				case 0: if (i == 13) v--; else add_carta (player1[i], n, v); i++; break;
				case 1: if (i == 13) v--; else add_carta (player2[j], n, v); j++; break;
				case 2: if (i == 13) v--; else add_carta (player3[k], n, v); k++; break;
				case 3: if (i == 13) v--; else add_carta (player4[l], n, v); l++; break;
		}
	}
	for (a = 0; a <= 12; a++) {
		res += player1[a];
	}
	return res;
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
void imprime_carta(char *path, int x, int y, long long int ESTADO, int naipe, int valor) {
	char *suit = NAIPES;
	char *rank = VALORES;
	char script[10240];
	sprintf(script, "%s?q=%lld", SCRIPT, rem_carta(ESTADO, naipe, valor));
	printf("<a xlink:href = \"%s\"><image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" /></a>\n", script, x, y, path, rank[valor], suit[naipe]);
}

/** \brief Imprime o estado

Esta função está a imprimir o estado em quatro colunas: uma para cada naipe
@param path	o URL correspondente à pasta que contém todas as cartas
@param ESTADO	O estado atual
*/

void imprime(char *path, long long int ESTADO) {
	int n, v;
	int x, y;
	x = 220;

	printf("<svg height = \"800\" width = \"800\">\n");
	printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");

	for(y = 670, n = 0; n < 4; n++) {
		for(v = 0; v < 13; v++)
			if(carta_existe(ESTADO, n, v)) {
				x += 20;
				imprime_carta(path, x, y, ESTADO, n, v);
			}
	}
	printf("</svg>\n");
}

/*
void imprime(char *path, long long int ESTADO) {
	int n, v;
	int x, y;
	y=410;
    n=0;
    v=0;
    x=10;
	printf("<svg height = \"800\" width = \"800\">\n");
	printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");
   
	while (n<4){
		while(v<13){
			if(carta_existe(ESTADO, n, v)) {
				x += 20;
				imprime_carta(path, x, y, ESTADO, n, v);
                
            }	
        v++;
        }
	printf("</svg>\n");
    n++;
}
}
*/

/** \brief Trata os argumentos da CGI

Esta função recebe a query que é passada à cgi-bin e trata-a.
Neste momento, a query contém o estado que é um inteiro que representa um conjunto de cartas.
Cada carta corresponde a um bit que está a 1 se essa carta está no conjunto e a 0 caso contrário.
Caso não seja passado nada à cgi-bin, ela assume que todas as cartas estão presentes.
@param query A query que é passada à cgi-bin
 */

/*
void parse(char *query) {
	long long int ESTADO;
	if(sscanf(query, "q=%lld", &ESTADO) == 1) {
		imprime(BARALHO, ESTADO);
	} else {
		imprime(BARALHO, baralhar());
	}
}
*/ 

void parse(char *query) {
	long long int ESTADO;
	if(sscanf(query, "q=%lld", &ESTADO) == 1) {
		imprime(BARALHO, ESTADO);
	} else {
		imprime(BARALHO, baralhar());
	}
}





/** \brief Função principal

Função principal do programa que imprime os cabeçalhos necessários e depois disso invoca
a função que vai imprimir o código html para desenhar as cartas
 */

/*
int main() {
/*
 * Cabeçalhos necessários numa CGI
 */
/*
	printf("Content-Type: text/html; charset=utf-8\n\n");
	printf("<header><title>Big2wo</title></header>\n");
	printf("<body>\n");

	printf("<h1>Big2wo</h1>\n");

/*
 * Ler os valores passados à cgi que estão na variável ambiente e passá-los ao programa
 */

/*
	parse(getenv("QUERY_STRING"));

	printf("</body>\n");
	return 0;
}
*/
int main () {

	int x;
	
	x = baralhar();

	printf("%d \n", x);

	return 0;
}