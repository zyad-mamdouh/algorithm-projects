#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

const int VALUE_MIN = 0;
const int VALUE_MAX = 1'000'000'000;

vector<int> generateRandomDataset(int n, mt19937& rng) {

    uniform_int_distribution<int> dist(VALUE_MIN, VALUE_MAX);

    vector<int> data(n);

    for (int& value : data) {
        value = dist(rng);
    }

    return data;
}

vector<int> generateNearlySortedDataset(int n, mt19937& rng) {

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        data[i] = i;
    }

    int numberOfSwaps = max(1, n / 100);

    uniform_int_distribution<int> dist(0, n - 1);

    for (int i = 0; i < numberOfSwaps; i++) {
        int a = dist(rng);
        int b = dist(rng);

        swap(data[a], data[b]);
    }

    return data;
}

vector<int> generateReverseSortedDataset(int n) {

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        data[i] = n - i;
    }

    return data;
}

vector<int> generateDuplicateDataset(int n, mt19937& rng) {

    const int DUPLICATE_VALUE_RANGE = 10'000;

    uniform_int_distribution<int> dist(0, DUPLICATE_VALUE_RANGE - 1);

    vector<int> data(n);

    for (int& value : data) {
        value = dist(rng);
    }

    return data;
}

bool saveDataset(
    const vector<int>& data,
    const string& filename
) {

    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << '\n';
        return false;
    }

    for (int value : data) {
        file << value << '\n';
    }

    return true;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: ./dataset_generator <N>\n";
        return 1;
    }

    int N = stoi(argv[1]);

    mt19937 rng(42);

    vector<int> randomData =
        generateRandomDataset(N, rng);

    vector<int> nearlySortedData =
        generateNearlySortedDataset(N, rng);

    vector<int> reverseSortedData =
        generateReverseSortedDataset(N);

    vector<int> duplicateData =
        generateDuplicateDataset(N, rng);


        saveDataset(randomData, "datasets/random.txt");

        saveDataset(nearlySortedData, "datasets/nearly_sorted.txt");

        saveDataset(reverseSortedData, "datasets/reverse_sorted.txt");
        
        saveDataset(duplicateData, "datasets/duplicates.txt");

    cout << "Generated datasets with N = "
         << N << '\n';

    return 0;
}
