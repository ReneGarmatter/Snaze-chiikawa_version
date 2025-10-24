
# Snaze — Snake (simulador / solver) em C++

Uma implementação simples de uma simulação automática do jogo Snake que lê mapas (puzzles) de arquivos,
encontra caminhos até itens (comida) usando busca em largura (BFS) e simula o movimento no terminal.

Sumário rápido
- Linguagem: C++17
- Compilação: Makefile (gera `bin/snaze`)
- Diretório de mapas: `assets/` (cada arquivo de mapa é um puzzle que o programa lê)

Requisitos
- g++ com suporte a C++17 (g++ 7+ recomendado)
- make

Compilando

No diretório raiz do projeto:

```bash
make
```

Isso compila os fontes em `source/` e produz `bin/snaze`.

Executando

```bash
./bin/snaze
```

Ao iniciar o programa você será solicitado a selecionar um mapa (a partir dos arquivos em `assets/`) e
quantas rodadas (apples) deseja que apareçam. A simulação então roda no terminal, atualizando o mapa.

Formato esperado dos arquivos de mapa (assets)
- O parser espera arquivos de texto com o primeiro linha contendo duas inteiros: número de linhas e colunas.
- As linhas seguintes representam o grid com caracteres:
  - `#` — parede
  - ` ` (espaço) ou `.` — chão / espaço vazio
  - `&` — posição inicial do 'snake' (spawn)
  - outras letras podem ser usadas no mapa, mas `&` é obrigatória como ponto inicial

Exemplo mínimo (map.txt):

```
5 7
#######
#     #
# &   #
#     #
#######
```


