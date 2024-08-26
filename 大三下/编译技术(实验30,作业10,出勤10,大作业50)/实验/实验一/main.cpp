#include <iostream>
#include <string>
using namespace std;
int isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}//�ж��Ƿ�����ĸ
int isPunct(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '(' || c == ')' || c == ';' || c == '=');
}//�ж��Ƿ��ǺϷ��ַ�
int isNum(char c) {
    return (c >= '0' && c <= '9');
}//�ж��Ƿ���0-9��10��������
int isInt8(char c) {
    return (c >= '0' && c <= '7');
}//�ж��Ƿ���0-7��8��������
int isInt16(char c) {
    return ((c >= '0' && c <= '9') || (c >= 'a') && c <= 'f');
}//�ж��Ƿ���0-f��16��������
int scan(char s[]) {
    int status = 1, i = 0;
    //��ʼ״̬Ϊ1�����Ϸ�״̬Ϊ0��iΪָ��
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
    //��ȥ���ս�̬
    return status;
    //��״̬����
}//״̬ת���㷨
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
}//��״̬����Ϊ��Ӧ����
int main() {

    //����һ���ַ�
    string s;
    getline(cin, s);

    //ѭ����ȡ��ʶ��
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
