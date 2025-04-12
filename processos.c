

//processos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processos.h"


/*inicio keity funcao 4*/
// Função para verificar se o ID já existe, ou seja, se é igual a outro no array.
int id_existe(char ids[][128], int total, char *id) {
	int i;
    for (i = 0; i < total; i++) {
        if (strcmp(ids[i], id) == 0) {
            return 1;  // ID já existe
        }
    }
    return 0;
}
// Função para contar ids_assunto diferentes.
int contar_ids_assunto_diferentes(char id_assunto[], char ids_unicos[][128], int *total_ids_unicos) {
    // Verificar se o id_assunto tem IDs no formato multivalorado
    if (id_assunto[0] == '{' && id_assunto[strlen(id_assunto) - 1] == '}') { // Remover as chaves { }
    
        id_assunto[strlen(id_assunto) - 1] = '\0'; // Remove o '}' final
        char *start = id_assunto + 1; // Pular a chave inicial '{'
			
        char *token = strtok(start, ","); // Separar os IDs pela vírgula
        while (token) {
            // Verificar se o ID já existe antes de adicionar
            if (!id_existe(ids_unicos, *total_ids_unicos, token)) {
                strncpy(ids_unicos[*total_ids_unicos], token, 128);
                (*total_ids_unicos)++;
            }
            token = strtok(NULL, ",");  // Próximo ID na lista
        }
    } else {
        // Caso não seja multivalorado, verificar se o ID existe
        if (!id_existe(ids_unicos, *total_ids_unicos, id_assunto)) {
            strncpy(ids_unicos[*total_ids_unicos], id_assunto, 128);
            (*total_ids_unicos)++;
        }
    }

    return *total_ids_unicos;
}

//Função 5 
void listar_processos_multivalorados(Processo processos[], int total_processos) {
    printf("Processos com ID de Assunto multivalorado:\n");
    int i;
    for (i = 0; i < total_processos; i++) {
        if (processos[i].id_assunto[0] == '{' && processos[i].id_assunto[strlen(processos[i].id_assunto) - 1] == '}') {
            // Verifica se há mais de um ID dentro das chaves
            char *conteudo = processos[i].id_assunto + 1; // Pula a primeira chave '{'
            conteudo[strlen(conteudo) - 1] = '\0'; // Remove a última chave '}'

            if (strchr(conteudo, ',') != NULL) { // Se houver vírgula, há mais de um ID
                printf("%d - %s\t%s\t%s\t%s\t%s}\t%s\n", i+2, processos[i].id, processos[i].numero, processos[i].data,
        			processos[i].id_classe, processos[i].id_assunto, processos[i].ano);
            }
        }
    }
}


/*fim keiy*/



/*KENAY*/
void remover_aspas(char *str) {
    int len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

// Função para remover chaves e espaços extras de um ID de classe
void normalizar_id_classe(char *classe) {
    int len = strlen(classe);
    
    // Remover espaços no início e fim
    while (len > 0 && (classe[0] == ' ' || classe[0] == '{')) {
        memmove(classe, classe + 1, len--);
    }
    while (len > 0 && (classe[len - 1] == ' ' || classe[len - 1] == '}')) {
        classe[--len] = '\0';
    }
}

//CONTAR PROCESSOS
void contar_processos_por_classe(Processo *processos, int total) {
    ClasseContador *classes = malloc(total * sizeof(ClasseContador));
    int num_classes = 0;
    int i, j;

    if (classes == NULL) {
        printf("Erro ao alocar memória para contagem de classes.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        char classe_atual[128];
        strcpy(classe_atual, processos[i].id_classe);
        remover_aspas(classe_atual);
        classe_atual[strcspn(classe_atual, "\n")] = '\0'; // Remove quebras de linha

        // Separar múltiplos valores por vírgula
        char *token = strtok(classe_atual, ",");
        while (token != NULL) {
            char classe_unica[128];
            strcpy(classe_unica, token);
            normalizar_id_classe(classe_unica);

            // Verificar se essa classe já foi registrada antes (mesmo com variações)
            int encontrado = 0;
            for (j = 0; j < num_classes; j++) {
                if (strcmp(classes[j].id_classe, classe_unica) == 0) {
                    classes[j].contador++;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(classes[num_classes].id_classe, classe_unica);
                classes[num_classes].contador = 1;
                num_classes++;
            }

            token = strtok(NULL, ","); // Próximo valor
        }
    }

    printf("\nContagem de processos por id_classe:\n");
    for (i = 0; i < num_classes; i++) {
        printf("%s: %d processos\n", classes[i].id_classe, classes[i].contador);
    }

    free(classes);
}

/*FIM KENAY*/



/*GUSTAVO*/
void buscar_processo_por_id(Processo *processos, int tamanho, const char *id_procurado) {
    
    int i;
	for (i = 0; i < tamanho; i++) {
        if (strcmp(processos[i].id, id_procurado) == 0) {
            printf("\nProcesso encontrado!\n");
            printf("ID: %s\n", processos[i].id);
            printf("Numero: %s\n", processos[i].numero);
            printf("Data de ajuizamento: %s\n", processos[i].data);
            calcular_tempo_cumulativo(processos[i].data);
            return;
        }
    }
    printf("\nProcesso com ID %s nao encontrado.\n", id_procurado);
}

void calcular_tempo_cumulativo(const char *data_ajuizamento) {
    struct tm data = {0};
    time_t hoje;
    struct tm *data_atual;

    int ano, mes, dia;
    if (sscanf(data_ajuizamento, "%4d-%2d-%2d", &ano, &mes, &dia) != 3) {
        printf("Erro ao interpretar a data.\n");
        return;
    }

    data.tm_year = ano - 1900;
    data.tm_mon = mes - 1;
    data.tm_mday = dia;

    time(&hoje);
    data_atual = localtime(&hoje);

    int anos = data_atual->tm_year + 1900 - ano;
    int meses = data_atual->tm_mon + 1 - mes;
    int dias = data_atual->tm_mday - dia;

    if (dias < 0) {
        meses--;
        dias += dias_no_mes((mes == 1 ? 12 : mes - 1), (mes == 1 ? ano - 1 : ano));
    }

    if (meses < 0) {
        anos--;
        meses += 12;
    }

    int total_dias = 0;
    
    int i;
	for (i = ano; i < data_atual->tm_year + 1900; i++) {
        total_dias += eh_bissexto(i) ? 366 : 365;
    }

    for (i = 1; i < mes; i++) {
        total_dias -= dias_no_mes(i, ano);
    }
    for (i = 1; i < data_atual->tm_mon + 1; i++) {
        total_dias += dias_no_mes(i, data_atual->tm_year + 1900);
    }

    total_dias -= dia;
    total_dias += data_atual->tm_mday;

    printf("Se passaram %d anos, %d meses e %d dias.\n", anos, meses, dias);
    printf("Totalizando aproximadamente %d dias.\n", total_dias);
}


int dias_no_mes(int mes, int ano) {
    int dias_por_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && eh_bissexto(ano)) {
        return 29;
    }
    return dias_por_mes[mes - 1];
}

int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}
/*FIM GUSTAVO*/



/*RUANITO*/
// Função para ordenar em ordem decrescente por data
void Quicksort(Processo *V, int inf, int sup) {
    if (inf < sup) {
        int P = Particao(V, inf, sup);
        Quicksort(V, inf, P - 1);
        Quicksort(V, P, sup);
    }
}

int CompararDatas(const char *data1, const char *data2) {
    return strcmp(data2, data1); // Ordem decrescente
}

int Particao(Processo *V, int inf, int sup) {
    Processo Pivot = V[(inf + sup) / 2];
    int i = inf;
    int j = sup;

    while (i <= j) {
        while (CompararDatas(V[i].data, Pivot.data) < 0) i++;
        while (CompararDatas(V[j].data, Pivot.data) > 0) j--;
        if (i <= j) {
            Swap(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}

void Swap(Processo *A, Processo *B) {
    Processo temp = *A;
    *A = *B;
    *B = temp;
}

/*FIM RUANITO*/



/*JONES*/
void Quicksort2(Processo *V, int inf, int sup) {
    if (inf < sup) {
        int P = Particao2(V, inf, sup);
        Quicksort2(V, inf, P - 1);
        Quicksort2(V, P, sup);
    }
}

int CompararIds2(const char *id1, const char *id2) {
    return strcmp(id1, id2); 
}

int Particao2(Processo *V, int inf, int sup) {
    Processo Pivot = V[(inf + sup) / 2];
    int i = inf;
    int j = sup;

    while (i <= j) {
        while (CompararIds2(V[i].id, Pivot.id) < 0) i++;
        while (CompararIds2(V[j].id, Pivot.id) > 0) j--;
        if (i <= j) {
            Swap2(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}

void Swap2(Processo *A, Processo *B) {
    Processo temp = *A;
    *A = *B;
    *B = temp;
}
/*FIM JONES*/

