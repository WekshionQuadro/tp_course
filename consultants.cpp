#include "consultants.h"
#include <cstdlib> // Для функции rand()
#include <iostream>

using namespace std;

// === Реализация базового класса Consultant ===
Consultant::Consultant(string n, string level) : name(n), levelName(level) {}
Consultant::~Consultant() {}
string Consultant::getName() const { return name; }
string Consultant::getLevelName() const { return levelName; }

// === Реализация СТАЖЕРА ===
InternConsultant::InternConsultant(string n) : Consultant(n, "Стажер") {}

vector<Component *> InternConsultant::buildPC(double budget, int purpose, const Catalog &catalog)
{
  vector<Component *> receipt;

  // Стажер не смотрит на бюджет, совместимость и цели.
  // Он берет случайную деталь с полки.
  if (!catalog.cpus.empty())
    receipt.push_back(catalog.cpus[rand() % catalog.cpus.size()]);

  if (!catalog.gpus.empty())
    receipt.push_back(catalog.gpus[rand() % catalog.gpus.size()]);

  if (!catalog.mobos.empty())
    receipt.push_back(catalog.mobos[rand() % catalog.mobos.size()]);

  if (!catalog.rams.empty())
    receipt.push_back(catalog.rams[rand() % catalog.rams.size()]);

  if (!catalog.psus.empty())
    receipt.push_back(catalog.psus[rand() % catalog.psus.size()]);

  if (!catalog.storages.empty())
    receipt.push_back(catalog.storages[rand() % catalog.storages.size()]);

  return receipt;
}

// === Реализация ЭКСПЕРТА ===
ExpertConsultant::ExpertConsultant(string n) : Consultant(n, "Эксперт") {}

vector<Component *> ExpertConsultant::buildPC(double budget, int purpose, const Catalog &catalog)
{
  vector<Component *> receipt;

  // Задаем весовые коэффициенты (пример для Игрового ПК - purpose == 1)
  double targetCpuBudget = budget * 0.25;
  double targetGpuBudget = budget * 0.45;

  // 1. Ищем лучший процессор, который вписывается в 25% бюджета
  CPU *selectedCpu = nullptr;
  for (CPU *cpu : catalog.cpus)
  {
    if (cpu->getPrice() <= targetCpuBudget)
    {
      // Если мы еще ничего не выбрали, или текущий процессор дороже (значит лучше), берем его
      if (selectedCpu == nullptr || cpu->getPrice() > selectedCpu->getPrice())
      {
        selectedCpu = cpu;
      }
    }
  }

  // Если по коэффициентам ничего не нашлось, берем самый дешевый
  if (selectedCpu == nullptr && !catalog.cpus.empty())
    selectedCpu = catalog.cpus[0];
  if (selectedCpu)
    receipt.push_back(selectedCpu);

  // 2. Ищем лучшую видеокарту под 45% бюджета
  GPU *selectedGpu = nullptr;
  for (GPU *gpu : catalog.gpus)
  {
    if (gpu->getPrice() <= targetGpuBudget)
    {
      if (selectedGpu == nullptr || gpu->getPrice() > selectedGpu->getPrice())
      {
        selectedGpu = gpu;
      }
    }
  }

  if (selectedGpu == nullptr && !catalog.gpus.empty())
    selectedGpu = catalog.gpus[0];
  if (selectedGpu)
    receipt.push_back(selectedGpu);

  // 3. Ищем материнскую плату (ОБЯЗАТЕЛЬНО СОВМЕСТИМУЮ ПО СОКЕТУ С ПРОЦЕССОРОМ)
  Motherboard *selectedMobo = nullptr;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (selectedCpu != nullptr && mobo->getSocket() == selectedCpu->getSocket())
    {
      selectedMobo = mobo;
      break; // Берем первую подошедшую по сокету для упрощения
    }
  }
  if (selectedMobo)
    receipt.push_back(selectedMobo);

  // TODO: Аналогично добавить поиск RAM (с проверкой частоты), Накопителя и Блока питания (проверка суммы Ватт)

  return receipt; // Возвращаем собранный с умом чек
}

// === Реализация ОПЫТНОГО ===
ExperiencedConsultant::ExperiencedConsultant(string n) : Consultant(n, "Опытный") {}

vector<Component *> ExperiencedConsultant::buildPC(double budget, int purpose, const Catalog &catalog)
{
  vector<Component *> receipt;

  // 1. Идеальные весовые коэффициенты (как у эксперта)
  double baseCpuBudget = budget * 0.25;
  double baseGpuBudget = budget * 0.45;

  // 2. Вносим случайное искажение (симуляция "человеческого фактора" или наличия товара)
  // rand() % 41 выдаст число от 0 до 40. Вычитаем 20 -> получаем от -20 до +20.
  // Делим на 100 и прибавляем 1.0 -> получаем множитель от 0.80 до 1.20
  double cpuModifier = 1.0 + ((rand() % 41 - 20) / 100.0);
  double gpuModifier = 1.0 + ((rand() % 41 - 20) / 100.0);

  double targetCpuBudget = baseCpuBudget * cpuModifier;
  double targetGpuBudget = baseGpuBudget * gpuModifier;

  // 3. Выбираем процессор, ориентируясь на ИСКАЖЕННЫЙ бюджет
  CPU *selectedCpu = nullptr;
  for (CPU *cpu : catalog.cpus)
  {
    if (cpu->getPrice() <= targetCpuBudget)
    {
      if (selectedCpu == nullptr || cpu->getPrice() > selectedCpu->getPrice())
      {
        selectedCpu = cpu;
      }
    }
  }
  if (selectedCpu == nullptr && !catalog.cpus.empty())
    selectedCpu = catalog.cpus[0];
  if (selectedCpu)
    receipt.push_back(selectedCpu);

  // 4. Выбираем видеокарту под ИСКАЖЕННЫЙ бюджет
  GPU *selectedGpu = nullptr;
  for (GPU *gpu : catalog.gpus)
  {
    if (gpu->getPrice() <= targetGpuBudget)
    {
      if (selectedGpu == nullptr || gpu->getPrice() > selectedGpu->getPrice())
      {
        selectedGpu = gpu;
      }
    }
  }
  if (selectedGpu == nullptr && !catalog.gpus.empty())
    selectedGpu = catalog.gpus[0];
  if (selectedGpu)
    receipt.push_back(selectedGpu);

  // 5. Выбираем материнскую плату (ОБЯЗАТЕЛЬНО СОВМЕСТИМУЮ ПО СОКЕТУ)
  // Опытный консультант знает, что сокеты должны совпадать, здесь он не ошибается.
  Motherboard *selectedMobo = nullptr;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (selectedCpu != nullptr && mobo->getSocket() == selectedCpu->getSocket())
    {
      selectedMobo = mobo;
      break;
    }
  }
  if (selectedMobo)
    receipt.push_back(selectedMobo);

  // TODO: Добавить RAM и Блок питания

  return receipt;
}