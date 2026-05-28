#include "consultants.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Реализация класса Consultant (базовый класс)
Consultant::Consultant(string n, string level) : name(n), levelName(level) {}
Consultant::~Consultant() {}
string Consultant::getName() { return name; }
string Consultant::getLevelName() { return levelName; }

// --- Базовые проверки на совместимость ---

bool Consultant::checkMobo(CPU *cpu, Motherboard *mobo)
{
  if (cpu == nullptr || mobo == nullptr)
    return false;
  return cpu->getSocket() == mobo->getSocket();
}

bool Consultant::checkRam(Motherboard *mobo, RAM *ram)
{
  if (mobo == nullptr || ram == nullptr)
    return false;
  return ram->getFrequency() <= mobo->getMaxRamFreq();
}

bool Consultant::checkPsu(int requiredTdp, PSU *psu)
{
  if (psu == nullptr)
    return false;
  return psu->getWattage() >= requiredTdp;
}

bool Consultant::checkCase(Motherboard *mobo, Case *pcCase)
{
  if (mobo == nullptr || pcCase == nullptr)
    return false;
  return pcCase->supports(mobo->getFormFactor());
}

// Реализация класса InternConsultant (консультант-стажер)
InternConsultant::InternConsultant(string n) : Consultant(n, "Стажер") {}

// Переопределенная функция сборки ПК консультантом-стажером
// Консультант-стажер игнорирует совместимость и бюджет, случайно выбирая комплектующие
vector<Component *> InternConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

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

// Реализация класса ExperiencedConsultant (опытный консультант)
// Опытный консультант собирает совместимый ПК, но искажает бюджет на +- 20% (случайность)
ExperiencedConsultant::ExperiencedConsultant(string n) : Consultant(n, "Опытный") {}

vector<Component *> ExperiencedConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  // Вносим случайное искажение в бюджет (от 0.8 до 1.2)
  double mod = 1.0 + ((rand() % 41 - 20) / 100.0);

  // Инициализация переменных для распределения бюджета на комплектующие
  double targetCpuBudget = 0, targetGpuBudget = 0, targetMoboBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  // с учетом случайного искажения
  switch (purpose)
  {
  case 1:
  {
    targetCpuBudget = budget * 0.20 * mod;
    targetGpuBudget = budget * 0.40 * mod;
    targetMoboBudget = budget * 0.10 * mod;
    targetRamBudget = budget * 0.10 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.10 * mod;
  }
  break;
  case 2:
  {
    targetCpuBudget = budget * 0.25 * mod;
    targetGpuBudget = budget * 0.25 * mod;
    targetMoboBudget = budget * 0.10 * mod;
    targetRamBudget = budget * 0.20 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.10 * mod;
  }
  break;
  case 3:
  {
    if (budget > 70000)
    {
      budget = 70000;
    }
    targetCpuBudget = budget * 0.35 * mod;
    targetGpuBudget = 0;
    targetMoboBudget = budget * 0.15 * mod;
    targetMoboBudget = budget * 0.10 * mod;
    targetRamBudget = budget * 0.20 * mod;
    targetStorageBudget = budget * 0.15 * mod;
    targetPsuBudget = budget * 0.15 * mod;
  }
  break;

  default:
    break;
  }

  // Подбор процессора
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
  if (selectedCpu == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего процессора. Сборка выдается без процессора!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedCpu);
  }

  // Подбор видеокарты
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
  if (selectedGpu == nullptr)
  {
    if (targetGpuBudget > 0)
    {
      std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей видеокарты. Сборка выдается без видеокарты!" << std::endl;
    }
  }
  else
  {
    receipt.push_back(selectedGpu);
  }

  // Подбор материнской платы
  Motherboard *selectedMobo = nullptr;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (selectedCpu != nullptr && mobo->getSocket() == selectedCpu->getSocket())
    {
      selectedMobo = mobo;
      break;
    }
  }
  if (selectedMobo == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей материнской платы. Сборка выдается без материнской платы!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedMobo);
  }

  // Подбор оперативной памяти
  RAM *selectedRam = nullptr;
  for (RAM *ram : catalog.rams)
  {
    if (ram->getPrice() <= targetRamBudget)
    {
      if (selectedMobo == nullptr || ram->getFrequency() <= selectedMobo->getMaxRamFreq())
      {
        if (selectedRam == nullptr || ram->getPrice() > selectedRam->getPrice())
          selectedRam = ram;
      }
    }
  }
  if (selectedRam == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей оперативной памяти. Сборка выдается без ОЗУ!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedRam);
  }

  // Подбор накопителя
  Storage *selectedStorage = nullptr;
  for (Storage *st : catalog.storages)
  {
    if (st->getPrice() <= targetStorageBudget)
    {
      if (selectedStorage == nullptr || st->getPrice() > selectedStorage->getPrice())
        selectedStorage = st;
    }
  }
  if (selectedStorage == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего накопителя. Сборка выдается без накопителя!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedStorage);
  }

  // Подбор блока питания
  PSU *selectedPsu = nullptr;
  int requiredPowerDraw = 0;
  if (selectedCpu)
    requiredPowerDraw += selectedCpu->getPowerDraw();
  if (selectedGpu)
    requiredPowerDraw += selectedGpu->getPowerDraw();

  for (PSU *psu : catalog.psus)
  {
    if (psu->getWattage() >= requiredPowerDraw && psu->getPrice() <= targetPsuBudget)
    {
      if (selectedPsu == nullptr || psu->getPrice() > selectedPsu->getPrice())
        selectedPsu = psu;
    }
  }
  if (selectedPsu == nullptr)
  {
    for (PSU *psu : catalog.psus)
    {
      if (psu->getWattage() >= requiredPowerDraw)
      {
        selectedPsu = psu;
        break;
      }
    }
  }

  // Если БП так и не нашелся (ни по бюджету, ни по мощности)
  if (selectedPsu == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет блока питания подходящей мощности. Сборка выдается без БП!" << std::endl;
  }
  else
  {
    // Если БП подобран успешно, добавляем его в чек
    receipt.push_back(selectedPsu);
  }

  return receipt;
}

// Реализация класса ExpertConsultant (консультант-эксперт)
// Консультант-эксперт собирает совместимы ПК, полностью соответсвуя бюджету
ExpertConsultant::ExpertConsultant(string n) : Consultant(n, "Эксперт") {}

vector<Component *> ExpertConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  double targetCpuBudget = 0, targetGpuBudget = 0, targetMoboBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  switch (purpose)
  {
  case 1:
  {
    // Игровой ПК: Упор на видеокарту
    targetCpuBudget = budget * 0.20;
    targetGpuBudget = budget * 0.40;
    targetMoboBudget = budget * 0.1;
    targetRamBudget = budget * 0.10;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.10;
  }
  break;
  case 2:
  {
    // Рабочий ПК: Упор на процессор и оперативную память
    targetCpuBudget = budget * 0.25;
    targetGpuBudget = budget * 0.25;
    targetMoboBudget = budget * 0.1;
    targetRamBudget = budget * 0.20;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.10;
  }
  break;
  case 3:
  {
    if (budget >= 50000)
    {
      budget = 50000; // Офисный ПК не должен быть дороже 50к
    }
    targetCpuBudget = budget * 0.40;
    targetGpuBudget = 0;
    targetMoboBudget = budget * 0.15;
    targetRamBudget = budget * 0.15;
    targetStorageBudget = budget * 0.15;
    targetPsuBudget = budget * 0.15;
  }
  break;

  default:
    break;
  }

  // Подбор процессора
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
  if (selectedCpu == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего процессора. Сборка выдается без процессора!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedCpu);
  }

  // Подбор видеокарты
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
  if (selectedGpu == nullptr)
  {
    if (targetGpuBudget > 0)
    {
      std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей видеокарты. Сборка выдается без видеокарты!" << std::endl;
    }
  }
  else
  {
    receipt.push_back(selectedGpu);
  }

  // Подбор материнской платы
  Motherboard *selectedMobo = nullptr;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (selectedCpu != nullptr && mobo->getSocket() == selectedCpu->getSocket())
    {
      selectedMobo = mobo;
      break;
    }
  }
  if (selectedMobo == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей материнской платы. Сборка выдается без материнской платы!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedMobo);
  }

  // Подбор оперативной памяти
  RAM *selectedRam = nullptr;
  for (RAM *ram : catalog.rams)
  {
    if (ram->getPrice() <= targetRamBudget)
    {
      if (selectedMobo == nullptr || ram->getFrequency() <= selectedMobo->getMaxRamFreq())
      {
        if (selectedRam == nullptr || ram->getPrice() > selectedRam->getPrice())
        {
          selectedRam = ram;
        }
      }
    }
  }
  if (selectedRam == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей оперативной памяти. Сборка выдается без ОЗУ!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedRam);
  }

  // Подбор накопителя
  Storage *selectedStorage = nullptr;
  for (Storage *st : catalog.storages)
  {
    if (st->getPrice() <= targetStorageBudget)
    {
      if (selectedStorage == nullptr || st->getPrice() > selectedStorage->getPrice())
      {
        selectedStorage = st;
      }
    }
  }
  if (selectedStorage == nullptr)
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего накопителя. Сборка выдается без накопителя!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedStorage);
  }

  // Подбор блока питания
  PSU *selectedPsu = nullptr;
  int requiredTdp = 0;
  if (selectedCpu)
    requiredTdp += selectedCpu->getPowerDraw();
  if (selectedGpu)
    requiredTdp += selectedGpu->getPowerDraw();
  requiredTdp = (int)(requiredTdp * 1.2);

  for (PSU *psu : catalog.psus)
  {
    if (psu->getWattage() >= requiredTdp && psu->getPrice() <= targetPsuBudget)
    {
      if (selectedPsu == nullptr || psu->getPrice() > selectedPsu->getPrice())
      {
        selectedPsu = psu;
      }
    }
  }
  if (selectedPsu == nullptr)
  {
    for (PSU *psu : catalog.psus)
    {
      if (psu->getWattage() >= requiredTdp)
      {
        selectedPsu = psu;
        break;
      }
    }
  }
  if (selectedPsu == nullptr)
  {
    std::cout << "\n Консультант " << name << " сообщает: В магазине нет блока питания подходящей мощности. Сборка выдается без БП!" << std::endl;
  }
  else
  {
    receipt.push_back(selectedPsu);
  }

  return receipt;
}