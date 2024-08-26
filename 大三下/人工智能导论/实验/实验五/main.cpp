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
定义node结点类
定义决策树类
决策树类内包含生成决策树函数——treegenerate  递归函数中，有三个基类，停止递归
1、全属于同一种类别，标记为叶结点
2、当前属性集为空，标记为该数据集中最多的类
3、样本集合为空，标记为叶结点，类别是父结点最多的类
*/
//  start, finish;

class DataSet {
public:
    vector<string> Attribute; //属性标签："花萼长度","花萼宽度","花萼长度","花瓣长度"
    vector<vector<string>> Data; // 属性值：5.1 3.5 1.4 0.2
    map<string, vector<string>> AttributeValue; //映射类型，整个表的数据：{"类别":{...},"花萼长度":{5.1,4.9,5.7....},"..":{...}}

    DataSet(); //初始构造函数
    DataSet(vector<vector<string>> data, vector<string> attribute); //过程的构造函数
    void Connect(); //关联属性标签与属性值
};
DataSet::DataSet() {
    Attribute = { "花萼长度","花萼宽度","花瓣长度","花瓣宽度" };
}
DataSet::DataSet(vector<vector<string>> data, vector<string> attribute) {
    Data = data;
    Attribute = attribute;
    Connect();
}
void DataSet::Connect() {
    if (Data.empty()) return;

    vector<vector<string>> attribute; //存储属性值的转置
    vector<string> TempAttribute = Attribute; //存储属性标签
    TempAttribute.push_back("类别"); //5
    attribute.resize(TempAttribute.size()); //5

    // Data 150行x5列
    for (int i = 0; i < Data[0].size(); i++) {  //i 0-4
        for (int j = 0; j < Data.size(); j++) { //j 0-149
            attribute[i].push_back(Data[j][i]);
        }

        AttributeValue[TempAttribute[i]] = attribute[i];
    }

}
void Read_file(DataSet& dataSet, string fname) {
    // 读取文件
    ifstream file_data(fname, ios::in);
    if (!file_data.is_open()) {
        cout << "Error: opening file fail" << endl;
        exit(1);
    }
    else {
        string line;
        vector<string> words;
        string word;

        // 读取数据
        istringstream sin;
        // 按行读取数据
        while (getline(file_data, line))
        {
            word.clear();
            words.clear();
            sin.clear();
            sin.str(line);
            while (getline(sin, word, ' ')) {
                words.push_back(word);  //将每一格中的数据逐个push
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
    //判断标准
    double Mid;
    string Attribute;
    vector<Node*> ChildrenNode;
    double nodeAccuracy;

};

class DecisionTree {
public:
    void TreeGenerate(DataSet& dataSet, Node* Father); //生成决策树，返回根结点的指针
    double CalcEntropy(DataSet& dataSet); //计算一个数据集的信息熵
    double CalcInfoGain(double midValue, DataSet& dataSet, string Value); //计算一个属性的信息增益

    double AccuracyRate(DataSet& dataSet, Node* node);
    vector<double> FindMidValue(DataSet& dataSet); //计算一个属性的划分点，构建循环计算一个属性的信息增益
    map<string, double> FindBestInfoGain(DataSet& dataSet); //找最大信息增益，返回最优属性以及最大增益的映射
    map<string, int> CountTimes(DataSet& dataSet); //计算各类别的样本数量
    void DestoryDecisionTree(Node* node);//删除决策树
    vector<string> Prediction(DataSet& dataSet, Node* node);
};
void DecisionTree::TreeGenerate(DataSet& dataSet, Node* Father) {

    Node* newNode = new Node;
    Father->ChildrenNode.push_back(newNode);
    vector<double> newMid = FindMidValue(dataSet);//本次的各属性最优划分点
    newNode->MidValue = newMid;

    // 情况1：如果数据集中数据属于同一类别，将node标记为C类叶结点
    bool isSame = true;
    string curAttr = dataSet.AttributeValue["类别"][0];
    for (int i = 0; i < dataSet.AttributeValue["类别"].size(); i++) {
        if (dataSet.AttributeValue["类别"][i] != curAttr) {
            isSame = false;
            break;
        }
    }
    if (isSame) {
        newNode->isLeaf = true;
        newNode->node_Attribute = curAttr;
        return;
    }

    // 情况2：属性集为空或数据集中样本在属性集上取值相同
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

    //情况3:从属性集中划分最优属性
    map<string, double> BestAttributeMap = FindBestInfoGain(dataSet);
    string BestAttribute = BestAttributeMap.begin()->first;
    newNode->Attribute = BestAttribute;

    //找出一个属性中的最优划分点
    vector<string> TempAttribute;
    TempAttribute.push_back(BestAttribute);
    vector<string> TempValue = dataSet.AttributeValue[BestAttribute];
    vector<string> TempAttr = dataSet.AttributeValue["类别"];
    vector<vector<string>> TempData(TempValue.size());
    for (int i = 0; i < TempValue.size(); i++) {
        TempData[i].push_back(TempValue[i]);
        TempData[i].push_back(TempAttr[i]);
    }
    DataSet d(TempData, TempAttribute);
    vector<double> MidArray = FindMidValue(d);

    double bestmid = MidArray[0];//最优属性的最优划分点
    newNode->Mid = bestmid;
    vector<vector<vector<string>>> NextData(2);//下一次分类的数据
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
            //情况4：需要预剪枝
            DataSet NewDataSet(NextData[i], dataSet.Attribute);

            //对newNode的属性初始化
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

            //对newChild初始化
            mp = CountTimes(NewDataSet); //先标记为该数据集中数量最多的类
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

// 预剪枝
double DecisionTree::AccuracyRate(DataSet& dataSet, Node* node) {
    vector<string> ClassArray = dataSet.AttributeValue["类别"];
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
//计算dataSet数据集中所有类别以及样本的出现次数
map<string, int>DecisionTree::CountTimes(DataSet& dataSet) {
    map<string, int> ClassCount;
    vector<string> classList = dataSet.AttributeValue["类别"];
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
    delete node;	//释放节点
    node = nullptr;
}

double DecisionTree::CalcEntropy(DataSet& dataSet) {
    int sum = dataSet.Data.size();//总数据数
    map<string, int> ClassCount = CountTimes(dataSet);

    vector<string> classList = dataSet.AttributeValue["类别"];
    double entropy = 0;//信息熵

    for (auto item = ClassCount.begin(); item != ClassCount.end(); item++) {
        double p = (double)item->second / sum;
        if (p == 0) entropy -= 0;
        else entropy -= p * log(p) / log(2);
    }
    return entropy;
}


vector<double> DecisionTree::FindMidValue(DataSet& dataSet) {//找出属性中最优划分点
    vector<double> bestMid;

    for (int i = 0; i < dataSet.Attribute.size(); i++) {
        vector<string> valueString = dataSet.AttributeValue[dataSet.Attribute[i]];

        //将属性值从string类型转为double类型
        vector<double> valueDouble;
        for (int j = 0; j < valueString.size(); j++) {
            valueDouble.push_back(stod(valueString[j]));
        }

        //排序double类型
        sort(valueDouble.begin(), valueDouble.end());

        vector<double> midArray;
        for (int j = 0; j < valueDouble.size() - 1; j++) {
            midArray.push_back((valueDouble[j] + valueDouble[j + 1]) / 2);
        }

        double bestmid;
        if (midArray.empty()) bestmid = valueDouble[0];
        else bestmid = midArray[0]; //初始化中间点
        double maxmidEntrophy = 0; //划分点最大的信息熵

        for (int j = 0; j < midArray.size(); j++) {
            double gain = CalcInfoGain(midArray[j], dataSet, dataSet.Attribute[i]);
            if (gain >= maxmidEntrophy) {
                maxmidEntrophy = gain;
                bestmid = midArray[j];
            }
        }
        bestMid.push_back(bestmid); //将最优划分点放入vector容器
    }
    return bestMid;
}

double DecisionTree::CalcInfoGain(double midValue, DataSet& dataSet, string Value) { //计算一个属性的信息增益
    vector<vector<string>> leftData;
    vector<vector<string>> rightData;
    int leftCount = 0;
    int sum = dataSet.Data.size();//样本数量
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
    double maxgain = 0;//属性的最大信息增益
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
    //开始计时
    clock_t start = clock();

    // 创建一个数据集对象
    DataSet dataSet;
    string fname = "D:\\learn\\大三下\\人工智能导论\\实验五决策树算法\\traindata.txt";
    Read_file(dataSet, fname);

    DecisionTree dt;
    Node* RootNode = new Node;

    //初始化父结点
    map<string, double> BestAttributeMap = dt.FindBestInfoGain(dataSet);
    string BestAttribute = BestAttributeMap.begin()->first;
    RootNode->Attribute = BestAttribute;

    vector<string> TempAttribute;
    TempAttribute.push_back(BestAttribute);
    vector<string> TempValue = dataSet.AttributeValue[BestAttribute];
    vector<string> TempAttr = dataSet.AttributeValue["类别"];
    vector<vector<string>> TempData(TempValue.size());
    for (int i = 0; i < TempValue.size(); i++) {
        TempData[i].push_back(TempValue[i]);
        TempData[i].push_back(TempAttr[i]);
    }
    DataSet d(TempData, TempAttribute);
    vector<double> MidArray = dt.FindMidValue(d);
    vector<double> Midd = dt.FindMidValue(dataSet);

    RootNode->MidValue = Midd;
    double bestmid = MidArray[0];//最优属性的最优划分点
    RootNode->Mid = bestmid;
    RootNode->isRoot = true;

    // 生成决策树(训练)
    dt.TreeGenerate(dataSet, RootNode);

    DataSet dataSet_pre;
    string fname_pre;
    fname_pre = "D:\\learn\\大三下\\人工智能导论\\实验五决策树算法\\testdata.txt";
    Read_file(dataSet_pre, fname_pre);
    vector<string> pre;
    pre = dt.Prediction(dataSet_pre, RootNode);

    //计算正确率百分比
    double accuracy_score = 0;
    int count_accuracy = 0;
    for (int i = 0; i < pre.size(); i++) {
        if (pre[i] == dataSet_pre.AttributeValue["类别"][i]) count_accuracy++;
    }
    accuracy_score = count_accuracy * 1.0 / pre.size();
    cout << fixed << setprecision(2) << "decision_tree's accuracy_score:" << accuracy_score * 100 << "%" << endl;


    // 释放内存
    dt.DestoryDecisionTree(RootNode);

    //运行时间
    clock_t finish = clock();
    cout << "(After)The time cost is:" << double(finish - start) / CLOCKS_PER_SEC << endl;

    return 0;
}
