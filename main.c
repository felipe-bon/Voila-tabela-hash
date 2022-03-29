#include <stdio.h>
#include <stdlib.h>
#include "T_hash.h"

#define TM_TB_HASH 1213

// checa para saber se é windows OS
// _WIN32 macro
#ifdef _WIN32
    #define limpar "cls"
  
// checa para saber se é linux OS 
// __linux__ macro
#elif __linux__
    #define limpar "clear"
  
#endif 

void menu_P(); 

int main()
{
   int flag = 0, CM = 0; // CM = comando
   char urlAUX[100];
   URLs Uaux;
   Hash *h;

   while(flag == 0)
   {
      menu_P();
      scanf("%d", &CM);

      if(CM == 6)
      {
         system(limpar);
         printf("\nPROGRAMA ENCERRADO!\n");
         return 0;
      }

      if(CM != 1)
      {
         system(limpar);
         printf("EH PRECISO CRIAR UMA TABELA HASH PRIMEIRO!\n    USE A OPERACAO [1]\n\n");
      }
      else
      {
         h = cria_hash(TM_TB_HASH);
         flag = 1;
         system(limpar);
         printf("TABELA HASH CRIADA COM SUCESSO!\n\n");
      }

      while(flag != 0)
      {

        menu_P();

        setbuf(stdin, NULL);
        scanf("%d", &CM);

        switch (CM)
        {
            case 1:
            system(limpar);
            printf("UMA TABELA HASH JÁ FOI CRIADA E ESTÁ EM USO!\n");
            printf("PARA CRIAR OUTRA APAGUE A ATUAL USANDO [5]!\n\n"); 																				// adequado para apagar a lista atual
            break;

            case 2:
            system(limpar);
            printf("Insira a URL longa: ");
            scanf("%s", Uaux.URL_longo);
            printf("Insira a URL curta: ");
            scanf("%s", Uaux.URL_curto);
            if(insere_endere_aberto(h, Uaux))
               printf("URL's inseridas com sucesso\n");
            else
               printf("erro ao inserir URLs\n");
            break;

            case 3:
            system(limpar);
            printf("buscar URL longa usando URL curta\n");
            printf("digite a URL curta: ");
            scanf("%s",urlAUX);
            if(busca_endere_aberto(h, urlAUX, &Uaux)){
               printf("URL longo: %s\n", Uaux.URL_longo);
               printf("URL curto: %s\n", Uaux.URL_curto);
            }
            else
               printf("Par de URL's nao encontrado\n");
            break;
            
            case 4:
            system(limpar);
            printf("digite a URL curta do par para ser apagdo: ");
            scanf("%s", urlAUX);
            if(remove_par(h, urlAUX, &Uaux))
               printf("par removido com sucesso\n");
            else
               printf("erro ao remover par\n");
            break;
            
            case 5:
            system(limpar);
            libera_hash(h);
            printf("tabela hash apagada com sucesso\n");
            flag = 0;
            break;

            case 6:  
            system(limpar);
            printf("\nPROGRAMA ENCERRADO!\n");
            return 0;

            default:  
            system(limpar);
            printf("%d EH UM COMANDO INVALIDO!\n\n", CM);
            setbuf(stdin,NULL);
         }

      }

   }

   return 0;
}

void menu_P()
{	
	
   printf("     MENU PRINCIPAL\n\n");
   printf(" [1] Criar tabela hash\n");			
   printf(" [2] Inserir par (chave, valor)\n");	
   printf(" [3] Buscar URL longo por URL curto\n");
   printf(" [4] Remover par (chave, valor)\n");
   printf(" [5] Apagar tabela hash\n");
   printf(" [6] Encerrar Programa\n");
}