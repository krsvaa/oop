#include <iostream> 
#include <vector> 
#include <fstream> 
#include <string> 
#include <sstream> 

using namespace std; 

class Car { 
    private: string name; // имя машины 
    string model; // модель машины public: 

    // Конструктор класса 
    Car(string n, string m) : name(n), model(m) {} 
    
    // Деструктор класса
    ~Car() { s
        std::cout << "Марка: " << name; 
        std::cout << " Модель: " << model << endl; 
    } 
}; 

int main() { 
    setlocale(LC_ALL, "Russian"); 
    vector<Car*> objects; //вектор для хранения машин 
    ifstream file("1.txt"); // Открываем файл 
    if (file.is_open()) { 
        std::cout << "File opened successfully" << std::endl; 
    } else { 
        std::cout << "Failed to open file" << std::endl; 
    } 
    string line; 
    while (getline(file, line) && objects.size() < 10) { 
        stringstream ss(line); 
        string brand; string number; 
        if (ss >> brand >> number) { 
            objects.push_back(new Car(brand, number)); 
        } 
    } 
    file.close(); 
    for (auto& car : objects) { 
        delete car; 
    } 
    objects.clear();
    return 0; 
}