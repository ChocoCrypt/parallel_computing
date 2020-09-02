#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

double get_mean(vector<double> t){
    double sum = 0;
    for (int i = 0; i < t.size(); i++){
        sum += t[i];
    }
    double mean = sum/t.size();
    return mean;
}

double get_standard_deviation(vector<double> t){
    double mean = get_mean(t);
    vector<double> t_2;
    for (int i = 0; i < t.size(); i++){
        t_2.push_back(t[i]*t[i]);
    }
    double mean_2 = get_mean(t_2);
    double variance = mean_2 - (mean*mean);
    double standard_deviation = variance*variance;
    return standard_deviation;
}

vector<double> read(string name){
    vector<double> result;
    ifstream file;
    string line = "";
    string file_size = "";
    string file_size_num = "";

    bool read = false;

    if (file.fail()){
        cout << "Error" << endl;
        exit(1);
    }

    file.open(name,ios::in);

    getline(file,file_size);

    for(int i = 0; i < file_size.size();i++){
        if (read){
            file_size_num += file_size[i];
        }
        if (file_size[i] == ':'){
            read = true;
        }
    }

    int reps = atof(file_size_num.c_str());

    for (int i = 0; i <= reps; i ++){
        if (i == 0){
            continue;
        }
        getline(file,line);
        double n = atof(line.c_str());
        result.push_back(n);
    }

    file.close();
    return result;
}

vector<double> get_speed_up(vector<double> serial, vector<double> parallel){
    vector<double> result;
    for (int i = 0; i < serial.size(); i++){
        double n = serial[i]/parallel[i];
        result.push_back(n);
    }
    return result;
}

int main(){
    string Parallel = "Parallel_Data.txt";
    string Serial = "Serial_Data.txt";

    vector<double> parallel_data = read(Parallel);
    vector<double> serial_data = read(Serial);

    vector<double> speed_up = get_speed_up(serial_data, parallel_data);

    double mean_speed_up = get_mean(speed_up);
    double standard_deviation_speed_up = get_standard_deviation(speed_up);


    cout << "El speed_up promedio es : " << mean_speed_up << endl;
    cout << "La desviacion estandar del speed_up es: " << standard_deviation_speed_up << endl;

    return 0;
}
