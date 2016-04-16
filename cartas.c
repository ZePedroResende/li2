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




#define FORMATO "%lld_%lld_%lld_%lld_%lld_%d_%d_%d_%d_%d_%d_%d_%d_%lld_%d_%lld_%lld_%lld_%lld"

/* A struct estado contém as variáveis, as quais vão ser alteradas e manipuladas de modo a produzir jogadas válidas, tanto pelo jogador
como pelos "bots"
Dentro desta struct existe: 
	1) mao[4] -> Array que contém a mão de cada jogador;
	2) highlight -> Carta(s) selecionada(s) pelo utilizador;
	3) cartas[4] -> Número de cartas de cada mão;
	4) play, pass -> Valor que varia entre 0 e 1 conforme a ação do utlizador;
	5) ultima_jogada_valida -> Número de jogador que realmente executou uma jogada válida;
	6) ultima_jogada -> Ultima carta/combinição jogada;
	7) ultimo_jogador -> Número do jogador que está a efetuar uma jogada;
	8) cartas_bots[4] -> Cartas que os bots jogaram; */

typedef long long int MAO;

struct estado {
	MAO mao[4];

	MAO highlight;

    
	int cartas[4];

	int play, pass, card, ultima_jogada_valida;

	MAO ultima_jogada;
	int ultimo_jogador;
	MAO cartas_bots[4];
};

/*
   criar tres funcoes para avaliar 5 cartas *straight
    
   separa valores
   separa naipes
   ordenacao

   quando tem um as: ver em que ordem tem um straight. A partir daí, é que vemos onde pomos o as.



   para avaliar o resto das combinações:

   usar separa-valores e separa-naipes



   separa valores . 
   cria um array com 14 posiçoes com o As e o 2 no principio e o A na 14 . 
   Se tiveres cinco poisçoes diferentes de 0 tens um strait .
   */



/* Transforma o estado numa string, de forma a ser passado ao url. */

typedef struct estado ESTADO;
char* estado2str(ESTADO e){
  static char str[10240];
  sprintf(str, FORMATO, e.mao[0], e.mao[1], e.mao[2], e.mao[3], e.highlight, e.cartas[0], e.cartas[1], e.cartas[2], e.cartas[3], e.play, e.pass, e.card,e.ultima_jogada_valida, e.ultima_jogada, e.ultimo_jogador, e.cartas_bots[0], e.cartas_bots[1], e.cartas_bots[2], e.cartas_bots[3]);

  return str;
}

/* Transforma a string do url num estado novo. */
ESTADO str2estado(char* str){
  ESTADO e;
  sscanf(str, FORMATO, &e.mao[0], &e.mao[1], &e.mao[2], &e.mao[3], &e.highlight, &e.cartas[0], &e.cartas[1], &e.cartas[2], &e.cartas[3], &e.play, &e.pass, &e.card,&e.ultima_jogada_valida, &e.ultima_jogada, &e.ultimo_jogador, &e.cartas_bots[0], &e.cartas_bots[1], &e.cartas_bots[2], &e.cartas_bots[3]);  

  return e;
}

int carta_existe(long long int ESTADO, int naipe, int valor) ;


/* Conforme as regras do jogo, a primeiro jogador a jogar é aquele que tem o 3 de ouros na sua mão.
Esta função procura nas mãos de cada jogador o valor e o naipe correspondentes ao 3 de ouros. O jogador que
tiver essa carta, passará a ser o ultimo_jogador, dando então prosseguimento. */

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

/* Função que distribui as cartas por todas as mãos, de igual modo (13 para cada).
Através da função "rand", as cartas são distribuidas aleatóriamente. Aqui, são feitas outras tarefas:
O ultimo_jogador vai tomar o valor da função primeiro_jogador, previamente definida, que indica o jogador que começa o jogo,
da-mos a e.cartas_bots[e.ultimo_jogador] o valor 1, de maneira que se um bot começar o jogo, este vai apresentar o 3 de ouros no tabuleiro,
e a ultima_jogada_valida toma o valor do ultimo_jogador, guardando assim o ultimo jogador que jogou corretamente. */

ESTADO baralhar () {
	int a=0 , i=0 , j=0 , k=0 , l=0 , n=0 , v=0, jogador;

	long long int player1[13];
	long long int player2[13];
	long long int player3[13]; 
	long long int player4[13];
	
	ESTADO e = {{0},0,{0},0,0,0,0,-1,0,{0}};

	e.cartas[0] = 13;
	e.cartas[1] = 13;
	e.cartas[2] = 13;
	e.cartas[3] = 13;
    
    e.cartas_bots[0] =0;
    e.cartas_bots[1] =0;
    e.cartas_bots[2] =0;
    e.cartas_bots[3] =0;


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
	e.cartas_bots[e.ultimo_jogador] = 1;
    e.ultima_jogada_valida = e.ultimo_jogador;

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



/** \brief Imprime o estado
Esta função está a imprimir o estado em quatro colunas: uma para cada naipe
@param path	o URL correspondente à pasta que contém todas as cartas
@param ESTADO	O estado atual
*/

/* Esta função tem como objetivo imprimir as cartas no tabuleiro. 
Se a carta a apresentar se encontre na mao do jogador (mao tomar o valor de 0 e o ultimo_jogador no estado for igual a 0), 
e caso a carta seja selecionada e entao adicionada ao highlight , se ja se encontrar no highlight, entao é removida do highlight .
Caso contrario , se a carta encontra-se na mao de um bot logo e imprimido o verso de uma carta caso contrario a carta 
ja foi jogada por um bot logo e mostrada a carta correspondente.
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
	/* if( carta_existe(e.mao[1],naipe,valor) || carta_existe(e.mao[2],naipe,valor) || carta_existe(e.mao[3],naipe,valor))
		printf("<image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/11C.png\" />\n", x, y, path); */ 
	/*else*/ printf("<image x = \"%d\" y = \"%d\" height = \"110\" width = \"80\" xlink:href = \"%s/%c%c.svg\" />\n", x, y, path, rank[valor], suit[naipe]);
	}
}



/*
Apresenta as cartas no tabuleiro nas respetivas coordenadas 
*/
void imprime (char *path, ESTADO e) {

	int n, v, m, bx1= 600 , by1 = 300 , bx2=340 , by2 = 150 , bx3= 100 , by3 = 300;
	int X[4] = {200, 700, 200, 10};
	int Y[4] = {550, 200, 10, 200};

	for(m = 0; m < 4; m++) { 

		int x = X[m], y = Y[m];

		for (v = 0; v < 13; v++) {
			for (n = 0; n < 4; n++){
				if(m == 1 && carta_existe(e.cartas_bots[1],n,v)){
                  imprime_carta(path, bx1, by1, e, m, n, v); 
                  by1+=20;
				}
				if(m == 2 && carta_existe(e.cartas_bots[2],n,v)){
				  imprime_carta(path, bx2, by2, e, m, n, v);
				  bx2+=20;
				}
				if(m == 3 && carta_existe(e.cartas_bots[3],n,v)){
				  imprime_carta(path,bx3, by3, e, m, n, v);
				  by3 += 20;
				} 
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
}


/*
Conta o número de cartas que se encontra numa mao numa dada altura
*/
int numero_de_cartas(MAO m) {

	int n, v, contaCartas=0;

	for (n = 0; n < 4; n++) {
			for (v = 0; v < 13; v++)
				if (carta_existe(m, n, v)) contaCartas++;
	}

	return contaCartas;
}

/* se a jogada for pa 5 :
	validar a tua mao
	validar a ultima jogada para saber se sao 5 car e se sim que tipo de 5 cartas
	validar as duas e ver se a nossa  tem o mesmo tipo e um valor maior ou se o tipo por si so e maior

	vai ter de ter uma compara para cada um dos tipos  
	*/

int combinacao_valida(MAO m) { 
	
	if ((numero_de_cartas (m)) > 3) {
	 	return 0;
	}

	else return 1;
}

/* Compara o tamanha entre duas mãos, ou seja, ve o tamanho da ultima jogada, e compara o tamanho com a jogada actual,
e vê se a combinação tem o mesmo tamanho */

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

/* Esta função obtém o maior naipe dentro de uma mão, de forma a ser usado para avaliar a maior jogada. */

int da_maior_naipe (MAO m){
 	int n, v, maior=0;

	for (n = 0; n < 4; n++) {

    for (v = 0; v < 13; v++)

      if (carta_existe(m, n, v)) { if (n > maior) maior =n;}
	}

	return maior;
}


/* Aqui, é verificado se a jogada actual é maior que a jogada anterior. Conforme o retorno da função dá valor, a jogada
actual é possível ser realizada ou não. Ao comparar, de os retornos das duas funções forem iguais, ou seja, se os maiores 
valores de cada mão forem iguais, comparamos o naipe, assim identificando qual a maior jogada */

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

int valida_fullhouse (MAO m) {

	int v,i,n,j;

	int contaValores[14];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

	for (i = 0; i < 14; i++) {
		if (contaValores[i] == 3) {
			for (j = 0; j < 14; j++) {
				if ((contaValores[j] == 2) && (contaValores[j] != contaValores[i])) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int maior_carta_trio_fullhouse (MAO m) {

	int v,i,n,j,var;

	int contaValores[14];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

	for (j = 0; j < 14; j++) {
		if (contaValores[j] == 3) {
			var = contaValores[j];
		}
	}

	switch (var) {
		case 0: { var = 11; } break;
		case 1: { var = 12; } break;
		default: { var -= 2; } break;
	}
	
	return var;
}

int valida_fourkind (MAO m) {
	
	int v,i,n,j;

	int contaValores[14];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

	for (j = 0; j < 14; j++) {
		if (contaValores[j] == 4) {
			return 1;
		}
	}

	return 0;
}

int maior_carta_fourkind (MAO m) {

	int v,i,n,j,var;

	int contaValores[14];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

	for (j = 0; j < 14; j++) {
		if (contaValores[j] == 4) {
			var = contaValores[j];
		}
	}

	switch (var) {
		case 0: { var = 11; } break;
		case 1: { var = 12; } break;
		default: { var -= 2; } break;
	}
	
	return var;
}

int valida_straightflush (MAO m) {

	int v,i,n,j,var,flag;

	int contaValores[14];
	int contaNaipes[4];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

int maior_carta_straightflush (MAO m) {

	int v,i,n,j,var;

	int contaValores[14];

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
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

	for (j = 0; j < 14; j++) {
		if (contaValores[j] == 5) {
			var = contaValores[j];
		}
	}

	switch (var) {
		case 0: { var = 11; } break;
		case 1: { var = 12; } break;
		default: { var -= 2; } break;
	}
	
	return var;
}

int validacao_5cartas (MAO m) {

	if ((valida_straightflush(m)) == 1) {
		return 5;
	}
	else {

		if ((valida_straight(m)) == 1) {
			return 1;
		}

		else {
			if ((valida_flush(m)) != -1) {
				return 2;
			}

			else {
				if ((valida_fullhouse(m)) == 1) {
					return 3;
				}

				else {
					if ((valida_fourkind(m)) == 1) {
						return 4;
					}					
				}
			}
		}
	}

	return -1;
}

/* É nesta função que a jogada do utilizador é verificada. Se esta for possível, é permitido ao utilizador colocar as cartas
no meio do tabuleiro, registando assim a sua jogada. Caso contrário, ou o utilizador passa, ou tenta arranjar outro tipo de combinação. */

int posso_jogar (ESTADO e) {
	
	if ((numero_de_cartas(e.highlight)) == 5) {
 		if (e.ultima_jogada == -1) {
			if (((validacao_5cartas(e.highlight)) != -1) && (carta_existe(e.highlight, 0, 0)) && (e.ultimo_jogador == 0)) {
				return 1;
			}
			else {
				return 0;
			} 		
 		}

 		else {
 			if (e.ultima_jogada_valida == 0) {
 				if (((validacao_5cartas(e.highlight)) != -1) && (e.ultimo_jogador == 0)) {
					return 1;
				}
				else {
					return 0;
				} 
 			}
 			else {
 				
 				if ((validacao_5cartas(e.highlight)) > (validacao_5cartas(e.ultima_jogada))) {
 					return 1;
 				}

 				else {
 					if ((validacao_5cartas(e.highlight)) < (validacao_5cartas(e.ultima_jogada))) {
 						return 0;
 					}
 						
 					else {
 						if ((validacao_5cartas(e.highlight)) == 1) {
 							/*VAI BUSCAR A MAIOR CARTA DAS DUAS*/
 							if ((maior_carta_straight(e.highlight)) > (maior_carta_straight(e.ultima_jogada))) {
 								return 1;
 							}
 							else {
 								if ((maior_carta_straight(e.highlight)) == (maior_carta_straight(e.ultima_jogada))) {
 									if ((maior_naipe_straight(e.highlight, (maior_carta_straight(e.highlight)))) > (maior_naipe_straight(e.ultima_jogada, (maior_carta_straight(e.ultima_jogada))))) {
 										return 1;
 									}
 									else {
 										return 0;
 									}
 								}
 							}
 						}
 						
 						else {
 							if ((validacao_5cartas(e.highlight)) == 2) {
 								/*VAI BUSCAR O NAIPE DAS DUAS, E VE SE O DE O HIGHLIGHT É MAIOR, E SE O NAIPE FOR IGUAL, VAI BUSCAR A MAIOR CARTA*/
 								if ((valida_flush(e.highlight)) < (valida_flush(e.ultima_jogada))) {
 									return 0;
 								}
 								else {
 									if ((valida_flush(e.highlight)) > (valida_flush(e.ultima_jogada))) {
 										return 1;
 									}
 									else { /*e.highlight == e.ultima_jogada*/
 										if ((maior_carta_flush(e.highlight)) < (maior_carta_flush(e.ultima_jogada))) {
 											return 0;
 										}
 										else {
 											return 1;
 										}
 									}
 								}
 							}
 							if ((validacao_5cartas(e.highlight)) == 3) {
 								if ((valida_fullhouse(e.highlight)) < (valida_fullhouse(e.ultima_jogada))) {
 									return 0;
 								}
 								else {
 									if ((valida_fullhouse(e.highlight)) > (valida_fullhouse(e.ultima_jogada))) {
 										return 1;
 									}
 									else {
 										if ((maior_carta_trio_fullhouse(e.highlight)) < (maior_carta_trio_fullhouse(e.ultima_jogada))) {
 											return 0;
 										}
 										else {
 											return 1;
 										}
 									}
 								}
 							}
 							if ((valida_fourkind(e.highlight)) == 4) {
 								if ((valida_fourkind(e.highlight)) < (valida_fourkind(e.ultima_jogada))) {
 									return 0;
 								}
 								else {
 									if ((valida_fourkind(e.highlight)) > (valida_fourkind(e.ultima_jogada))) {
 										return 1;
 									}
 									else {
 										if ((maior_carta_fourkind(e.highlight)) < (maior_carta_fourkind(e.ultima_jogada))) {
 											return 0;
 										}
 										else {
 											return 1;
 										}
 									}
 								}
 							}
 							if ((valida_straightflush(e.highlight)) == 5) {
 								if ((valida_straightflush(e.highlight)) < (valida_straightflush(e.ultima_jogada))) {
 									return 0;
 								}
 								else {
 									if ((valida_straightflush(e.highlight)) > (valida_straightflush(e.ultima_jogada))) {
 										return 1;
 									}
 									else {
 										if ((maior_carta_straightflush(e.highlight)) < (maior_carta_straightflush(e.ultima_jogada))) {
 											return 0;
 										}
 										else {
 											return 1;
 										}
 									}
 								}
 							}
 						}
 					}
 				}
 				return 0;
 			}
 		}
	}

	else {
		if (e.ultima_jogada == -1) {
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
  
  		if (e.ultima_jogada_valida == 0) {
			if (!combinacao_valida (e.highlight) ) { 
				return 0;
			}
			else {
	 			if (e.ultimo_jogador != 0) {
	 				return 0; 
	 			}
				else {
	 				if ((da_valor (e.highlight) != -1) ) {
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
}

/* Em cada jogada, o jogador é incrementado, tomando assim o controlo do jogador que está em jogo. 
Como estes variam entre 0 e 3 (4 jogadores), enquanto ele for diferente de 3, vai incrementar para um próximo jogador, e uma próxima jogada. */
	
int incrementa_jogador (ESTADO e){
  if (e.ultimo_jogador != 3) return (e.ultimo_jogador += 1);
  else return 0;
}

ESTADO bots2(ESTADO e);

/* Esta função trata de imprimir o botão "SUBMIT" na página HTML. Aqui, usamos a função posso_jogar.
Se for possível jogar, o botão é clicável, sendo primitida a jogada. Caso contrário, o botão fica mais escuro, não sendo clicável. */

void imprime_botao_jogar(ESTADO e) {

	char script[10240];
	ESTADO novo = e;

	if (posso_jogar(e)) {
	    novo.ultima_jogada = e.highlight;
        novo.cartas[0] = e.cartas[0] - (numero_de_cartas(novo.ultima_jogada));
      	novo.ultimo_jogador = incrementa_jogador(e);
		novo.play = 1;
    	novo.ultima_jogada_valida = 0;	
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"280\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/SubmitLI2.png\" /></a>\n", script); 
	}

	else {
		printf("<image x = \"280\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/SubmitLI2out.png\" />\n"); 
	}
}

/* Esta função trata de imprimir o botão "PASS" na página HTML. Quando o utilizador não tem nenhuma combinação válida possível
em relação a última jogada, é possível usar o botão "PASS". O utilizador pode usar sempre o botão "PASS", 
excepto quando é o primeiro a jogar (3 de ouros) ou quando todos passam a jogada e este foi o ultimo a jogar uma carta/combinaçao  */

void imprime_botao_passar(ESTADO e) {

	char script[10240];
	ESTADO novo = e;

	if(e.ultimo_jogador == 0 && e.ultima_jogada != -1 && e.ultima_jogada_valida != 0){
		novo.ultima_jogada = e.ultima_jogada;
   		novo.highlight = 0;
    	novo.ultimo_jogador = incrementa_jogador(e);
    	novo.pass = 1;
		sprintf(script, "%s?%s", SCRIPT, estado2str(novo));
		printf("<a xlink:href = \"%s\"><image x = \"380\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/PassLI2.png\" /></a>\n", script); 
}

	else {
		printf("<image x = \"380\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/PassLI2out.png\" />\n"); 
	}
}


/*
a funçao jogar vai ser invocada pela funçao parse , 
e vai retirar as cartas da mao do jogador caso esta exista no highlight , 
colocando a na posiçao do tabuleiro correspondete a jogada do utilizador
ou seja, vai ser a funçao executada quando carregamos no botao jogar para um dado highlight .
Esta funçao tambem convoca as funçoes dos bots que executam as suas jogadas enquanto nao for a vez do utilizador jogar
*/

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
    
    e = bots2(e);
    
    while(e.ultimo_jogador != 0){
    	e = bots2(e);
    }
	
	e.highlight = 0; 


	return e;
}

/*
funçao invocada na parse , que vai ser executada quando carregamos no botao passar, e que so incrementa o jogador e mantem o resto do estado.
Esta funçao tambem convoca as funçoes dos bots que executam as suas jogadas enquanto nao for a vez do utilizador jogar. 
*/

ESTADO passar (ESTADO e) {
	
	e.pass = 0;
  	e = bots2(e);
  	
  	while(e.ultimo_jogador != 0){
    	e = bots2(e);
  	}
	

	e.highlight = 0; 
	return e;
}

/* A valida_bots_jogadas_normais e validacao_2maos_bots sao as funçoes que vao validar as jogadas dos bots */

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

int validacao_2maos_bots (ESTADO e, MAO p) {

	if (!combinacao_valida(p)) {
		return 0;
	}

	else {

		if(!compara_tamanho(e.ultima_jogada, p)) {
			return 0;
		}

		else {
			if(!combinacao_maior (e.ultima_jogada, p)) {
				return 0;
			}
		}
	}

	return 1;
}


/*
a bots1 vai ser executa para quando um bot começa a jogar(tem o 3 de ouros na sua mao) 
E executada na modificaçao do baralhar na parse 
*/
ESTADO bots1(ESTADO e){
if (e.ultima_jogada == -1 && e.ultimo_jogador != 0 ){
 	e.cartas[e.ultimo_jogador] =( e.cartas[(e.ultimo_jogador)]) - 1;
 	e.mao[e.ultimo_jogador] = rem_carta(e.mao[(e.ultimo_jogador)],0,0);
 	e.ultima_jogada = 1;
 	e.ultimo_jogador = incrementa_jogador(e);
 	e.card = 0;
 	e.cartas_bots[e.ultimo_jogador] = 2;
 	
 	return e;
}

	return e;
}


int maior_carta_straight_bots(MAO m){
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
				return j;
			}
			j--;
		}
	}
	else {
		j = 13;
		while ((j-4) >= 1) {
			if ((contaValores[j] != 0) && (contaValores[j-1] != 0) && (contaValores[j-3] != 0) && (contaValores[j-4] != 0)) {
				return j;
			}
		}
		j--;
	}
	return -1;
}

int descodifica_straight (int maiorCarta) {
	int v;
	v = maiorCarta;
	switch (v) {
		case 0: { v = 11; } break;
		case 1: { v = 12; } break;
		default: { v -= 2; } break;
	}
	return v;
}

int maior_naipe_straight_bots (MAO m, int maiorCarta) {
	int i,n;
	i = 0;
		for (n = 3; n >= 0; --n) {
			if (carta_existe(m,n,maiorCarta)) i = n;
		}
	return i;
}


ESTADO joga_straight(ESTADO e) {

	long long int m = 0;

	int v1,v2,v3,v4,v5,n1,n2,n3,n4,n5;

	v1 = descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]));
	v2 = descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]) - 1);
	v3 = descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]) - 2);
	v4 = descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]) - 3);
	v5 = descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]) - 4);
	n1 = (maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]))))); 
	n2 = (maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador])))) - 1);
	n3 = (maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador])))) - 2);
	n4 = (maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador])))) - 3);
	n5 = (maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador])))) - 4);
	
	m = add_carta((add_carta((add_carta((add_carta((add_carta(0,n1,v1)),n2,v2)),n3,v3)),n4,v4)),n5,v5);
	e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = rem_carta((rem_carta((rem_carta((rem_carta((rem_carta(e.mao[e.ultimo_jogador],n1,v1)),n2,v2)),n3,v3)),n4,v4)),n5,v5);
	e.ultima_jogada_valida = e.ultimo_jogador;
	e.ultimo_jogador = incrementa_jogador(e);
	e.card = 0;
	return e;
}


ESTADO passabot(ESTADO e) {
	e.cartas_bots[e.ultimo_jogador] = 0;
	e.ultimo_jogador = incrementa_jogador(e);
	return e;
}

ESTADO fazjogada (ESTADO e, int v){
  switch(v){
  	case 1: if ((maior_carta_straight_bots(e.mao[e.ultimo_jogador])) > (maior_carta_straight_bots(e.ultima_jogada))) {
  				return (joga_straight(e));
  			} 
			else {
				if ((maior_carta_straight_bots(e.mao[e.ultimo_jogador])) == (maior_carta_straight_bots(e.ultima_jogada))) {
					if ((maior_naipe_straight_bots(e.mao[e.ultimo_jogador],(descodifica_straight(maior_carta_straight_bots(e.mao[e.ultimo_jogador]))))) > (maior_naipe_straight_bots(e.ultima_jogada,(descodifica_straight(maior_carta_straight_bots(e.ultima_jogada)))))) {
						e = joga_straight(e);
						return e;
					}
			 		else {
			 			e = passabot(e);
			 			return e;
			 		}
				}
			}
			break;
  }
  return e; /* PARA RESOLVER PROBLEMA DE COMPILAÇÃO */
}

ESTADO pbot(ESTADO e){
  	int v;
  	v = 0;
  	v = validacao_5cartas(e.ultima_jogada);
  	e = (fazjogada (e, v));
	return e;
}

/*
a bots2 vai ser executada para quando um bot executar uma joga que nao seja jogar 3 de ouros, isto inclui jogadas de 1, 2, 3 cartas e tambem passagens pelos mesmos.
*/
ESTADO bots2(ESTADO e){
	long long int m=0;
	long long int z=0;
	long long int p=0;
	long long int g=0; 
	int n,v,k,l,ncartas;

ncartas = numero_de_cartas(e.ultima_jogada);

if (ncartas == 1) {
	if (e.ultima_jogada_valida == e.ultimo_jogador ){
		for (v = 0; v <= 12; v++){
      		for (n = 0; n <= 3; n++){
        		m = add_carta(0,n,v);
        		if (carta_existe(e.mao[e.ultimo_jogador],n,v)){
          			m = add_carta(0,n,v);
          			e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
	          		e.ultima_jogada = m;
	          		e.cartas_bots[e.ultimo_jogador] = m;
	          		e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
	          		e.ultima_jogada_valida = e.ultimo_jogador;
	          		e.ultimo_jogador = incrementa_jogador(e);
	          		e.card = 0;
          			return e;
        		}	
      		}	
		}
	}

	else { 
		for (v = 0; v <= 12; v++){
    		for (n = 0; n <= 3; n++){
				m = add_carta(0,n,v);
				if (carta_existe(e.mao[e.ultimo_jogador],n,v) && valida_bots_jogadas_normais(e,m)){
					m = add_carta(0,n,v);
					e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
					e.ultima_jogada = m;
					e.cartas_bots[e.ultimo_jogador] = m;
					e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
					e.ultima_jogada_valida = e.ultimo_jogador;
					e.ultimo_jogador = incrementa_jogador(e);
					e.card = 0;
        			return e;
      			}
      		}
 		}
	}
}




if (ncartas == 2) {

	if (e.ultima_jogada_valida == e.ultimo_jogador ){
		for (v = 0; v <= 12; v++){
      		for (n = 0; n <= 3; n++){
        		m = add_carta(0,n,v);
        		if (carta_existe(e.mao[e.ultimo_jogador],n,v)){
          			m = add_carta(0,n,v);
          			e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
	          		e.ultima_jogada = m;
	          		e.cartas_bots[e.ultimo_jogador] = m;
	          		e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
	          		e.ultima_jogada_valida = e.ultimo_jogador;
	          		e.ultimo_jogador = incrementa_jogador(e);
	          		e.card = 0;
          			return e;
        		}	
      		}	
		}
	}

else {
	for(v = 0; v <= 12; v++) {
			for(n = 0; n <= 3; n++) {
				if (carta_existe(e.mao[e.ultimo_jogador], n, v)) {
        			m = add_carta(0,n,v);			
					for(k = 0; k <= 3; k++) {
      					z = add_carta(0, k, v);
      				    m = add_carta(0,n,v);
      					p = add_carta(m,k,v);
      					if (carta_existe(e.mao[e.ultimo_jogador],k,v) && z != m && validacao_2maos_bots(e,p) ) {
      						m = add_carta(0,n,v);
      						p = add_carta(m, k, v);
      						e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 2;
      						e.ultima_jogada = p;
      						e.cartas_bots[e.ultimo_jogador] = p;
      						e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador], n, v);
      						e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador], k, v);
      						e.ultima_jogada_valida = e.ultimo_jogador;
      						e.ultimo_jogador = incrementa_jogador(e);
      						e.card = 0;
      						return e;
      					}
      				}
			    }
    	    }
  	}
}
}
 
if (ncartas == 3) {

	if (e.ultima_jogada_valida == e.ultimo_jogador ){
		for (v = 0; v <= 12; v++){
      		for (n = 0; n <= 3; n++){
        		m = add_carta(0,n,v);
        		if (carta_existe(e.mao[e.ultimo_jogador],n,v)){
          			m = add_carta(0,n,v);
          			e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
	          		e.ultima_jogada = m;
	          		e.cartas_bots[e.ultimo_jogador] = m;
	          		e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
	          		e.ultima_jogada_valida = e.ultimo_jogador;
	          		e.ultimo_jogador = incrementa_jogador(e);
	          		e.card = 0;
          			return e;
        		}	
      		}	
		}
	}
}
else{
	for(v = 0; v <= 12; v++) {
		
		for(n = 0; n <= 3; n++) {

			if (carta_existe(e.mao[e.ultimo_jogador], n, v)) {
        		
        		m = add_carta(0,n,v);			

				for(l = 0; l <= 3; l++) {
                	if (carta_existe(e.mao[e.ultimo_jogador], l, v)) { 
						g = add_carta(0,l,v);

					for(k = 0; k <= 3; k++) {
                        g = add_carta(0,l,v);
      					z = add_carta(0, k, v);
      				    m = add_carta(0,n,v);
      					p = add_carta(m,k,v);
      					p = add_carta(p,l,v);
      				
      					if (carta_existe(e.mao[e.ultimo_jogador],k,v) && z != m && g != m && g != z && validacao_2maos_bots(e,p) ) {
      						m = add_carta(0,n,v);
      						p = add_carta(m, k, v);
      						p = add_carta(p,l,v);
      						e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 3;
      						e.ultima_jogada = p;
      						e.cartas_bots[e.ultimo_jogador] = p;
      						e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador], n, v);
      						e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador], k, v);
      						e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador], l, v);
      						e.ultima_jogada_valida = e.ultimo_jogador;
      						e.ultimo_jogador = incrementa_jogador(e);
      						e.card = 0;
      						return e;
      					}
      				}
				}
				}
			}
    	}
  	}
  }

  if (ncartas == 5) {
  	if (e.ultima_jogada_valida == e.ultimo_jogador){
		for (v = 0; v <= 12; v++){
      		for (n = 0; n <= 3; n++){
        		m = add_carta(0,n,v);
        		if (carta_existe(e.mao[e.ultimo_jogador],n,v)){
          			m = add_carta(0,n,v);
          			e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) -1 ;
	          		e.ultima_jogada = m;
	          		e.cartas_bots[e.ultimo_jogador] = m;
	          		e.mao[e.ultimo_jogador] = rem_carta(e.mao[e.ultimo_jogador],n,v) ;
	          		e.ultima_jogada_valida = e.ultimo_jogador;
	          		e.ultimo_jogador = incrementa_jogador(e);
	          		e.card = 0;
          			return e;
        		}	
      		}	
		}
	}
	else {
		
		e = pbot(e);
		return e;
	}
  }


	e.cartas_bots[e.ultimo_jogador] = 0;
	e.ultimo_jogador = incrementa_jogador(e);
	return e;
}

/*
Imprime botao resete  vai imprimir um botao quando algum dos jogadores ganha a ronda ou seja acaba as cartas da sua mae 
*/
void imprime_botao_reset(ESTADO e) {

	char script[10240];
	
	if (e.cartas[0] != 0 && e.cartas[1] != 0 && e.cartas[2] != 0 && e.cartas[3] != 0 ){

}
else {	
    e = bots1(baralhar());
   
   while(e.ultimo_jogador != 0){
     	e = bots2(e);
   }
		sprintf(script, "%s?%s", SCRIPT, estado2str(e));
		printf("<a xlink:href = \"%s\"><image x = \"480\" y = \"700\" height = \"80\" width = \"80\" xlink:href = \"http://localhost/cards/Reset.png\" /></a>\n", script);
}
}





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
		if (e.play) e = jogar(e);
        if (e.pass) e = passar(e);
    
    	a=e.mao[0];
    	printf("%d\n", a);
	}


	else {
		
   		e = bots1(baralhar());
   	
   		while(e.ultimo_jogador != 0){
     		e = bots2(e);
   		}

 		a=e.mao[0];
		printf("%d\n", a);
	}
	
	imprime(BARALHO, e);
    imprime_botao_jogar(e);
  	imprime_botao_passar(e);
  	imprime_botao_reset(e);
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
/*	printf("<rect x = \"0\" y = \"0\" height = \"800\" width = \"800\" style = \"fill:#007700\"/>\n");*/
printf("<image x = \"0\" y = \"0\" height = \"800\" width = \"800\" xlink:href = \"http://localhost/cards/tab.svg\" /></a>\n");


/*
 * Ler os valores passados à cgi que estão na variável ambiente e passá-los ao programa
 */

	parse(getenv("QUERY_STRING"));
	printf("</svg>\n");
	printf("</body>\n");
	return 0;
}

