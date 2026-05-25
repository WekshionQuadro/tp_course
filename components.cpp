#include <iostream>
#include <string>

using namespace std;

class Component
{
protected:
  string name;
  double price;

public:
  Component(string n, double p) : name(n), price(p) {}

  virtual ~Component() {}

  string getName() const { return name; }
  double getPrice() const { return price; }

  virtual void printInfo() const = 0;
};

// 2. КЛАСС-НАСЛЕДНИК (Процессор)
class CPU : public Component
{
private:
  // Специфичные поля только для процессора
  string socket;
  int cores;
  int threads;
  double frequency;
  int tdp; // Потребляемая мощность в Ваттах

public:
  // Конструктор процессора. Сначала вызывает конструктор Component, затем инициализирует свои поля.
  CPU(string n, double p, string s, int c, int th, double f, int t)
      : Component(n, p), socket(s), cores(c), threads(th), frequency(f), tdp(t) {}

  // Переопределение виртуальной функции для вывода данных на экран (или в файл)
  void printInfo() const override
  {
    cout << "[CPU] " << name << " | Цена: " << price << " руб." << endl
         << "      Сокет: " << socket << " | Ядра/Потоки: " << cores << "/" << threads
         << " | Частота: " << frequency << " ГГц | TDP: " << tdp << " Вт" << endl;
  }

  // Специфичные геттеры, которые понадобятся консультанту для проверки совместимости
  string getSocket() const { return socket; }
  int getTdp() const { return tdp; }
};

int main()
{
  // Небольшой тест нашей архитектуры
  // Создаем процессор через указатель на базовый класс (демонстрация полиморфизма)
  Component *myCpu = new CPU("Intel Core i5-12400F", 15500.0, "LGA1700", 6, 12, 4.4, 65);

  // Вызываем виртуальную функцию. Программа сама понимает, что это CPU!
  myCpu->printInfo();

  delete myCpu; // Не забываем чистить память
  return 0;
}