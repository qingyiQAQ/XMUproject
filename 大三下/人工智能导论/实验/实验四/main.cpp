#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// ����Ŀ�꺯��
double objectiveFunction(double x) {
    return 11 * sin(6 * x) + 7 * cos(5 * x);
}

// �½���������ڵ�ǰ��Ļ����Ͻ���΢С�仯
double generateNewSolution(double currentSolution, double stepSize, double a, double b) {
    // �������������һ��С�ĸ�������Ϊ�仯��
    double change = ((double)rand() / RAND_MAX) * stepSize;
    // ��������仯�ķ����������Ǹ�
    if (rand() % 2 == 0) {
        // ���½����������� [a, b] ��
        return (currentSolution + change > b) ? b : currentSolution + change;
    }
    else {
        // ���½����������� [a, b] ��
        return (currentSolution - change < a) ? a : currentSolution - change;
    }
}

// Metropolis����׼��
bool accept(double delta, double temperature) {
    if (delta < 0) {
        return true; // ���ǽ��ܸ��Ž�
    }
    else {
        double probability = exp(-delta / temperature);
        double r = ((double)rand() / RAND_MAX);
        return r < probability; // ��һ�����ʽ����ӽ�
    }
}

// ģ���˻��㷨�����Сֵ
double simulatedAnnealing(double initialTemperature, double coolingFactor, double stepSize, int iterations, double a, double b) {
    srand(time(NULL));

    double currentSolution = 0; // ��ʼ��״̬
    double temperature = initialTemperature; // ��ʼ�¶�

    for (int i = 0; i < iterations; ++i) {
        // �����½�
        double newSolution = generateNewSolution(currentSolution, stepSize, a, b);

        // ����Ŀ�꺯����
        double delta = objectiveFunction(newSolution) - objectiveFunction(currentSolution);

        // �ж��Ƿ�����½�
        if (accept(delta, temperature)) {
            currentSolution = newSolution;
        }

        // �����¶�
        temperature *= coolingFactor;
    }

    return currentSolution;
}

int main() {
    // ��������
    double initialTemperature = 1000.0; // ��ʼ�¶�
    double coolingFactor = 0.99; // �¶�˥������
    double stepSize = 0.1; // ������������
    int iterations = 10000; // ��������

    // ����ģ���˻��㷨�����Сֵ
    double minSolution = simulatedAnnealing(initialTemperature, coolingFactor, stepSize, iterations, 0, 2 * acos(-1.0));

    cout << "��Сֵ: " << objectiveFunction(minSolution) << endl;
    cout << "���Ž�: " << minSolution << endl;

    return 0;
}
