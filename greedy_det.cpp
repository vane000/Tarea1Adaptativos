#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]){

    if(argc > 2){
        if(argv[1][0] != '-' || argv[1][1] != 'i'){
            cout<<"Debes ingresar el comando -i "<<endl;
            return 0;
        }
    }else{
        cout<<"Debes ingresar el formato de ejecución <Greedy> -i <instancia-problema>"<<endl;
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
    for (int i = 0; i < dataset.size(); i++){
        cout<<dataset[i]<<endl;
    }
    cout<<dataset.size()<<endl;
    
    return 1;
}
