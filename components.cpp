#include "components.h"
#include <iostream>

using namespace std;

Component::Component(string n, double p) : name(n), price(p) {}
Component::~Component() {}
string Component::getName() { return name; }
double Component::getPrice() { return price; }
void Component::printInfo() {}

CPU::CPU(string n, double p, string s, int c, int th, double f, int t)
    : Component(n, p), socket(s), cores(c), threads(th), frequency(f), tdp(t) {}

void CPU::printInfo()
{
  cout << "[CPU] " << name << " | " << price << " руб. | Сокет: " << socket
       << " | " << cores << " ядер / " << threads << " потоков | "
       << frequency << " ГГц | TDP: " << tdp << " Вт" << endl;
}
string CPU::getSocket() { return socket; }
int CPU::getTdp() { return tdp; }

GPU::GPU(string n, double p, int pScore, int t)
    : Component(n, p), powerScore(pScore), tdp(t) {}

void GPU::printInfo()
{
  cout << "[GPU] " << name << " | " << price << " руб. | Оценка мощности: "
       << powerScore << "/100 | TDP: " << tdp << " Вт" << endl;
}
int GPU::getPowerScore() { return powerScore; }
int GPU::getTdp() { return tdp; }

Motherboard::Motherboard(string n, double p, string s, double maxFreq)
    : Component(n, p), socket(s), maxRamFreq(maxFreq) {}

void Motherboard::printInfo()
{
  cout << "[Мат. плата] " << name << " | " << price << " руб. | Сокет: "
       << socket << " | Макс. частота ОЗУ: " << maxRamFreq << " МГц" << endl;
}
string Motherboard::getSocket() { return socket; }
double Motherboard::getMaxRamFreq() { return maxRamFreq; }

RAM::RAM(string n, double p, double freq)
    : Component(n, p), frequency(freq) {}

void RAM::printInfo()
{
  cout << "[ОЗУ] " << name << " | " << price << " руб. | Частота: "
       << frequency << " МГц" << endl;
}
double RAM::getFrequency() { return frequency; }

PSU::PSU(string n, double p, int w)
    : Component(n, p), wattage(w) {}

void PSU::printInfo()
{
  cout << "[БП] " << name << " | " << price << " руб. | Мощность: "
       << wattage << " Вт" << endl;
}
int PSU::getWattage() { return wattage; }

Storage::Storage(string n, double p, int cap, string t)
    : Component(n, p), capacity(cap), type(t) {}

void Storage::printInfo()
{
  cout << "[Накопитель] " << name << " (" << type << ") | " << price
       << " руб. | Объем: " << capacity << " ГБ" << endl;
}