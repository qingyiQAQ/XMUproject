#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ����iris���ݽṹ
struct IrisData {
    double sepalLength;
    double sepalWidth;
    double petalLength;
    double petalWidth;
    string species;
};

// ������������֮���ŷ�Ͼ���
double euclideanDistance(const IrisData& a, const IrisData& b) {
    return sqrt(pow(a.sepalLength - b.sepalLength, 2) +
        pow(a.sepalWidth - b.sepalWidth, 2) +
        pow(a.petalLength - b.petalLength, 2) +
        pow(a.petalWidth - b.petalWidth, 2));
}

// KNN�㷨
string knn(const vector<IrisData>& trainData, const IrisData& testData, int k) {
    // �������������ѵ�������ľ��룬����������������
    vector<pair<double, string>> distances;
    for (const auto& trainSample : trainData) {
        double dist = euclideanDistance(trainSample, testData);
        distances.push_back(make_pair(dist, trainSample.species));
    }
    sort(distances.begin(), distances.end());

    // ͳ��ǰk����������������
    unordered_map<string, int> freq;
    for (int i = 0; i < k; ++i) {
        freq[distances[i].second]++;
    }

    // �ҵ�Ƶ����ߵ����
    int maxFreq = 0;
    string predClass;
    for (const auto& pair : freq) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            predClass = pair.first;
        }
    }

    return predClass;
}

int main() {
    ifstream trainFile("D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\traindata.txt");
    ifstream testFile("D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\testdata.txt");
    if (!trainFile.is_open() || !testFile.is_open()) {
        cout << "Failed to open files." << endl;
        return 1;
    }
    // ʾ�����ݼ�
    vector<IrisData> irisData, targetData;

    string line;
    while (getline(trainFile, line)) {
        stringstream ss(line);
        vector<double> values;
        double val;
        while (ss >> val) {
            values.push_back(val);
        }
        irisData.push_back({ values[0],values[1],values[2],values[3],to_string(values[4]) });
    }

    while (getline(testFile, line)) {
        stringstream ss(line);
        vector<double> values;
        double val;
        while (ss >> val) {
            values.push_back(val);
        }
        targetData.push_back({ values[0],values[1],values[2],values[3],to_string(values[4]) });
    }

    // ����Kֵ
    int k = 3;

    int error = 0;

    for (int i = 0; i < targetData.size(); i++) {
        string predClass = knn(irisData, targetData[i], k);
        if (predClass != targetData[i].species)error++;
    }


    cout << "Test Accuracy: " << (targetData.size() - error) * 100.0 / targetData.size() << "%" << endl;

    return 0;
}
