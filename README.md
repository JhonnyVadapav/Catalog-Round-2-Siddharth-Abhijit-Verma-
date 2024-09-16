# Catalog-Round-2-Siddharth-Abhijit-Verma-
# Polynomial Fitting and Error Detection

This C++ project performs polynomial interpolation using Lagrange's method and identifies incorrect points in a dataset. It reads a set of points with values in various bases, fits a polynomial to these points, and determines which points do not fit the polynomial within a specified tolerance.

## Features

- **Polynomial Interpolation**: Uses Lagrange interpolation to fit a polynomial to a subset of given points.
- **Error Detection**: Identifies points that do not fit the polynomial within a given tolerance.
- **Base Conversion**: Converts values from different numeric bases to decimal.

## Compilation and Execution

### Prerequisites

- A C++ compiler (e.g., `g++`)

### Compilation

To compile the program, use the following command:

```sh
g++ -o polynomial_fitting polynomial_fitting.cpp -std=c++11
```
##Example
```bash
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
```
```output
Polynomial Coefficients: 86087694.933340445161 -3271332407.466505527496 51996967739.723167419434 -449549942949.707519531250 2300177120918.536621093750 -7084328591456.998046875000 12709642929166.861328125000 -11987539344072.025390625000 33198405829203.144531250000 
Incorrect points: 2 3 4 5 6 7 8 9 
```
