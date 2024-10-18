#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <cstring>

using namespace std;

// Функция для чтения графа из бинарного файла
vector<vector<int>> readGraph(const string &filename, int &n) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(1);
    }

    file.read(reinterpret_cast<char*>(&n), sizeof(int16_t));
    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int16_t value;
            file.read(reinterpret_cast<char*>(&value), sizeof(int16_t));
            graph[i][j] = (value == INT_MAX ? INT_MAX : value); // -1 означает отсутствие ребра
        }
    }

    file.close();
    return graph;
}

// Алгоритм Беллмана-Форда
bool bellmanFord(const vector<vector<int>> &graph, vector<int> &dist, int src) {
    int n = graph.size();
    dist[src] = 0;

    // Шаги алгоритма Беллмана-Форда
    for (int i = 1; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Проверка на отрицательный цикл
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                return true; // Обнаружен отрицательный цикл
            }
        }
    }
    return false;
}

// Алгоритм Джонсона
vector<vector<int>> johnson(const vector<vector<int>> &graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    // Используем Беллмана-Форда для добавления новой вершины и получения корректных весов
    vector<int> h(n, 0);
    if (bellmanFord(graph, h, n)) {
        cerr << "Граф содержит отрицательный цикл!" << endl;
        exit(1);
    }

    // Пересчитываем веса рёбер
    vector<vector<int>> newGraph = graph;
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (newGraph[u][v] != INT_MAX) {
                newGraph[u][v] += h[u] - h[v];
            }
        }
    }

    // Применяем алгоритм Дейкстры для всех вершин
    for (int u = 0; u < n; ++u) {
        vector<int> d(n, INT_MAX);
        d[u] = 0;
        for (int i = 0; i < n; ++i) {
            for (int v = 0; v < n; ++v) {
                if (newGraph[u][v] != INT_MAX && d[u] + newGraph[u][v] < d[v]) {
                    d[v] = d[u] + newGraph[u][v];
                }
            }
        }
        dist[u] = d;
    }

    return dist;
}

// Функция для записи результата в файл
void writeResult(const string &filename, bool hasNegativeCycle, const vector<int> &dist, const vector<vector<int>> &allPairsDist) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Ошибка открытия выходного файла: " << filename << endl;
        exit(1);
    }

    if (hasNegativeCycle) {
        outfile << "Граф содержит отрицательный цикл\n";
    } else {
        // Вывод вектора расстояний
        outfile << "Вектор расстояний от нулевой вершины: ";
        for (int d : dist) {
            outfile << d << " ";
        }
        outfile << endl;

        // Вычисление диаметра, радиуса, центральных и периферийных вершин
        int diameter = 0, radius = INT_MAX;
        vector<int> eccentricities(allPairsDist.size(), 0);
        vector<int> centralVertices, peripheralVertices;

        for (int u = 0; u < allPairsDist.size(); ++u) {
            for (int v = 0; v < allPairsDist.size(); ++v) {
                if (allPairsDist[u][v] != INT_MAX) {
                    eccentricities[u] = max(eccentricities[u], allPairsDist[u][v]);
                }
            }
            diameter = max(diameter, eccentricities[u]);
            radius = min(radius, eccentricities[u]);
        }

        for (int u = 0; u < allPairsDist.size(); ++u) {
            if (eccentricities[u] == radius) {
                centralVertices.push_back(u);
            }
            if (eccentricities[u] == diameter) {
                peripheralVertices.push_back(u);
            }
        }

        outfile << "Диаметр: " << diameter << endl;
        outfile << "Радиус: " << radius << endl;

        outfile << "Центральные вершины: ";
        for (int v : centralVertices) {
            outfile << v << " ";
        }
        outfile << endl;

        outfile << "Периферийные вершины: ";
        for (int v : peripheralVertices) {
            outfile << v << " ";
        }
        outfile << endl;
    }

    outfile.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Использование: " << argv[0] << " inputfile [-o outputfile]" << endl;
        return 1;
    }

    string inputFilename = argv[1];
    string outputFilename = "output.txt";

    if (argc > 2 && strcmp(argv[2], "-o") == 0 && argc > 3) {
        outputFilename = argv[3];
    }

    int n;
    vector<vector<int>> graph = readGraph(inputFilename, n);

    vector<int> dist(n, INT_MAX);
    bool hasNegativeCycle = bellmanFord(graph, dist, 0);

    if (!hasNegativeCycle) {
        vector<vector<int>> allPairsDist = johnson(graph);
        writeResult(outputFilename, hasNegativeCycle, dist, allPairsDist);
    } else {
        writeResult(outputFilename, hasNegativeCycle, dist, {});
    }

    return 0;
}