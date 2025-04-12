
//processos.h

#ifndef PROCESSOS_H
#define PROCESSOS_H

typedef struct {
    char id[128];
    char numero[128];
    char data[128];
    char id_classe[128];
    char id_assunto[128];
    char ano[128];
} Processo;

typedef struct {
    char id_classe[128];
    int contador;
} ClasseContador;



//Keity
// Função para verificar se o ID já existe, ou seja se é igual a outro no array. funcao 4 keity
int id_existe(char ids[][128], int total, char *id);

// Função para contar ids_assunto diferentes. funcao 4 keity
int contar_ids_assunto_diferentes(char id_assunto[], char ids_unicos[][128], int *total_ids_unicos);

// Função 5 para listar processos com id_assunto multivalorado. keity
void listar_processos_multivalorados(Processo processos[], int total_processos);



//KENAY
void contar_processos_por_classe(Processo *processos, int total);

void normalizar_id_classe(char *classe);

void remover_aspas(char *str);


//GUSTAVO
void buscar_processo_por_id(Processo *processos, int tamanho, const char *id_procurado);

void calcular_tempo_cumulativo(const char *data_ajuizamento);

int dias_no_mes(int mes, int ano);

int eh_bissexto(int ano);

//RUANITO
void Quicksort(Processo *V, int inf, int sup);
int CompararDatas(const char *data1, const char *data2);
int Particao(Processo *V, int inf, int sup);
void Swap(Processo *A, Processo *B);

//JONES
void Quicksort2(Processo *V, int inf, int sup);
int CompararIds2(const char *id1, const char *id2);
int Particao2(Processo *V, int inf, int sup);
void Swap2(Processo *A, Processo *B);



#endif
