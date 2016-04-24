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

int compara_tamanho(MAO m1, MAO m2){
	if (numero_de_cartas(m1) == numero_de_cartas(m2)) {
		return 1;
	} 

	return 0;
}

int combinacao_valida(MAO m) { 
	
	if ((numero_de_cartas (m)) > 3) {
	 	return 0;
	}

	else return 1;
}


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


int maior_naipe_straight_bots (MAO m, int maiorCarta) {
	int i,n;
	i = 0;
		for (n = 3; n >= 0; --n) {
			if (carta_existe(m,n,maiorCarta)) i = n;
		}
	return i;
}


ESTADO joga_straight(ESTADO e) {

 	long long int m=0, n=0;

	int v1,v2,v3,v4,v5,n1,n2,n3,n4,n5,p1,p2,p3,p4,p5;

  p1 = maior_carta_straight_bots (e.mao[e.ultimo_jogador]);
  p2 = (maior_carta_straight_bots(e.mao[e.ultimo_jogador]))-1;
  p3 = (maior_carta_straight_bots(e.mao[e.ultimo_jogador]))-2;
  p4 = (maior_carta_straight_bots(e.mao[e.ultimo_jogador]))-3;
  p5 = (maior_carta_straight_bots(e.mao[e.ultimo_jogador]))-4;

	v1 = descodifica_straight(p1);
	v2 = descodifica_straight(p2);
	v3 = descodifica_straight(p3);
	v4 = descodifica_straight(p4);
	v5 = descodifica_straight(p5);

  n1 = maior_naipe_straight_bots((e.mao[e.ultimo_jogador]),v1);
  n2 = maior_naipe_straight_bots((e.mao[e.ultimo_jogador]),v2);
	n3 = maior_naipe_straight_bots((e.mao[e.ultimo_jogador]),v3);
	n4 = maior_naipe_straight_bots((e.mao[e.ultimo_jogador]),v4);
	n5 = maior_naipe_straight_bots((e.mao[e.ultimo_jogador]),v5);
	
	m = add_carta(0,n1,v1);
  m = add_carta(m,n2,v2);
  m = add_carta(m,n3,v3);
  m = add_carta(m,n4,v4);
  m = add_carta(m,n5,v5);

  n = rem_carta((e.mao[e.ultimo_jogador]),n1,v1);
  n = rem_carta(n,n2,v2);
  n = rem_carta(n,n3,v3);
  n = rem_carta(n,n4,v4);
  n = rem_carta(n,n5,v5);

  e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = n;
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

int maior_carta_flush_bots (MAO m, int n1) {
	int i,v,flag;
	i = 0;
	flag = 0;
	for (v = 12; (v >= 0) && (flag != 1); --v) {
		if (carta_existe(m,n1,v)) {
			flag = 1;
			i = v;
		}	
	}
	return i;
}

ESTADO joga_flush(ESTADO e) {

	long long int m=0, n=0;

	int flag1,flag2,flag3,flag4,v1,v2,v3,v4,v5,p1=0,p2=0,p3=0,p4=0,p5=0,n1;
	
	n1 = valida_flush(e.mao[e.ultimo_jogador]); 
 	v1 = maior_carta_flush_bots(e.mao[e.ultimo_jogador], n1);
	
	flag1 = 0;
	p1 = v1;
	for(v2 = (v1 - 1); v2 >= 0 && flag1 != 1; --v2) {
		if (carta_existe(e.mao[e.ultimo_jogador],n1,v2)) {
			p2 = v2;
			flag1 = 1;
		} 
	}
	
	flag2 = 0;
	for (v3 = v2; v3 >= 0 && flag2 != 1; --v3) {
		if (carta_existe(e.mao[e.ultimo_jogador],n1,v3)) {
			p3 = v3;
			flag2 = 1;
		}
	}

	flag3 = 0;
	for (v4 = v3; v4 >= 0 && flag3 != 1; --v4) {
		if (carta_existe(e.mao[e.ultimo_jogador],n1,v4)) {
			p4 = v4;
			flag3 = 1;
		}
	}
	
	flag4 = 0;
	for (v5 = v4; v5 >= 0 && flag4 != 1; --v5) {
		if (carta_existe(e.mao[e.ultimo_jogador],n1,v5)) {
			p5 = v5;
			flag4 = 1;
		}
	}
	
  	m = add_carta(0,n1,p1);
  	m = add_carta(m,n1,p2);
  	m = add_carta(m,n1,p3);
  	m = add_carta(m,n1,p4);
  	m = add_carta(m,n1,p5);

  	n = rem_carta((e.mao[e.ultimo_jogador]),n1,p1);
  	n = rem_carta(n,n1,p2);
  	n = rem_carta(n,n1,p3);
  	n = rem_carta(n,n1,p4);
  	n = rem_carta(n,n1,p5);

    e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = n;
	e.ultima_jogada_valida = e.ultimo_jogador;
	e.ultimo_jogador = incrementa_jogador(e);
	e.card = 0;
	return e;
}



int maior_naipeCarta_straightflush_bots (MAO m) {

	int v,i,n,j,x,p0,p1,p2,p3,p4;
	int contaValores[14];
	int contaNaipes[4];
	int maioresCartasStraightsPossiveis[8];

	x = p0 = p1 = p2 = p3 = p4 = 0;

	for (i = 0; i < 14; i++) {
		contaValores[i] = 0;
	}

	for (i = 0; i < 4; i++) {
		contaNaipes[i] = 0;
	}

	for (i = 0; i < 4; i++) {
		maioresCartasStraightsPossiveis[i] = -1;
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

	for (i = 13, j = 0; (i - 4) >= 0; --i) {
		if ((contaValores[i] != 0) && (contaValores[i-1] != 0) && (contaValores[i-2] != 0) && (contaValores[i-3] != 0) && (contaValores[i-4] != 0)) {
			maioresCartasStraightsPossiveis[j] = i;
			j++;
		}
	}

	for (i = 0; i < 8; i++) {
		if (maioresCartasStraightsPossiveis[i] != -1) {
       	 	x = maioresCartasStraightsPossiveis[i];
       	 	p0 = descodifica_straight(x);  
			p1 = descodifica_straight(x-1);
        	p2 = descodifica_straight(x-2);
        	p3 = descodifica_straight(x-3);
       	 	p4 = descodifica_straight(x-4);
	
			for (n = 3; n >= 0; --n) {
				if ((carta_existe(m,n,p0)) && (carta_existe(m,n,p1)) && (carta_existe(m,n,p2)) && (carta_existe(m,n,p3)) && (carta_existe(m,n,p4))) {
					return n;
				}
			}
		}		
	}
	return -1; 
}

int codifica(int v){
	switch (v) {
		case 11: return 13; break;
    	case 12: return 1; break;
		default:{v=v+2; return v;} break;
	}	
}

int da_carta_fourkind (MAO m) {

	int v,i,n,j,var=0,flag;
	int contaValores[13];

	for (i = 0; i < 13; i++) {
		contaValores[i] = 0;
	}

	i = 0;
	for (v = 0; v < 13; v++) {
		for(n = 0; n < 4; n++) {
			if ((carta_existe(m,n,v))) {
				contaValores[i]++;
			}	
    	}
    	i++;
	}

	flag = 0;
	for (j = 0; (j < 13) && (flag != 1); j++) {
		if (contaValores[j] == 1) {
			var = j;
			flag = 1;
		}
	}
	printf("%d\n",var );
	return var;
}

int maior_carta_par_fullhouse (MAO m) {

	int v,i,n,j,var,flag;

	int contaValores[13];

	for (i = 0; i < 13; i++) {
		contaValores[i] = 0;
	}

	i = 0;
	for (v = 0; v < 13; v++) {
		for(n = 0; n < 4; n++) {
			if (carta_existe(m,n,v)) {
				contaValores[i]++;
			}	
    	}
    	i++;
	}

	flag = 0;
	for (j = 0; (j < 14) && (flag != 1); j++) {
		if (contaValores[j] == 2) {
			var = j;
			flag = 1;
		}
	}

	return var;
}

ESTADO joga_fullhouse(ESTADO e) {

	long long int m=0, n=0;

	int v1=0,n3=0,n2=0,n1=0,p=0,p1=0,p2=0,p3=0,np1=0,np2=0,flag,flag1,flag2,flag3,flag4;

  	v1 = valida_fullhouse(e.mao[e.ultimo_jogador]);
  	
  	p = maior_carta_par_fullhouse(e.mao[e.ultimo_jogador]); /* valor do par */

  	flag = 0;
  	for (n = 3; n >= 0 && flag != 1; --n) {
  		if(carta_existe(e.mao[e.ultimo_jogador], n, v1)) {
  			n1 = n;
  			flag = 1;
  		}
  	}

  	flag1 = 0;
  	p1 = n1-1;
  	for (n = p1; n >= 0 && flag1 != 1; --n) {
  		if(carta_existe(e.mao[e.ultimo_jogador], n, v1)) {
  			n2 = n;
  			flag1 = 1;
  		}
  	}

  	flag2 = 0;
  	p2 = n2-1;
  	for (n = p2; n >= 0 && flag2 != 1; --n) {
  		if (carta_existe(e.mao[e.ultimo_jogador], n, v1)) {
  			n3 = n;
  			flag2 = 1;
  		}
  	}

  	flag3 = 0;
  	for (n = 3; n >= 0 && flag3 != 1; --n) {
  		if (carta_existe(e.mao[e.ultimo_jogador], n, p)) {
  			np1 = n;
  			flag3 = 1;
  		}
  	}
  	
  	flag4 = 0;
  	p3 = n;
  	for (n = p3; n >= 0 && flag4 != 1; --n) {
  		if (carta_existe(e.mao[e.ultimo_jogador], n, p)) {
  			np2 = n;
  			flag4 = 1;
  		}
  	}

	m = add_carta(0,n1,v1);
  	m = add_carta(m,n2,v1);
  	m = add_carta(m,n3,v1);
  	m = add_carta(m,np1,p);
  	m = add_carta(m,np2,p);

  	n = rem_carta((e.mao[e.ultimo_jogador]),n1,v1);
  	n = rem_carta(n,n2,v1);
  	n = rem_carta(n,n3,v1);
  	n = rem_carta(n,np1,p);
  	n = rem_carta(n,np2,p);

  	e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = n;
	e.ultima_jogada_valida = e.ultimo_jogador;
	e.ultimo_jogador = incrementa_jogador(e);
	e.card = 0;
	return e;
}


ESTADO joga_fourkind(ESTADO e) {

	long long int m=0, n=0;

	int v1=0,n2=0,n1=0,p=0;

  	v1 = maior_carta_fourkind(e.mao[e.ultimo_jogador]);
  	
  	p = da_carta_fourkind(e.mao[e.ultimo_jogador]);

  	for (n1 = 3; n1 >= 0; --n1) {
  		if (carta_existe(e.mao[e.ultimo_jogador],n1,p)) {
  			n2 = n1;
  		}	
  	}
  	/* os v's são todos iguais, exceto v5 */

	m = add_carta(0,0,v1);
  	m = add_carta(m,1,v1);
  	m = add_carta(m,2,v1);
  	m = add_carta(m,3,v1);
  	m = add_carta(m,n2,p);

  	n = rem_carta((e.mao[e.ultimo_jogador]),0,v1);
  	n = rem_carta(n,1,v1);
  	n = rem_carta(n,2,v1);
  	n = rem_carta(n,3,v1);
  	n = rem_carta(n,n2,p);

  	e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = n;
	e.ultima_jogada_valida = e.ultimo_jogador;
	e.ultimo_jogador = incrementa_jogador(e);
	e.card = 0;
	return e;
}


ESTADO joga_straightflush(ESTADO e) {

	long long int m=0, n=0;

	int v1,v2,v3,v4,v5,n1,n2,n3,n4,n5,p2,p3,p4,p5;

  	v1 = maior_carta_straightflush_bots (e.mao[e.ultimo_jogador]);
  	p2 = codifica ((maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]))-1);
  	p3 = codifica ((maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]))-2);
  	p4 = codifica ((maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]))-3);
  	p5 = codifica ((maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]))-4);

	v2 = descodifica_straight(p2);
	v3 = descodifica_straight(p3);
	v4 = descodifica_straight(p4);
	v5 = descodifica_straight(p5);
/* os ns sao todos iguais */
  	n1 = maior_naipeCarta_straightflush_bots((e.mao[e.ultimo_jogador]));
  	n2 = maior_naipeCarta_straightflush_bots((e.mao[e.ultimo_jogador]));
	n3 = maior_naipeCarta_straightflush_bots((e.mao[e.ultimo_jogador]));
	n4 = maior_naipeCarta_straightflush_bots((e.mao[e.ultimo_jogador]));
	n5 = maior_naipeCarta_straightflush_bots((e.mao[e.ultimo_jogador]));
	
	m = add_carta(0,n1,v1);
  	m = add_carta(m,n2,v2);
  	m = add_carta(m,n3,v3);
  	m = add_carta(m,n4,v4);
  	m = add_carta(m,n5,v5);

  	n = rem_carta((e.mao[e.ultimo_jogador]),n1,v1);
  	n = rem_carta(n,n2,v2);
  	n = rem_carta(n,n3,v3);
  	n = rem_carta(n,n4,v4);
  	n = rem_carta(n,n5,v5);

  	e.cartas[e.ultimo_jogador] = (e.cartas[e.ultimo_jogador]) - 5;
	e.ultima_jogada = m;
	e.cartas_bots[e.ultimo_jogador] = m;
	e.mao[e.ultimo_jogador] = n;
	e.ultima_jogada_valida = e.ultimo_jogador;
	e.ultimo_jogador = incrementa_jogador(e);
	e.card = 0;
	return e;
}

ESTADO fazjogada (ESTADO e, int v) {
	if (v == 1) {
		if (maior_carta_straight_bots(e.mao[e.ultimo_jogador]) > maior_carta_straight_bots(e.ultima_jogada)) {  
			e = joga_straight(e);
			return e;
		}
		else {
			if ((maior_carta_straight_bots(e.mao[e.ultimo_jogador])) == (maior_carta_straight_bots(e.ultima_jogada))) {
				e = joga_straight(e);
				return e;
			}
			else{
				if (valida_flush(e.mao[e.ultimo_jogador]) != -1){
					e = joga_flush(e);
					return e;
				}
				else {
					if (valida_fullhouse(e.mao[e.ultimo_jogador]) != -1) {
						e = joga_fullhouse(e);
						return e;
					}
					else {
						if (maior_carta_fourkind(e.mao[e.ultimo_jogador]) != -1) {
							e = joga_fourkind(e);
							return e;
						}
						else {
							if (maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) != -1){
								e = joga_straightflush(e);
								return e;
							}
							else {
								e.cartas_bots[e.ultimo_jogador] = 0;
			    				e.ultimo_jogador = incrementa_jogador(e);
								return e;
							}
						}
					}
				}
			}
		}
	}

	if (v == 2) {
		if ((valida_flush(e.mao[e.ultimo_jogador])) > (valida_flush(e.ultima_jogada))) {
			e = joga_flush(e);
			return e;
		}
		else {
			if ((valida_flush(e.mao[e.ultimo_jogador])) == (valida_flush(e.ultima_jogada))) {
				if ((maior_carta_flush_bots(e.mao[e.ultimo_jogador], (valida_flush(e.mao[e.ultimo_jogador])))) > (maior_carta_flush_bots(e.ultima_jogada, (valida_flush(e.ultima_jogada))))) {
					e = joga_flush(e);
					return e;
				}
			}		
			else {
				if (valida_fullhouse(e.mao[e.ultimo_jogador]) != -1) {
					e = joga_fullhouse(e);
					return e;
				}
				else {
					if (maior_carta_fourkind(e.mao[e.ultimo_jogador]) != -1) {
						e = joga_fourkind(e);
						return e;
					}
					else {
						if (maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) != -1){
							e = joga_straightflush(e);
							return e;
						}
						else {
							e.cartas_bots[e.ultimo_jogador] = 0;
							e.ultimo_jogador = incrementa_jogador(e);
							return e;
						}
					}
				}
			}
		}
	}

	if (v == 3) {
		if (valida_fullhouse(e.mao[e.ultimo_jogador]) > valida_fullhouse(e.ultima_jogada) && (valida_fullhouse(e.mao[e.ultimo_jogador] != -1))) {
			e = joga_fullhouse(e);
			return e;
		}
		else {
			if (maior_carta_fourkind(e.mao[e.ultimo_jogador]) != -1) {
				e = joga_fourkind(e);
				return e;
			}
			else {
				if (maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) != -1) {
					e = joga_straightflush(e);
					return e;
				}
				else {
					e.cartas_bots[e.ultimo_jogador] = 0;
					e.ultimo_jogador = incrementa_jogador(e);
					return e;
				}
			}
		}
	}

	if (v == 4) {
		if ((maior_carta_fourkind(e.mao[e.ultimo_jogador])) > (maior_carta_fourkind(e.ultima_jogada)) && (maior_carta_fourkind(e.mao[e.ultimo_jogador]) != -1)) {
			e = joga_fourkind(e);
			return e;
		}
		else {
			if (maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) != -1){
				e = joga_straightflush(e);
				return e;
			}
			else {
				e.cartas_bots[e.ultimo_jogador] = 0;
				e.ultimo_jogador = incrementa_jogador(e);
				return e;
			}
		}
	}

	if (v == 5) {
		if((maior_carta_straightflush_bots(e.mao[e.ultimo_jogador]) == -1)) {
			e.cartas_bots[e.ultimo_jogador] = 0;
			e.ultimo_jogador = incrementa_jogador(e);
			return e;
		}
		else {
			if (codifica(maior_carta_straightflush_bots(e.mao[e.ultimo_jogador])) > codifica(maior_carta_straightflush_bots(e.ultima_jogada))) {
				e = joga_straightflush(e);
				return e;
			}
			else {
				if ((codifica(maior_carta_straightflush_bots(e.mao[e.ultimo_jogador])) == (codifica(maior_carta_straightflush_bots(e.ultima_jogada)))) && (maior_naipeCarta_straightflush_bots(e.mao[e.ultimo_jogador])) > (maior_naipeCarta_straightflush_bots(e.ultima_jogada))) {
					e = joga_straightflush(e);
					return e;
				}
			}
		}
	}

	e = passabot(e);
	return e;
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
