#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

// Gera uma população inicial
vector<vector<int>> generate_population(int population_size, int item_count) {
    vector<vector<int>> population(population_size, vector<int>(item_count));
    for (auto &individual : population) {
        for (auto &gene : individual) {
            gene = rand() % 2; // Gera 0 ou 1 aleatoriamente
        }
    }
    return population;
}

// Função de fitness
vector<int> fitness(const vector<int>& weight, const vector<int>& value, const vector<vector<int>>& population, int capacity) {
    vector<int> fitness_values(population.size());
    for (size_t i = 0; i < population.size(); ++i) {
        int total_value = 0;
        int total_weight = 0;
        for (size_t j = 0; j < population[i].size(); ++j) {
            if (population[i][j]) {
                total_value += value[j];
                total_weight += weight[j];
            }
        }
        fitness_values[i] = (total_weight <= capacity) ? total_value : 0;
    }
    return fitness_values;
}

// Seleção
vector<vector<int>> selection(const vector<int>& fitness_values, int num_parents, const vector<vector<int>>& population) {
    vector<pair<int, int>> fitness_index;
    for (size_t i = 0; i < fitness_values.size(); ++i) {
        fitness_index.emplace_back(fitness_values[i], i);
    }
    sort(fitness_index.rbegin(), fitness_index.rend());
    vector<vector<int>> parents(num_parents);
    for (int i = 0; i < num_parents; ++i) {
        parents[i] = population[fitness_index[i].second];
    }
    return parents;
}

// Crossover
vector<vector<int>> crossover(const vector<vector<int>>& parents, int num_offsprings) {
    vector<vector<int>> offsprings(num_offsprings, vector<int>(parents[0].size()));
    size_t crossover_point = parents[0].size() / 2;
    int parent_count = parents.size();

    for (int i = 0; i < num_offsprings; ++i) {
        int parent1_idx = i % parent_count;
        int parent2_idx = (i + 1) % parent_count;
        for (size_t j = 0; j < parents[0].size(); ++j) {
            if (j < crossover_point) {
                offsprings[i][j] = parents[parent1_idx][j];
            } else {
                offsprings[i][j] = parents[parent2_idx][j];
            }
        }
    }
    return offsprings;
}

// Mutação
void mutation(vector<vector<int>>& offsprings, double mutation_rate) {
    for (auto& individual : offsprings) {
        if (static_cast<double>(rand()) / RAND_MAX < mutation_rate) {
            int index = rand() % individual.size();
            individual[index] = 1 - individual[index]; // Inverte o gene
        }
    }
}

// Otimização
pair<vector<int>, int> optimize(const vector<int>& weight, const vector<int>& value, vector<vector<int>> population,
                                int num_generations, int capacity) {
    int population_size = population.size();
    int num_parents = population_size / 2;
    int num_offsprings = population_size - num_parents;
    double mutation_rate = 0.15;

    vector<int> best_solution;
    int best_fitness = 0;

    for (int gen = 0; gen < num_generations; ++gen) {
        auto fitness_values = fitness(weight, value, population, capacity);
        auto parents = selection(fitness_values, num_parents, population);
        auto offsprings = crossover(parents, num_offsprings);
        mutation(offsprings, mutation_rate);

        // Atualiza a população com pais e filhos
        for (int i = 0; i < num_parents; ++i) {
            population[i] = parents[i];
        }
        for (int i = 0; i < num_offsprings; ++i) {
            population[num_parents + i] = offsprings[i];
        }

        // Atualiza melhor solução
        auto max_fitness_it = max_element(fitness_values.begin(), fitness_values.end());
        if (*max_fitness_it > best_fitness) {
            best_fitness = *max_fitness_it;
            best_solution = population[max_fitness_it - fitness_values.begin()];
        }
    }
    return {best_solution, best_fitness};
}

// Programa principal
int main() {
    srand(static_cast<unsigned>(time(0)));

    int item_count = 40;
    int population_size = 16;
    int num_generations = 1000;
    int knapsack_capacity = 100;

    vector<int> weights(item_count);
    vector<int> values(item_count);
    for (int i = 0; i < item_count; ++i) {
        weights[i] = rand() % 15 + 1; // Pesos aleatórios entre 1 e 15
        values[i] = rand() % 100 + 1; // Valores aleatórios entre 1 e 100
    }

    auto population = generate_population(population_size, item_count);

    auto result = optimize(weights, values, population, num_generations, knapsack_capacity);

    const auto& best_solution = result.first;
    int best_fitness = result.second;

    cout << "Melhor solução:\n";
    for (size_t i = 0; i < best_solution.size(); ++i) {
        if (best_solution[i]) {
            cout << "Item " << i + 1 << " (Peso: " << weights[i] << ", Valor: " << values[i] << ")\n";
        }
    }

    cout << "Fitness da melhor solução: " << best_fitness << "\n";
    return 0;
}
