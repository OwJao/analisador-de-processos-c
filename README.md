# Análise de Processos Judiciais em C

Este projeto em C realiza a leitura, análise e organização de dados de processos judiciais a partir de um arquivo CSV. Ele oferece funcionalidades como contagem de IDs únicos, ordenação por data e ID, busca por identificador e estatísticas por classe processual.

## 📁 Estrutura do Projeto

- `main.c`: Função principal responsável pela leitura do CSV e chamada das funções de análise.
- `processos.c`: Implementação das funções de manipulação e análise dos dados.
- `processos.h`: Definições das estruturas e declarações de funções.

## ⚙️ Funcionalidades

- Leitura de processos a partir de um CSV
- Contagem de IDs de assunto únicos
- Listagem de processos com IDs multivalorados
- Contagem de processos por classe
- Busca por ID de processo
- Ordenação decrescente por data de ajuizamento
- Ordenação crescente por ID

## 🧪 Execução

Para compilar o projeto, utilize um compilador C como `gcc`:

```bash
gcc main.c processos.c -o analisador.exe
