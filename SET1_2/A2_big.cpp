#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>

template<typename Value>
class HashTable {
public:
    HashTable() {
        table.resize(size);
    }

    void insert(const Value& value) {
        size_t index = hash(value);
        size_t step = 1;

        while (table[index] != empty && table[index] != deleted) {
            index = (index + step) % table.size();
            step++;
        }

        table[index] = value;
    }

    void insertSquare(const Value& value) {
        size_t index = hash(value);
        size_t step = 1;

        while (table[index] != empty && table[index] != deleted) {
            index = (index + step + step * step) % table.size();
            step++;
        }

        table[index] = value;
    }

    void insertCube(const Value& value) {
        size_t index = hash(value);
        size_t step = 1;

        while (table[index] != empty && table[index] != deleted) {
            index = (index + step + step * step + step * step * step) % table.size();
            step++;
        }

        table[index] = value;
    }

    int stepsToFind(const Value& value) {
        size_t index = hash(value);
        size_t step = 0;

        while (table[index] != empty) {
            index = (index + step) % size;
            step++;
            if (table[index] == value) {
                return step;
            }
        }

        return -1;
    }

    int stepsToFindSquare(const Value& value) {
        size_t index = hash(value);
        size_t step = 0;

        while (table[index] != empty) {
            index = (index + step + step * step) % size;
            step++;
            if (table[index] == value) {
                return step;
            }
        }

        return -1;
    }

    int stepsToFindCube(const Value& value) {
        size_t index = hash(value);
        size_t step = 0;

        while (table[index] != empty) {
            index = (index + step + step * step + step * step * step) % size;
            step++;
            if (table[index] == value) {
                return step;
            }
        }

        return -1;
    }

    std::pair<double, double> getClasterInfo() {
        int count = 0;
        int size = 0;
        int overall_size = 0;
        for (size_t i = 0; i < table.size(); i++) {
            if (table[i] != empty && table[i] != deleted) {
                size++;
            } else {
                if (size > 0) {
                    overall_size += size;
                    count++;
                    size = 0;
                }
            }
        }
        return {static_cast<double>(count), static_cast<double>(overall_size) / count};
    }

private:
    static constexpr size_t size = 100000;
    static constexpr Value empty = Value();
    static constexpr Value deleted = Value();

    std::vector<Value> table;
    size_t hash(const Value& value) const {
        return std::hash<Value>{}(value) % table.size();
    }
};

void bigTest() {
        HashTable<int> linearTable, squareTable, cubeTable;
    std::vector<int> values;
    values.reserve(80000);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    for (int i = 0; i < 80000; i++) {
        int value = dist(gen);
        linearTable.insert(value);
        squareTable.insertSquare(value);
        cubeTable.insertCube(value);
        values.push_back(value);
    }

    double linearStepsAvg = 0, squareStepsAvg = 0, cubeStepsAvg = 0;
    for (int value : values) {
        linearStepsAvg += linearTable.stepsToFind(value);
        squareStepsAvg += squareTable.stepsToFindSquare(value);
        cubeStepsAvg += cubeTable.stepsToFindCube(value);
    }

    linearStepsAvg /= values.size();
    squareStepsAvg /= values.size();
    cubeStepsAvg /= values.size();

    std::cout << "collizii (i don't know how to translate this)" << std::endl;
    std::cout << "Linear: " << linearStepsAvg << std::endl;
    std::cout << "Square: " << squareStepsAvg << std::endl;
    std::cout << "Cube: " << cubeStepsAvg << std::endl << std::endl;

    std::cout << "claster info" << std::endl;
    std::pair<double, double> linearInfo = linearTable.getClasterInfo();
    std::pair<double, double> squareInfo = squareTable.getClasterInfo();
    std::pair<double, double> cubeInfo = cubeTable.getClasterInfo();
    std::cout << "Linear: number of clusters " << linearInfo.first << ", avg size of cluster " << linearInfo.second << std::endl;
    std::cout << "Square: number of clusters " << squareInfo.first << ", avg size of cluster " << squareInfo.second << std::endl;
    std::cout << "Cube: number of clusters " << cubeInfo.first << ", avg size of cluster " << cubeInfo.second << std::endl;
}

int main() {
    std::cout << "Test 1" << std::endl;
    bigTest();
    std::cout << "\nTest 2" << std::endl;
    bigTest();
    std::cout << "\nTest 3" << std::endl;
    bigTest();
    return 0;
}
