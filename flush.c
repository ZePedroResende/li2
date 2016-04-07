int flush (MAO m , MAO p){
	if (m == -1) {
		if (confirma_naipe) return 1;
	}
else {
	if (confirma_naipe(m) < confirma_naipe(p)) return 1;
	if (confirma_naipe(m) > confirma_naipe(p)) return 0;
	if (confirma_naipe(m) == confirma_naipe(p)){
		if (maior_valor(m) < maior_valor(p)) return 1;
		else return 0; 
	}
}
}

int confirma_naipe(MAO m){
 	int n, v, maior=0;

	for (n = 0; n < 4; n++) {

    for (v = 0; v < 13; v++)

      if (carta_existe(m, n, v)) { 
      	if (n == naipe) naipe =n;
        else {
        	return -1 ; 
        }
      }
	}

	return naipe;
}

int maior_valor (MAO m){

 	int n, v, maiorValor=-1;



	for (n = 0; n < 4 ; n++) {

    for (v = 0; v < 13 ; v++)

      if (carta_existe(m, n, v)){
        if (v <= maiorValor){
          return -1 ;

        }
        else maiorValor= v;

      }
	}
	return maiorValor;

}