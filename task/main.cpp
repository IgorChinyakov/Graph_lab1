#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

// Функция для чтения графа из бинарного файла
vector<vector<int>> readGraph(const string &filename, int &n)
{
    ifstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        exit(1);
    }

    file.read(reinterpret_cast<char *>(&n), sizeof(int16_t));
    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int16_t value;
            file.read(reinterpret_cast<char *>(&value), sizeof(int16_t));
            if (i != j && value == 0)
                graph[i][j] = INT_MAX;
            else
                graph[i][j] = value; //
            // cout << value << ' ';
        }
        // cout << '\n';
    }

    file.close();
    return graph;
}

// Алгоритм Беллмана-Форда
bool bellmanFord(const vector<vector<int>> &graph, vector<int> &dist, int src)
{
    int n = graph.size();
    dist.assign(n, INT_MAX);
    dist[src] = 0; // Дополнительная вершина со стартовым расстоянием 0

    // Шаги алгоритма Беллмана-Форда
    for (int i = 1; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Проверка на отрицательный цикл
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            if (graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                cout << graph[u][v];
                return true; // Обнаружен отрицательный цикл
            }
        }
    }
    return false;
}

vector<int> dijkstra(int src, const vector<vector<int>> &graph, const vector<int> &h)
{
     int V = graph.size();
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != INT_MAX) {
                int weight = graph[u][v] + h[u] - h[v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return dist;
    // int n = graph.size();
    // vector<int> dist(n, INT_MAX);   // расстояния от src до всех вершин
    // vector<bool> visited(n, false); // отметка посещенных вершин

    // dist[src] = 0; // начальная вершина

    // for (int i = 0; i < n - 1; i++)
    // {
    //     // Найти вершину с минимальным расстоянием из непосещенных
    //     int minDist = INT_MAX, minIndex = -1;

    //     for (int v = 0; v < n; v++)
    //     {
    //         if (!visited[v] && dist[v] <= minDist)
    //         {
    //             minDist = dist[v];
    //             minIndex = v;
    //         }
    //     }

    //     int u = minIndex;
    //     visited[u] = true;

    //     // Обновить расстояния для смежных вершин
    //     for (int v = 0; v < n; v++)
    //     {
    //         // Проверяем, что ребро существует (graph[u][v] != INT_MAX), вершина не посещена,
    //         // и расстояние до v через u меньше, чем текущее значение dist[v]
    //         if (!visited[v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
    //         {
    //             dist[v] = dist[u] + graph[u][v];
    //         }
    //     }
    // }

    // return dist;
}

// Алгоритм Джонсона
vector<vector<int>> johnson(const vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    vector<vector<int>> newGraph(n+1, vector<int>(n+1, INT_MAX));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            newGraph[i][j] = graph[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        newGraph[n][i] = 0;
    }
    

    // Используем Беллмана-Форда для добавления новой вершины и получения корректных весов
    vector<int> h;
    if (bellmanFord(newGraph, h, n))
    {
        cerr << "Граф содержит отрицательный цикл!" << endl;
        exit(1);
    }

    // for (int i = 0; i < n; i++)
    // {
    //     cout << h[i] << endl;
    // }
    
    // // Пересчитываем веса рёбер
    // for (int u = 0; u < n; ++u)
    // {
    //     for (int v = 0; v < n; ++v)
    //     {
    //         if (newGraph[u][v] != n)
    //         {
    //             newGraph[u][v] += h[u] - h[v];
    //         }
    //     }
    // }

    // Применяем алгоритм Дейкстры для всех вершин
    for (int u = 0; u < n; ++u)
    {
        // vector<int> d(n, INT_MAX);
        dist[u] = dijkstra(u, newGraph, h);

        for (int v = 0; v < n; v++)
        {
            if (dist[u][v] != INT_MAX)
            {
                dist[u][v] += (h[v] - h[u]);
            }
        }

        // d[u] = 0;
        // for (int i = 0; i < n; ++i) {
        //     for (int v = 0; v < n; ++v) {
        //         if (newGraph[u][v] != INT_MAX && d[u] + newGraph[u][v] < d[v]) {
        //             d[v] = d[u] + newGraph[u][v];
        //         }
        //     }
        // }
        // dist[u] = d;
    }

    return dist;
}

// Функция для записи результата в файл
void writeResult(const string &filename, bool hasNegativeCycle, const vector<int> &dist, const vector<vector<int>> &allPairsDist)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "Ошибка открытия выходного файла: " << filename << endl;
        exit(1);
    }

    if (hasNegativeCycle)
    {
        outfile << "Граф содержит отрицательный цикл\n";
    }
    else
    {
        // Вывод вектора расстояний
        outfile << "Вектор расстояний от нулевой вершины: ";
        for (int d : dist)
        {
            outfile << d << " ";
        }
        outfile << endl;

        // Вычисление диаметра, радиуса, центральных и периферийных вершин
        int diameter = INT_MIN, radius = INT_MAX;
        vector<int> eccentricities(allPairsDist.size(), INT_MAX);
        // cout << "размер: " << allPairsDist.size() << endl;
        vector<int> centralVertices, peripheralVertices;

        for (int u = 0; u < allPairsDist.size(); ++u)
        {
            int max_eccentricity = INT_MIN;
            for (int v = 0; v < allPairsDist.size(); ++v)
            {
                if (u != v)
                {
                    // cout << "Вершины: " << u << " - " << v << ' ' << allPairsDist[u][v] << endl;
                    max_eccentricity = max(max_eccentricity, allPairsDist[u][v]);
                    // if (u == 0)
                    // {
                    //     cout << u << " - " << v << ':' << allPairsDist[u][v] << endl;
                    // }
                }
            }

            eccentricities[u] = max_eccentricity;
        }

        for (int i = 0; i < allPairsDist.size(); i++)
        {
            diameter = max(diameter, eccentricities[i]);
            radius = min(radius, eccentricities[i]);
        }

        for (int u = 0; u < allPairsDist.size(); ++u)
        {
            if (eccentricities[u] == radius)
            {
                centralVertices.push_back(u);
            }
            if (eccentricities[u] == diameter)
            {
                peripheralVertices.push_back(u);
            }
        }

        // outfile << "Эксцентиристеты: " << endl;
        // for (int v : eccentricities)
        // {
        //     outfile << v << " ";
        // }
        // outfile << endl;

        outfile << "Диаметр: " << diameter << endl;
        outfile << "Радиус: " << radius << endl;

        outfile << "Центральные вершины: ";
        for (int v : centralVertices)
        {
            outfile << v << " ";
        }
        outfile << endl;

        outfile << "Периферийные вершины: ";
        for (int v : peripheralVertices)
        {
            outfile << v << " ";
        }
        outfile << endl;
    }

    outfile.close();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Использование: " << argv[0] << " inputfile [-o outputfile]" << endl;
        return 1;
    }

    string inputFilename = argv[1];
    string outputFilename = "output.txt";

    if (argc > 2 && strcmp(argv[2], "-o") == 0 && argc > 3)
    {
        outputFilename = argv[3];
    }

    int n;
    vector<vector<int>> graph = readGraph(inputFilename, n);

    vector<int> dist(n, INT_MAX);
    bool hasNegativeCycle = bellmanFord(graph, dist, 0);

    if (!hasNegativeCycle)
    {
        vector<vector<int>> allPairsDist = johnson(graph);
        writeResult(outputFilename, hasNegativeCycle, dist, allPairsDist);
    }
    else
    {
        writeResult(outputFilename, hasNegativeCycle, dist, {});
    }

    return 0;
}