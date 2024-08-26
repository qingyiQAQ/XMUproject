#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

// ����������ṹ
const int INPUT_NODES = 4;
const int HIDDEN_NODES = 10;
const int OUTPUT_NODES = 3;

// ����ѧϰ�ʺ͵�������
const double LEARNING_RATE = 0.1;
const int EPOCHS = 1000;

// ������������
class NeuralNetwork {
private:
    vector<vector<double>> inputHiddenWeights;
    vector<vector<double>> hiddenOutputWeights;
    vector<double> hiddenBiases;
    vector<double> outputBiases;

public:
    NeuralNetwork() {
        // ��ʼ��Ȩ�غ�ƫ��
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < INPUT_NODES; ++i) {
            vector<double> weights;
            for (int j = 0; j < HIDDEN_NODES; ++j) {
                weights.push_back(dist(gen));
            }
            inputHiddenWeights.push_back(weights);
        }

        for (int i = 0; i < HIDDEN_NODES; ++i) {
            vector<double> weights;
            for (int j = 0; j < OUTPUT_NODES; ++j) {
                weights.push_back(dist(gen));
            }
            hiddenOutputWeights.push_back(weights);
            hiddenBiases.push_back(dist(gen));
        }

        for (int i = 0; i < OUTPUT_NODES; ++i) {
            outputBiases.push_back(dist(gen));
        }
    }

    // sigmoid����
    double sigmoid(double x) {
        return 1 / (1 + exp(-x));
    }

    // �������������
    vector<double> feedForward(const vector<double>& inputs) {
        vector<double> hiddenOutputs(HIDDEN_NODES);
        vector<double> outputs(OUTPUT_NODES);

        // �������������
        for (int i = 0; i < HIDDEN_NODES; ++i) {
            double sum = 0.0;
            for (int j = 0; j < INPUT_NODES; ++j) {
                sum += inputs[j] * inputHiddenWeights[j][i];
            }
            sum += hiddenBiases[i];
            hiddenOutputs[i] = sigmoid(sum);
        }

        // ������������
        for (int i = 0; i < OUTPUT_NODES; ++i) {
            double sum = 0.0;
            for (int j = 0; j < HIDDEN_NODES; ++j) {
                sum += hiddenOutputs[j] * hiddenOutputWeights[j][i];
            }
            sum += outputBiases[i];
            outputs[i] = sigmoid(sum);
        }

        return outputs;
    }

    // ����Ȩ�غ�ƫ��
    void updateWeights(const vector<double>& inputs, const vector<double>& targets) {
        vector<double> hiddenOutputs(HIDDEN_NODES);
        vector<double> outputs(OUTPUT_NODES);

        // ǰ�򴫲�
        for (int i = 0; i < HIDDEN_NODES; ++i) {
            double sum = 0.0;
            for (int j = 0; j < INPUT_NODES; ++j) {
                sum += inputs[j] * inputHiddenWeights[j][i];
            }
            sum += hiddenBiases[i];
            hiddenOutputs[i] = sigmoid(sum);
        }

        for (int i = 0; i < OUTPUT_NODES; ++i) {
            double sum = 0.0;
            for (int j = 0; j < HIDDEN_NODES; ++j) {
                sum += hiddenOutputs[j] * hiddenOutputWeights[j][i];
            }
            sum += outputBiases[i];
            outputs[i] = sigmoid(sum);
        }

        // ���򴫲�
        vector<double> outputErrors(OUTPUT_NODES);
        for (int i = 0; i < OUTPUT_NODES; ++i) {
            outputErrors[i] = (targets[i] - outputs[i]) * outputs[i] * (1 - outputs[i]);
        }

        vector<double> hiddenErrors(HIDDEN_NODES);
        for (int i = 0; i < HIDDEN_NODES; ++i) {
            double error = 0.0;
            for (int j = 0; j < OUTPUT_NODES; ++j) {
                error += outputErrors[j] * hiddenOutputWeights[i][j];
            }
            hiddenErrors[i] = error * hiddenOutputs[i] * (1 - hiddenOutputs[i]);
        }

        // ���������Ȩ�غ�ƫ��
        for (int i = 0; i < OUTPUT_NODES; ++i) {
            for (int j = 0; j < HIDDEN_NODES; ++j) {
                hiddenOutputWeights[j][i] += LEARNING_RATE * outputErrors[i] * hiddenOutputs[j];
            }
            outputBiases[i] += LEARNING_RATE * outputErrors[i];
        }

        // ����������Ȩ�غ�ƫ��
        for (int i = 0; i < HIDDEN_NODES; ++i) {
            for (int j = 0; j < INPUT_NODES; ++j) {
                inputHiddenWeights[j][i] += LEARNING_RATE * hiddenErrors[i] * inputs[j];
            }
            hiddenBiases[i] += LEARNING_RATE * hiddenErrors[i];
        }
    }
};

int main() {
    // ��ȡѵ�����Ͳ��Լ�����
    ifstream trainFile("D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\traindata.txt");
    ifstream testFile("D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\testdata.txt");
    if (!trainFile.is_open() || !testFile.is_open()) {
        cout << "Failed to open files." << endl;
        return 1;
    }

    // ��ȡ���ݲ�ת��Ϊ��������õĸ�ʽ
    vector<vector<double>> trainInputs;
    vector<vector<double>> trainTargets;
    vector<vector<double>> testInputs;
    vector<vector<double>> testTargets;

    string line;
    while (getline(trainFile, line)) {
        stringstream ss(line);
        vector<double> values;
        double val;
        while (ss >> val) {
            values.push_back(val);
        }
        trainInputs.push_back({ values[0], values[1], values[2], values[3] });
        trainTargets.push_back({ values[4] == 0.0 ? 1.0 : 0.0,
                                values[4] == 1.0 ? 1.0 : 0.0,
                                values[4] == 2.0 ? 1.0 : 0.0 });
    }

    while (getline(testFile, line)) {
        stringstream ss(line);
        vector<double> values;
        double val;
        while (ss >> val) {
            values.push_back(val);
        }
        testInputs.push_back({ values[0], values[1], values[2], values[3] });
        testTargets.push_back({ values[4] == 0.0 ? 1.0 : 0.0,
                               values[4] == 1.0 ? 1.0 : 0.0,
                               values[4] == 2.0 ? 1.0 : 0.0 });
    }

    // ����������
    NeuralNetwork nn;

    // ѵ��������
    for (int epoch = 0; epoch < EPOCHS; ++epoch) {
        double totalError = 0.0;
        for (size_t i = 0; i < trainInputs.size(); ++i) {
            auto outputs = nn.feedForward(trainInputs[i]);
            vector<double> targets(trainTargets[i].begin(), trainTargets[i].end());
            totalError += 0.5 * ((targets[0] - outputs[0]) * (targets[0] - outputs[0]) +
                (targets[1] - outputs[1]) * (targets[1] - outputs[1]) +
                (targets[2] - outputs[2]) * (targets[2] - outputs[2]));

            nn.updateWeights(trainInputs[i], targets);
        }
        cout << "Epoch: " << epoch << ", Error: " << totalError << endl;
    }

    // �ڲ��Լ��ϲ���������
    int correct = 0;
    for (size_t i = 0; i < testInputs.size(); ++i) {
        auto outputs = nn.feedForward(testInputs[i]);
        vector<double> targets(testTargets[i].begin(), testTargets[i].end());

        // �����ת��Ϊ���
        int predictedClass = distance(outputs.begin(), max_element(outputs.begin(), outputs.end())) + 1;
        int trueClass = distance(targets.begin(), max_element(targets.begin(), targets.end())) + 1;

        if (predictedClass == trueClass) {
            correct++;
        }
    }

    double accuracy = static_cast<double>(correct) / testInputs.size() * 100.0;
    cout << "Test Accuracy: " << accuracy << "%" << endl;

    return 0;
}
