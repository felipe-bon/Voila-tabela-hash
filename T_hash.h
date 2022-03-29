
struct urls{

    char URL_longo[100], URL_curto[50];

};typedef struct urls URLs;

struct hash{

    int qtd, tamanho_tabela;
    URLs **itens;

};typedef struct hash Hash;

Hash* cria_hash(int tamanho_tabela);
void libera_hash(Hash* hash);
int valor_URL_curto(char *URL_curto);
int chave_divisao(int chave, int tamanho_tabela);
int insere_endere_aberto(Hash *h, struct urls U);
int sondagem_linear(int pos, int i, int tamanho_tabela);
int busca_endere_aberto(Hash* h, char *url_curto, struct urls* U);
int remove_par(Hash* h, char *url_curto, struct urls* U);