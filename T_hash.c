#include "T_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hash* cria_hash(int tamanho_tabela){
    Hash *h = (Hash*) malloc(sizeof(Hash));
    if(h != NULL){
        int i;
        h->tamanho_tabela = tamanho_tabela;
        h->itens = (struct urls**) malloc (tamanho_tabela*sizeof(struct urls));
        if(h->itens == NULL){
            free(h);
            return NULL;
        }
        h->qtd = 0;
        for(i = 0; i < h->tamanho_tabela; i++)
            h->itens[i] = NULL;
    }
    return h;
}

void libera_hash(Hash* h){
    if(h != NULL){
        int i;
        for(i = 0; i < h->tamanho_tabela; i++){
            if(h->itens[i] != NULL)
                free(h->itens[i]);
        }
        free(h->itens);
        free(h);
    }
}

int valor_URL_curto(char *URL_curto){
    int i, valor = 7;
    int tamanho = strlen(URL_curto);
    for(i = 0; i < tamanho; i++)
        valor = 31 * valor + (int) URL_curto[i];

    return valor;
}

int chave_divisao(int chave, int tamanho_tabela){
    return (chave & 0x7fffffff) % tamanho_tabela;
}

int sondagem_linear(int pos, int i, int tamanho_tabela){
    return((pos+1) & 0x7fffffff) % tamanho_tabela;
}

int insere_endere_aberto(Hash *h, struct urls U){

    if(h == NULL || h->qtd == h->tamanho_tabela)
        return 0;

    int chave = valor_URL_curto(U.URL_curto);
    int i, pos, nova_pos;
    pos = chave_divisao(chave, h->tamanho_tabela);
    for(i = 0; i < h->tamanho_tabela; i++){
        nova_pos = sondagem_linear(pos,i,h->tamanho_tabela);
        if(h->itens[nova_pos] == NULL){
            struct urls* nova;
            nova = (struct urls*) malloc (sizeof(struct urls));
            if(nova == NULL)
                return 0;

            *nova = U;
            h->itens[nova_pos] = nova;
            h->qtd++;
            return 1;
        }
    } 
    return 0;   
}

int busca_endere_aberto(Hash* h, char *url_curto, struct urls* U){
    if(h == NULL)
        return 0;

    int i, pos, nova_pos;

    pos = chave_divisao(valor_URL_curto(url_curto), h->tamanho_tabela);
    for(i = 0; i < h->tamanho_tabela; i++){
        nova_pos = sondagem_linear(pos, i, h->tamanho_tabela);
        if(h->itens[nova_pos] == NULL)
            return 0;
        if(strcmp(h->itens[nova_pos]->URL_curto,url_curto) == 0){
            *U = *(h->itens[nova_pos]);
            return 1;
        }
    }
    return 0;
}

int remove_par(Hash* h, char *url_curto, struct urls* U){

    if(h == NULL)
        return 0;

    int i, pos, nova_pos;

    pos = chave_divisao(valor_URL_curto(url_curto), h->tamanho_tabela);
    for(i = 0; i < h->tamanho_tabela; i++){
        nova_pos = sondagem_linear(pos, i, h->tamanho_tabela);
        if(h->itens[nova_pos] == NULL)
            return 0;
        if(strcmp(h->itens[nova_pos]->URL_curto,url_curto) == 0){
            free(h->itens[i]);
            return 1;
        }
    }

    return 0;
}