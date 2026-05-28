#include "consultants.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Реализация класса Consultant (базовый класс)
Consultant::Consultant(string n, string level) : name(n), levelName(level) {}
Consultant::~Consultant() {}
string Consultant::getName() { return name; }
string Consultant::getLevelName() { return levelName; }

// Реализация функций проверок на совместимость комплектующих

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

  return (ram->getType() == mobo->getDdrType()) && (ram->getFrequency() <= mobo->getMaxRamFreq());
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
// Консультант-стажер игнорирует бюджет, выбирая комплектующие случайно, но учитывает совместимость
vector<Component *> InternConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  // Подбор процессора
  CPU *selectedCpu = nullptr;
  vector<CPU *> validCpus = catalog.cpus;
  if (validCpus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего процессора. Сборка выдается без процессора!" << std::endl;
  }
  else
  {
    selectedCpu = validCpus[rand() % validCpus.size()];
    receipt.push_back(selectedCpu);
  }

  // Подбор видеокарты
  GPU *selectedGpu = nullptr;
  vector<GPU *> validGpus = catalog.gpus;
  if (validGpus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей видеокарты. Сборка выдается без видеокарты!" << std::endl;
  }
  else
  {
    selectedGpu = validGpus[rand() % validGpus.size()];
    receipt.push_back(selectedGpu);
  }

  // Подбор материнской платы
  Motherboard *selectedMobo = nullptr;
  vector<Motherboard *> validMobos;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (checkMobo(selectedCpu, mobo))
      validMobos.push_back(mobo);
  }
  if (validMobos.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей материнской платы. Сборка выдается без материнской платы!" << std::endl;
  }
  else
  {
    selectedMobo = validMobos[rand() % validMobos.size()];
    receipt.push_back(selectedMobo);
  }

  // Подбор оперативной памяти
  RAM *selectedRam = nullptr;
  vector<RAM *> validRams;
  for (RAM *ram : catalog.rams)
  {
    if (checkRam(selectedMobo, ram))
      validRams.push_back(ram);
  }
  if (validRams.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей оперативной памяти. Сборка выдается без ОЗУ!" << std::endl;
  }
  else
  {
    selectedRam = validRams[rand() % validRams.size()];
    receipt.push_back(selectedRam);
  }

  // Подбор накопителя
  Storage *selectedStorage = nullptr;
  vector<Storage *> validStorages = catalog.storages;
  if (validStorages.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего накопителя. Сборка выдается без накопителя!" << std::endl;
  }
  else
  {
    selectedStorage = validStorages[rand() % validStorages.size()];
    receipt.push_back(selectedStorage);
  }

  // Подбор блока питания
  PSU *selectedPsu = nullptr;
  int requiredPowerDraw = 0;
  if (selectedCpu)
    requiredPowerDraw += selectedCpu->getPowerDraw();
  if (selectedGpu)
    requiredPowerDraw += selectedGpu->getPowerDraw();
  requiredPowerDraw = (int)(requiredPowerDraw * 1.2);

  vector<PSU *> validPsus;
  for (PSU *psu : catalog.psus)
  {
    if (checkPsu(requiredPowerDraw, psu))
      validPsus.push_back(psu);
  }
  if (validPsus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет блока питания подходящей мощности. Сборка выдается без БП!" << std::endl;
  }
  else
  {
    selectedPsu = validPsus[rand() % validPsus.size()];
    receipt.push_back(selectedPsu);
  }

  // Подбор корпуса
  Case *selectedCase = nullptr;
  vector<Case *> validCases;
  for (Case *pcCase : catalog.cases)
  {
    if (checkCase(selectedMobo, pcCase))
      validCases.push_back(pcCase);
  }
  if (validCases.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего корпуса. Сборка выдается без корпуса!" << std::endl;
  }
  else
  {
    selectedCase = validCases[rand() % validCases.size()];
    receipt.push_back(selectedCase);
  }

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
  double targetCpuBudget = 0, targetGpuBudget = 0, targetMoboBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0, targetCaseBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  // с учетом случайного искажения
  switch (purpose)
  {
  case 1:
  {
    targetCpuBudget = budget * 0.20 * mod;
    targetGpuBudget = budget * 0.35 * mod;
    targetMoboBudget = budget * 0.10 * mod;
    targetRamBudget = budget * 0.10 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.075 * mod;
    targetCaseBudget = budget * 0.075 * mod;
  }
  break;
  case 2:
  {
    targetCpuBudget = budget * 0.25 * mod;
    targetGpuBudget = budget * 0.25 * mod;
    targetMoboBudget = budget * 0.10 * mod;
    targetRamBudget = budget * 0.15 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.075 * mod;
    targetCaseBudget = budget * 0.075 * mod;
  }
  break;
  case 3:
  {
    if (budget > 70000)
    {
      budget = 70000;
    }
    targetCpuBudget = budget * 0.30 * mod;
    targetGpuBudget = 0;
    targetMoboBudget = budget * 0.15 * mod;
    targetRamBudget = budget * 0.20 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.125 * mod;
    targetCaseBudget = budget * 0.125 * mod;
  }
  break;

  default:
    break;
  }

  // Подбор процессора
  CPU *selectedCpu = nullptr;
  vector<CPU *> validCpus;
  for (CPU *cpu : catalog.cpus)
  {
    if (cpu->getPrice() <= targetCpuBudget)
      validCpus.push_back(cpu);
  }
  if (validCpus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего процессора. Сборка выдается без процессора!" << std::endl;
  }
  else
  {
    selectedCpu = validCpus[0];
    for (CPU *cpu : validCpus)
    {
      if (cpu->getPrice() > selectedCpu->getPrice())
        selectedCpu = cpu;
    }
    receipt.push_back(selectedCpu);
  }

  // Подбор видеокарты
  GPU *selectedGpu = nullptr;
  vector<GPU *> validGpus;
  for (GPU *gpu : catalog.gpus)
  {
    if (gpu->getPrice() <= targetGpuBudget)
      validGpus.push_back(gpu);
  }
  if (validGpus.empty())
  {
    if (targetGpuBudget > 0)
    {
      std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей видеокарты. Сборка выдается без видеокарты!" << std::endl;
    }
  }
  else
  {
    selectedGpu = validGpus[0];
    for (GPU *gpu : validGpus)
    {
      if (gpu->getPrice() > selectedGpu->getPrice())
        selectedGpu = gpu;
    }
    receipt.push_back(selectedGpu);
  }

  // Подбор материнской платы
  Motherboard *selectedMobo = nullptr;
  vector<Motherboard *> validMobos;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (checkMobo(selectedCpu, mobo) && mobo->getPrice() <= targetMoboBudget)
      validMobos.push_back(mobo);
  }
  if (validMobos.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей материнской платы. Сборка выдается без материнской платы!" << std::endl;
  }
  else
  {
    selectedMobo = validMobos[0];
    for (Motherboard *mobo : validMobos)
    {
      if (mobo->getPrice() > selectedMobo->getPrice())
        selectedMobo = mobo;
    }
    receipt.push_back(selectedMobo);
  }

  // Подбор оперативной памяти
  RAM *selectedRam = nullptr;
  vector<RAM *> validRams;
  for (RAM *ram : catalog.rams)
  {
    if (checkRam(selectedMobo, ram) && ram->getPrice() <= targetRamBudget)
      validRams.push_back(ram);
  }
  if (validRams.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей оперативной памяти. Сборка выдается без ОЗУ!" << std::endl;
  }
  else
  {
    selectedRam = validRams[0];
    for (RAM *ram : validRams)
    {
      if (ram->getPrice() > selectedRam->getPrice())
        selectedRam = ram;
    }
    receipt.push_back(selectedRam);
  }

  // Подбор накопителя
  Storage *selectedStorage = nullptr;
  vector<Storage *> validStorages;
  for (Storage *st : catalog.storages)
  {
    if (st->getPrice() <= targetStorageBudget)
      validStorages.push_back(st);
  }
  if (validStorages.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего накопителя. Сборка выдается без накопителя!" << std::endl;
  }
  else
  {
    selectedStorage = validStorages[0];
    for (Storage *st : validStorages)
    {
      if (st->getPrice() > selectedStorage->getPrice())
        selectedStorage = st;
    }
    receipt.push_back(selectedStorage);
  }

  // Подбор блока питания
  PSU *selectedPsu = nullptr;
  int requiredPowerDraw = 0;
  if (selectedCpu)
    requiredPowerDraw += selectedCpu->getPowerDraw();
  if (selectedGpu)
    requiredPowerDraw += selectedGpu->getPowerDraw();

  vector<PSU *> validPsus;
  for (PSU *psu : catalog.psus)
  {
    if (checkPsu(requiredPowerDraw, psu) && psu->getPrice() <= targetPsuBudget)
      validPsus.push_back(psu);
  }
  if (validPsus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего блока питания. Сборка выдается без БП!" << std::endl;
  }
  else
  {
    selectedPsu = validPsus[0];
    for (PSU *psu : validPsus)
    {
      if (psu->getPrice() > selectedPsu->getPrice())
        selectedPsu = psu;
    }
    receipt.push_back(selectedPsu);
  }

  // Подбор корпуса
  Case *selectedCase = nullptr;
  vector<Case *> validCases;
  for (Case *pcCase : catalog.cases)
  {
    if (checkCase(selectedMobo, pcCase) && pcCase->getPrice() <= targetCaseBudget)
      validCases.push_back(pcCase);
  }
  if (validCases.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего корпуса. Сборка выдается без корпуса!" << std::endl;
  }
  else
  {
    selectedCase = validCases[0];
    for (Case *pcCase : validCases)
    {
      if (pcCase->getPrice() > selectedCase->getPrice())
        selectedCase = pcCase;
    }
    receipt.push_back(selectedCase);
  }

  return receipt;
}

// Реализация класса ExpertConsultant (консультант-эксперт)
// Консультант-эксперт собирает совместимы ПК, полностью соответсвуя бюджету
ExpertConsultant::ExpertConsultant(string n) : Consultant(n, "Эксперт") {}

vector<Component *> ExpertConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  double targetCpuBudget = 0, targetGpuBudget = 0, targetMoboBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0, targetCaseBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  switch (purpose)
  {
  case 1:
  {
    // Игровой ПК: Упор на видеокарту
    targetCpuBudget = budget * 0.20;
    targetGpuBudget = budget * 0.35;
    targetMoboBudget = budget * 0.10;
    targetRamBudget = budget * 0.10;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.075;
    targetCaseBudget = budget * 0.075;
  }
  break;
  case 2:
  {
    // Рабочий ПК: Упор на процессор и оперативную память
    targetCpuBudget = budget * 0.25;
    targetGpuBudget = budget * 0.25;
    targetMoboBudget = budget * 0.10;
    targetRamBudget = budget * 0.15;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.075;
    targetCaseBudget = budget * 0.075;
  }
  break;
  case 3:
  {
    if (budget >= 50000)
    {
      budget = 50000; // Офисный ПК не должен быть дороже 50к
    }
    targetCpuBudget = budget * 0.3;
    targetGpuBudget = 0;
    targetMoboBudget = budget * 0.15;
    targetRamBudget = budget * 0.20;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.125;
    targetCaseBudget = budget * 0.125;
  }
  break;

  default:
    break;
  }

  // Подбор процессора
  CPU *selectedCpu = nullptr;
  vector<CPU *> validCpus;
  for (CPU *cpu : catalog.cpus)
  {
    if (cpu->getPrice() <= targetCpuBudget)
      validCpus.push_back(cpu);
  }
  if (validCpus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего процессора. Сборка выдается без процессора!" << std::endl;
  }
  else
  {
    selectedCpu = validCpus[0];
    for (CPU *cpu : validCpus)
    {
      if (cpu->getPrice() > selectedCpu->getPrice())
        selectedCpu = cpu;
    }
    receipt.push_back(selectedCpu);
  }

  // Подбор видеокарты
  GPU *selectedGpu = nullptr;
  vector<GPU *> validGpus;
  for (GPU *gpu : catalog.gpus)
  {
    if (gpu->getPrice() <= targetGpuBudget)
      validGpus.push_back(gpu);
  }
  if (validGpus.empty())
  {
    if (targetGpuBudget > 0)
    {
      std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей видеокарты. Сборка выдается без видеокарты!" << std::endl;
    }
  }
  else
  {
    selectedGpu = validGpus[0];
    for (GPU *gpu : validGpus)
    {
      if (gpu->getPrice() > selectedGpu->getPrice())
        selectedGpu = gpu;
    }
    receipt.push_back(selectedGpu);
  }

  // Подбор материнской платы
  Motherboard *selectedMobo = nullptr;
  vector<Motherboard *> validMobos;
  for (Motherboard *mobo : catalog.mobos)
  {
    if (checkMobo(selectedCpu, mobo) && mobo->getPrice() <= targetMoboBudget)
      validMobos.push_back(mobo);
  }
  if (validMobos.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей материнской платы. Сборка выдается без материнской платы!" << std::endl;
  }
  else
  {
    selectedMobo = validMobos[0];
    for (Motherboard *mobo : validMobos)
    {
      if (mobo->getPrice() > selectedMobo->getPrice())
        selectedMobo = mobo;
    }
    receipt.push_back(selectedMobo);
  }

  // Подбор оперативной памяти
  RAM *selectedRam = nullptr;
  vector<RAM *> validRams;
  for (RAM *ram : catalog.rams)
  {
    if (checkRam(selectedMobo, ram) && ram->getPrice() <= targetRamBudget)
      validRams.push_back(ram);
  }
  if (validRams.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящей оперативной памяти. Сборка выдается без ОЗУ!" << std::endl;
  }
  else
  {
    selectedRam = validRams[0];
    for (RAM *ram : validRams)
    {
      if (ram->getPrice() > selectedRam->getPrice())
        selectedRam = ram;
    }
    receipt.push_back(selectedRam);
  }

  // Подбор накопителя
  Storage *selectedStorage = nullptr;
  vector<Storage *> validStorages;
  for (Storage *st : catalog.storages)
  {
    if (st->getPrice() <= targetStorageBudget)
      validStorages.push_back(st);
  }
  if (validStorages.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего накопителя. Сборка выдается без накопителя!" << std::endl;
  }
  else
  {
    selectedStorage = validStorages[0];
    for (Storage *st : validStorages)
    {
      if (st->getPrice() > selectedStorage->getPrice())
        selectedStorage = st;
    }
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

  vector<PSU *> validPsus;
  for (PSU *psu : catalog.psus)
  {
    if (checkPsu(requiredTdp, psu) && psu->getPrice() <= targetPsuBudget)
      validPsus.push_back(psu);
  }
  if (validPsus.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего блока питания. Сборка выдается без БП!" << std::endl;
  }
  else
  {
    selectedPsu = validPsus[0];
    for (PSU *psu : validPsus)
    {
      if (psu->getPrice() > selectedPsu->getPrice())
        selectedPsu = psu;
    }
    receipt.push_back(selectedPsu);
  }

  // Подбор корпуса
  Case *selectedCase = nullptr;
  vector<Case *> validCases;
  for (Case *pcCase : catalog.cases)
  {
    if (checkCase(selectedMobo, pcCase) && pcCase->getPrice() <= targetCaseBudget)
      validCases.push_back(pcCase);
  }
  if (validCases.empty())
  {
    std::cout << "\n[!] Консультант " << name << " сообщает: В магазине нет подходящего корпуса. Сборка выдается без корпуса!" << std::endl;
  }
  else
  {
    selectedCase = validCases[0];
    for (Case *pcCase : validCases)
    {
      if (pcCase->getPrice() > selectedCase->getPrice())
        selectedCase = pcCase;
    }
    receipt.push_back(selectedCase);
  }

  return receipt;
}