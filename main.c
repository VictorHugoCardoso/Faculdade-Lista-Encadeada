#include "funcoes.h"

int main(){

	FILE *j,*p,*t;
	if( ((j = fopen("jogadores.bin","r+b")) == NULL) || ((p = fopen("partidas.bin","r+b")) == NULL) || ((t = fopen("torneios.bin","r+b")) == NULL)){
		printf("Erro na abertura dos arquivos!\n");       //abre o arquivo para leitura e gravacao em binario
		return 1;                                         //caso nao seja possivel, encerra o programa
	}
	int resp=1;
	
	while(1){
        system("cls");
        printf("           *-----------------------*\n");
        printf("           |  SISTEMA DE TORNEIOS  |\n");
        printf("           *-----------------------*\n");
        printf("*--------------------------------------------*\n");
        printf("| |01| - Imprimir Lista de Jogadores         |\n");
        printf("| |02| - Imprimir Lista de Partidas          |\n");
        printf("| |03| - Imprimir Lista de Torneios          |\n");
        printf("*--------------------------------------------*\n");
        printf("| |04| - Inserir Jogador                     |\n");
        printf("| |05| - Remover Jogador por nome            |\n");
        printf("*--------------------------------------------*\n");
        printf("| |06| - Inserir Partida                     |\n");
        printf("| |07| - Remover Partida por ID              |\n");
        printf("*--------------------------------------------*\n");
        printf("| |08| - Inserir Torneio                     |\n");
        printf("| |09| - Remover Torneio por data            |\n");
        printf("*--------------------------------------------*\n");
        printf("| |10| - Carregar Arquivo                    |\n");
        printf("*--------------------------------------------*\n");
        printf("| |00| - Sair                                |\n");
        printf("*--------------------------------------------*\n\n");
        printf("ESCOLHA: ");
        fflush(stdin);
        scanf("%d", &resp);
        system("cls");
        
        switch(resp){
			case 1:
			
				imprimir_jogadores(j); 
				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 2:
				imprimir_partidas(p); 
				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 3:
				imprimir_torneios(t); 
				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 4:
				insere_jogador(j);
				break;
			case 5:
				remove_jogador(j);
				break;
			case 6:
				insere_partida(p);
				break;
			case 7:
				remove_partida(p);
				break;
			case 8:
				insere_torneio(t);
				break;
			case 9:
				remove_torneio(t);
				break;

			case 10:
			 
                fclose(j); 
                fclose(p); 
                fclose(t); 
                j = fopen("jogadores.bin","w+b"); // reabre para sobrescrever
                p = fopen("partidas.bin","w+b"); // reabre para sobrescrever
                t = fopen("torneios.bin","w+b"); // reabre para sobrescrever
                inicializa(j,p,t,"lista.txt"); // carrega o arquivo de texto para o arquivo binario
                fclose(j); // fecha o arquivo
                fclose(p); // fecha o arquivo
                fclose(t); // fecha o arquivo
                j = fopen("jogadores.bin","r+b"); //  e reabre-o para leitura
                p = fopen("partidas.bin","r+b"); //  e reabre-o para leitura
                t = fopen("torneios.bin","r+b"); //  e reabre-o para leitura
               // scanf("%*c");// serve apenas para impressao
               // scanf("%*c");
                break;

			case 0:
				fclose(j); 
                fclose(p); 
                fclose(t); 
                exit(1);
            default:
                printf("Invalido\n");
        }
    }
	return 0;
}
