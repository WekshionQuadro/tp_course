#include "store.h"
#include <iostream>
#include <fstream>

using namespace std;

Store::Store() {}

Store::~Store()
{
  // Здесь позже напишем очистку памяти (удаление объектов из каталога)
}

void Store::loadCPUs(const string &filepath)
{
  ifstream file(filepath);
  if (!file.is_open())
  {
    cout << "Ошибка: не удалось открыть " << filepath << endl;
    return;
  }

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

  string name, socket;
  double price, maxFreq;

  while (file >> name >> price >> socket >> maxFreq)
  {
    catalog.mobos.push_back(new Motherboard(name, price, socket, maxFreq));
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

  string name;
  double price, freq;

  while (file >> name >> price >> freq)
  {
    catalog.rams.push_back(new RAM(name, price, freq));
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

// Главный метод, который вызывает все остальные
void Store::loadAllData()
{
  loadCPUs("Комплектующие/cpu.txt");
  loadGPUs("Комплектующие/gpu.txt");
  loadMotherboards("Комплектующие/motherboard.txt");
  loadRAMs("Комплектующие/ram.txt");
  loadPSUs("Комплектующие/psu.txt");
  loadStorages("Комплектующие/storage.txt");

  cout << "Данные из папки 'Комплектующие' успешно загружены!" << endl;
}

void Store::startSimulation()
{
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

  Consultant *consultant = nullptr;
  int randNum = rand() % 3;
  if (randNum == 0)
  {
    consultant = new InternConsultant("Олег");
  }
  else if (randNum == 1)
  {
    consultant = new ExperiencedConsultant("Анна");
  }
  else
  {
    consultant = new ExpertConsultant("Виктор");
  }

  cout << "\nК вам подходит консультант " << consultant->getName()
       << " (Уровень: " << consultant->getLevelName() << ")" << endl;
  cout << "Идет подбор комплектующих..." << endl;

  vector<Component *> receipt = consultant->buildPC(budget, purpose, catalog);

  // Подсчет ВЫЧИСЛЯЕМЫХ ПОКАЗАТЕЛЕЙ
  double totalCost = 0;
  for (Component *comp : receipt)
  {
    totalCost += comp->getPrice();
  }
  double remainingBudget = budget - totalCost;

  // Вывод чека на экран
  cout << "\n=== ВАШ ЧЕК ===" << endl;
  for (Component *comp : receipt)
  {
    comp->printInfo(); // Полиморфный вывод информации
  }
  cout << "------------------------" << endl;
  cout << "Итоговая стоимость: " << totalCost << " руб." << endl;
  cout << "Остаток бюджета: " << remainingBudget << " руб." << endl;

  // ЗАПИСЬ РЕЗУЛЬТАТОВ В ФАЙЛ
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

    // Здесь можно добавить "Индекс сбалансированности" на будущее

    outFile.close();
    cout << "\nЧек успешно сохранен в файл result.txt!" << endl;
  }
  else
  {
    cout << "\nОшибка при сохранении чека в файл." << endl;
  }

  // Очистка памяти
  delete consultant;
}