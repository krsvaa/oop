#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class ProgramError {
protected:
    std::string message;
public:
    ProgramError(const std::string& msg = "Ошибка в программе") : message(msg) {}
    virtual ~ProgramError() = default;
    virtual void print() const {
        std::cout << "Error: " << message << std::endl;
    }
};

class MemoryAccessError : public ProgramError {
public:
    MemoryAccessError(const std::string& msg = "Ошибка доступа к памяти") : ProgramError(msg) {}
    void print() const override {
        std::cout << "MemoryAccessError: " << message << std::endl;
    }
};

class MathError : public ProgramError {
public:
    MathError(const std::string& msg = "Математическая ошибка") : ProgramError(msg) {}
    void print() const override {
        std::cout << "MathError: " << message << std::endl;
    }
};

class DivisionByZeroError : public MathError {
public:
    DivisionByZeroError(const std::string& msg = "Деление на ноль") : MathError(msg) {}
    void print() const override {
        std::cout << "DivisionByZeroError: " << message << std::endl;
    }
};

class OverflowError : public MathError {
public:
    OverflowError(const std::string& msg = "Переполнение") : MathError(msg) {}
    void print() const override {
        std::cout << "OverflowError: " << message << std::endl;
    }
};

template<typename T>
class PointerArray {
private:
    std::vector<T*> pointers;
public:
    ~PointerArray() {
        for (auto ptr : pointers) {
            delete ptr;
        }
    }
    void add(T* ptr) {
        pointers.push_back(ptr);
    }
    T*& operator[](size_t index) {
        if (index >= pointers.size()) {
            throw std::runtime_error("Выход за границы массива");
        }
        return pointers[index];
    }
    size_t getSize() const {
        return pointers.size();
    }
};

class DemoClass {
private:
    int id;
    std::string name;
public:
    DemoClass(int i, const std::string& n) : id(i), name(n) {}
    void display() const {
        std::cout << "DemoClass [id=" << id << ", name='" << name << "']" << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        std::cout << "~~errorArray~~" << std::endl;
        PointerArray<ProgramError> errorArray;
        errorArray.add(new ProgramError("Базовая ошибка"));
        errorArray.add(new MemoryAccessError());
        errorArray.add(new DivisionByZeroError());
        errorArray.add(new OverflowError());
        
        for (size_t i = 0; i < errorArray.getSize(); ++i) {
            errorArray[i]->print();
        }
        //std::cout << "\\Попытка доступа к несуществующему индексу 10" << std::endl;
        //errorArray[10]->print();
        std::cout << "~~demoArray~~" << std::endl;
        PointerArray<DemoClass> demoArray;
        demoArray.add(new DemoClass(1, "Первый"));
        demoArray.add(new DemoClass(2, "Второй"));
        for (size_t i = 0; i < demoArray.getSize(); ++i) {
            demoArray[i]->display();
        }
        std::cout << "\\Попытка доступа к несуществующему индексу 10" << std::endl;
        demoArray[10]->display();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Поймано критическое runtime_error: " << e.what() << std::endl;
        std::cout << "Программа будет завершена аварийно" << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "Поймано необработанное исключение: " << e.what() << std::endl;
        std::cout << "Программа будет завершена аварийно" << std::endl;
        return 1;
    }
    return 0;
}