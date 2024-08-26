#include <iostream>
#include <string>
using namespace std;
int isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}//判断是否是字母
int isPunct(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '(' || c == ')' || c == ';' || c == '=');
}//判断是否是合法字符
int isNum(char c) {
    return (c >= '0' && c <= '9');
}//判断是否是0-9的10进制数字
int isInt8(char c) {
    return (c >= '0' && c <= '7');
}//判断是否是0-7的8进制数字
int isInt16(char c) {
    return ((c >= '0' && c <= '9') || (c >= 'a') && c <= 'f');
}//判断是否是0-f的16进制数字
int scan(char s[]) {
    int status = 1, i = 0;
    //初始状态为1，不合法状态为0，i为指针
    while (s[i] && status) {
        switch (status)
        {
        case 1: {
            /*char s_copy[10];
            strncpy(s_copy, s, n);
            s_copy[n] = '\0';*/
            if (strcmp(s, "else") == 0) {
                status = 17; i += 3; break;
            }
            if (strcmp(s, "if") == 0) {
                status = 18; i += 1; break;
            }
            if (strcmp(s, "do") == 0) {
                status = 20; i += 1; break;
            }
            if (strcmp(s, "then") == 0) {
                status = 21; i += 3; break;
            }
            if (strcmp(s, "while") == 0) {
                status = 22; i += 4; break;
            }
            if (s[i] == '0') status = 5;
            else if (isAlpha(s[i]))status = 2;
            else if (isPunct(s[i]))status = 19;
            else if (s[i] >= '1' && s[i] <= '9')status = 14;
            else status = 0;
            break;
        }
        case 2: {
            if (isAlpha(s[i]) || isNum(s[i]))status = 3;
            else status = 0;
            break;
        }
        case 3: {
            if (isAlpha(s[i]) || isNum(s[i]))status = 3;
            else if (s[i] == '.' || s[i] == '_')status = 4;
            else status = 0;
            break;
        }
        case 4: {
            if (isAlpha(s[i]) || isNum(s[i]))status = 3;
            else status = 0;
            break;
        }
        case 5: {
            if (s[i] == 'o' || s[i] == 'O')status = 6;
            else if (s[i] == 'x' || s[i] == 'X')status = 10;
            else if (s[i] == '.')status = 16;
            else status = 0;
            break;
        }
        case 6: {
            if (isInt8(s[i]))status = 7;
            else status = 0;
            break;
        }
        case 7: {
            if (isInt8(s[i]))status = 7;
            else if (s[i] == '.')status = 8;
            else status = 0;
            break;
        }
        case 8: {
            if (isInt8(s[i]))status = 9;
            else status = 0;
            break;
        }
        case 9: {
            if (isInt8(s[i]))status = 9;
            else status = 0;
            break;
        }
        case 10: {
            if (isInt16(s[i]))status = 11;
            else status = 0;
            break;
        }
        case 11: {
            if (isInt16(s[i]))status = 11;
            else if (s[i] == '.')status = 12;
            else status = 0;
            break;
        }
        case 12: {
            if (isInt16(s[i]))status = 13;
            else status = 0;
            break;
        }
        case 13: {
            if (isInt16(s[i]))status = 13;
            else status = 0;
            break;
        }
        case 14: {
            if (isNum(s[i]))status = 14;
            else if (s[i] == '.')status = 15;
            else status = 0;
            break;
        }
        case 15: {
            if (isNum(s[i]))status = 16;
            else status = 0;
            break;
        }
        default:status = 0;
        }
        i++;
    }
    if (status==1 || status == 6 || status == 8 
        || status == 10 || status == 12 || status == 15)status = 0;
    //除去非终结态
    return status;
    //将状态返回
}//状态转移算法
string processStatus(int status) {
    switch (status)
    {
    case 2:
    case 3:
    case 4:return "IDN"; break;
    case 7:
    case 9:return "INT8"; break;
    case 11:
    case 13:return "INT16"; break;
    case 5:
    case 14:
    case 16:return "INT10"; break;
    case 17:return "ELSE"; break;
    case 18:return "IF"; break;
    case 19:return "_"; break;
    case 20:return "DO"; break;
    case 21:return "THEN"; break;
    case 22:return "WHILE"; break;
    }
}//将状态处理为对应属性
int main() {

    //输入一行字符
    string s;
    getline(cin, s);

    //循环读取并识别
    int i = 0, j = 0;
    char temp[100];
    while (s[i + j]) {
        if (!(s[i + j] == ' ' || isPunct(s[i + j]))) {
            temp[j] = s[i + j];
            j++;
            continue;
        }
        temp[j] = '\0';
        cout << temp << "\t" << processStatus(scan(temp)) << endl;
        char punct = 0;
        while (s[i + j] == ' ' || isPunct(s[i + j])) {
            if (isPunct(s[i + j]))punct = s[i + j];
            j++;
        }
        if (punct)cout << punct << "\t_" << endl;
        i += j;
        j = 0;
    }

    return 0;
}
