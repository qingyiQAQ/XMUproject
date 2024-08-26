#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// 定义目标函数
double objectiveFunction(double x) {
    return 11 * sin(6 * x) + 7 * cos(5 * x);
}

// 新解产生器：在当前解的基础上进行微小变化
double generateNewSolution(double currentSolution, double stepSize, double a, double b) {
    // 这里以随机生成一个小的浮点数作为变化量
    double change = ((double)rand() / RAND_MAX) * stepSize;
    // 随机决定变化的方向是正还是负
    if (rand() % 2 == 0) {
        // 将新解限制在区间 [a, b] 内
        return (currentSolution + change > b) ? b : currentSolution + change;
    }
    else {
        // 将新解限制在区间 [a, b] 内
        return (currentSolution - change < a) ? a : currentSolution - change;
    }
}

// Metropolis接受准则
bool accept(double delta, double temperature) {
    if (delta < 0) {
        return true; // 总是接受更优解
    }
    else {
        double probability = exp(-delta / temperature);
        double r = ((double)rand() / RAND_MAX);
        return r < probability; // 以一定概率接受劣解
    }
}

// 模拟退火算法求解最小值
double simulatedAnnealing(double initialTemperature, double coolingFactor, double stepSize, int iterations, double a, double b) {
    srand(time(NULL));

    double currentSolution = 0; // 初始解状态
    double temperature = initialTemperature; // 初始温度

    for (int i = 0; i < iterations; ++i) {
        // 产生新解
        double newSolution = generateNewSolution(currentSolution, stepSize, a, b);

        // 计算目标函数差
        double delta = objectiveFunction(newSolution) - objectiveFunction(currentSolution);

        // 判断是否接受新解
        if (accept(delta, temperature)) {
            currentSolution = newSolution;
        }

        // 更新温度
        temperature *= coolingFactor;
    }

    return currentSolution;
}

int main() {
    // 参数设置
    double initialTemperature = 1000.0; // 初始温度
    double coolingFactor = 0.99; // 温度衰减因子
    double stepSize = 0.1; // 搜索步长因子
    int iterations = 10000; // 迭代次数

    // 调用模拟退火算法求解最小值
    double minSolution = simulatedAnnealing(initialTemperature, coolingFactor, stepSize, iterations, 0, 2 * acos(-1.0));

    cout << "最小值: " << objectiveFunction(minSolution) << endl;
    cout << "最优解: " << minSolution << endl;

    return 0;
}
