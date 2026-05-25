#include "components.h"
#include <iostream>

using namespace std;

// === Реализация Component ===
Component::Component(string n, double p) : name(n), price(p) {}
Component::~Component() {}
string Component::getName() const { return name; }
double Component::getPrice() const { return price; }

// === Реализация CPU ===
CPU::CPU(string n, double p, string s, int c, int th, double f, int t)
    : Component(n, p), socket(s), cores(c), threads(th), frequency(f), tdp(t) {}

void CPU::printInfo() const
{
  cout << "[CPU] " << name << " | " << price << " руб. | Сокет: " << socket
       << " | " << cores << " ядер / " << threads << " потоков | "
       << frequency << " ГГц | TDP: " << tdp << " Вт" << endl;
}
string CPU::getSocket() const { return socket; }
int CPU::getTdp() const { return tdp; }

// === Реализация GPU ===
GPU::GPU(string n, double p, int pScore, int t)
    : Component(n, p), powerScore(pScore), tdp(t) {}

void GPU::printInfo() const
{
  cout << "[GPU] " << name << " | " << price << " руб. | Оценка мощности: "
       << powerScore << "/100 | TDP: " << tdp << " Вт" << endl;
}
int GPU::getPowerScore() const { return powerScore; }
int GPU::getTdp() const { return tdp; }

// === Реализация Motherboard ===
Motherboard::Motherboard(string n, double p, string s, double maxFreq)
    : Component(n, p), socket(s), maxRamFreq(maxFreq) {}

void Motherboard::printInfo() const
{
  cout << "[Мат. плата] " << name << " | " << price << " руб. | Сокет: "
       << socket << " | Макс. частота ОЗУ: " << maxRamFreq << " МГц" << endl;
}
string Motherboard::getSocket() const { return socket; }
double Motherboard::getMaxRamFreq() const { return maxRamFreq; }

// === Реализация RAM ===
RAM::RAM(string n, double p, double freq)
    : Component(n, p), frequency(freq) {}

void RAM::printInfo() const
{
  cout << "[ОЗУ] " << name << " | " << price << " руб. | Частота: "
       << frequency << " МГц" << endl;
}
double RAM::getFrequency() const { return frequency; }

// === Реализация PSU ===
PSU::PSU(string n, double p, int w)
    : Component(n, p), wattage(w) {}

void PSU::printInfo() const
{
  cout << "[БП] " << name << " | " << price << " руб. | Мощность: "
       << wattage << " Вт" << endl;
}
int PSU::getWattage() const { return wattage; }

// === Реализация Storage ===
Storage::Storage(string n, double p, int cap, string t)
    : Component(n, p), capacity(cap), type(t) {}

void Storage::printInfo() const
{
  cout << "[Накопитель] " << name << " (" << type << ") | " << price
       << " руб. | Объем: " << capacity << " ГБ" << endl;
}