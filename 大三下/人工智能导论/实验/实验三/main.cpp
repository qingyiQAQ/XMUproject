#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

//最大迭代次数
const int MAX_ITERATIONS = 200;
//粒子群粒子数目
const int POPULATION_SIZE = 50;
//惯性因子
const double INERTIA_WEIGHT = 0.5;
//认知因子
const double COGNITIVE_WEIGHT = 2.0;
//社会因子
const double SOCIAL_WEIGHT = 2.0;
//最大速度
const double V_MAX = 0.2;
//终止阈值
const double TERMINATION_THRESHOLD = 1e-6;

//粒子结构体
struct Particle {
    vector<int> position;
    vector<int> pbest;
    double fitness;
    vector<double> velocity;
};

//随机生成城市访问顺序
vector<int> generateRandomPermutation(int n) {
    vector<int> permutation;
    for (int i = 0; i < n; ++i) {
        permutation.push_back(i);
    }
    random_shuffle(permutation.begin(), permutation.end());
    return permutation;
}

//得到两个城市之间的距离
double distanceBetweenCities(int city1, int city2, const vector<vector<double>>& distances) {
    return distances[city1][city2];
}

//计算一个路径的总距离
double calculatePathDistance(const vector<int>& path, const vector<vector<double>>& distances) {
    double totalDistance = 0.0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += distanceBetweenCities(path[i], path[i + 1], distances);
    }
    totalDistance += distanceBetweenCities(path.back(), path.front(), distances); // Return to start city
    return totalDistance;
}

//初始化粒子群
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

//更新粒子的位置和速度
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

//PSO算法
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
    //城市位置定义
    vector<vector<double>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    srand(time(NULL));

    vector<int> optimalPath = PSO(distances, MAX_ITERATIONS, POPULATION_SIZE,
        INERTIA_WEIGHT, COGNITIVE_WEIGHT, SOCIAL_WEIGHT, V_MAX);

    cout << "最优路线: ";
    for (int city : optimalPath) {
        cout << city << " ";
    }
    cout << endl;

    cout << "总距离: " << calculatePathDistance(optimalPath, distances) << endl;

    return 0;
}
