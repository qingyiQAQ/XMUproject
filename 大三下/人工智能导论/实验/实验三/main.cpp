#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

//����������
const int MAX_ITERATIONS = 200;
//����Ⱥ������Ŀ
const int POPULATION_SIZE = 50;
//��������
const double INERTIA_WEIGHT = 0.5;
//��֪����
const double COGNITIVE_WEIGHT = 2.0;
//�������
const double SOCIAL_WEIGHT = 2.0;
//����ٶ�
const double V_MAX = 0.2;
//��ֹ��ֵ
const double TERMINATION_THRESHOLD = 1e-6;

//���ӽṹ��
struct Particle {
    vector<int> position;
    vector<int> pbest;
    double fitness;
    vector<double> velocity;
};

//������ɳ��з���˳��
vector<int> generateRandomPermutation(int n) {
    vector<int> permutation;
    for (int i = 0; i < n; ++i) {
        permutation.push_back(i);
    }
    random_shuffle(permutation.begin(), permutation.end());
    return permutation;
}

//�õ���������֮��ľ���
double distanceBetweenCities(int city1, int city2, const vector<vector<double>>& distances) {
    return distances[city1][city2];
}

//����һ��·�����ܾ���
double calculatePathDistance(const vector<int>& path, const vector<vector<double>>& distances) {
    double totalDistance = 0.0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += distanceBetweenCities(path[i], path[i + 1], distances);
    }
    totalDistance += distanceBetweenCities(path.back(), path.front(), distances); // Return to start city
    return totalDistance;
}

//��ʼ������Ⱥ
vector<Particle> initializeParticles(int populationSize, int cityCount) {
    vector<Particle> particles;
    for (int i = 0; i < populationSize; ++i) {
        Particle particle;
        particle.position = generateRandomPermutation(cityCount);
        particle.pbest = particle.position;
        particle.fitness = numeric_limits<double>::max();
        particle.velocity.resize(cityCount, 0.0);
        particles.push_back(particle);
    }
    return particles;
}

//�������ӵ�λ�ú��ٶ�
void updateParticle(Particle& particle, const vector<int>& gbest, double inertiaWeight,
    double cognitiveWeight, double socialWeight, double vMax) {
    for (int i = 0; i < particle.position.size(); ++i) {
        double r1 = static_cast<double>(rand()) / RAND_MAX;
        double r2 = static_cast<double>(rand()) / RAND_MAX;
        double cognitiveComponent = cognitiveWeight * r1 * (particle.pbest[i] - particle.position[i]);
        double socialComponent = socialWeight * r2 * (gbest[i] - particle.position[i]);
        particle.velocity[i] = inertiaWeight * particle.velocity[i] + cognitiveComponent + socialComponent;
        if (particle.velocity[i] > vMax) {
            particle.velocity[i] = vMax;
        }
        else if (particle.velocity[i] < -vMax) {
            particle.velocity[i] = -vMax;
        }
        particle.position[i] += round(particle.velocity[i]);
    }
}

//PSO�㷨
vector<int> PSO(const vector<vector<double>>& distances, int maxIterations, int populationSize,
    double inertiaWeight, double cognitiveWeight, double socialWeight, double vMax) {
    int cityCount = distances.size();
    vector<Particle> particles = initializeParticles(populationSize, cityCount);
    vector<int> gbest = particles[0].position;
    double gbestFitness = calculatePathDistance(gbest, distances);

    for (int iter = 0; iter < maxIterations; ++iter) {
        for (int i = 0; i < populationSize; ++i) {
            double fitness = calculatePathDistance(particles[i].position, distances);
            if (fitness < particles[i].fitness) {
                particles[i].fitness = fitness;
                particles[i].pbest = particles[i].position;
                if (fitness < gbestFitness) {
                    gbest = particles[i].pbest;
                    gbestFitness = fitness;
                }
            }
        }
        for (int i = 0; i < populationSize; ++i) {
            updateParticle(particles[i], gbest, inertiaWeight, cognitiveWeight, socialWeight, vMax);
        }
    }

    return gbest;
}

int main() {
    //����λ�ö���
    vector<vector<double>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    srand(time(NULL));

    vector<int> optimalPath = PSO(distances, MAX_ITERATIONS, POPULATION_SIZE,
        INERTIA_WEIGHT, COGNITIVE_WEIGHT, SOCIAL_WEIGHT, V_MAX);

    cout << "����·��: ";
    for (int city : optimalPath) {
        cout << city << " ";
    }
    cout << endl;

    cout << "�ܾ���: " << calculatePathDistance(optimalPath, distances) << endl;

    return 0;
}
