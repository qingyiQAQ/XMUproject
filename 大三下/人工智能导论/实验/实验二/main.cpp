#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

// �����������ṹ��
struct City {
    int x, y;
};

// ��ʼ����Ⱥ
vector<vector<int>> initializePopulation(int populationSize, int numCities) {
    vector<vector<int>> population(populationSize, vector<int>(numCities));
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < numCities; ++j) {
            population[i][j] = j;
        }
        random_shuffle(population[i].begin(), population[i].end());
    }
    return population;
}

// ������������֮��ľ���
double distance(City city1, City city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

// ����·�����ܾ���
double totalDistance(const vector<int>& path, const vector<City>& cities) {
    double total = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        total += distance(cities[path[i]], cities[path[i + 1]]);
    }
    total += distance(cities[path.back()], cities[path.front()]);
    return total;
}

// ������Ӧ��
vector<double> fitness(const vector<vector<int>>& population, const vector<City>& cities) {
    vector<double> fitnessValues(population.size());
    for (size_t i = 0; i < population.size(); ++i) {
        fitnessValues[i] = 1.0 / totalDistance(population[i], cities);
    }
    return fitnessValues;
}

// ѡ����
int selectParent(const vector<double>& fitnessValues) {
    double sumFitness = 0.0;
    for (double fitness : fitnessValues) {
        sumFitness += fitness;
    }
    double avgFitness = sumFitness / fitnessValues.size();
    while(true) {
        int i = rand() % fitnessValues.size();
        if (fitnessValues[i] >= avgFitness)return i;
    }
}

// ���溯��
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int startPos = rand() % parent1.size();
    int endPos = rand() % parent1.size();
    if (startPos > endPos) {
        swap(startPos, endPos);
    }
    vector<int> child(parent1.begin() + startPos, parent1.begin() + endPos);
    for (int city : parent2) {
        if (find(child.begin(), child.end(), city) == child.end()) {
            child.push_back(city);
        }
    }
    return child;
}

// ���캯��
void mutate(vector<int>& individual) {
    int pos1 = rand() % individual.size();
    int pos2 = rand() % individual.size();
    swap(individual[pos1], individual[pos2]);
}

int main() {
    // ����·��
    vector<int> best = { 0,1,2,3,4 };

    // �����������
    vector<City> cities = { {0, 2}, {1, 9}, {3, 0}, {2, 4}, {4, 7} };

    // ��ʼ����Ⱥ
    int populationSize = 600;
    vector<vector<int>> population = initializePopulation(populationSize, cities.size());

    // ��������
    int numGenerations = 100;

    for (int generation = 0; generation < numGenerations; ++generation) {
        // ������Ӧ��
        vector<double> fitnessValues = fitness(population, cities);

        // ѡ����һ����Ⱥ
        vector<vector<int>> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            int parent1 = selectParent(fitnessValues);
            int parent2 = selectParent(fitnessValues);
            newPopulation.push_back(crossover(population[parent1], population[parent2]));
        }

        // ����
        for (vector<int>& individual : newPopulation) {
            if (static_cast<double>(rand()) / RAND_MAX < 0.05) {
                mutate(individual);
            }
        }

        // ������Ⱥ
        population = newPopulation;

        // ѡ����Ѹ���
        double bestFitness = 0.0;
        int bestIndex = 0;
        for (size_t i = 0; i < population.size(); ++i) {
            double currentFitness = 1.0 / totalDistance(population[i], cities);
            if (currentFitness > bestFitness) {
                bestFitness = currentFitness;
                bestIndex = i;
            }
        }
        double oldFitness = 1.0/ totalDistance(best, cities);
        if (oldFitness < bestFitness)best = population[bestIndex];
    }

    // ������
    cout << "���·����";
    for (int city : best) {
        cout << city << " ";
    }
    cout << endl;
    cout << "·�����ȣ�";
    cout << totalDistance(best, cities) << endl;

    return 0;
}
