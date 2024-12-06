# Algoritmo Genético para o Problema da Mochila

Este programa implementa um algoritmo genético para resolver o **Problema da Mochila Binária**. Ele foi traduzido de um código original em Python para C++ para o projeto extra da disciplina de **SuperComp**.

## Funcionamento

O algoritmo tenta encontrar a melhor combinação de itens que podem ser colocados em uma mochila de capacidade limitada, maximizando o valor total enquanto respeita o peso máximo permitido.

O programa utiliza:
- **População inicial**: Geração aleatória de combinações de itens.
- **Função de fitness**: Avaliação da qualidade de cada combinação com base no valor total e na restrição de peso.
- **Seleção**: Escolha das melhores combinações para gerar a próxima geração.
- **Crossover**: Combinação de características de "pais" para gerar "filhos".
- **Mutação**: Alteração aleatória em algumas combinações para explorar novas soluções.

## Entrada

Os pesos e valores dos itens são gerados aleatoriamente no início do programa:
- **Peso**: Entre 1 e 15.
- **Valor**: Entre 1 e 100.
- **Capacidade da mochila**: 100 unidades.

## Saída

O programa imprime:
1. Os itens selecionados na melhor solução.
2. O peso e o valor total dessa solução.
3. A pontuação (fitness) da solução encontrada.

## Como Compilar e Executar

1. Compile o programa usando o `g++`:
   ```bash
   g++ -std=c++11 -o alg_gen alg_gen.cpp
   ```
2. Execute o programa:
   ```bash
   ./alg_gen
   ```
