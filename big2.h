#define SCRIPT		"http://127.0.0.1/cgi-bin/cartas"
#define BARALHO		"http://127.0.0.1/cards"
#define NAIPES		"DCHS"
#define VALORES		"3456789TJQKA2"
#define FORMATO 
typedef long long int MAO;

struct estado {
	MAO mao[4];
	MAO highlight;
	int cartas[4];
	int play, pass, card, ultima_jogada_valida;
	MAO ultima_jogada;
	int ultimo_jogador;
	MAO cartas_bots[4];
  int layout;
};


typedef struct estado ESTADO;




char* estado2str(ESTADO e);
ESTADO str2estado(char* str);
int carta_existe(long long int ESTADO, int naipe, int valor) ;
int primeiro_jogar(ESTADO e);
long long int add_carta(long long int ESTADO, int naipe, int valor);
ESTADO baralhar ();
int indice(int naipe, int valor); 
long long int rem_carta(long long int ESTADO, int naipe, int valor);
int carta_existe(long long int ESTADO, int naipe, int valor) ;
void imprime_carta(char *path, int x, int y, ESTADO e, int mao, int naipe, int valor) ;
void imprime (char *path, ESTADO e) 
int numero_de_cartas(MAO m) ;
int combinacao_valida(MAO m) ; 
int compara_tamanho(MAO m1, MAO m2);
int da_valor (MAO m);
int da_maior_naipe (MAO m);
int combinacao_maior (MAO m1, MAO m2) ;
int valida_straight (MAO m) ;
int maior_carta_straight (MAO m) ;
int maior_naipe_straight (MAO m, int maiorCarta) ;
int valida_flush (MAO m) ;
int maior_carta_flush (MAO m) ;
int valida_fullhouse (MAO m) ;
int maior_carta_trio_fullhouse (MAO m) ;
int valida_fourkind (MAO m) ;
int maior_carta_fourkind (MAO m) ;
int valida_straightflush (MAO m) ;
int maior_carta_straight_bots(MAO m);
int descodifica_straight (int maiorCarta) ;
int maior_carta_straightflush_bots (MAO m) ;
int validacao_5cartas (MAO m) ;
int posso_jogar (ESTADO e) ;
int incrementa_jogador (ESTADO e);
ESTADO bots2(ESTADO e);
void imprime_botao_jogar(ESTADO e) ;
void imprime_botao_passar(ESTADO e) ;
ESTADO jogar (ESTADO e) ;
ESTADO passar (ESTADO e) ;
int valida_bots_jogadas_normais (ESTADO e, MAO m) ;
int validacao_2maos_bots (ESTADO e, MAO p) ;
ESTADO bots1(ESTADO e)
int maior_naipe_straight_bots (MAO m, int maiorCarta) ;
ESTADO joga_straight(ESTADO e) ;
ESTADO passabot(ESTADO e) ;
int maior_carta_flush_bots (MAO m, int n1) ;
ESTADO joga_flush(ESTADO e) ;
int maior_naipeCarta_straightflush_bots (MAO m) ;
int codifica(int v);
int da_carta_fourkind (MAO m) ;
int maior_carta_par_fullhouse (MAO m) ;
ESTADO joga_fullhouse(ESTADO e) ;
ESTADO joga_fourkind(ESTADO e) ;
ESTADO joga_straightflush(ESTADO e) ;
ESTADO fazjogada (ESTADO e, int v) ;
ESTADO pbot(ESTADO e);
void imprime_botao_reset(ESTADO e) ;
void imprime_botao_layout(ESTADO e) ;
void imprime_botao_trofeu(ESTADO e) ;
ESTADO sugestao_straightflush(ESTADO e) ;
ESTADO sugestao_fourkind(ESTADO e) ;
ESTADO sugestao_fullhouse(ESTADO e) ;
ESTADO sugestao_flush(ESTADO e) ;
ESTADO sugestao_straight(ESTADO e) ;
ESTADO fazsugestao (ESTADO e, int v) ;
ESTADO cartas5sugestao (ESTADO e);
ESTADO sugestao1(ESTADO e);
ESTADO sugestao2(ESTADO e);
ESTADO clear(ESTADO e);
void imprime_botao_clear(ESTADO e) ;
void imprime_botao_sugestao(ESTADO e) ;
void parse (char *query) ;


