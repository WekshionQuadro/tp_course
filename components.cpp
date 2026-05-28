#include "components.h"
#include <iostream>

using namespace std;

// Реализация класса Component (базовый класс)
Component::Component(string n, double p) : name(n), price(p) {}
Component::~Component() {}
string Component::getName() { return name; }
double Component::getPrice() { return price; }

// Реализация класса CPU (видеокарта)
CPU::CPU(string n, double p, string s, int c, int th, double f, int t)
    : Component(n, p), socket(s), cores(c), threads(th), frequency(f), powerDraw(t) {}

void CPU::printInfo()
{
  cout << "[CPU] " << name << " | " << price << " руб. | Сокет: " << socket
       << " | " << cores << " ядер / " << threads << " потоков | "
       << frequency << " ГГц | TDP: " << powerDraw << " Вт" << endl;
}
string CPU::getSocket() { return socket; }
int CPU::getPowerDraw() { return powerDraw; }

// Реализация класса GPU (процессор)
GPU::GPU(string n, double p, int pScore, int t)
    : Component(n, p), powerScore(pScore), powerDraw(t) {}

void GPU::printInfo()
{
  cout << "[GPU] " << name << " | " << price << " руб. | Оценка мощности: "
       << powerScore << "/100 | TDP: " << powerDraw << " Вт" << endl;
}
int GPU::getPowerScore() { return powerScore; }
int GPU::getPowerDraw() { return powerDraw; }

// Реализация класса Motherboard
Motherboard::Motherboard(string n, double p, string s, string ddr, string f, double maxFreq)
    : Component(n, p), socket(s), ddrType(ddr), formFactor(f), maxRamFreq(maxFreq) {}

void Motherboard::printInfo()
{
  cout << "[Мат. плата] " << name << " | " << price << " руб. | Сокет: "
       << socket << " | Память: " << ddrType << " | Форм-фактор: " << formFactor << " | Макс. ОЗУ: " << maxRamFreq << " МГц" << endl;
}
string Motherboard::getSocket() { return socket; }
string Motherboard::getDdrType() { return ddrType; }
string Motherboard::getFormFactor() { return formFactor; }
double Motherboard::getMaxRamFreq() { return maxRamFreq; }

// Реализация класса RAM
RAM::RAM(string n, double p, string t, double freq)
    : Component(n, p), type(t), frequency(freq) {}

void RAM::printInfo()
{
  cout << "[ОЗУ] " << name << " | " << price << " руб. | Тип: " << type << " | Частота: "
       << frequency << " МГц" << endl;
}
string RAM::getType() { return type; }
double RAM::getFrequency() { return frequency; }

// Реализация класса PSU (блок питания)
PSU::PSU(string n, double p, int w)
    : Component(n, p), wattage(w) {}

void PSU::printInfo()
{
  cout << "[БП] " << name << " | " << price << " руб. | Мощность: "
       << wattage << " Вт" << endl;
}
int PSU::getWattage() { return wattage; }

// Реализация класса Storage (накопитель)
Storage::Storage(string n, double p, int cap, string t)
    : Component(n, p), capacity(cap), type(t) {}

void Storage::printInfo()
{
  cout << "[Накопитель] " << name << " (" << type << ") | " << price
       << " руб. | Объем: " << capacity << " ГБ" << endl;
}

// Реализация класса Case (корпус)
Case::Case(string n, double p, string size, string forms)
    : Component(n, p), sizeType(size), supportedFormFactors(forms) {}

void Case::printInfo()
{
  cout << "[Корпус] " << name << " | " << price << " руб. | Типоразмер: "
       << sizeType << " | Поддерживает: " << supportedFormFactors << endl;
}

bool Case::supports(string moboFormFactor)
{
  // Функция find ищет подстроку. Если не нашла, возвращает std::string::npos
  if (supportedFormFactors.find(moboFormFactor) != std::string::npos)
  {
    return true; // Форм-фактор найден, плата влезет!
  }
  return false;
}