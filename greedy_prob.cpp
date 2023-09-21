#include <time.h>

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    if (argc > 3) {
        if (argv[1][0] != '-' || argv[1][1] != 'i') {
            cout << "Debes ingresar el comando -i " << endl;
            return 0;
        }
    } else {
        cout << "Debes ingresar el formato de ejecución <Greedy> -i "
                "<instancia-problema> <probabilidad-aleatoriedad> "
             << endl;
        return 0;
    }

    fstream file;
    string path = argv[2];
    vector<string> dataset;
    int alpha = atoi(argv[3]);
    file.open(path, ios::in);

    if (file.is_open()) {
        string data;
        while (getline(file, data)) {
            dataset.push_back(data);
        }
        file.close();
    }

    // for (int i = 0; i < dataset.size(); i++) {
    //     cout << dataset[i] << endl;
    // }
    // cout << dataset.size() << endl;

    vector<int> distances(dataset.size(), 0);
    string result = "";
    int cost = 0;

    // elegir como primera letra la mas frecuente o tomar una letra aleatoria
    if (alpha > rand() % 100 + 1) {
        char list[4] = {'A', 'C', 'T', 'G'};
        int randomIndex = rand() % 4;
        char choosen = list[randomIndex];
        result += choosen;
        for (int i = 0; i < dataset.size(); i++) {
            if (dataset[i][0] != choosen) {
                distances[i]++;
            }
        }
    } else {
        map<char, int> m;
        for (int i = 0; i < dataset.size(); i++) {
            m[dataset[i][0]]++;
        }

        auto best = max_element(
            m.begin(), m.end(),
            [](auto &a, auto &b) -> bool { return a.second < b.second; });
        result += best->first;
        for (int i = 0; i < dataset.size(); i++) {
            if (dataset[i][0] != best->first) {
                distances[i]++;
            }
        }
    }
    // cout << best->first << " " << best->second << endl;

    for (auto value : distances) {
        cost += value * value;
    }
    // cout << cost << endl;

    // elegir siguientes letras
    // cada columna
    for (int i = 1; i < dataset[0].size() - 1; i++) {
        int min_cost = INT_MAX;
        char best_letter;
        vector<int> best_distances;
        // cada letra
        // cout << "probando columna" << i << endl;
        // elección entre estrategia greedy o aleatorio
        if (alpha > rand() % 100 + 1) {
            char list[4] = {'A', 'C', 'T', 'G'};
            int randomIndex = rand() % 4;
            char choosen = list[randomIndex];
            cost = 0;
            best_letter = choosen;
            best_distances = distances;
            for (int sequence = 0; sequence < dataset.size(); sequence++) {
                if (dataset[sequence][i] != choosen) {
                    best_distances[sequence]++;
                }
            }
            for (auto value : best_distances) {
                cost += value * value;
            }
        } else {
            for (char letter : {'A', 'C', 'T', 'G'}) {
                // cada fila
                // copiar distancias
                // cout << "probando letra " << letter << endl;
                vector<int> distances_copy = distances;
                cost = 0;
                for (int sequence = 0; sequence < dataset.size(); sequence++) {
                    if (dataset[sequence][i] != letter) {
                        distances_copy[sequence]++;
                    }
                    // cout << sequence << endl;
                }
                // cout << "hola" << endl;
                for (auto value : distances_copy) {
                    cost += value * value;
                }
                // cout << "costo acumulado: " << cost << endl;
                // cout << "chao" << endl;
                if (cost < min_cost) {
                    min_cost = cost;
                    best_letter = letter;
                    best_distances = distances_copy;
                }
            }
        }
        // cout << result << endl;
        // cout << "mejor letra " << best_letter << endl;
        result += best_letter;
        distances = best_distances;
    }

    //cout << result << endl;
    cout << cost << endl;

    return 0;
}
