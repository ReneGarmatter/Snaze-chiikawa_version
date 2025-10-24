
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

Problemas comuns e solução rápida
- `terminate called after throwing an instance of 'std::runtime_error'` — `directory not found`:
  - O programa tenta ler arquivos em `assets/` relativo ao diretório de trabalho atual.
  - Execute o binário a partir do diretório do projeto (onde existe a pasta `assets/`):

```bash
cd /caminho/para/o/projeto
./bin/snaze
```

- `assets/` faltando ou arquivos mal formatados:
  - Verifique se há arquivos em `assets/` e se cada arquivo tem a linha de dimensões seguida pelo grid.
  - Se um mapa não tiver o caractere `&` (spawn), o parser lançará uma exceção.

Ignorar binários no Git
- O repositório já possui `.gitignore` configurado para ignorar `bin/`. Se `bin/` já estiver versionado, remova do índice com:

```bash
git rm -r --cached bin
git commit -m "Stop tracking bin/"
```

Melhorias sugeridas (próximos passos)
- Adicionar argumentos de linha de comando para configurar diretório de assets, mapa específico e número de rounds.
- Tratar erros de parser mais graciosamente e reportar qual arquivo está com problema.
- Corrigir warnings de compilação menores (signed/unsigned, variáveis não usadas).
- Adicionar testes para o parser (`snake.cpp`) e o pathfinder (`puzzles.cpp`).

Contribuindo
- Abra issues para bugs e features. Pull requests são bem-vindos — mantenha o estilo de código e adicione testes quando possível.

Licença
- Não há licença explícita neste repositório. Se for compartilhar/redistribuir, considere adicionar uma licença permissiva (MIT/Apache-2.0) ou outra de sua escolha.

Contato
- Se precisar que eu torne o programa aceitando argumentos de linha de comando, limpando warnings, ou adicionando testes, diga qual você prefere e eu implemento.

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ao5BHHrY)
﻿# Projeto Snaze

