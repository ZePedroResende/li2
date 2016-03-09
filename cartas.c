#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// >> 1 - menos significativo com o boda (n/2) . << 1 mais significativo com o boda (n*2)
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





#define FORMATO "%lld_%lld_%lld_%lld_%d_%d_%d_%d_%lld_%d_%d_%d"

typedef long long int MAO;
//passar p/ codigo isto
/*typedef struct  estado
{
	MAO mao[4];
	int cartas[4];
	MAO selecao;

	int passar, jogar, selecionar; //se 1 exectua funcao

} ESTADO;

ESTADO str2estado (char* str) {
	ESTADO e;
	sscanf(str, FORMATO, &e.mao[0], &e.mao[1], &e.mao[2], &e.mao[3], &e.cartas[0], &e.cartas[1], &e.cartas[2],&e.cartas[3], &e.selecao, &e.passar, &e.selecionar, &e.jogar);
	return e;
}

char* estado2str (ESTADO e){
	static char res[10240];
	sprintf(res, FORMATO, e.mao[0], e.mao[1], e.mao[2], e.mao[3], e.cartas[0],e.cartas[1],e.cartas[2],e.cartas[3], e.selecao, e.passar, e.selecionar, e.jogar);
	return res;
}
*/



long long int add_carta(long long int ESTADO, int naipe, int valor);

void baralhar (MAO *array) {
	long long int a , i , j , k , l , n , v;
	long long int res1 = 0;
	long long int res2 = 0;
	long long int res3 = 0;
	long long int res4 = 0;
    a = i = j = k = l = n = v = 0;
	long long int player1[13];
	long long int player2[13];
	long long int player3[13];
	long long int player4[13];
	int jogador;
	srand (time(NULL));
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
		res1 += player1[a];
	}

	for (a = 0; a <= 12; a++) {
		res2 += player2[a];
	}

	for (a = 0; a <= 12; a++) {
		res3 += player3[a];
	}

	for (a = 0; a <= 12; a++) {
		res4 += player4[a];
	}

	array[0] = res1;
	array[1] = res2;
	array[2] = res3;
	array[3] = res4;
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
void imprime_carta(char *path, int x, int y, long long int ESTADO, long long int ESTADO1, long long int ESTADO2, long long int ESTADO3 , int naipe, int valor) {
	char *suit = NAIPES;
	char *rank = VALORES;
	char script[10240];
	sprintf(script, "%s?%lld_%lld_%lld_%lld", SCRIPT, rem_carta(ESTADO, naipe, valor), rem_carta(ESTADO1, naipe, valor), rem_carta(ESTADO2, naipe, valor),rem_carta(ESTADO3, naipe, valor));
	printf("<a xlink:href = \"%s\"><image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" /></a>\n", script, x, y, path, rank[valor], suit[naipe]);
}

/** \brief Imprime o estado

Esta função está a imprimir o estado em quatro colunas: uma para cada naipe
@param path	o URL correspondente à pasta que contém todas as cartas
@param ESTADO	O estado atual
*/

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
	MAO array [4]={};
	baralhar (array);
	if(sscanf(query, "%lld_%lld_%lld_%lld", &array[0], &array[1], &array[2], &array[3]) == 4) {
    imprime(BARALHO, array);

	} else {
   
	imprime(BARALHO, array);
}
}





/** \brief Função principal

Função principal do programa que imprime os cabeçalhos necessários e depois disso invoca
a função que vai imprimir o código html para desenhar as cartas
 */


int main() {
/*
 * Cabeçalhos necessários numa CGI
 */


/* ESTADO e;
		int i;
		char str[10240];
		
		for (i=0;i<4;i++) {
		 e.mao[i]=0;
		 e.cartas[i]=0;
		}
		e.selecao=0;
		e.passar = e.jogar = e.selecionar = 0;

 scanf("%s", str); //getevcoiso
		e=str2estado(str);


		printf("%s\n",estado2str (e));

*/

	printf("Content-Type: text/html; charset=utf-8\n\n");
	printf("<header><title>Big2wo</title></header>\n");
	printf("<body>\n");
  printf("<h1>Big2wo</h1>\n");

/*
 * Ler os valores passados à cgi que estão na variável ambiente e passá-los ao programa
 */


	parse(getenv("QUERY_STRING"));

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
