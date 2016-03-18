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




long long int add_carta(long long int ESTADO, int naipe, int valor);

ESTADO baralhar () {
	
	ESTADO e = {{0},0,{0},0,0,0,0,0};

	e.cartas[0] = 13;
	e.cartas[1] = 13;
	e.cartas[2] = 13;
	e.cartas[3] = 13;


	long long int a , i , j , k , l , n , v;
    a = i = j = k = l = n = v = 0;
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
	novo.card = 1; // parte do estado que define uma açao 
   
	if (mao == 0) {
		if (carta_existe (novo.highlight, naipe, valor)) {
			novo.highlight = rem_carta(novo.highlight, naipe, valor); //se ela ja esta subida, ao ser clicada outra vez, desce
		}

		else {
			novo.highlight = add_carta(novo.highlight, naipe, valor); // senão estiver subida, tem de ser subida ao clicar.	
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
	int X[4] = {200, 10, 200, 600};
	int Y[4] = {550, 200, 10, 200};

	for(m = 0; m < 4; m++) { 

		int x = X[m], y = Y[m];

		for (n = 0; n < 4; n++) {
			
			for (v = 0; v < 13; v++)
				
				if (carta_existe(e.mao[m], n, v)) {
					
					if (m % 2 == 0) { // SE NA MAO TIVER 0 E 2, AVANÇA O X (SE A MINHA VOU O 0 OU O 2, AVANÇA O X)
						x += 20;
					}

					else {
						y += 20; // SE TIVER NA MAO 1 E 2, AVANÇA O Y (SE A MINHA MAO FOR...)
					}

					if (m == 0 && carta_existe(e.highlight, n, v)) {
						imprime_carta(path, x, (y - 20), e, m, n, v); //AO SER SELECIONADA UMA CARTA, A CARTA SOBE! HOLY SHIT!	
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
//TER 4 FUNÇÕES AUXILIARES PARA 1 CARTA, 2 CARTAS, 3 CARTAS, 4 CARTAS, 5 CARTAS 
	//CARTAS QUE ESTÃO DENTRO DE UMA COMBINAÇÃO VALIDA TEM O MESMO VALOR, se nao tiver é nao valida.



int numero_de_cartas(MAO m){
	
	int n, v, contaCartas=0;

	for (n = 0; n < 4; n++) {
			
			for (v = 0; v < 13; v++)
				
				if (carta_existe(m, n, v)) contaCartas++;
	}

	return contaCartas;
}



int combinacao_valida(MAO m) { 
	
	if ((numero_de_cartas (m)) > 3) {
	 	return 0;
	}
	
	return 1;
}

int compara_tamanho(MAO m1, MAO m2){
	if (numero_de_cartas(m1) == numero_de_cartas(m2)) {
		return 1;
	} 

	return 0;
}

int combinacao_maior (MAO m1, MAO m2) {
		if (m1 > m2) {
			return 0;
		}
	
	return 1;
}


int posso_jogar (ESTADO e) {
	
	if (!combinacao_valida (e.highlight)) { 
		return 0;
	}
	else {
	 	
	 	if (e.ultimo_jogador != 0) {
	 		return 0; 
	 	}
		else {
	 		
	 		if (!combinacao_maior (e.ultima_jogada, e.highlight)) {
	 			return 0;
	 		}
		}
	}	

	return 1;
}
	



void imprime_botao_jogar(ESTADO e) {

	char script[10240];
	ESTADO novo = e;
	
	if (posso_jogar(e)) {
		novo.ultima_jogada = e.highlight;
		novo.play = 1;
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"120\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/SubmitLI2.png\" /></a>\n", script); //IMPRIME BOTAO EM FORMATO PNG (BOTAO ESSE QUE FOI COPIADO PARA A PASTA HTML)
	}

	else {
		printf("<image x = \"120\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/SubmitLI2.png\" />\n"); //SE EU CONSEGUIR JOGAR, O BOTAO É CLICAVEL, SENÃO NÃO É
	}
}	




ESTADO jogar (ESTADO e) {
	
	int n, v, x, y, m;

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


	if (query != NULL && strlen(query) != 0) {
		e = str2estado(query); //função que tinha sido dada pelo professor
		if (e.card) e.card = 0;

		if (e.play) e = jogar(e);
	}	

	else {
		e = baralhar();
	}
	
	imprime(BARALHO, e);
	imprime_botao_jogar(e);

}





/*
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
*/




/** \brief Função principal
Função principal do programa que imprime os cabeçalhos necessários e depois disso invoca
a função que vai imprimir o código html para desenhar as cartas
 */


int main() {
/*
 * Cabeçalhos necessários numa CGI
 */

 	srandom(time(NULL));
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