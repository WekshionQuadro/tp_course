#pragma once
#include <string>

// Базовый абстрактный класс для любого типа комплектующих
class Component
{
protected:
  std::string name; // Название
  double price;     // Цена

public:
  Component(std::string n, double p);
  virtual ~Component();

  std::string getName();
  double getPrice();

  virtual void printInfo() = 0;
};

// Класс процессора
class CPU : public Component
{
private:
  std::string socket; // Сокет
  int cores;          // Кол-во ядер
  int threads;        // Кол-во потоков
  double frequency;   // Частота
  int powerDraw;      // Энергопотребление

public:
  CPU(std::string n, double p, std::string s, int c, int th, double f, int t);
  void printInfo() override;

  std::string getSocket();
  int getPowerDraw();
};

// Класс видеокарты
class GPU : public Component
{
private:
  int powerScore; // Оценочная мощность (0 - 100)
  int powerDraw;  // Энергопотребление

public:
  GPU(std::string n, double p, int pScore, int t);
  void printInfo() override;

  int getPowerScore();
  int getPowerDraw();
};

// Класс материнской платы
class Motherboard : public Component
{
private:
  std::string socket;     // Сокет процессора
  std::string formFactor; // Форм-фактор
  double maxRamFreq;      // Максимальная поддерживаемая частота оперативной памяти

public:
  Motherboard(std::string n, double p, std::string s, std::string f, double maxFreq);
  void printInfo() override;

  std::string getSocket();
  std::string getFormFactor();
  double getMaxRamFreq();
};

// Класс оперативной памяти
class RAM : public Component
{
private:
  double frequency; // Частота

public:
  RAM(std::string n, double p, double freq);
  void printInfo() override;

  double getFrequency();
};

// Класс блока питания
class PSU : public Component
{
private:
  int wattage; // Мощность

public:
  PSU(std::string n, double p, int w);
  void printInfo() override;

  int getWattage();
};

// Класс накопителей
class Storage : public Component
{
private:
  int capacity;     // Объем
  std::string type; // Тип

public:
  Storage(std::string n, double p, int cap, std::string t);
  void printInfo() override;
};

// Класс корпуса
class Case : public Component
{
private:
  std::string sizeType;             // Типоразмер
  std::string supportedFormFactors; // Строка со всеми поддерживаемыми форматами

public:
  Case(std::string n, double p, std::string size, std::string forms);
  void printInfo() override;

  bool supports(std::string moboFormFactor);
};
