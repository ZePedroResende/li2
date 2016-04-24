
/* TROCAR OS CICLOS WHILE NO JOGAR, MUDAR NA PARSE O BOT, E MUDAR NO PASSAR */
ESTADO jogar5cartas_bot_inteligente (ESTADO e) {

	long long int m = 0;
	int n,v;
	n = 0;
	v = 0;

	
	if (maior_carta_straight_bots(e.mao[e.ultimo_jogador]) != -1) {
			e = joga_straight(e);
			e.ultimo_jogador = incrementa_jogador(e);
			return e;
		}
	else {
		if (valida_flush(e.mao[e.ultimo_jogador]) != -1) {
			e = joga_flush(e);
			e.ultimo_jogador = incrementa_jogador(e);
			return e;
		}	
		else {
			if (valida_fullhouse(e.mao[e.ultimo_jogador]) != -1) {
				e = joga_fullhouse(e);
				e.ultimo_jogador = incrementa_jogador(e);
				return e;
			}		
			else {
				if (maior_carta_fourkind(e.mao[e.ultimo_jogador]) != -1) {
					e = joga_fourkind(e);
					e.ultimo_jogador = incrementa_jogador(e);
					return e;
				}
				else {
					if (maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) != -1) {
						e = joga_straightflush(e);
						e.ultimo_jogador = incrementa_jogador(e);
						return e;
					}
					else {
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
			}
		}
	}

	return e;
}


ESTADO bot_inteligente(ESTADO e) {
	long long int m=0;
	long long int z=0;
	long long int p=0;
	long long int g=0; 
	int n,v,k,l,ncartas;
printf("!!!1!!\n");
ncartas = numero_de_cartas(e.ultima_jogada);

if (ncartas == 1) {
	if (e.ultima_jogada_valida == e.ultimo_jogador ){
		e = jogar5cartas_bot_inteligente(e);
		return e;
	printf("####2#####\n");
	}

	else { 
			printf("$$$$$4$$$$$\n");
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
		e = jogar5cartas_bot_inteligente(e);
		return e;
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
		e = jogar5cartas_bot_inteligente(e);
		return e;
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
}
  if (ncartas == 5) {
  	if (e.ultima_jogada_valida == e.ultimo_jogador){
		e = jogar5cartas_bot_inteligente(e);
		return e;
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