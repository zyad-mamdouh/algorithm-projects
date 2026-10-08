#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> loadDataset(const string& filename) {
    ifstream file(filename);
    vector<int> data;

    int value;
    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

bool validateRandom(const vector<int>& data) {
    return !data.empty();
}

bool validateNearlySorted(const vector<int>& data) {
    int disorderCount = 0;

    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] < data[i - 1]) {
            disorderCount++;
        }
    }

    return disorderCount <= static_cast<int>(data.size() * 0.02);
}

bool validateReverseSorted(const vector<int>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] >= data[i - 1]) {
            return false;
        }
    }

    return true;
}

bool validateDuplicates(const vector<int>& data) {
    if (data.empty()) {
        return false;
    }

    vector<int> sorted = data;
    sort(sorted.begin(), sorted.end());

    int uniqueValues = 1;

    for (size_t i = 1; i < sorted.size(); i++) {
        if (sorted[i] != sorted[i - 1]) {
            uniqueValues++;
        }
    }

    return uniqueValues < static_cast<int>(data.size());
}

void validateDataset(
    const string& name,
    const string& filename,
    int expectedSize,
    bool (*validator)(const vector<int>&)
) {
    vector<int> data = loadDataset(filename);

    cout << name << ":\n";
    cout << "  Count: " << data.size() << "\n";

    if (data.size() != expectedSize) {
        cout << "  FAIL: incorrect size\n";
        return;
    }

    if (validator(data)) {
        cout << "  PASS\n";
    } else {
        cout << "  FAIL\n";
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Usage: ./dataset_validator <N>\n";
        return 1;
    }

    int expectedSize = stoi(argv[1]);

    validateDataset(
        "Random",
        "datasets/random.txt",
        expectedSize,
        validateRandom
    );

    validateDataset(
        "Nearly Sorted",
        "datasets/nearly_sorted.txt",
        expectedSize,
        validateNearlySorted
    );

    validateDataset(
        "Reverse Sorted",
        "datasets/reverse_sorted.txt",
        expectedSize,
        validateReverseSorted
    );

    validateDataset(
        "Duplicates",
        "datasets/duplicates.txt",
        expectedSize,
        validateDuplicates
    );

    return 0;
}