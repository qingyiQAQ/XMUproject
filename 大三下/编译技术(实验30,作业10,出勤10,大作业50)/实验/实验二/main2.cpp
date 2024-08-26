#include <iostream>
#include <string>
#include <vector>
using namespace std;

char* s;//输入字符串

class S{
public:
    string place, code, begin, next;
};
class C {
public:
    string true_, false_, code;
};
typedef class {
public:
    string code, place;
}E, T, F;

int tempnum = 1;//临时变量标号
int labelnum = 0;

#define idn 1
#define int8 2
#define int10 3
#define int16 4
#define if_tkn 5
#define while_tkn 6
#define else_tkn 7
#define then_tkn 8
#define do_tkn 9
#define add 10
#define sub 11
#define mul 12
#define div 13
#define less 14
#define greater 15
#define equal 16
#define l_par 17
#define r_par 18
#define sem 19

int lookahead;//下一个token
string lookaheadstring;

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
int scan() {
    int status = 1, flag = 0;
    //初始状态为1，不合法状态为0，i为指针
    while (s[0] && status && !flag) {
        switch (status)
        {
        case 1: {
            if (strncmp(s, "else", 4) == 0) {
                status = 16; s += 4; return status;
            }
            if (strncmp(s, "if", 2) == 0) {
                status = 17; s += 2; return status;
            }
            if (strncmp(s, "do", 2) == 0) {
                status = 18; s += 2; return status;
            }
            if (strncmp(s, "then", 4) == 0) {
                status = 19; s += 4; return status;
            }
            if (strncmp(s, "while", 5) == 0) {
                status = 20; s += 5; return status;
            }
            if (s[0] == '0') status = 4;
            else if (isAlpha(s[0])) {

                status = 3;
            }
            else if (isPunct(s[0])) {
                switch (s[0]) {
                case '+':status = 21; break;
                case '-':status = 22; break;
                case '*':status = 23; break;
                case '/':status = 24; break;
                case '<':status = 25; break;
                case '>':status = 26; break;
                case '=':status = 27; break;
                case '(':status = 28; break;
                case ')':status = 29; break;
                case ';':status = 30; break;
                }
                s++; return status;
            }
            else if (s[0] >= '1' && s[0] <= '9')status = 13;
            else flag = 1;
            break;
        }
        case 2: {
            if (isAlpha(s[0]) || isNum(s[0]))status = 2;
            else if (s[0] == '.' || s[0] == '_')status = 3;
            else flag = 1;
            break;
        }
        case 3: {
            if (isAlpha(s[0]) || isNum(s[0]))status = 3;
            else flag = 1;
            break;
        }
        case 4: {
            if (s[0] == 'o' || s[0] == 'O')status = 5;
            else if (s[0] == 'x' || s[0] == 'X')status = 9;
            else if (s[0] == '.')status = 14;
            else flag = 1;
            break;
        }
        case 5: {
            if (isInt8(s[0]))status = 6;
            else flag = 1;
            break;
        }
        case 6: {
            if (isInt8(s[0]))status = 6;
            else if (s[0] == '.')status = 7;
            else flag = 1;
            break;
        }
        case 7: {
            if (isInt8(s[0]))status = 8;
            else flag = 1;
            break;
        }
        case 8: {
            if (isInt8(s[0]))status = 8;
            else flag = 1;
            break;
        }
        case 9: {
            if (isInt16(s[0]))status = 10;
            else flag = 1;
            break;
        }
        case 10: {
            if (isInt16(s[0]))status = 10;
            else if (s[0] == '.')status = 11;
            else flag = 1;
            break;
        }
        case 11: {
            if (isInt16(s[0]))status = 12;
            else flag = 1;
            break;
        }
        case 12: {
            if (isInt16(s[0]))status = 12;
            else flag = 1;
            break;
        }
        case 13: {
            if (isNum(s[0]))status = 13;
            else if (s[0] == '.')status = 14;
            else flag = 1;
            break;
        }
        case 14: {
            if (isNum(s[0]))status = 15;
            else flag = 1;
            break;
        }
        case 15: {
            if (isNum(s[0]))status = 15;
            else flag = 1;
            break;
        }
        }
        if(!flag)s++;
    }
    if (status == 1 || status == 5 || status == 7
        || status == 9 || status == 11 || status == 14)status = 0;
    //除去非终结态
    return status;
    //将状态返回
}//状态转移算法
int processStatus(int status) {
    switch (status)
    {
    case 2:
    case 3:return idn; break;
    case 6:
    case 8:return int8; break;
    case 10:
    case 12:return int16; break;
    case 4:
    case 13:
    case 15:return int10; break;
    case 16:return else_tkn; break;
    case 17:return if_tkn; break;
    case 18:return do_tkn; break;
    case 19:return then_tkn; break;
    case 20:return while_tkn; break;
    case 21:return add; break;
    case 22:return sub; break;
    case 23:return mul; break;
    case 24:return div; break;
    case 25:return less; break;
    case 26:return greater; break;
    case 27:return equal; break;
    case 28:return l_par; break;
    case 29:return r_par; break;
    case 30:return sem; break;
    }
    return 0;
}//将状态处理为对应属性
int getToken() {
    while (s[0] == ' ')s++;//每次获得token前先去除空格
    char* s_copy = s;
    int type = processStatus(scan());
    int length = 0;
    while (s_copy + length != s) length++;
    lookaheadstring = string(s_copy, length);
    return type;
}
void err() {
    cout << "error!";
    exit(1);
}
string newtemp() {
    return "t" + to_string(tempnum++);
}
string newlabel() {
    return "L" + to_string(labelnum++);
}
S parse_S0(S);
S parse_S(S);
S parse_S_(C&,S);
C parse_C();
C parse_C_(E);
E parse_E();
E parse_E_(E);
F parse_F();
T parse_T();
F parse_T_(T);
void matchToken(int expected) {
    if (lookahead != expected) {
        err();
    }
    else {
        lookahead = getToken();
    }
}
S parse_S0(S s) {
    S s1 = parse_S(s);
    matchToken(sem);
    return s1;
}
S parse_S(S s) {
    S s1;
    if (lookahead == idn) {
        //cout << "S-> id = E" << endl;
        string id = lookaheadstring;
        matchToken(idn);
        matchToken(equal);
        E e = parse_E();
        s1.code = e.code + id + " := " + e.place + "\n";
    }
    else if (lookahead == while_tkn) {
        //cout << "S-> while C do S" << endl;
        matchToken(while_tkn);
        C c = parse_C();
        if (s.begin == "")s1.begin = newlabel();
        else s1.begin = s.begin;
        c.true_ = newlabel();
        c.false_ = s.next;
        c.code.replace(c.code.find('!'), 1, c.true_);
        c.code.replace(c.code.find('?'), 1, c.false_);
        matchToken(do_tkn);
        s1.next = s1.begin;
        S s2 = parse_S(s1);
        s2.next = s.begin;
        s1.code = ((s.begin == "") ? (s1.begin + ": ") : "") 
            + c.code + c.true_ + ": " + s2.code + "goto: " + s1.begin + "\n";
    }
    else if (lookahead == if_tkn) {
        //cout << "S-> if C then S S'" << endl;
        matchToken(if_tkn);
        C c = parse_C();
        c.true_ = newlabel();
        c.false_ = s.next;
        c.code.replace(c.code.find('!'), 1, c.true_);
        c.code.replace(c.code.find('?'), 1, c.false_);
        matchToken(then_tkn);
        s1.next = s.next;
        s1.begin = c.true_;
        S s2 = parse_S(s1);
        S s3 = parse_S_(c,s1);
        s2.next = s.next;
        s3.next = s.next;
        s1.code = c.code + c.true_ + ": " + s2.code + s3.code;
    }
    else err();
    return s1;
}
S parse_S_(C& c,S s) {
    S s1;
    if (lookahead == else_tkn) {
        //cout << "S'-> else S" << endl;
        matchToken(else_tkn);
        S s2 = parse_S(s1);
        s1.next = s.next;
        c.false_ = newlabel();
        c.code.replace(c.code.find('?'), 1, c.false_);
        s1.code = "goto: " + s.next + "\n" + c.false_ + ": " + s2.code;
    }
    else return s1;
}
C parse_C() {
    //cout << "C-> E C'" << endl;
    E e = parse_E();
    return parse_C_(e);
}
C parse_C_(E e) {
    C c1;
    if (lookahead == greater) {
        //cout << "C'-> > E" << endl;
        matchToken(lookahead);
        E e1 = parse_E();
        c1.code = e.code + e1.code + "if " + e.place + " > " + e1.place + " goto: !\ngoto: ?\n";
    }
    else if (lookahead == less) {
        //cout << "C'-> < E" << endl;
        matchToken(lookahead);
        E e1 = parse_E();
        c1.code = e.code + e1.code + "if " + e.place + " < " + e1.place + " goto: !\ngoto: ?\n";
    }
    else if (lookahead == equal) {
        //cout << "C'-> = E" << endl;
        matchToken(lookahead);
        E e1 = parse_E();
        c1.code = e.code + e1.code + "if " + e.place + " = " + e1.place + " goto: !\ngoto: ?\n";
    }
    else err();
    return c1;
}
E parse_E() {
    //cout << "E-> T E'" << endl;
    T t = parse_T();
    return parse_E_(t);
}
E parse_E_(E e) {
    E e1;
    if (lookahead == add) {
        //cout << "E'-> + E E'" << endl;
        matchToken(add);
        E e2 = parse_E();
        e1.place = newtemp();
        e1.code = e.code + e2.code + e1.place + " := " + e.place + " + " + e2.place + "\n";
        return parse_E_(e1);
    }
    else if (lookahead == sub) {
        //cout << "E'-> - E E'" << endl;
        matchToken(sub);
        E e2 = parse_E();
        e1.place = newtemp();
        e1.code = e.code + e2.code + e1.place + " := " + e.place + " - " + e2.place + "\n";
        return parse_E_(e1);
    }
    else {
        return e;
    }
}
T parse_T() {
    //cout << "T-> F T'" << endl;
    F f = parse_F();
    return parse_T_(f);
}
T parse_T_(T t) {
    T t1;
    if (lookahead == mul) {
        //cout << "T'-> * F T'" << endl;
        matchToken(mul);
        F f = parse_F();
        t1.place = newtemp();
        t1.code = t.code + f.code + t1.place + " := " + t.place + " * " + f.place + "\n";
        return parse_T_(t1);
    }
    else if (lookahead == div) {
        //cout << "T'-> / F T'" << endl;
        matchToken(div);
        F f = parse_F();
        t1.place = newtemp();
        t1.code = t.code + f.code + t1.place + " := " + t.place + " / " + f.place + "\n";
        return parse_T_(t1);
    }
    else {
        return t;
    }
}
F parse_F() {
    F f;
    if (lookahead == l_par) {
        //cout << "F-> (E)" << endl;
        matchToken(l_par);
        E e = parse_E();
        matchToken(r_par);
        f.place = e.place;
        f.code = e.code;
    }
    else if (lookahead == idn) {
        //cout << "F-> idn" << endl;
        f.place = lookaheadstring;
        f.code = "";
        matchToken(idn);
    }
    else if (lookahead == int8) {
        //cout << "F-> idn8" << endl;
        f.place = to_string(stoi(lookaheadstring.substr(2), nullptr, 8));
        f.code = "";
        matchToken(int8);
    }
    else if (lookahead == int10) {
        //cout << "F-> idn10" << endl;
        f.place = lookaheadstring;
        f.code = "";
        matchToken(int10);
    }
    else if (lookahead == int16) {
        //cout << "F-> idn16" << endl;
        f.place = to_string(stoi(lookaheadstring.substr(2), nullptr, 16));
        f.code = "";
        matchToken(int16);
    }
    else err();
    return f;
}
int main() {
    string input;
    getline(cin, input);
    s = (char*)input.c_str();
    lookahead = getToken();
    S s;
    s.next = newlabel();
    s.begin = "";
    s.code = "";
    cout << parse_S0(s).code;
    cout << "L0:  //S.next";
}
//while (a3+15)>0xa do if x2 = 7 then while y<z do y = x * y / z;