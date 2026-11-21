# Controle de Gastos e Orçamento Pessoal (C)

Projeto prático em dupla da disciplina de **Linguagem de Programação** — FATEC.
Aplicação de console modularizada (TAD) em C, com **vetor de ponteiros**, **alocação dinâmica** e **persistência em arquivo texto**.

---

## 1. Identificação da dupla

| Nome completo | RA |
|---|---|
| `Bruno Henrique Assenço` | `1630482613033` |
| `Caio Hideki Gomes Kawati` | `1630482613008` |

- **Disciplina:** Linguagem de Programação
- **Professor:** Marcos Roberto de Moraes
- **Curso:** Análise e Desenvolvimento de Sistemas (ADS)
- **Data de entrega:** 21/11/2026

---

## 2. Tema escolhido e motivo

**Tema 9 — Controle de Gastos e Orçamento Pessoal.**

Cada despesa possui: código, categoria, descrição, mês (MM/AAAA) e valor pago.

**Motivo da escolha:**

Escolhemos o tema de Controle de Gastos e Orçamento Pessoal por ser um assunto do dia a dia, fácil de entender e de testar. Os dados de uma despesa (código, categoria, descrição, mês e valor) se encaixam bem em uma struct, o que nos permitiu praticar ponteiros, alocação dinâmica e manipulação de arquivos. Além disso, o relatório de custo total e maior despesa é simples de conferir, o que ajudou a validar se o programa estava funcionando corretamente.

---

## 3. Funcionalidades

O sistema apresenta um menu no console com as ações:

| Opção | Ação | Descrição |
|---|---|---|
| 1 | Cadastrar | Lê os dados do teclado, aloca memória com `malloc` e guarda o ponteiro na primeira posição livre do vetor |
| 2 | Listar | Percorre o vetor e exibe todas as despesas cadastradas |
| 3 | Buscar | Localiza uma despesa pelo código e exibe os detalhes |
| 4 | Relatório | Mostra o **custo total acumulado** e a **despesa de maior valor** |
| 5 | Salvar e sair | Grava tudo em `dados.txt`, libera a memória e encerra |

Ao iniciar, o programa carrega automaticamente os dados de `dados.txt`. Se o arquivo não existir, o sistema começa vazio, sem erro.

---

## 4. Estrutura do repositório

```
projeto-dupla/
│
├── despesas.h    # Interface (TAD): struct, #define, typedef e protótipos
├── despesas.c    # Implementação das operações do TAD
├── main.c        # Ponto de entrada, menu e navegação
├── dados.txt     # Arquivo de persistência (gerado/lido pela aplicação)
└── README.md     # Documentação
```

---

## 5. Relato de modelagem e organização

### 5.1 Divisão de tarefas

| Integrante | Responsabilidades |
|---|---|
| `Bruno Henrique Assenço` | `despesas.h, funções carregar/salvar, README` |
| `Caio Hideki Gomes Kawati` | `main.c, funções cadastrar/listar/buscar/relatório, testes` |

### 5.2 Arquitetura (TAD)

O projeto foi separado em três arquivos, seguindo o modelo de Tipo Abstrato de Dados:

- **`despesas.h` (interface):** define `MAX` (capacidade máxima de 100 registros), a `struct` da despesa com `typedef` e os protótipos de todas as funções.
- **`despesas.c` (implementação):** contém o código de cada função declarada no `.h`.
- **`main.c` (aplicação):** declara o vetor de ponteiros, inicializa tudo com `NULL`, carrega os dados e executa o laço do menu (`do...while` com `switch`).

### 5.3 Estrutura de dados

```c
#define MAX 100

typedef struct {
    int codigo;
    char categoria[30];
    char descricao[50];
    char mes[10];
    float valor;
} Despesa;
```

Os dados ficam em um **vetor de ponteiros** (`Despesa *vetor[MAX]`), e não em um vetor estático de structs. Assim, só se reserva memória para as despesas que realmente existem: cada posição começa em `NULL` e recebe um endereço quando o registro é criado com `malloc(sizeof(Despesa))`.

### 5.4 Funções do TAD

| Função | O que faz |
|---|---|
| `carregar(vetor)` | Abre `dados.txt` em modo `"r"`. Se não existir, retorna sem erro. Lê linha a linha com `fgets` e preenche a struct com `sscanf`, alocando cada registro |
| `salvar(vetor)` | Abre `dados.txt` em modo `"w"`, percorre o vetor e grava cada registro não nulo com `fprintf` |
| `cadastrar(vetor)` | Procura a primeira posição `NULL`, aloca memória e lê os campos. Informa se o vetor estiver cheio ou faltar memória |
| `listar(vetor)` | Exibe todos os registros não nulos |
| `buscar(vetor)` | Busca por código e exibe os detalhes, ou informa que não encontrou |
| `relatorio(vetor)` | Calcula o custo total e identifica a despesa de maior valor |
| `liberar(vetor)` | Executa `free()` em cada posição não nula |

### 5.5 Decisões de projeto

- **Formato do arquivo:** um registro por linha, campos separados por ponto e vírgula (`;`), o que facilita a leitura com `sscanf` e o formato `%[^;]`.
- **Verificações de erro:** o retorno de `fopen` e de `malloc` é sempre testado antes do uso.
- **Fechamento de arquivos:** todo `FILE *` aberto é fechado com `fclose()`.
- **Memória:** ao escolher "Salvar e sair", o programa grava os dados e só então libera cada ponteiro.
- **Comentários no código:** as funções foram comentadas passo a passo para facilitar o entendimento e a manutenção.

### 5.6 Formato do `dados.txt`

```
codigo;categoria;descricao;mes;valor
```

Exemplo:

```
1;Moradia;Aluguel;11/2026;1200.00
2;Alimentacao;Mercado;11/2026;450.50
3;Transporte;Combustivel;11/2026;220.00
```

> Atenção: como o `;` é o separador, evite usá-lo nos textos de categoria e descrição.

---

## 6. Como compilar e executar

### Requisitos

- Compilador **GCC** (Linux, macOS, ou Windows via MinGW / MSYS2 / WSL)

### Compilação

Na pasta do projeto, execute:

```bash
gcc main.c despesas.c -o gastos
```

Para ver avisos do compilador (recomendado):

```bash
gcc -Wall -Wextra main.c despesas.c -o gastos
```

### Execução

**Linux / macOS / WSL:**

```bash
./gastos
```

**Windows (Prompt de Comando ou PowerShell):**

```bash
gastos.exe
```

### Usando uma IDE (Code::Blocks, Dev-C++ etc.)

1. Crie um projeto de console em C.
2. Adicione os três arquivos: `main.c`, `despesas.c` e `despesas.h`.
3. Compile e execute (o `dados.txt` será criado na pasta de execução).

---

## 7. Exemplo de uso

```
1 - Cadastrar
2 - Listar
3 - Buscar
4 - Relatorio
5 - Salvar e sair
Opcao: 1
Codigo: 1
Categoria: Moradia
Descricao: Aluguel
Mes (MM/AAAA): 11/2026
Valor: 1200

Opcao: 4
Custo total: R$ 1200.00
Maior despesa: Aluguel - R$ 1200.00
```

---

## 8. Requisitos do projeto atendidos

- [x] Arquitetura modular com `.h`, `.c` e `main.c`
- [x] `#define MAX` e vetor de ponteiros para a struct
- [x] Todos os ponteiros inicializados com `NULL`
- [x] Alocação dinâmica sob demanda com `malloc(sizeof(...))`
- [x] Liberação da memória com `free()` antes de encerrar
- [x] Carga de dados no início (`fopen "r"`, `fgets` e `sscanf`), iniciando vazio se não houver arquivo
- [x] Gravação em arquivo texto (`fopen "w"` e `fprintf`)
- [x] Fechamento de todos os `FILE *` com `fclose()`
- [x] Menu com `do...while` e `switch` (cadastrar, listar, buscar, relatório, salvar e sair)
- [x] Struct com mais de 4 campos de tipos variados (inteiro, strings e ponto flutuante)

---

## 9. Possíveis melhorias futuras

- Impedir códigos repetidos no cadastro
- Validar o formato do mês (MM/AAAA) e valores negativos
- Limitar o tamanho das entradas para evitar estouro de buffer
- Opções de editar e excluir despesas
- Relatório por categoria e por mês
- Versão web do sistema

---

## 10. Observações para o professor

> [!NOTE]
> Alguns pontos do trabalho foram feitos com auxílio de Inteligência Artificial, como soluções em algumas dificuldades quanto a lógica, e também na construção de alguns pontos do código, como:

---

### 🔹 String de formato

Trecho da função `carregar` (`despesas.c`), que lê cada linha do `dados.txt` e separa os campos da struct:

```c
sscanf(linha, "%d;%[^;];%[^;];%[^;];%f",
       &vetor[i]->codigo,
       vetor[i]->categoria,
       vetor[i]->descricao,
       vetor[i]->mes,
       &vetor[i]->valor);
```

> **Comentário:** a construção desse formato, que é o inverso do usado no `fprintf` da função `salvar`, teve ajuda de IA para entender o funcionamento do `%[^;]` e aplicar ao trabalho.

---

### 🔹 Uso do operador seta (`->`)

Trecho da função `listar` (`despesas.c`), que percorre o vetor de ponteiros e exibe as despesas cadastradas:

```c
for (i = 0; i < MAX; i++) {
    if (vetor[i] != NULL) {
        printf("%d | %s | %s | %s | R$ %.2f\n",
               vetor[i]->codigo,
               vetor[i]->categoria,
               vetor[i]->descricao,
               vetor[i]->mes,
               vetor[i]->valor);
    }
}
```

> **Comentário:** trechos com o uso da seta (`->`) teve ajuda de IA para entender seu funcionamento e aplicar ao trabalho.

---

## 11. Autores

- `Bruno Henrique Assenço` — RA `1630482613033`
- `Caio Hideki Gomes Kawati` — RA `1630482613008`
