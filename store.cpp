#include "store.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Store::Store() {}

Store::~Store()
{
  for (Consultant *c : consultants)
  {
    delete c;
  }

  // Устраняем утечку памяти, очищая каталоги комплектующих
  for (CPU *comp : catalog.cpus)
    delete comp;
  for (GPU *comp : catalog.gpus)
    delete comp;
  for (Motherboard *comp : catalog.mobos)
    delete comp;
  for (RAM *comp : catalog.rams)
    delete comp;
  for (PSU *comp : catalog.psus)
    delete comp;
  for (Storage *comp : catalog.storages)
    delete comp;
  for (Case *comp : catalog.cases)
    delete comp;
}

void Store::loadCPUs(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name, socket;
  double price, freq;
  int cores, threads, tdp;

  while (file >> name >> price >> socket >> cores >> threads >> freq >> tdp)
  {
    catalog.cpus.push_back(new CPU(name, price, socket, cores, threads, freq, tdp));
  }
  file.close();
}

void Store::loadGPUs(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name;
  double price;
  int powerScore, tdp;

  while (file >> name >> price >> powerScore >> tdp)
  {
    catalog.gpus.push_back(new GPU(name, price, powerScore, tdp));
  }
  file.close();
}

void Store::loadMotherboards(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name, socket, ddrType, formFactor;
  double price, maxFreq;

  while (file >> name >> price >> socket >> ddrType >> maxFreq >> formFactor)
  {
    catalog.mobos.push_back(new Motherboard(name, price, socket, ddrType, formFactor, maxFreq));
  }
  file.close();
}

void Store::loadRAMs(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name, type;
  double price, freq;

  while (file >> name >> price >> type >> freq)
  {
    catalog.rams.push_back(new RAM(name, price, type, freq));
  }
  file.close();
}

void Store::loadPSUs(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name;
  double price;
  int wattage;

  while (file >> name >> price >> wattage)
  {
    catalog.psus.push_back(new PSU(name, price, wattage));
  }
  file.close();
}

void Store::loadStorages(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name, type;
  double price;
  int capacity;

  while (file >> name >> price >> capacity >> type)
  {
    catalog.storages.push_back(new Storage(name, price, capacity, type));
  }
  file.close();
}

void Store::loadCases(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
    return;

  string header;
  getline(file, header);

  string name, sizeType, supportedForms;
  double price;

  while (file >> name >> price >> sizeType >> supportedForms)
  {
    catalog.cases.push_back(new Case(name, price, sizeType, supportedForms));
  }
  file.close();
}

void Store::loadConsultants(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
  {
    cout << "Ошибка: не удалось открыть " << filepath << endl;
    return;
  }

  string header;
  getline(file, header);

  string name, level;
  while (file >> name >> level)
  {
    if (level == "Стажер")
    {
      consultants.push_back(new InternConsultant(name));
    }
    else if (level == "Опытный")
    {
      consultants.push_back(new ExperiencedConsultant(name));
    }
    else if (level == "Эксперт")
    {
      consultants.push_back(new ExpertConsultant(name));
    }
  }
  file.close();
}

void Store::loadAllData()
{
  loadCPUs("Комплектующие/cpu.txt");
  loadGPUs("Комплектующие/gpu.txt");
  loadMotherboards("Комплектующие/motherboard.txt");
  loadRAMs("Комплектующие/ram.txt");
  loadPSUs("Комплектующие/psu.txt");
  loadStorages("Комплектующие/storage.txt");
  loadCases("Комплектующие/case.txt");
  loadConsultants("Комплектующие/consultants.txt");

  cout << "Данные из папки 'Комплектующие' успешно загружены!" << endl;
}

void Store::startSimulation()
{
  if (consultants.empty())
  {
    cout << "Ошибка: список консультантов пуст! Проверьте файл consultants.txt" << endl;
    return;
  }

  double budget;
  int purpose;

  cout << "\n=== Добро пожаловать в конфигуратор ПК! ===" << endl;
  cout << "Введите ваш бюджет (в рублях): ";
  cin >> budget;

  cout << "Выберите назначение ПК:" << endl;
  cout << "1 - Игровой" << endl;
  cout << "2 - Рабочий (Рендер, Программирование)" << endl;
  cout << "3 - Офисный/Домашний" << endl;
  cout << "Ваш выбор (1-3): ";
  cin >> purpose;

  int randIndex = rand() % consultants.size();
  Consultant *consultant = consultants[randIndex];

  cout << "\nК вам подходит консультант " << consultant->getName()
       << " (Уровень: " << consultant->getLevelName() << ")" << endl;
  cout << "Идет подбор комплектующих..." << endl;

  vector<Component *> receipt = consultant->buildPC(budget, purpose, catalog);

  double totalCost = 0;
  for (Component *comp : receipt)
  {
    totalCost += comp->getPrice();
  }
  double remainingBudget = budget - totalCost;

  cout << "\n=== ВАШ ЧЕК ===" << endl;
  for (Component *comp : receipt)
  {
    comp->printInfo();
  }
  cout << "------------------------" << endl;
  cout << "Итоговая стоимость: " << totalCost << " руб." << endl;
  cout << "Остаток бюджета: " << remainingBudget << " руб." << endl;

  ofstream outFile("result.txt");
  if (outFile.is_open())
  {
    outFile << "=== ВАШ ЧЕК ===" << endl;
    outFile << "Консультант: " << consultant->getName() << " (" << consultant->getLevelName() << ")\n\n";

    for (Component *comp : receipt)
    {
      outFile << comp->getName() << " - " << comp->getPrice() << " руб." << endl;
    }
    outFile << "------------------------\n";
    outFile << "Итоговая стоимость: " << totalCost << " руб.\n";
    outFile << "Остаток бюджета: " << remainingBudget << " руб.\n";

    outFile.close();
    cout << "\nЧек успешно сохранен в файл result.txt!" << endl;
  }
  else
  {
    cout << "\nОшибка при сохранении чека в файл." << endl;
  }
}