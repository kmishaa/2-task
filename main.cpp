#include <iostream>
#include <set>

using namespace std;

class troika {
public:
    troika() {
        col_a = -1;
        col_b = -1;
        col_c = -1;
    }
    troika(const int& a, const int& b, const int& c) {
        col_a = a;
        col_b = b;
        col_c = c;
    }
    int col_a, col_b, col_c;
};

bool operator==(const troika& lhs, const troika& rhs) {
    return lhs.col_a == rhs.col_a && lhs.col_b == rhs.col_b && lhs.col_c == rhs.col_c;
}

bool operator<(const troika& lhs, const troika& rhs) {
    if (lhs.col_a < rhs.col_a) return true;
    if (lhs.col_a == rhs.col_a && lhs.col_b < rhs.col_b) return true;
    if (lhs.col_a == rhs.col_a && lhs.col_b == rhs.col_b && lhs.col_c < rhs.col_c) return true;
    return false;
}

troika start(const int& a, const int& b, const int& c, const int& bank) {
    int col_a = bank / a;
    if (bank - col_a * a == 0) return troika(col_a, 0, 0);
    while (col_a >= 0) {
        if (bank - col_a * a < min(b, c)) { col_a--; continue; }
        int col_b = (bank - col_a * a) / b;
        if (bank - col_a * a - col_b * b == 0) return troika(col_a, col_b, 0);
        while (col_b >= 0) {
            if (bank - col_a * a - col_b * b < c || (bank - col_a * a - col_b * b) % c != 0) { col_b--; continue; }
            int col_c = (bank - col_a * a - col_b * b) / c;
            return troika(col_a, col_b, col_c);
        }
        col_a--;
    }
    return troika();
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int x, y, z;
    cin >> x >> y >> z;

    int bank = x + y + z;

    troika start_t = start(a, b, c, bank);
    if (start_t == troika()) { cout << 0; return 0; }
    set<troika> trs;
    trs.insert(start_t);
    //cout << start_t.col_a << ", " << start_t.col_b << ", " << start_t.col_c << endl;
    while (start_t.col_a > 0) {
        start_t.col_a--;
        int col_b = (bank - start_t.col_a * a) / b;
        if (bank - start_t.col_a * a - col_b * b == 0) trs.insert(troika(start_t.col_a, col_b, 0));
        while (col_b >= 0) {
            int col_c = (bank - start_t.col_a * a - col_b * b) / c;
            if (bank - start_t.col_a * a - col_b * b - col_c * c == 0) trs.insert(troika(start_t.col_a, col_b, col_c));
            col_b--;
        }
    }

    //for (troika t : trs) {
    //    cout << t.col_a << ", " << t.col_b << ", " << t.col_c << endl;
    //}

    cout << trs.size();

    return 0;
}
