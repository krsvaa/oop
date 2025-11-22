#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Shop
{
private:
    string product; // название продукта
    int count; // кол-во продукции
public:
    Shop() : product(""), count(0) {
        cout << "Создан новый товар" << endl;
    }
    Shop(string prod, int sh) : product(prod), count(sh) {
        cout << "Товар:" << product << "  В кол-ве: " << count << endl;
    }

    string getProduct() const { return product; }
    int getCount() const { return count; }

    ~Shop() {
        cout << "Товар " << product << " удален" << endl;
    }
};

class Magazine
{
private:
    vector<unique_ptr<Shop>> objects;

public:
    // Добавление товара
    void addProduct(const string& product, int count) {
        objects.push_back(make_unique<Shop>(product, count));
    }

    // Поиск товара
    void findProduct(const string& product) {
        bool found = false;
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getProduct() == product) {
                cout << "Товар на полке: " << i + 1 << endl;
                cout << "Количество: " << objects[i]->getCount() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Такого товара нет(" << endl;
        }
    }

    // Удаление товара
    void deleteProduct(const string& product) {
        auto new_end = remove_if(objects.begin(), objects.end(), [&product](const unique_ptr<Shop>& obj) {
            return obj->getProduct() == product;
            });

        objects.erase(new_end, objects.end());
        cout << "Товар удален" << endl;
    }
};

void Dialog() {
    cout << "Введите 0, чтобы выйти." << endl;
    cout << "Введите 1, чтобы добавить продукт." << endl;
    cout << "Введите 2, чтобы найти продукт." << endl;
    cout << "Введите 3, чтобы удалить продукт." << endl;
    cout << "Ваш выбор:" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Magazine magazine;

    int option = 1;
    while (option > 0) {
        Dialog();
        cin >> option;

        cin.ignore();

        switch (option) {
        case 1: {
            string str;
            int i;
            cout << "Введите название продукта: ";
            getline(cin, str);
            cout << "Введите кол-во продукта: ";
            cin >> i;
            magazine.addProduct(str, i);
            break;
        }
        case 2: {
            string find;
            cout << "Введите название продукта для поиска: ";
            getline(cin, find);
            magazine.findProduct(find);
            break;
        }
        case 3: {
            string toDelete;
            cout << "Введите название продукта для удаления: ";
            getline(cin, toDelete);
            magazine.deleteProduct(toDelete);
            break;
        }
        default:
            cout << "Магазин закрывается)" << endl;
            option = 0;
            break;
        }
    }
    return 0;
}