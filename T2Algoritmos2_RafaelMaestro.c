/* Programa desenvolvido como Trabalho 2 da disciplina de Algoritmos 2 - UNESP Bauru
Por Jõao Pedro de Freitas Zanqui e Rafael Maestro dos Santos */

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

#define baixo 80
#define cima 72
#define esc 27
#define enter 13
#define F1 59

void gotoxy (int x, int y)
{
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void texto(int x, int y, char texto[])
{
    gotoxy(x, y);
    printf("     %s", texto);
}

void selecao(int x, int y, char texto[]) 
{
    gotoxy(x, y);
    printf(" --> %s", texto);
}

void menu(int opc, int n) {
    int i;
    char x[15][1000] = {"Escolha a Operacao desejada:", "Para fechar o programa pressione a tecla 'ESC'...", "Para chamar o arquivo ajuda pressione a tecla 'F1'...",
	"Cadastrar PRODUTOS", "Alterar PRODUTOS", "Excluir PRODUTOS", "Consultar PRODUTOS", "Manipular outro ARQUIVO", "Alterar o nome do ARQUIVO", "Remover o ARQUIVO", 
	"Listar os ARQUIVOS da PASTA", "Criar PASTAS", "Alterar o nome de PASTAS", "Mudar os arquivos de PASTAS", "Alterar cores"};

    for(i=0; i<=n; i++)
    {
        if(i==0 || i==1 || i==2)
            texto(0, 1+i, x[i]);
        else
            texto(0, i+3, x[i]);
    }

    for(i=0; i<=n; i++) 
    {
        if(i==0 || i==1 || i==2)
            texto(0, 1+i, x[i]);
        else {
            if(opc==i-1)
                selecao(0, i+3, x[i]);
            else
                texto(0, i+3, x[i]);
        }
    }
}

typedef struct
{
    char nome[20];
    int id, qtd, existe;
    float preco, peso;
    
} registro;

void cadastro(char nomeArq[], FILE *arquivo) {
	char opc = '1';		
	registro x;
	
    if((arquivo = fopen(nomeArq, "ab"))==NULL) {
    	if((arquivo = fopen(nomeArq, "wb"))==NULL) {
    		printf("Falha ao abrir o arquivo...");
    		getch();
			system("cls");
    		return;
		}
	}
	else 
		fseek (arquivo, 0, SEEK_END);
	
	do {
		system("cls");
		fflush(stdin);

		x.existe = 1;
		printf("\n\t\tCadastro de um novo produto:\n\tNOME --> ");
		gets(x.nome);
		printf("\tPreco --> R$ ");
		scanf("%f", &x.preco);
		fflush(stdin);
		printf("\tQuantidade --> ");
		scanf("%d", &x.qtd);
		printf("\tPeso do produto (em g) --> ");
		scanf("%f", &x.peso);
		printf("\tID do produto --> ");
		scanf("%d", &x.id);
		
		fwrite(&x, sizeof(x), 1, arquivo);
		
		system("cls");
		printf("\n\t\tProduto cadastrado com sucesso...");
		printf("\n\n\t\tDeseja cadastrar um novo produto?\n\t1 - SIM\n\t2 - NAO\n\t");
		
		do {
			fflush(stdin);
			opc = getch();
			if(opc!='1' && opc!='2') {
				printf("\nPor favor digite uma opcao valida...");
			}
		} while(opc!='1' && opc!='2');
		
		if(opc=='2') {
			fclose(arquivo);
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n\n");
		    getch();
			system("cls");
			return;
		}
		
		else {
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu de Cadastro...\n\n");
		    getch();
		}
		
	} while(opc=='1');
}

void alterar(char nomeArq[], FILE *arquivo) {
	
	if((arquivo = fopen(nomeArq, "r+b"))==NULL) {
    		printf("Falha ao abrir o arquivo...");
    		getch();
    		system("cls");
    		return;
	}
	
	int achou, id;
	char opc = '1';
	registro x;
	
	do {
		achou=0;
		rewind(arquivo);
		system("cls");
		printf("\n\t\tDigite o ID do produto que deseja alterar\n\t--> ");
		scanf("%d", &id);
		system("cls");
		
		while (fread (&x, sizeof(registro), 1, arquivo) == 1 && achou==0) {
	   		if (x.id == id && x.existe) {
				printf("\n\t\tProduto\n\tID: %d\n\tNOME: %s\n\tPESO: %.2fg\n\tPRECO: R$ %.2f\n\tQUANTIDADE: %d", x.id,x.nome, x.peso, x.preco, x.qtd);
	    		printf("\n\n\n\tID --> ");
				scanf("%d", &x.id);
				fflush(stdin);
				printf("\n\tNOME --> ");
				gets(x.nome);
				printf("\n\tPeso --> ");
				scanf("%f", &x.peso);
				printf("\n\tPreco --> R$ ");
				scanf("%f", &x.preco);
				printf("\n\tQuantidade --> ");
				scanf("%d", &x.qtd);
	    
	    		fseek (arquivo, -sizeof(registro), SEEK_CUR);
				fwrite(&x,sizeof(registro),1,arquivo);
	    		fflush (arquivo);
	    		achou = 1;
		    }
		    if(achou==1)
		    	break;
		}
		
		if(achou==0)
			printf("\n\n\t\tNao existe um produto com o id %d...", id);
		else if (achou==1)
			printf("\n\t\tProduto Alterado com sucesso...");
		
			printf("\n\n\t\tDeseja Alterar um novo produto?\n\t1 - SIM\n\t2 - NAO\n\t");
		
		do {
			fflush(stdin);
			opc = getch();
			if(opc!='1' && opc!='2') {
				printf("\nPor favor digite uma opcao valida...");
			}
		} while(opc!='1' && opc!='2');
		
		if(opc=='2') {
			fclose(arquivo);
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n\n");
		    getch();
			system("cls");
			return;
		}
		
		else {
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu de Alteração...\n\n");
		    getch();
		}
		
	} while(opc=='1');	
}

void apagaReg(char nomeArq[], FILE *arquivo) {
	
	char opc='1', conf;
  	registro x;
  	int numero, achou;
  	char numstr[30];
  // Abertura do arquivo
  	if ((arquivo = fopen(nomeArq, "r+b")) == NULL) {
    	printf ("Falha ao abrir o arquivo...\n\n");
    	getch();
    	system("cls");
    	return;
	}
    
	do {
		achou=0;
    	rewind(arquivo);
    	system("cls");
  		printf ("\n\t Qual o ID do produto que deseja apagar? \n\t --> ");
  		scanf ("%d",&numero);
  //	 Leitura dos registros
  		while (fread (&x, sizeof(registro), 1, arquivo) == 1 && !achou)
    		if (x.existe && x.id == numero) {
     			printf ("\n\t Nome: %s", x.nome);
     			printf ("\n\t ID: %d", x.id);
     			printf ("\n\t Quantidade: %d unidade(s)", x.qtd);
     			printf ("\n\t Peso (g): %.2f", x.peso);
     			printf ("\n\t Preço R$: %.2f", x.preco);
     			achou=1;
     			break;
     		}
				
			fflush (stdin); // "Limpa" o buffer de entrada - teclado
			if (achou==1) {
				
				printf("\n\n\tDeseja realmente apagar o produto %s ?\n\t1 - SIM\n\t2 - NAO\n\t", x.nome);
				do {
					fflush(stdin);
					conf = getch();
					if(conf!='1' && conf!='2') {
						printf("\nPor favor digite uma opcao valida...");
					}
				} while(conf!='1' && conf!='2');
				
		    	if (conf == '1') {
		    		x.existe = 0;
		    	    // Volta o ponteiro
		    	    // Grava os dados lidos - alterados
		    		fseek (arquivo,-sizeof(registro),SEEK_CUR);
		       		fwrite(&x,sizeof(registro),1,arquivo);
		       		fflush (arquivo);
		        	printf ("\n\t Produto %s REMOVIDO...",x.nome);
		        	getch();
				}
		      	
				else {
		       		printf ("\n\t Produto %s NÃO removido...\n\n",x.nome);
		    	}
		    }
				
			else {
				printf ("\n\t Nao há produto cadastrado com id %d.\n\n",numero);
			}		
    
       	printf("\n\n\t\tDeseja apagar um outro produto?\n\t1 - SIM\n\t2 - NAO\n\t");

        do {
			fflush(stdin);
			opc = getch();
			if(opc!='1' && opc!='2') {
				printf("\nPor favor digite uma opcao valida...");
			}
		} while(opc!='1' && opc!='2');
		
		if(opc=='2') {
			fclose(arquivo);
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n\n");
		    getch();
			system("cls");
			return;
		}
		
		else {
			printf ("\n\t Pressione qualquer tecla para voltar para o Menu de Exclusão...\n\n");
		    getch();
		}
		
	} while(opc=='1');
}

void excluir(char nomeArq[], FILE *arquivo, int removido) {
	FILE *temp;
	registro x;
	
	if((arquivo = fopen(nomeArq, "r+b"))==NULL && !removido) {
   			printf("Falha ao excluir fisicamente os registros...\n\n");
   			getch();
   			system("cls");
   			return;
	}
	
	if((temp = fopen("temp.bak", "w+b"))==NULL) {
   			printf("Falha ao excluir fisicamente os registros...\n\n");
   			getch();
   			system("cls");
   			return;
	}

	
	while (fread (&x, sizeof(registro), 1, arquivo) == 1)
    	if (x.existe)
     		fwrite(&x, sizeof(x), 1, temp);
    
    fclose(temp);
    fclose(arquivo);
    remove(nomeArq);
    
	if(!removido)
		rename("temp.bak", nomeArq);
	else
		remove("temp.bak");
}

void consultar(char nomeArq[], FILE *arquivo) {
	registro x;
	int achou=0, id;
	char opc = '1', nome[20];
	
	if((arquivo = fopen(nomeArq, "rb"))==NULL) {
    		printf("Falha ao abrir o arquivo...\n\n");
    		getch();
    		system("cls");
    		return;
	}
	
	do{
		system("cls");
		achou=0;
		rewind(arquivo);
		
		printf("\n\t\tEscolha a forma de pesquisa do registro\n\t1 - NOME\n\t2 - ID\n");
		do {
				fflush(stdin);
				opc = getch();
				if(opc!='1' && opc!='2') {
					printf("\nPor favor digite uma opcao valida...");
				}
			} while(opc!='1' && opc!='2');
			
		if(opc=='1') {
			printf("\n\t\tDigite o NOME do produto que deseja pesquisar\n\t--> ");
			fflush(stdin);
			gets(nome);
		}
		
		else {
			printf("\n\t\tDigite o ID do produto que deseja pesquisar\n\t--> ");
			scanf("%d", &id);
		}
			
		while(fread(&x, sizeof(registro), 1, arquivo)==1 && !achou) {
			if(opc=='1') {
				if(strcmp(x.nome, nome)==0 && x.existe) {
					printf ("\n\t Nome: %s", x.nome);
	     			printf ("\n\t ID: %d", x.id);
	     			printf ("\n\t Quantidade: %d unidade(s)", x.qtd);
	     			printf ("\n\t Peso (g): %.2f", x.peso);
	     			printf ("\n\t Preço R$: %.2f", x.preco);
	     			achou=1;
	     			break;
				}
			}
			
			else {
				if(x.id == id && x.existe) {
					printf ("\n\t Nome: %s", x.nome);
	     			printf ("\n\t ID: %d", x.id);
	     			printf ("\n\t Quantidade: %d unidade(s)", x.qtd);
	     			printf ("\n\t Peso (g): %.2f", x.peso);
	     			printf ("\n\t Preço R$: %.2f", x.preco);
	     			achou=1;
	     			break;
				}
			}
		}
		
		if(!achou) {
			if(opc=='1')
				printf("\n\n\tNao foi encontrado nenhum produto com o NOME %s...", nome);
			else
				printf("\n\n\tNao foi encontrado nenhum produto com o ID %d...", id);
		}
		
		printf("\n\n\t\tDeseja buscar outro produto?\n\t1 - SIM\n\t2 - NAO\n\t");
	
	        do {
				fflush(stdin);
				opc = getch();
				if(opc!='1' && opc!='2') {
					printf("\nPor favor digite uma opcao valida...");
				}
			} while(opc!='1' && opc!='2');
			
			if(opc=='2') {
				fclose(arquivo);
				printf ("\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n\n");
			    getch();
				system("cls");
				return;
			}
			
			else {
				printf ("\n\t Pressione qualquer tecla para voltar para o Menu de Consulta...\n\n");
			    getch();
			}
	}while(opc=='1');
}

char* trocarNome(char nomeArq[], FILE *arquivo){
    FILE *temp;
    registro x;
    char trocaNome[30];
    
    
	if((arquivo = fopen(nomeArq, "r+b"))==NULL) {
        printf("\n\tO arquivo nao existe...\n\n");
        getch();
        system("cls");
        return nomeArq;
    }

    printf("\t Digite o novo nome do arquivo\n\t--> ");
    fflush(stdin);
    gets(trocaNome);
    strcat(trocaNome, ".bak");
	

    (temp = fopen("temp.bak", "w+b"));

    while (fread (&x, sizeof(registro), 1, arquivo) == 1)
        if (x.existe)
             fwrite(&x, sizeof(x), 1, temp);

    fclose(temp);
    fclose(arquivo);
    remove(nomeArq);
    rename("temp.bak", trocaNome);
    
    printf("\n\tArquivo %s trocado para %s com sucesso...", nomeArq, trocaNome);
    getch(); 
    system("cls");
    
    return trocaNome;
}

void remover(char nomeArq[], FILE *arquivo) {
	system("cls");
	int opc;
	
	if((arquivo = fopen(nomeArq, "rb"))==NULL) {
        printf("\n\tO Arquivo nao existe...\n\n");
        getch();
        system("cls");
        return;
    }
    
    
	printf("\n\tTem Certeza que deseja remover o arquivo %s ?\n\t1 - SIM\n\t2 - NAO\n", nomeArq);
	
	do {
		fflush(stdin);
		opc = getch();
		if(opc!='1' && opc!='2') {
			printf("\nPor favor digite uma opcao valida...");
		}
	} while(opc!='1' && opc!='2');
			
	if(opc=='1') {
		fclose(arquivo);
		if(remove(nomeArq)==0)
			printf ("\n\t O arquivo %s foi removido com sucesso...\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n", nomeArq);
		else
			printf ("\n\t Falha ao remover o arquivo...\n\t Pressione qualquer tecla para voltar para o Menu Principal...\n");	
	    getch();
	}
			
	else {
		fclose(arquivo);
		printf ("\n\t O arquivo %s não foi removido...\n\tPressione qualquer tecla para voltar para o Menu Principal...\n", nomeArq);
	    getch();
	}
	
	system("cls");
}

void mostraTempo(){
	
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  gotoxy(5, 20);
  printf ( "%s", asctime (timeinfo) );
  

}

void listaArquivosPasta(){

    system("cls");
    printf("Arquivos existentes no diretório atual:\n");
    system("tree /f");
    printf("\nPara voltar ao menu pressione qualquer tecla...");
    getch();
    system("cls");


}

void exibeAjuda() {
	
	system("cls");
   	FILE *ajuda;
   	char c[10000];

    if((ajuda = fopen("ajuda.txt", "r"))==NULL){
    	printf("\n\tO arquivo ajuda não existe...\n\n\tPressione qualquer tecla para voltar ao menu principal...\n");
	}

	while(fgets(c, 10000, ajuda) != NULL){
    	int i;
    	i = 0;
    	for(i=0; i<strlen(c); i++){
		    c[i] = c[i] - 10;
	    }
	}
	
	fclose(ajuda);
    printf("%s", c);
    printf("\n\n\tPressione qualquer tecla para voltar ao menu principal...\n");
    getch();
    system("cls");
}

void criaPasta(){

    system("cls");
    printf("\n\tCrie uma pasta no diretório atual");
    char str1[20], str2[]={"mkdir "};
    fflush(stdin);
    printf("\n\tDigite o nome da pasta que deseja criar\n\t-->  ");
    gets(str1);

    strcat(str2, str1);

    system(str2);
    printf("\n\tPasta criada com sucesso!\n\tPressione qualquer tecla para voltar ao menu principal...\n");
    getch();
    system("cls");
}

void renomeiaPasta(){

    system("cls");
    printf("\n\tEdite o nome de uma pasta no diretório atual");
    char str1[20], str2[]={"rename "}, str3[20];
    fflush(stdin);
    printf("\n\tDigite o nome ATUAL da pasta\n\t-->  ");
    gets(str1);
    strcat(str1, " ");
    strcat(str2, str1);
    fflush(stdin);
    printf("\n\tDigite o NOVO nome da pasta\n\t-->  ");
    gets(str3);

    strcat(str2, str3);

    system("cls");
	system(str2);
	printf("\n\tPressione qualquer tecla para voltar ao menu principal...\n");
	getch();
    system("cls");
}

void mudarDePasta()
{
	char pastaAtual[20], nomeArq[20], diretorio1[50], diretorio2[50], comando[50]={"copy "}, teste[50];
	FILE *arquivo;
	
	system("cls");
	printf("\n\tMude arquivos de pasta...");
	printf("\n\n\tDigite o nome da pasta onde se encontra o arquivo \n\t(se ele estiver no diretório atual nao digite nada e apenas pressione enter...)\n\t --> ");
	fflush(stdin);
	gets(pastaAtual);
	printf("\tDigite o nome do arquivo\n\t --> ");
	gets(nomeArq);
	
	if(strcmp(pastaAtual, "")!=0) {
		strcat(pastaAtual, "\\");
		strcat(nomeArq, ".bak");
		strcat(pastaAtual, nomeArq);
		strcpy(diretorio1, pastaAtual);	
	}
	
	else {
		strcat(nomeArq, ".bak");
		strcpy(diretorio1, nomeArq);
	}
	
	if((arquivo = fopen(diretorio1, "rb"))==NULL) {
		printf("\n\n\tPASTA ou ARQUIVO inexistente....");
		getch();
		system("cls");
		return;
	}
	
	fclose(arquivo);
	
	printf("\n\n\tDigite o nome da pasta para onde será transferido o arquivo\n\t(se quiser transferir para o diretório atual nao digite nada e apenas pressione enter...)\n\t --> ");
	fflush(stdin);
	gets(pastaAtual);
	
	
	if(strcmp(pastaAtual, "")!=0) {
		strcpy(diretorio2, pastaAtual);	
		
		strcpy(teste, diretorio2);
		strcat(teste, "\\");
		strcat(teste, "test_pasta_existe.bak");	
	
		if((arquivo = fopen(teste, "wb"))==NULL) {
			printf("\n\n\tPASTA inexistente...");
			getch();
			system("cls");
			return;
		}
		
		fclose(arquivo);
		remove(teste);
	}
	
	else {
		strcpy(diretorio2, "");
	}
		
	strcat(comando, diretorio1);
	strcat(comando, " ");
	strcat(comando, diretorio2);
	
	system(comando);
	remove(diretorio1);
	
	printf("\n\n\tPressione qualquer tecla para voltar ao menu principal...");
	getch();
	system("cls");
}

void mudaCor() {
    char cor[5];
    char str[]={"color "};
    fflush(stdin);
    printf("\n\tCaso não saiba quais numeros representam quais cores, pode consulta-los no arquivo de ajuda!\n");
    printf("\n\tDigite os dois digitos que representam as cores que deseja para primeiro plano e\n\ttela de fundo do console: \n\n\t --> ");
    gets(cor);
    strcat(str, cor);
    system(str);
    
    printf("\n\tPressione qualquer tecla para voltar ao menu principal...");
	getch();
	system("cls");
}

int main() 
{
	setlocale(LC_ALL, "");
	FILE *arquivo;
    int opc=2, n=14, removido, voltar;
    char t, nomeArq[20];
	
	do {
		voltar=1;
		removido=0;
		printf("\t Digite o nome do arquivo que deseja manipular\n\t--> ");
		fflush(stdin);
		gets(nomeArq);
		strcat(nomeArq, ".bak");
		system("cls");
		
		if((arquivo = fopen(nomeArq, "ab"))==NULL) {
    		if((arquivo = fopen(nomeArq, "wb"))==NULL) {
    			printf("Falha ao abrir o arquivo...");
    			getch();
				system("cls");
			}
		}
		
		fclose(arquivo);
	
	    do {
		   	mostraTempo();
			menu(opc, n);       
	        t=getch();
	
	        if(t<0) {
	            t=getch();
	            system("cls");
	
	            if(t==baixo) {
	                opc++;
	                if(opc>n-1)
	                    opc=2;
	                menu(opc, n);
	            }
	
	            else if(t==cima) {
	                opc--;
	                if(opc<2)
	                    opc=n-1;
	                menu(opc, n);
	            }
	        }
	
	        else if(t==enter) {
	            system("cls");
	
	            switch(opc)
	            {
	                case 2: cadastro(nomeArq, arquivo);
	                        break;
	                case 3: alterar(nomeArq, arquivo);
	                        break;
	                case 4: apagaReg(nomeArq, arquivo);
	                        break;
	                case 5:	consultar(nomeArq, arquivo);
	                        break;
	                case 6: excluir(nomeArq, arquivo, removido);
							voltar=0;
	                        break;
	                case 7: strcpy(nomeArq, trocarNome(nomeArq, arquivo));
	                		break;
	                case 8: remover(nomeArq, arquivo);
	                		removido=1;
	                		break;
	                case 9: listaArquivosPasta();
	                		break;
	                case 10: criaPasta();
	                		 break;
	                case 11: renomeiaPasta();
	                		 break;
	                case 12: mudarDePasta();
	                		 break;
	                case 13: mudaCor();
	                		 break;
	            }
	        }
	        
	        else if(t==esc) {
	        		system("cls");
	            	excluir(nomeArq, arquivo, removido);
	            	return 0;
			}
			
			else if(t==F1) {
				exibeAjuda();
			}
			
			else
				menu(opc, n);
	        
	    } while(voltar!=0);
	    
	}while(t!=esc);
    return 0;
}
