#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
using namespace std;

void reverse(int arr[],int n){
    int l=0, r=n-1;
    while(l<r){
    int temp = arr[l];
    arr[l]=arr[r];
    arr[r]=temp;
    l++ ; r--;   
    }
}

string add(string a, string b) {
    if (a.length() < b.length()) swap(a, b);
    int n1 = a.length(), n2 = b.length(), n = 0;
    int* x = new int[n1];
    int* y = new int[n1];
    int* z = new int[n1 + 1];

    for (int i = 0; i < n1; i++) x[i] = a[i] - '0';
    for (int i = 0; i < n2; i++) y[i] = b[i] - '0';
    for (int i = n2; i < n1; i++) y[i] = 0;

    reverse(x, n1); 
    reverse(y, n1);

    int nho = 0;
    for (int i = 0; i < n1; i++) {
        int temp = x[i] + y[i] + nho;
        z[n++] = temp % 10;
        nho = temp / 10;
    }
    if (nho > 0) z[n++] = nho;

    reverse(z, n);
    string result = "";
    for (int i = 0; i < n; i++) result += (z[i] + '0');

    delete[] x; 
    delete[] y; 
    delete[] z;
    return result;
}

string sub(string a, string b) {
    bool negative = false;
    if (a.length() < b.length() || (a.length() == b.length() && a < b)) {
        swap(a, b);
        negative = true;
    }

    int n1 = a.length(), n2 = b.length(), n = 0;
    int* x = new int[n1];
    int* y = new int[n1];
    int* z = new int[n1];

    for (int i = 0; i < n1; i++) x[i] = a[i] - '0';
    for (int i = 0; i < n2; i++) y[i] = b[i] - '0';
    for (int i = n2; i < n1; i++) y[i] = 0;

    reverse(x, n1); 
    reverse(y, n1);

    int nho = 0;
    for (int i = 0; i < n1; i++) {
        int temp = x[i] - y[i] - nho;
        if (temp < 0) {
            temp += 10;
            nho = 1;
        } else {
            nho = 0;
        }
        z[n++] = temp;
    }

    while (n > 1 && z[n - 1] == 0) n--;
    reverse(z, n);

    string result = (negative ? "-" : "");
    for (int i = 0; i < n; i++) result += (z[i] + '0');

    delete[] x; 
    delete[] y; 
    delete[] z;
    return result;
}

string multiply(string a, string b) {
    bool negative = false;
    if (a[0] == '-') {
        negative = !negative;
        a = a.substr(1);
    }
    if (b[0] == '-') {
        negative = !negative;
        b = b.substr(1);
    }

    int n1 = a.length(), n2 = b.length();
    int* x = new int[n1];
    int* y = new int[n2];
    int* z = new int[n1 + n2]();

    for (int i = 0; i < n1; i++) x[i] = a[i] - '0';
    for (int i = 0; i < n2; i++) y[i] = b[i] - '0';
    reverse(x, n1); 
    reverse(y, n2);

    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n1; j++) {
            int temp = x[j] * y[i] + z[i + j];
            z[i + j] = temp % 10;
            z[i + j + 1] += temp / 10;
        }
    }

    int size = n1 + n2;
    while (size > 1 && z[size - 1] == 0) size--;
    reverse(z, size);

    string result = negative ? "-" : "";
    for (int i = 0; i < size; i++) result += (z[i] + '0');

    delete[] x; 
    delete[] y; 
    delete[] z;
    return result;
}

string subtractStrings(string a, string b) {
    return sub(a, b);  // dùng lại sub()
}

string divide(string a, string b) {
    bool isNegative = false;

    if (a[0] == '-') {
        isNegative = !isNegative;
        a = a.substr(1);
    }
    if (b[0] == '-') {
        isNegative = !isNegative;
        b = b.substr(1);
    }

    if (b == "0") {cout<<"khong the chia cho khong";} return "0";

    if (a == "0" || a.length() < b.length() || (a.length() == b.length() && a < b)) return "0";

    string thuong = "", so_du = "";
    for (int i = 0; i < a.length(); i++) {
        so_du += a[i];
        while (so_du.length() > 1 && so_du[0] == '0') so_du.erase(0, 1);

        int count = 0;
        while (so_du.length() > b.length() || (so_du.length() == b.length() && so_du >= b)) {
            so_du = subtractStrings(so_du, b);
            count++;
        }
        thuong += (count + '0');
    }

    while (thuong.length() > 1 && thuong[0] == '0') thuong.erase(0, 1);
    if (isNegative && thuong != "0") thuong = "-" + thuong;
    return thuong;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string applyOp(string a, string b, char op) {
    if (op == '+') return add(a, b);
    if (op == '-') return sub(a, b);
    if (op == '*') return multiply(a, b);
    if (op == '/') return divide(a, b);
    return "0";
}

string evaluate(const string& expr) {
    stack<string> values;
    stack<char> ops;
    int i = 0;
    while (i < expr.length()) {
        if (isspace(expr[i])) { i++; continue; }

        if (expr[i] == '(') {
            ops.push(expr[i]);
            i++;
        }
        else if (isdigit(expr[i]) || (expr[i] == '-' && (i == 0 || expr[i - 1] == '('))) {
            string val = "";
            if (expr[i] == '-') val += expr[i++];
            while (i < expr.length() && isdigit(expr[i])) val += expr[i++];
            values.push(val);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                string b = values.top(); values.pop();
                string a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            if (!ops.empty()) ops.pop(); // bỏ '('
            i++;
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                string b = values.top(); values.pop();
                string a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(expr[i]);
            i++;
        }
    }

    while (!ops.empty()) {
        string b = values.top(); values.pop();
        string a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

bool isValidExpression(const string& expr) {
    stack<char> parens;
    bool expectOperand = true;

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isspace(c)) continue;

        if (expectOperand) {
            if (isdigit(c)) {
                expectOperand = false;
            } else if (c == '(') {
                parens.push(c);
            } else if (c == '-' && (i + 1 < expr.length()) &&
                       (isdigit(expr[i + 1]) || expr[i + 1] == '(')) {
                expectOperand = true;
            } else {
                return false;
            }
        } else {
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                expectOperand = true;
            } else if (c == ')') {
                if (parens.empty()) return false;
                parens.pop();
                expectOperand = false;
            } else {
                return false;
            }
        }
    }

    return parens.empty() && !expectOperand;
}

int main() {
    ifstream infile("D:\\24120273_Lab1\\tests.txt");
    ofstream outfile("D:\\24120273_Lab1\\output_24120273.txt");

    if (!infile.is_open()) {
        cerr << "Không thể mở file input\n";
        return 1;
    }

    if (!outfile.is_open()) {
        cerr << "Không thể tạo file output\n";
        return 1;
    }

    string line;
    while (getline(infile, line)) {

        try {
            string result = evaluate(line);
            outfile << result << endl;
        } catch (const exception& e) {
            outfile << "Error: " << e.what() << endl;
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
