#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <climits>

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc > 2) {
        if (argv[1][0] != '-' || argv[1][1] != 'i') {
            cout << "Debes ingresar el comando -i " << endl;
            return 0;
        }
    } else {
        cout << "Debes ingresar el formato de ejecución <Greedy> -i "
                "<instancia-problema>"
             << endl;
        return 0;
    }
    fstream file;
    string path = argv[2];
    vector<string> dataset;

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

    // elegir como primera letra la mas frecuente
    map<char, int> m;
    for (int i = 0; i < dataset.size(); i++) {
        m[dataset[i][0]]++;
    }
    auto best = max_element(m.begin(), m.end(), [](auto &a, auto &b) -> bool {
        return a.second < b.second;
    });

    // cout << best->first << " " << best->second << endl;
    result += best->first;

    for (int i = 0; i < dataset.size(); i++) {
        if (dataset[i][0] != best->first) {
            distances[i]++;
        }
    }

    for (auto value : distances) {
        cost += value * value;
    }
    // cout << cost << endl;

    // elegir siguientes letras
    // cada columna
    for (int i = 1; i < dataset[0].size(); i++) {
        int min_cost = INT_MAX;
        char best_letter = 'A';
        vector<int> best_distances;
        // cada letra
        for (char letter : {'A', 'C', 'T', 'G'}) {
            // cada fila
            // copiar distancias
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
            // cout << "chao" << endl;
            if (cost < min_cost) {
                min_cost = cost;
                best_letter = letter;
                best_distances = distances_copy;
            }
        }
        result += best_letter;
        distances = best_distances;
    }

    cout << result << endl;
    for (auto value : distances) {
        cost += value * value;
    }
    cout << cost << endl;
    
    return 1;
}
