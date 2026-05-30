#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include <iomanip>
using namespace std;

bool reverseCompare(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() > b.length();
    return a > b;
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc != 3) {
        cerr << "Loi cu phap! Vui long su dung: test_gen.<ext> <int/strlexi/strlenlexi> <1/2/3/4/5>\n";
        cerr << "Vi du: test_gen.exe int 3\n";
        return 1;
    }

    string type = argv[1];
    int test_num = stoi(argv[2]);

    random_device rd;
    mt19937 gen(rd());

    // PHẦN 1: BÀI INT (N = 100000)
    if (type == "int") {
        int n = 100000;
        cout << n << "\n";
        
        if (test_num == 1) {
            for (int i = n; i >= 1; i--) cout << i << "\n";
        } 
        else if (test_num == 2) {
            for (int i = 0; i < n; i++) cout << -9999 << "\n";
        } 
        else if (test_num == 3) {
            for (int i = 0; i < n; i++) {
                if (i % 4 == 0) cout << INT_MIN << "\n";
                else if (i % 4 == 1) cout << INT_MAX << "\n";
                else if (i % 4 == 2) cout << 0 << "\n";
                else cout << (i * -999) << "\n";
            }
        } 
        else if (test_num == 4) {
            int half = n / 2;
            for (int i = half; i >= 1; i--) cout << i << "\n";
            for (int i = 1; i <= half; i++) cout << i << "\n";
        } 
        else if (test_num == 5) {
            uniform_int_distribution<int> dis(INT_MIN, INT_MAX);
            for (int i = 0; i < n; i++) cout << dis(gen) << "\n";
        }
    }

    // PHẦN 2: BÀI STRLEXI (N = 100000)
    else if (type == "strlexi") {
        int n = 100000;
        cout << n << "\n";
        uniform_int_distribution<int> char_dis(0, 25);

        if (test_num == 1) {
            string identical_string(100, 'z');
            for (int i = 0; i < n; i++) cout << identical_string << "\n";
        } 
        else if (test_num == 2) {
            string prefix(99, 'a');
            for (int i = 0; i < n; i++) cout << prefix << (char)('a' + char_dis(gen)) << "\n";
        } 
        else if (test_num == 3) {
            vector<string> arr(n);
            uniform_int_distribution<int> len_dis(50, 100);
            for (int i = 0; i < n; i++) {
                int len = len_dis(gen);
                string s = "";
                for (int j = 0; j < len; j++) s += (char)('a' + char_dis(gen));
                arr[i] = s;
            }
            sort(arr.begin(), arr.end(), greater<string>());
            for (int i = 0; i < n; i++) cout << arr[i] << "\n";
        } 
        else if (test_num == 4) {
            for (int i = 0; i < n / 2; i++) {
                string short_str = "";
                for (int j = 0; j < 10; j++) short_str += (char)('a' + char_dis(gen));
                string long_str = short_str;
                for (int j = 0; j < 90; j++) long_str += (char)('a' + char_dis(gen));
                cout << short_str << "\n" << long_str << "\n";
            }
        } 
        else if (test_num == 5) {
            uniform_int_distribution<int> len_dis(10, 100);
            for (int i = 0; i < n; i++) {
                int len = len_dis(gen);
                string s = "";
                for (int j = 0; j < len; j++) s += (char)('a' + char_dis(gen));
                cout << s << "\n";
            }
        }
    }

    // PHẦN 3: BÀI STRLENLEXI (N = 10000)
    else if (type == "strlenlexi") {
        int n = 10000;
        cout << n << "\n";
        uniform_int_distribution<int> char_dis(0, 25);

        if (test_num == 1) {
            for (int i = 0; i < n / 2; i++) {
                cout << "aaaaaaaaaaaaaaaaaaaa" << "\n"; // Dài 20
                cout << "zzzzzzzzz" << "\n"; // Dài 9
            }
        } 
        else if (test_num == 2) {
            string prefix(99, 'x');
            for (int i = 0; i < n; i++) cout << prefix << (char)('a' + char_dis(gen)) << "\n";
        } 
        else if (test_num == 3) {
            vector<string> arr(n);
            uniform_int_distribution<int> len_dis(10, 100);
            for (int i = 0; i < n; i++) {
                int len = len_dis(gen);
                string s = "";
                for (int j = 0; j < len; j++) s += (char)('a' + char_dis(gen));
                arr[i] = s;
            }
            sort(arr.begin(), arr.end(), reverseCompare);
            for (int i = 0; i < n; i++) cout << arr[i] << "\n";
        } 
        else if (test_num == 4) {
            string identical_string(100, 'm');
            for (int i = 0; i < n; i++) cout << identical_string << "\n";
        } 
        else if (test_num == 5) {
            uniform_int_distribution<int> len_dis(10, 100);
            for (int i = 0; i < n; i++) {
                int len = (i % 10 < 3) ? ((i % 2 == 0) ? 10 : 100) : len_dis(gen);
                string s = "";
                for (int j = 0; j < len; j++) s += (char)('a' + char_dis(gen));
                cout << s << "\n";
            }
        }
    } 
    else {
        cerr << "Loai bai toan khong hop le! Vui long chon int, strlexi hoac strlenlexi.\n";
        return 1;
    }

    return 0;
}