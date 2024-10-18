#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

// Функция для записи графа в бинарный файл
void writeGraphToBinaryFile(const string &filename, const vector<vector<int>> &graph) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        exit(1);
    }

    // Записываем размер матрицы
    int32_t n = graph.size();
    file.write(reinterpret_cast<const char*>(&n), sizeof(int32_t));

    // Записываем матрицу смежности
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int32_t value = graph[i][j];
            cout << value << ' ';
            file.write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
        }
        cout << '\n';
    }

    file.close();
}

int main() {
    // Пример: граф с 4 вершинами
    vector<vector<int>> graph = {
        {0, 3, INT_MAX, 7},
        {3, 0, 4, 2},
        {INT_MAX, 4, 0, 5},
        {7, -4, 5, 0}
    };

    string filename = "graph.bin";
    writeGraphToBinaryFile(filename, graph);

    cout << "Граф записан в бинарный файл: " << filename << endl;
    return 0;
}
