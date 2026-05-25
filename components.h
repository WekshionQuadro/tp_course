#pragma once
#include <string>

// === БАЗОВЫЙ КЛАСС ===
class Component
{
protected:
  std::string name;
  double price;

public:
  Component(std::string n, double p);
  virtual ~Component();

  std::string getName() const;
  double getPrice() const;

  virtual void printInfo() const = 0;
};

// === ПРОЦЕССОР (CPU) ===
class CPU : public Component
{
private:
  std::string socket;
  int cores;
  int threads;
  double frequency;
  int tdp;

public:
  CPU(std::string n, double p, std::string s, int c, int th, double f, int t);
  void printInfo() const override;

  std::string getSocket() const;
  int getTdp() const;
};

// === ВИДЕОКАРТА (GPU) ===
class GPU : public Component
{
private:
  int powerScore; // Мощность от 0 до 100
  int tdp;        // Потребляемая мощность

public:
  GPU(std::string n, double p, int pScore, int t);
  void printInfo() const override;

  int getPowerScore() const;
  int getTdp() const;
};

// === МАТЕРИНСКАЯ ПЛАТА (Motherboard) ===
class Motherboard : public Component
{
private:
  std::string socket;
  double maxRamFreq; // Максимально поддерживаемая частота RAM

public:
  Motherboard(std::string n, double p, std::string s, double maxFreq);
  void printInfo() const override;

  std::string getSocket() const;
  double getMaxRamFreq() const;
};

// === ОПЕРАТИВНАЯ ПАМЯТЬ (RAM) ===
class RAM : public Component
{
private:
  double frequency;

public:
  RAM(std::string n, double p, double freq);
  void printInfo() const override;

  double getFrequency() const;
};

// === БЛОК ПИТАНИЯ (PSU) ===
class PSU : public Component
{
private:
  int wattage; // Мощность в ваттах

public:
  PSU(std::string n, double p, int w);
  void printInfo() const override;

  int getWattage() const;
};

// === НАКОПИТЕЛЬ (Storage) ===
class Storage : public Component
{
private:
  int capacity;     // Объем памяти в ГБ
  std::string type; // SSD или HDD

public:
  Storage(std::string n, double p, int cap, std::string t);
  void printInfo() const override;
};