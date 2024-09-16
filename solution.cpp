#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Convert value from given base to decimal
long long decode_base(const string& value, int base) {
    return stoll(value, nullptr, base);
}

// Perform polynomial fitting using Gaussian elimination
vector<double> lagrange_interpolation(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    vector<double> coeffs(n);

    // Construct the Vandermonde matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = pow(x[i], n - j - 1);
        }
        b[i] = y[i];
    }

    // Gaussian elimination
    for (int i = 0; i < n; ++i) {
        // Find the maximum element in this column
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (fabs(A[k][i]) > fabs(A[max_row][i])) {
                max_row = k;
            }
        }
        // Swap rows
        swap(A[i], A[max_row]);
        swap(b[i], b[max_row]);

        // Check for zero diagonal elements
        if (fabs(A[i][i]) < 1e-10) {
            cerr << "Matrix is singular or nearly singular" << endl;
            exit(EXIT_FAILURE);
        }

        // Eliminate column below
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Back substitution
    for (int i = n - 1; i >= 0; --i) {
        coeffs[i] = b[i] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            b[k] -= A[k][i] * coeffs[i];
        }
    }

    return coeffs;
}

// Evaluate polynomial with coefficients at x
double evaluate_polynomial(const vector<double>& coeffs, double x) {
    double result = 0.0;
    double power = 1.0;
    for (double coeff : coeffs) {
        result += coeff * power;
        power *= x;
    }
    return result;
}

// Find incorrect points in the given test case
void find_incorrect_points(const map<string, map<string, string>>& test_case) {
    map<string, string> keys = test_case.at("keys");
    int n = stoi(keys.at("n"));
    int k = stoi(keys.at("k"));
    
    vector<double> x_vals;
    vector<double> y_vals;
    
    for (const auto& [key, value] : test_case) {
        if (key != "keys") {
            int x = stoi(key);
            int base = stoi(value.at("base"));
            long long y = decode_base(value.at("value"), base);
            x_vals.push_back(static_cast<double>(x));
            y_vals.push_back(static_cast<double>(y));
        }
    }
    
    vector<double> coeffs = lagrange_interpolation(x_vals, y_vals);
    
    cout << "Polynomial Coefficients: ";
    for (double coeff : coeffs) {
        cout << fixed << setprecision(12) << coeff << " "; // Increased precision
    }
    cout << endl;
    
    vector<int> incorrect_points;
    
    for (const auto& [key, value] : test_case) {
        if (key != "keys") {
            int x = stoi(key);
            long long expected_y = decode_base(value.at("value"), stoi(value.at("base")));
            double actual_y = evaluate_polynomial(coeffs, static_cast<double>(x));
            
            // Increased tolerance level
            if (fabs(actual_y - expected_y) >= 1e-3) { // Adjusted tolerance
                incorrect_points.push_back(x);
            }
        }
    }
    
    cout << "Incorrect points: ";
    for (int x : incorrect_points) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    map<string, map<string, string>> test_case = {
        {"keys", {{"n", "9"}, {"k", "6"}}},
        {"1", {{"base", "10"}, {"value", "28735619723837"}}},
        {"2", {{"base", "16"}, {"value", "1A228867F0CA"}}},
        {"3", {{"base", "12"}, {"value", "32811A4AA0B7B"}}},
        {"4", {{"base", "11"}, {"value", "917978721331A"}}},
        {"5", {{"base", "16"}, {"value", "1A22886782E1"}}},
        {"6", {{"base", "10"}, {"value", "28735619654702"}}},
        {"7", {{"base", "14"}, {"value", "71AB5070CC4B"}}},
        {"8", {{"base", "9"}, {"value", "122662581541670"}}},
        {"9", {{"base", "8"}, {"value", "642121030037605"}}}
    };
    
    find_incorrect_points(test_case);
    
    return 0;
}
