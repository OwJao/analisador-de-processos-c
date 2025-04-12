

//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processos.h"

int main() {
    FILE *f = fopen("processo_043_202409032338.csv", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int capacidade = 200;
    Processo *processos = malloc(capacidade * sizeof(Processo));
    if (processos == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(f);
        return 1;
    }

    char linha[1024];
    int i = 0;


  	char cabecalho[100];
    fgets(cabecalho, sizeof(linha), f); // Ignora o cabeçalho
    
    // Array para armazenar os IDs de assunto únicos. keity
    char ids_unicos[1000][128];  // Supondo que haja no máximo 1000 IDs únicos
    int total_ids_unicos = 0;
	//
	
    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (i >= capacidade) {
            capacidade *= 2;  // Dobra a capacidade
            processos = realloc(processos, capacidade * sizeof(Processo));
            if (processos == NULL) {
                printf("Erro de realocação de memória.\n");
                fclose(f);
                return 1;
            }
        }

        char *token;
        token = strtok(linha, ",");
        strncpy(processos[i].id, token, sizeof(processos[i].id));

        token = strtok(NULL, ",");
        strncpy(processos[i].numero, token, sizeof(processos[i].numero));

        token = strtok(NULL, ",");
        strncpy(processos[i].data, token, sizeof(processos[i].data));

        // ID_CLASSE
        token = strtok(NULL, ",");
        if (token && token[0] == '"') {  // Se começa com aspas, juntar corretamente
            char temp[256];
            strcpy(temp, token);
            while ((token = strtok(NULL, ",")) != NULL) {
                strcat(temp, ",");
                strcat(temp, token);
                if (temp[strlen(temp) - 1] == '"') break;  // Parar ao encontrar a aspa de fechamento
            }
            strncpy(processos[i].id_classe, temp, sizeof(processos[i].id_classe));
            remover_aspas(processos[i].id_classe);
        } else {
            strncpy(processos[i].id_classe, token, sizeof(processos[i].id_classe));
        }

        // ID_ASSUNTO
        token = strtok(NULL, ",");
        if (token && token[0] == '"') {  // Se começa com aspas, juntar corretamente
            char temp[256];
            strcpy(temp, token);
            while ((token = strtok(NULL, ",")) != NULL) {
                strcat(temp, ",");
                strcat(temp, token);
                if (temp[strlen(temp) - 1] == '"') break;  // Parar ao encontrar a aspa de fechamento
            }
            strncpy(processos[i].id_assunto, temp, sizeof(processos[i].id_assunto));
            remover_aspas(processos[i].id_assunto);
        } else {
            strncpy(processos[i].id_assunto, token, sizeof(processos[i].id_assunto));
        }

        token = strtok(NULL, "\n");
        strncpy(processos[i].ano, token, sizeof(processos[i].ano));

		//printf("%s\t%s\t%s\t%s\t%s\t%s\n", processos[i].id, processos[i].numero, processos[i].data,
        //processos[i].id_classe, processos[i].id_assunto, processos[i].ano);
             
        // Chama a função para contar os IDs de assunto únicos. funcao 4 keity
        // Passando uma cópia da string para a função contar_ids_assunto_diferentes para não alterar a original
        char id_assunto_copy[128];
        strncpy(id_assunto_copy, processos[i].id_assunto, sizeof(id_assunto_copy));
        contar_ids_assunto_diferentes(id_assunto_copy, ids_unicos, &total_ids_unicos);
				
        i++;
      
    }
    
    
    
	//AGORA EU SEI. UMA LINHA DO CABECALHO E OUTRA DO 0 DO VETOR
	//240 - 2 = id_assunto multivalorado
	
    /*printf("\nValor do processo:\n");
    if (i > 240) {
        printf("%s\n", processos[240].id_assunto);
    } else {
        printf("Menos de 15 processos no arquivo.\n");
    }*/
	
	//funcao 4 keity
    //Total de IDs de assunto únicos.
    printf("\nTotal de IDs de assunto diferentes: %d\n\n\n", total_ids_unicos);
    // Exibe os IDs únicos.
    /*int j;
    for (j = 0; j < total_ids_unicos; j++) {
        printf("%s\n", ids_unicos[j]);
    }*/
    
    //GUSTAVO
    char id_procurado[128];
    printf("Digite o ID do processo: ");
    scanf("%s", id_procurado);

    buscar_processo_por_id(processos, i, id_procurado);
    
    //Keity
   	listar_processos_multivalorados(processos, i);
   
   
   // Contar processos para cada id_classe - KENAY
    contar_processos_por_classe(processos, i);
    
    
    //RUANITO
    Quicksort(processos, 0, i - 1);

    FILE *arquivo = fopen("decrescente_data_ajuizamento.csv", "w"); // "w" cria um novo arquivo
    fprintf(arquivo, "%s", cabecalho);
    int j;
    for (j = 0; j < i; j++) {
        fprintf(arquivo, "%s\t%s\t%s\t%s\t%s}\t%s\n",
               processos[j].id, processos[j].numero, processos[j].data,
               processos[j].id_classe, processos[j].id_assunto, processos[j].ano);
    }
    
    //JONES
    Quicksort2(processos, 0, i - 1);

    FILE *arquivo2 = fopen("crescente_id.csv", "w"); // "w" cria um novo arquivo
    fprintf(arquivo2, "%s", cabecalho);
	for (j = 0; j < i; j++) {
        fprintf(arquivo2, "%s\t%s\t%s\t%s\t%s}\t%s\n",
               processos[j].id, processos[j].numero, processos[j].data,
               processos[j].id_classe, processos[j].id_assunto, processos[j].ano);
    }


    
    free(processos);
    fclose(f);
    return 0;
}

