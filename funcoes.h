#include "header.h"

cabecalho* le_cabecalho(FILE* arq){
	cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
	fseek(arq,0,SEEK_SET);
	fread(cab,sizeof(cabecalho),1,arq);
	return cab;
}

void escreve_cabecalho(FILE* arq, cabecalho* cab){
	fseek(arq,0,SEEK_SET);
	fwrite(cab,sizeof(cabecalho),1,arq);
}

void cria_lista_vazia(FILE* arq){
	cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
	cab->pos_cabeca = -1;
	cab->pos_topo = 0;
	cab->pos_livre = -1;
	escreve_cabecalho(arq,cab);
	free(cab);
}

jogador* le_jogador(FILE* arq, int pos) {
	jogador *x = (jogador*)malloc(sizeof(jogador));
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(jogador),SEEK_SET);
	fread(x,sizeof(jogador),1,arq);
	return x;
}

void escreve_jogador(FILE* arq, jogador* x, int pos){
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(jogador),SEEK_SET);
	fwrite(x,sizeof(jogador),1,arq);
}

void insere_jogador_binario(FILE* arq, jogador* j){
	cabecalho* cab = le_cabecalho(arq);
	
	j->prox = cab->pos_cabeca;
	if(cab->pos_livre == -1) {
		escreve_jogador(arq,j,cab->pos_topo);
		cab->pos_cabeca = cab->pos_topo;
		cab->pos_topo++;
	}else{
		jogador* aux = le_jogador(arq,cab->pos_livre);
		escreve_jogador(arq,j,cab->pos_livre);
		cab->pos_cabeca = cab->pos_livre;
		cab->pos_livre = aux->prox;
		free(aux);
	}
	escreve_cabecalho(arq,cab);

	free(cab);
}

void insere_jogador(FILE *f){
	jogador *j = (jogador*) malloc(sizeof(jogador));
	
	printf("Entre com o nome do jogador: \n");
	fflush(stdin);
	scanf("%[^\n]",&j->nome);

	printf("\nInsira a pontuacao do jogador: \n");
	fflush(stdin);
	scanf("%d",&j->score);

	printf("\nInsira o numero de partidas: \n");
	fflush(stdin);
	scanf("%d",&j->npartidas);

	insere_jogador_binario(f,j);
	free(j);
}

partida* le_partida(FILE* arq, int pos) {
	partida *x = (partida*)malloc(sizeof(partida));
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(partida),SEEK_SET);
	fread(x,sizeof(partida),1,arq);
	return x;
}

void escreve_partida(FILE* arq, partida* x, int pos){
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(partida),SEEK_SET);
	fwrite(x,sizeof(partida),1,arq);
}

void insere_partida_binario(FILE* arq, partida* p){
	cabecalho* cab = le_cabecalho(arq);
	
	p->prox = cab->pos_cabeca;
	if(cab->pos_livre == -1) {
		escreve_partida(arq,p,cab->pos_topo);
		cab->pos_cabeca = cab->pos_topo;
		cab->pos_topo++;
	}else{
		partida* aux = le_partida(arq,cab->pos_livre);
		escreve_partida(arq,p,cab->pos_livre);
		cab->pos_cabeca = cab->pos_livre;
		cab->pos_livre = aux->prox;
		free(aux);
	}
	escreve_cabecalho(arq,cab);

	free(cab);
}

void insere_partida(FILE *f){
	partida *p = (partida*) malloc(sizeof(partida));
	
	printf("Entre com o ID da Partida: \n");
	fflush(stdin);
	scanf("%d",&p->id);

	printf("\nInsira o nome do Primeiro jogador: \n");
	fflush(stdin);
	scanf("%[^\n]",&p->nome1);
	
	printf("\nEntre com a pontuacao do Primeiro jogador: \n");
	fflush(stdin);
	scanf("%d",&p->pontuacao1);
	
	printf("\nInsira o nome do Segundo jogador: \n");
	fflush(stdin);
	scanf("%[^\n]",&p->nome2);
	
	printf("\nEntre com a pontuacao do Segundo jogador: \n");
	fflush(stdin);
	scanf("%d",&p->pontuacao2);
	
	insere_partida_binario(f,p);
	free(p);
}

torneio* le_torneio(FILE* arq, int pos) {
	torneio *x = (torneio*)malloc(sizeof(torneio));
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(torneio),SEEK_SET);
	fread(x,sizeof(torneio),1,arq);
	return x;
}

void escreve_torneio(FILE* arq, torneio* x, int pos){
	fseek(arq,sizeof(cabecalho)+ pos*sizeof(torneio),SEEK_SET);
	fwrite(x,sizeof(torneio),1,arq);
}

void insere_torneio_binario(FILE* arq, torneio* t){
	cabecalho* cab = le_cabecalho(arq);
	t->prox = cab->pos_cabeca;
	if(cab->pos_livre == -1) {
		escreve_torneio(arq,t,cab->pos_topo);
		cab->pos_cabeca = cab->pos_topo;
		cab->pos_topo++;
	}else{
		torneio* aux = le_torneio(arq,cab->pos_livre);
		escreve_torneio(arq,t,cab->pos_livre);
		cab->pos_cabeca = cab->pos_livre;
		cab->pos_livre = aux->prox;
		free(aux);
	}
	escreve_cabecalho(arq,cab);
	free(cab);
}

void insere_torneio(FILE *f){
	torneio *t = (torneio*) malloc(sizeof(torneio));
	
	printf("Entre com o nome do Torneio: \n");
	fflush(stdin);
	scanf("%[^\n]",&t->nome);
	
	printf("\nInsira a data do Torneio: \n");
	fflush(stdin);
	scanf("%[^\n]",&t->data);

	printf("\nInsira o local do Torneio: \n");
	fflush(stdin);
	scanf("%[^\n]",&t->local);

	insere_torneio_binario(f,t);
	free(t);
}

void imprimir_jogadores(FILE* f){
	jogador* j = (jogador*) malloc(sizeof(jogador));
	fseek(f,sizeof(cabecalho),SEEK_SET);			//posiciona o curso apos o cabecalho

    if(fread(j,sizeof(jogador),1,f) == 0){
        printf("Nao ha jogadores cadastrados!\n");
	}else{
		printf("[                            [LISTA DE JOGADORES]                          ]\n");
		printf("*--------------------------------------------------------------------------*\n");
        printf("| [NOME]                         [SCORE]               [N PARTIDAS]        |\n");
        printf("*--------------------------------------------------------------------------*\n");
        while(fread(j,sizeof(jogador),1,f)){   //enquanto tiver jogadores para ler...           	
            if(strcmp(j->nome,"0") != 0) printf("| %s [%d] {%d}\n",j->nome, j->score, j->npartidas);
        }
    }
}

void imprimir_partidas(FILE* f){
	partida* p = (partida*) malloc(sizeof(partida));

	fseek(f,sizeof(cabecalho),SEEK_SET);			//posiciona o curso apos o cabecalho

    if(fread(p,sizeof(partida),1,f) == 0){
        printf("Nao ha partidas cadastrados!\n");
	}else{
		printf("[                            [LISTA DE PARTIDAS]                           ]\n");
		printf("*--------------------------------------------------------------------------*\n");
        printf("| [ID]        [NOME 1]    [PONTUACAO 1] | [NOME 2]    [PONTUACAO 2]        |\n");
        printf("*--------------------------------------------------------------------------*\n");
        while(fread(p,sizeof(partida),1,f) != 0){ 	//enquanto tiver jogadores para ler...
     	    if(strcmp(p->nome1,"0") != 0) printf("| %d  [%s] {%d}  |  [%s] {%d}\n",p->id, p->nome1,p->pontuacao1, p->nome2,p->pontuacao2);
        }
    }
}

void imprimir_torneios(FILE* f){
	torneio* t = (torneio*) malloc(sizeof(torneio));

	fseek(f,sizeof(cabecalho),SEEK_SET);	//posiciona o curso apos o cabecalho

    if(fread(t,sizeof(torneio),1,f) == 0){
        printf("Nao ha torneios cadastrados!\n");
	}else{
		printf("[                            [LISTA DE TORNEIOS]                           ]\n");
		printf("*--------------------------------------------------------------------------*\n");
        printf("| [NOME]                       [DATA]                        [LOCAL]       |\n");
        printf("*--------------------------------------------------------------------------*\n");
        while(fread(t,sizeof(torneio),1,f) != 0){
            if(strcmp(t->nome,"0") != 0) printf("| %s               [%s]            %s\n",t->nome, t->data, t->local);
        }
    }
}


int power(int x, int y){					//x elevado por y
	int n,i;
	n=1;
	for(i=0;i<y;i++)
		n *= 10;
	return n;
}

int strtodig(char* s, int l){				//transforma uma string em um numero
	int i,n = 0;
	for(i=0;i<l;i++){
		n += (s[i] - '0') * power(10,l -1 -i);	//o caracter multiplicado pelo valor de sua posicao
	}
	return n;
}

int inicializa(FILE *jogad,FILE *partid,FILE *tornei, char* txt){
	cria_lista_vazia(tornei);	//como o arquivo é sobrescrito, uma nova lista precisa ser criada
	cria_lista_vazia(partid);	//como o arquivo é sobrescrito, uma nova lista precisa ser criada
	cria_lista_vazia(jogad);	//como o arquivo é sobrescrito, uma nova lista precisa ser criada
	char s[200];

	FILE *arq;
	if((arq = fopen(txt,"r")) == NULL){
		printf("Erro ao abrir o arquivo texto\n");		//retorna o codigo de erro 1 se houver
		return 1;										//erro na abertura do arquivo
	}

	fseek(arq,0,SEEK_SET);								//posiciona o cursor no comeco do arquivo texto

	jogador *j = (jogador*) malloc(sizeof(jogador));			
	partida *p = (partida*) malloc(sizeof(partida));			
	torneio *t = (torneio*) malloc(sizeof(torneio));			
	int i,k;
	char aux[10];
	
	while(fgets(s,100,arq) != 0){
		for(i=0;i<MAX_NOME;i++){
            j->nome[i] = '\0';
            p->nome1[i] = '\0';
            p->nome2[i] = '\0';
            t->nome[i] = '\0';
            t->local[i] = '\0';
        }
        
        for(i=0;i<MAX_DATA;i++){
			t->data[i] = '\0';
		}
			
		if(s[0] == 'J'){
			
			k = 0;
			i = 2;
			while(s[i] != ','){			
				j->nome[k] = s[i];	
				i++;k++;			
			}
			
			k = 0;
			i += 1;
			
			while(s[i] != ',' && i<strlen(s)){			
				aux[k] = s[i];	
				i++;k++;			
			}
			
			j->score = strtodig(aux,k);
			
			i += 1;
			
			for(k=0; i<strlen(s)-1; i++,k++){	
				aux[k] = s[i];				
			}
			
			j->npartidas = strtodig(aux,k);
			
			insere_jogador_binario(jogad,j);
		}
		if(s[0] == 'P'){
			
			k = 0;
			i = 2;
			
			while(s[i] != ','){			
				aux[k] = s[i];
				i++;k++;			
			}
			
			p->id = strtodig(aux,k);
			
			k = 0;
			i += 1;
			
			while(s[i] != ','){			
				p->nome1[k] = s[i];	
				i++;k++;			
			}
			
			k = 0;
			i += 1;
			
			while(s[i] != ','){			
				aux[k] = s[i];	
				i++;k++;			
			}
			
			p->pontuacao1 = strtodig(aux,k);
			
			k = 0;
			i += 1;
			
			while(s[i] != ',' && i<strlen(s)){			
				p->nome2[k] = s[i];	
				i++;k++;			
			}
			
			k = 0;
			i += 1;
			
			for(k=0; i<strlen(s)-1; i++,k++){	
				aux[k] = s[i];				
			}
			
			p->pontuacao2 = strtodig(aux,k);
			
			insere_partida_binario(partid,p);
		}
		
		if(s[0] == 'T'){
			
			k = 0;
			i = 2;
			
			while(s[i] != ','){			
				t->nome[k] = s[i];	
				i++;k++;			
			}
			
			k = 0;
			i += 1;
			
			while(s[i] != ',' && i<strlen(s)){			
				t->data[k] = s[i];	
				i++;k++;			
			}
			
			k = 0;
			i += 1;
			
			for(k=0; i<strlen(s)-1; i++,k++){	
				t->local[k] = s[i];				
			}
			
			insere_torneio_binario(tornei,t);
		}
	}
	
	fclose(arq);			
	free(j);			
	free(p);			
	free(t);			
    printf("O arquivo foi inicializado com sucesso!\n");
	return 0;
}

void remove_jogador(FILE* arq){
	jogador* j = (jogador*) malloc(sizeof(jogador));
	cabecalho* cab = le_cabecalho(arq);
	int flag=1;
	int pos_aux = cab->pos_cabeca;
	int pos_ant = cab->pos_cabeca;
	char nome[MAX_NOME];
	printf("Entre com o nome do jogador que queira remover:\n");
	fflush(stdin);
	scanf("%[^\n]",nome);
	while(pos_aux != -1 && (j = le_jogador(arq,pos_aux)) != NULL && strcmp(j->nome,nome) != 0){
		pos_ant	= pos_aux;
		pos_aux = j->prox;
		free(j);
		j = NULL;
	}
	if(pos_aux != -1 && j->npartidas == 0){
		if(pos_ant == pos_aux){ 						//remoção na cabeça
			cab->pos_cabeca = j->prox;
		}
		else{ 											//remoção no meio
			jogador* ant = le_jogador(arq,pos_ant);
			ant->prox = j->prox;
			escreve_jogador(arq,ant,pos_ant);
			free(ant);	
		}
		j->prox = cab->pos_livre;							// torna o nó removido um nó livre
		cab->pos_livre = pos_aux;
		strcpy(j->nome,"0");
		escreve_jogador(arq,j,pos_aux);
		escreve_cabecalho(arq,cab);
		free(j);
		flag=0;
	}
	free(cab);
	if(flag == 1) printf("Jogador não removido\n");
	else printf("Jogador removido com sucesso\n");
}

void remove_partida(FILE* arq){
	partida* p = (partida*) malloc(sizeof(partida));
	cabecalho* cab = le_cabecalho(arq);
	int flag=1;
	int pos_aux = cab->pos_cabeca;
	int pos_ant = cab->pos_cabeca;
	int id;
	printf("Entre com o id da partida que deseja remover:\n");
	fflush(stdin);
	scanf("%d",&id);
	while(pos_aux != -1 && (p = le_partida(arq,pos_aux)) != NULL && p->id != id){
		pos_ant	= pos_aux;
		pos_aux = p->prox;
		free(p);
		p = NULL;
	}
	if(pos_aux != -1){
		if(pos_ant == pos_aux){							//remoção na cabeça
			cab->pos_cabeca = p->prox;
		}
		else{ 											//remoção no meio
			partida* ant = le_partida(arq,pos_ant);
			ant->prox = p->prox;
			escreve_partida(arq,ant,pos_ant);
			free(ant);	
		}
		p->prox = cab->pos_livre; 							// torna o nó removido um nó livre
		cab->pos_livre = pos_aux;
		strcpy(p->nome1,"0");
		escreve_partida(arq,p,pos_aux);
		escreve_cabecalho(arq,cab);
		free(p);
		flag=0;
	}
	free(cab);
	if(flag == 1) printf("Partida não encontrada\n");
	else printf("Partida encontrada e removida com sucesso\n");
}

void remove_torneio(FILE* arq){
	torneio* t = (torneio*) malloc(sizeof(torneio));
	cabecalho* cab = le_cabecalho(arq);
	int flag=1;
	int pos_aux = cab->pos_cabeca;
	int pos_ant = cab->pos_cabeca;
	char data[MAX_DATA];
	printf("Entre com a data do torneio que deseja remover:\n");
	fflush(stdin);
	scanf("%[^\n]",data);
	while(pos_aux != -1 && (t = le_torneio(arq,pos_aux)) != NULL && strcmp(t->data,data) != 0){
		pos_ant	= pos_aux;
		pos_aux = t->prox;
		free(t);
		t = NULL;
	}
	if(pos_aux != -1 && t->p == NULL){
		if(pos_ant == pos_aux){ 						//remoção na cabeça
			cab->pos_cabeca = t->prox;
		}
		else{ 											//remoção no meio
			torneio* ant = le_torneio(arq,pos_ant);
			ant->prox = t->prox;
			escreve_torneio(arq,ant,pos_ant);
			free(ant);	
		}
		t->prox = cab->pos_livre; 							// torna o nó removido um nó livre
		cab->pos_livre = pos_aux;
		strcpy(t->nome,"0");
		escreve_torneio(arq,t,pos_aux);
		escreve_cabecalho(arq,cab);
		free(t);
		flag=0;
	}
	free(cab);
	if(flag == 1) printf("Torneio não removido\n");
	else printf("Torneio removido com sucesso\n");
}