#include<iostream>

#include<fstream>
#include<istream>
#include<iomanip>
#include<sstream>
#include<stdio.h>

#include<vector>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include<algorithm>
#include<time.h>
using namespace std;

/*
����node�����
�����������
���������ڰ������ɾ�������������treegenerate  �ݹ麯���У����������ֹ࣬ͣ�ݹ�
1��ȫ����ͬһ����𣬱��ΪҶ���
2����ǰ���Լ�Ϊ�գ����Ϊ�����ݼ���������
3����������Ϊ�գ����ΪҶ��㣬����Ǹ����������
*/
//  start, finish;

class DataSet {
public:
    vector<string> Attribute; //���Ա�ǩ��"���೤��","������","���೤��","���곤��"
    vector<vector<string>> Data; // ����ֵ��5.1 3.5 1.4 0.2
    map<string, vector<string>> AttributeValue; //ӳ�����ͣ�����������ݣ�{"���":{...},"���೤��":{5.1,4.9,5.7....},"..":{...}}

    DataSet(); //��ʼ���캯��
    DataSet(vector<vector<string>> data, vector<string> attribute); //���̵Ĺ��캯��
    void Connect(); //�������Ա�ǩ������ֵ
};
DataSet::DataSet() {
    Attribute = { "���೤��","������","���곤��","������" };
}
DataSet::DataSet(vector<vector<string>> data, vector<string> attribute) {
    Data = data;
    Attribute = attribute;
    Connect();
}
void DataSet::Connect() {
    if (Data.empty()) return;

    vector<vector<string>> attribute; //�洢����ֵ��ת��
    vector<string> TempAttribute = Attribute; //�洢���Ա�ǩ
    TempAttribute.push_back("���"); //5
    attribute.resize(TempAttribute.size()); //5

    // Data 150��x5��
    for (int i = 0; i < Data[0].size(); i++) {  //i 0-4
        for (int j = 0; j < Data.size(); j++) { //j 0-149
            attribute[i].push_back(Data[j][i]);
        }

        AttributeValue[TempAttribute[i]] = attribute[i];
    }

}
void Read_file(DataSet& dataSet, string fname) {
    // ��ȡ�ļ�
    ifstream file_data(fname, ios::in);
    if (!file_data.is_open()) {
        cout << "Error: opening file fail" << endl;
        exit(1);
    }
    else {
        string line;
        vector<string> words;
        string word;

        // ��ȡ����
        istringstream sin;
        // ���ж�ȡ����
        while (getline(file_data, line))
        {
            word.clear();
            words.clear();
            sin.clear();
            sin.str(line);
            while (getline(sin, word, ' ')) {
                words.push_back(word);  //��ÿһ���е��������push
            }
            dataSet.Data.push_back(words);
        }
        file_data.close();
    }
    dataSet.Connect();
}

class Node {
public:
    Node() {
        isLeaf = false;
        isRoot = false;
        nodeAccuracy = 0;
    }

    vector<double> MidValue;
    bool isLeaf;
    bool isRoot;
    string node_Attribute;
    //�жϱ�׼
    double Mid;
    string Attribute;
    vector<Node*> ChildrenNode;
    double nodeAccuracy;

};

class DecisionTree {
public:
    void TreeGenerate(DataSet& dataSet, Node* Father); //���ɾ����������ظ�����ָ��
    double CalcEntropy(DataSet& dataSet); //����һ�����ݼ�����Ϣ��
    double CalcInfoGain(double midValue, DataSet& dataSet, string Value); //����һ�����Ե���Ϣ����

    double AccuracyRate(DataSet& dataSet, Node* node);
    vector<double> FindMidValue(DataSet& dataSet); //����һ�����ԵĻ��ֵ㣬����ѭ������һ�����Ե���Ϣ����
    map<string, double> FindBestInfoGain(DataSet& dataSet); //�������Ϣ���棬�������������Լ���������ӳ��
    map<string, int> CountTimes(DataSet& dataSet); //�����������������
    void DestoryDecisionTree(Node* node);//ɾ��������
    vector<string> Prediction(DataSet& dataSet, Node* node);
};
void DecisionTree::TreeGenerate(DataSet& dataSet, Node* Father) {

    Node* newNode = new Node;
    Father->ChildrenNode.push_back(newNode);
    vector<double> newMid = FindMidValue(dataSet);//���εĸ��������Ż��ֵ�
    newNode->MidValue = newMid;

    // ���1��������ݼ�����������ͬһ��𣬽�node���ΪC��Ҷ���
    bool isSame = true;
    string curAttr = dataSet.AttributeValue["���"][0];
    for (int i = 0; i < dataSet.AttributeValue["���"].size(); i++) {
        if (dataSet.AttributeValue["���"][i] != curAttr) {
            isSame = false;
            break;
        }
    }
    if (isSame) {
        newNode->isLeaf = true;
        newNode->node_Attribute = curAttr;
        return;
    }

    // ���2�����Լ�Ϊ�ջ����ݼ������������Լ���ȡֵ��ͬ
    isSame = true;
    for (int i = 0; i < dataSet.Attribute.size(); i++) {
        string a = dataSet.AttributeValue[dataSet.Attribute[i]][0];
        if (stod(a) > Father->MidValue[i]) {//?
            for (int j = 1; j < dataSet.Data.size(); j++) {
                if (stod(dataSet.AttributeValue[dataSet.Attribute[i]][j]) <= Father->MidValue[i]) {
                    isSame = false;
                    break;
                }
            }
        }
        else {
            for (int j = 1; j < dataSet.Data.size(); j++) {
                if (stod(dataSet.AttributeValue[dataSet.Attribute[i]][j]) > Father->MidValue[i]) {
                    isSame = false;
                    break;
                }
            }
        }
        if (isSame == false) break;
    }
    if (dataSet.Attribute.empty() || isSame == true) {
        newNode->isLeaf = true;
        map<string, int> mp = CountTimes(dataSet);
        int maxTimes = -1;
        string maxValue;
        for (auto i = mp.begin(); i != mp.end(); i++) {
            if (i->second > maxTimes) {
                maxValue = i->first;
                maxTimes = i->second;
            }
        }
        newNode->node_Attribute = maxValue;
        return;
    }

    //���3:�����Լ��л�����������
    map<string, double> BestAttributeMap = FindBestInfoGain(dataSet);
    string BestAttribute = BestAttributeMap.begin()->first;
    newNode->Attribute = BestAttribute;

    //�ҳ�һ�������е����Ż��ֵ�
    vector<string> TempAttribute;
    TempAttribute.push_back(BestAttribute);
    vector<string> TempValue = dataSet.AttributeValue[BestAttribute];
    vector<string> TempAttr = dataSet.AttributeValue["���"];
    vector<vector<string>> TempData(TempValue.size());
    for (int i = 0; i < TempValue.size(); i++) {
        TempData[i].push_back(TempValue[i]);
        TempData[i].push_back(TempAttr[i]);
    }
    DataSet d(TempData, TempAttribute);
    vector<double> MidArray = FindMidValue(d);

    double bestmid = MidArray[0];//�������Ե����Ż��ֵ�
    newNode->Mid = bestmid;
    vector<vector<vector<string>>> NextData(2);//��һ�η��������
    for (int i = 0; i < dataSet.Data.size(); i++) {
        if (stod(dataSet.AttributeValue[BestAttribute][i]) < bestmid) {
            NextData[0].push_back(dataSet.Data[i]);
        }
        else {
            NextData[1].push_back(dataSet.Data[i]);
        }
    }


    for (int i = 0; i < NextData.size(); i++) {
        Node* newChild = new Node;

        if (NextData[i].empty()) {
            newNode->ChildrenNode.push_back(newChild);
            newChild->isLeaf = true;
            map<string, int>mp = CountTimes(dataSet);
            int maxTimes = -1;
            string maxValue;
            for (auto i = mp.begin(); i != mp.end(); i++) {
                if (i->second > maxTimes) {
                    maxValue = i->first;
                    maxTimes = i->second;
                }
            }
            newChild->node_Attribute = maxValue;

            return;
        }
        else {
            //���4����ҪԤ��֦
            DataSet NewDataSet(NextData[i], dataSet.Attribute);

            //��newNode�����Գ�ʼ��
            map<string, int> mp = CountTimes(dataSet);
            int maxTimes = -1;
            string maxValue;
            for (auto i = mp.begin(); i != mp.end(); i++) {
                if (i->second > maxTimes) {
                    maxValue = i->first;
                    maxTimes = i->second;
                }
            }
            newNode->node_Attribute = maxValue;

            //��newChild��ʼ��
            mp = CountTimes(NewDataSet); //�ȱ��Ϊ�����ݼ�������������
            maxTimes = -1;
            maxValue = "";
            for (auto i = mp.begin(); i != mp.end(); i++) {
                if (i->second > maxTimes) {
                    maxValue = i->first;
                    maxTimes = i->second;
                }
            }
            newChild->node_Attribute = maxValue;

            if (AccuracyRate(dataSet, newNode) > AccuracyRate(NewDataSet, newChild)) {
                newNode->isLeaf = true;
                delete newChild;
                return;
            }
            delete newChild;
            TreeGenerate(NewDataSet, newNode);
        }
    }
}

// Ԥ��֦
double DecisionTree::AccuracyRate(DataSet& dataSet, Node* node) {
    vector<string> ClassArray = dataSet.AttributeValue["���"];
    string NodeAttr = node->node_Attribute;
    int count = 0;
    for (int i = 0; i < ClassArray.size(); i++) {
        if (NodeAttr == ClassArray[i]) count++;
    }
    return 1.0 * count / ClassArray.size();
}

vector<string> DecisionTree::Prediction(DataSet& dataSet, Node* node) {
    vector<string> ClassArray;
    if (node->isLeaf) {
        ClassArray.push_back(node->node_Attribute);
        return ClassArray;
    }
    else {
        for (int i = 0; i < dataSet.Data.size(); i++) {
            vector<string> oneClass;
            vector<vector<string>> tempData;
            tempData.push_back(dataSet.Data[i]);
            DataSet d(tempData, dataSet.Attribute);
            if (stod(dataSet.AttributeValue[node->Attribute][i]) < node->Mid || node->isRoot) {
                oneClass = Prediction(d, node->ChildrenNode[0]);
            }
            else {
                oneClass = Prediction(d, node->ChildrenNode[1]);
            }
            for (int j = 0; j < oneClass.size(); j++)
                ClassArray.push_back(oneClass[j]);

        }
    }
    return ClassArray;
}
//����dataSet���ݼ�����������Լ������ĳ��ִ���
map<string, int>DecisionTree::CountTimes(DataSet& dataSet) {
    map<string, int> ClassCount;
    vector<string> classList = dataSet.AttributeValue["���"];
    for (int i = 0; i < classList.size(); i++) {
        if (!ClassCount.count(classList[i])) {
            ClassCount.insert({ classList[i],0 });
        }
        ClassCount[classList[i]]++;
    }
    return ClassCount;
}
void DecisionTree::DestoryDecisionTree(Node* node) {
    if (!node->isLeaf)
    {
        for (size_t i = 0; i < node->ChildrenNode.size(); i++)
        {
            DestoryDecisionTree(node->ChildrenNode[i]);
        }
    }
    delete node;	//�ͷŽڵ�
    node = nullptr;
}

double DecisionTree::CalcEntropy(DataSet& dataSet) {
    int sum = dataSet.Data.size();//��������
    map<string, int> ClassCount = CountTimes(dataSet);

    vector<string> classList = dataSet.AttributeValue["���"];
    double entropy = 0;//��Ϣ��

    for (auto item = ClassCount.begin(); item != ClassCount.end(); item++) {
        double p = (double)item->second / sum;
        if (p == 0) entropy -= 0;
        else entropy -= p * log(p) / log(2);
    }
    return entropy;
}


vector<double> DecisionTree::FindMidValue(DataSet& dataSet) {//�ҳ����������Ż��ֵ�
    vector<double> bestMid;

    for (int i = 0; i < dataSet.Attribute.size(); i++) {
        vector<string> valueString = dataSet.AttributeValue[dataSet.Attribute[i]];

        //������ֵ��string����תΪdouble����
        vector<double> valueDouble;
        for (int j = 0; j < valueString.size(); j++) {
            valueDouble.push_back(stod(valueString[j]));
        }

        //����double����
        sort(valueDouble.begin(), valueDouble.end());

        vector<double> midArray;
        for (int j = 0; j < valueDouble.size() - 1; j++) {
            midArray.push_back((valueDouble[j] + valueDouble[j + 1]) / 2);
        }

        double bestmid;
        if (midArray.empty()) bestmid = valueDouble[0];
        else bestmid = midArray[0]; //��ʼ���м��
        double maxmidEntrophy = 0; //���ֵ�������Ϣ��

        for (int j = 0; j < midArray.size(); j++) {
            double gain = CalcInfoGain(midArray[j], dataSet, dataSet.Attribute[i]);
            if (gain >= maxmidEntrophy) {
                maxmidEntrophy = gain;
                bestmid = midArray[j];
            }
        }
        bestMid.push_back(bestmid); //�����Ż��ֵ����vector����
    }
    return bestMid;
}

double DecisionTree::CalcInfoGain(double midValue, DataSet& dataSet, string Value) { //����һ�����Ե���Ϣ����
    vector<vector<string>> leftData;
    vector<vector<string>> rightData;
    int leftCount = 0;
    int sum = dataSet.Data.size();//��������
    double mid = midValue;

    for (int i = 0; i < dataSet.Data.size(); i++) {
        if (stod(dataSet.AttributeValue[Value][i]) <= mid) {
            leftCount++;
            leftData.push_back(dataSet.Data[i]);
        }
        else {
            rightData.push_back(dataSet.Data[i]);
        }
    }
    DataSet d1(leftData, dataSet.Attribute);
    DataSet d2(rightData, dataSet.Attribute);
    double gain = CalcEntropy(dataSet) - leftCount * CalcEntropy(d1) / sum - (sum - leftCount) * CalcEntropy(d2) / sum;

    return gain;
}

map<string, double> DecisionTree::FindBestInfoGain(DataSet& dataSet) {
    double maxgain = 0;//���Ե������Ϣ����
    string bestAttri;
    vector<double> middle = FindMidValue(dataSet);
    for (int i = 0; i < dataSet.Attribute.size(); i++) {
        double mid = middle[i];
        double gain = CalcInfoGain(mid, dataSet, dataSet.Attribute[i]);
        if (gain > maxgain) {
            maxgain = gain;
            bestAttri = dataSet.Attribute[i];
        }
    }
    map<string, double> mp;
    mp[bestAttri] = maxgain;
    // cout<<"FindBestInforGain Over!"<<endl;
    return mp;
}



int main()
{
    //��ʼ��ʱ
    clock_t start = clock();

    // ����һ�����ݼ�����
    DataSet dataSet;
    string fname = "D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\traindata.txt";
    Read_file(dataSet, fname);

    DecisionTree dt;
    Node* RootNode = new Node;

    //��ʼ�������
    map<string, double> BestAttributeMap = dt.FindBestInfoGain(dataSet);
    string BestAttribute = BestAttributeMap.begin()->first;
    RootNode->Attribute = BestAttribute;

    vector<string> TempAttribute;
    TempAttribute.push_back(BestAttribute);
    vector<string> TempValue = dataSet.AttributeValue[BestAttribute];
    vector<string> TempAttr = dataSet.AttributeValue["���"];
    vector<vector<string>> TempData(TempValue.size());
    for (int i = 0; i < TempValue.size(); i++) {
        TempData[i].push_back(TempValue[i]);
        TempData[i].push_back(TempAttr[i]);
    }
    DataSet d(TempData, TempAttribute);
    vector<double> MidArray = dt.FindMidValue(d);
    vector<double> Midd = dt.FindMidValue(dataSet);

    RootNode->MidValue = Midd;
    double bestmid = MidArray[0];//�������Ե����Ż��ֵ�
    RootNode->Mid = bestmid;
    RootNode->isRoot = true;

    // ���ɾ�����(ѵ��)
    dt.TreeGenerate(dataSet, RootNode);

    DataSet dataSet_pre;
    string fname_pre;
    fname_pre = "D:\\learn\\������\\�˹����ܵ���\\ʵ����������㷨\\testdata.txt";
    Read_file(dataSet_pre, fname_pre);
    vector<string> pre;
    pre = dt.Prediction(dataSet_pre, RootNode);

    //������ȷ�ʰٷֱ�
    double accuracy_score = 0;
    int count_accuracy = 0;
    for (int i = 0; i < pre.size(); i++) {
        if (pre[i] == dataSet_pre.AttributeValue["���"][i]) count_accuracy++;
    }
    accuracy_score = count_accuracy * 1.0 / pre.size();
    cout << fixed << setprecision(2) << "decision_tree's accuracy_score:" << accuracy_score * 100 << "%" << endl;


    // �ͷ��ڴ�
    dt.DestoryDecisionTree(RootNode);

    //����ʱ��
    clock_t finish = clock();
    cout << "(After)The time cost is:" << double(finish - start) / CLOCKS_PER_SEC << endl;

    return 0;
}
