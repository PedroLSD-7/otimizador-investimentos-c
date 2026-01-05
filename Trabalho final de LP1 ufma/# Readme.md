# Readme

# Otimizador de Investimentos em C (Estratégia Gulosa)

Este projeto em C implementa um **algoritmo guloso** para selecionar
ações de investimento com base no valor disponível pelo usuário. 
A estratégia busca **maximizar o retorno financeiro** escolhendo
ações com a **maior razão de lucro por real investido**, respeitando
o limite de orçamento fornecido.

# Objetivo

Dado um capital disponível, o programa lê uma lista de ações de um 
arquivo específico (com base no perfil do investidor) e seleciona 
a melhor combinação de ações, priorizando aquelas com **melhor custo-benefício**, 
isto é, maior **razão lucro/preço**.

# Tecnologias Utilizadas

- Definições com #define: constantes são definidas para tamanhos de strings e limites de arrays, garantindo flexibilidade e facilidade de manutenção:
  TAM_COD, TAM_DESC para tamanhos de strings.
  MAX_ACOES, MAX_LINHA para limites de vetores e buffers.

- Estruturas (struct):
  Usadas para agrupar os dados relacionados a cada ação em um único tipo (Acao).
  Campos incluem strings (cod, nome), números de ponto flutuante (preco, retorno, lucro, razao).

- Arrays Matriz e etrutura recursiva:
  Usados para armazenar a lista de ações lidas do arquivo (Acao lista[MAX_ACOES]).
  Vetores simples, unidimensionais.
  Uso de Matriz recursiva.

- Manipulação de Arquivos:
  Abrir, ler e fechar arquivos texto para obter os dados das ações (fopen, fgets, fclose).
  Análise de strings com sscanf para extrair campos.

- Manipulação de Strings:
  Uso de funções como strcpy para copiar caminhos e strings.
  Armazenamento e leitura de strings fixas com tamanho limitado.

- Algoritmo Guloso:
  Ordenação das ações baseada na razão lucro/preço.
  Seleção iterativa das ações mais vantajosas até o limite de investimento.

- Laços de repetição (for, while):
  Para ler dados, ordenar a lista, e percorrer as ações.

- Condicionais (if, else if, else):
  Para definir o arquivo de dados com base no valor investido.
  Para controlar a seleção das ações.

- Entrada e saída padrão:
  Interação com o usuário via terminal (scanf, printf).


# Como Funciona

1. O usuário informa o valor que deseja investir.
2. Com base no valor, o programa escolhe um dos quatro arquivos:
   - `iniciante.txt`
   - `moderado.txt`
   - `dificil.txt`
   - `expert.txt`
3. Cada arquivo contém uma lista de ações com:
   - Código
   - Preço
   - Retorno percentual
   - Nome
4. O programa calcula, para cada ação:
   - Lucro: `preco * retorno / 100`
   - Razão: `lucro / preco` (eficiência)
5. As ações são ordenadas da maior para a menor razão.
6. A estratégia gulosa seleciona as melhores ações até consumir todo o valor disponível.
7. Mostra as ações escolhidas, total investido, lucro e soma dos retornos.


# Exemplo de Entrada de Arquivo

Formato de cada linha do arquivo:

<COD> <PREÇO> <RETORNO_PERCENTUAL> <NOME>

exemplo:

A 4500.50 5.5 US_BANK
B 6200.75 7.8 EU_AUTO
C 3800.25 4.9 JP_ELEC


# Regras
> - Código: até 3 caracteres
> - Nome: até 19 caracteres
> - Os campos são separados por espaços


# Arquivos por Perfil de Investidor

| Faixa de Investimento      | Arquivo Usado              |
|----------------------------|----------------------------|
| Abaixo de 250              | Não é permitido investir   |
| De 250 a 1.000             | iniciante.txt              |
| De 1.001 a 38.000          | moderado.txt               |
| De 38.001 a 65.000         | dificil.txt                |
| Acima de 65.000            | expert.txt                 |

> Os arquivos devem estar localizados em:
> `C:\Users\user\OneDrive\Desktop\TRABALHOFINALLPI\`

# Atenção: Caminho dos Arquivos
O programa utiliza caminhos absolutos para abrir os arquivos .txt.
Esses caminhos funcionam apenas na máquina onde foram definidos.

Exemplo de caminho absoluto:

> C:\Users\erick\OneDrive\Desktop\TRABALHOFINALLPI\moderado.txt

# Se você for executar o programa em outro computador, verifique:

> Se os arquivos .txt estão disponíveis.
> Se o caminho está correto de acordo com o nome do usuário e pastas do sistema.
> Você pode editar os caminhos no código-fonte (main()) conforme necessário.

# Para evitar esse problema, você pode colocar os arquivos na mesma pasta do executável e usar apenas os nomes dos arquivos, assim:

`strcpy(caminho, "moderado.txt");`

# Funcionamento

1. O usuário informa quanto deseja investir.
2. O programa escolhe o arquivo correto com base no valor informado.
3. As ações são lidas e para cada uma é calculado:
   - `lucro = preco * retorno / 100`
   - `razao = lucro / preco` (eficiência do investimento)
4. As ações são ordenadas pela razão (maior primeiro).
5. O algoritmo seleciona as ações mais rentáveis enquanto houver orçamento.


# Como Compilar

>bash
`gcc otimizador_guloso.c -o otimizador`

# Execução
No terminal:

# dash
./otimizador

O programa perguntará:
Qual o valor de investimento?

# yaml

Qual o valor de investimento? 1000

# E então mostrará:

- Ações disponíveis
- Ações selecionadas pela estratégia gulosa
- Total investido
- Lucro esperado
- Soma dos retornos percentuais

# xemplo de saída para diferentes valores de investimento
> Investimento: 10.000

ACOES DISPONIVEIS
COD  PRECO     RETORNO    NOME
A    4500.50    5.50%     US_BANK
B    6200.75    7.80%     EU_AUTO
C    3800.25    4.90%     JP_ELEC
D    7100.00    8.90%     CN_TECH
E    5500.60    6.50%     UK_PHARMA

MELHOR COMBINACAO DE INVESTIMENTO
COD  PRECO     RETORNO    NOME
D    7100.00    8.90%     CN_TECH
C    3800.25    4.90%     JP_ELEC

TOTAL INVESTIDO: R$ 10900.25
LUCRO ESPERADO: R$ 818.11
SOMA DAS PORCENTAGENS DE RETORNO: 13.80%

# Explicação da Estratégia Gulosa

A cada passo, o programa escolhe a ação com a maior razão lucro/preço que
ainda cabe no orçamento restante. Isso garante uma boa eficiência em termos
de retorno por real investido, mesmo que não explore todas as combinações
possíveis (como faria a força bruta). É mais rápida e funciona muito bem em
cenários com muitas ações.

# Vantagens
- Simples e eficiente
- Muito mais rápida que algoritmos exaustivos
- Ideal para arquivos grandes


# Autores
- Ericksen Renan Araujo Fernandes
- Renan Gomes
- Pedro Luis Silva Dias


