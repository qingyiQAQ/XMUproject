#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 3; // 3x3�İ���������
struct State {
    vector<vector<int>> board;
    int g; // ���ﵱǰ״̬�Ĵ���
    int h; // ����ʽ���Ƶ�Ŀ��״̬�Ĵ���
    int f; // f = g + h
    pair<int, int> zero; // ��¼�հ׸��λ�ã�������0��λ�ã�
    string path; // ��¼���ﵱǰ״̬��·��

    bool operator>(const State& s) const {
        return f > s.f;
    }
};

// ���������پ���
int heuristic(const vector<vector<int>>& current, const vector<vector<int>>& goal) {
    int dist = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (current[i][j] == 0) continue; // ���Կհ׸�
            for (int m = 0; m < N; ++m) {
                for (int n = 0; n < N; ++n) {
                    if (current[i][j] == goal[m][n]) {
                        dist += abs(i - m) + abs(j - n);
                    }
                }
            }
        }
    }
    return dist;
}

// ���״̬�Ƿ�ΪĿ��״̬
bool isGoal(const vector<vector<int>>& state, const vector<vector<int>>& goal) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (state[i][j] != goal[i][j])
                return false;
    return true;
}

// ��ӡ·��
void printPath(const string& path) {
    for (char move : path) {
        switch (move) {
        case 'U': cout << "Up "; break;
        case 'D': cout << "Down "; break;
        case 'L': cout << "Left "; break;
        case 'R': cout << "Right "; break;
        }
    }
    cout << "\n";
}

// A* �㷨
void aStar(vector<vector<int>> start, vector<vector<int>> goal) {
    priority_queue<State, vector<State>, greater<State>> openSet;
    map<vector<vector<int>>, bool> visited;

    pair<int, int> zeroPos;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (start[i][j] == 0) {
                zeroPos = { i, j };
                break;
            }
        }
    }

    State initialState{ start, 0, heuristic(start, goal), heuristic(start, goal), zeroPos, "" };
    openSet.push(initialState);

    while (!openSet.empty()) {
        State currentState = openSet.top();
        openSet.pop();//��open����ɾ����һ��״̬

        visited[currentState.board] = true;

        if (isGoal(currentState.board, goal)) {
            cout << "Solution found!\n";
            printPath(currentState.path);
            return;
        }//����Ѿ��ﵽĿ��״̬�򷵻�

        vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} }; // �ң����£���
        string moves = "RLDU"; // ��Ӧ������ƶ�

        for (int i = 0; i < 4; ++i) {
            pair<int, int> nextZero = { currentState.zero.first + directions[i].first, currentState.zero.second + directions[i].second };

            if (nextZero.first >= 0 && nextZero.first < N && nextZero.second >= 0 && nextZero.second < N) {
                State nextState = currentState;
                swap(nextState.board[currentState.zero.first][currentState.zero.second], nextState.board[nextZero.first][nextZero.second]);
                nextState.zero = nextZero;
                nextState.g++;
                nextState.h = heuristic(nextState.board, goal);
                nextState.f = nextState.g + nextState.h;
                nextState.path += moves[i];
                //printPath(currentState.path);
                if (!visited[nextState.board]) {
                    openSet.push(nextState);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = { {2, 8, 3}, {1, 6, 4}, {7, 0, 5} };
    vector<vector<int>> goal = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };

    aStar(start, goal);

    return 0;
}
