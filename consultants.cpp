#include "consultants.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Consultant::Consultant(string n, string level) : name(n), levelName(level) {}
Consultant::~Consultant() {}
string Consultant::getName() { return name; }
string Consultant::getLevelName() { return levelName; }

InternConsultant::InternConsultant(string n) : Consultant(n, "Стажер") {}

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

ExpertConsultant::ExpertConsultant(string n) : Consultant(n, "Эксперт") {}

vector<Component *> ExpertConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  double targetCpuBudget = 0, targetGpuBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  switch (purpose)
  {
  case 1:
  {
    // Игровой ПК: Упор на видеокарту
    targetCpuBudget = budget * 0.25;
    targetGpuBudget = budget * 0.45;
    targetRamBudget = budget * 0.10;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.10;
  }
  break;
  case 2:
  {
    // Рабочий ПК: Упор на процессор и оперативную память
    targetCpuBudget = budget * 0.30;
    targetGpuBudget = budget * 0.30;
    targetRamBudget = budget * 0.20;
    targetStorageBudget = budget * 0.10;
    targetPsuBudget = budget * 0.10;
  }
  break;
  case 3:
  {
    if (budget > 70000)
    {
      budget = 70000; // Офисный ПК не должен быть дороже 70к
    }
    targetCpuBudget = budget * 0.40;
    targetGpuBudget = 0; // Для офиса видеокарта не нужна, хватит "встройки"
    targetRamBudget = budget * 0.20;
    targetStorageBudget = budget * 0.20;
    targetPsuBudget = budget * 0.20;
  }
  break;

  default:
    break;
  }

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
  if (selectedCpu != nullptr)
    receipt.push_back(selectedCpu);

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
  if (selectedRam == nullptr && !catalog.rams.empty())
    selectedRam = catalog.rams[0];
  if (selectedRam)
    receipt.push_back(selectedRam);

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
  if (selectedStorage == nullptr && !catalog.storages.empty())
    selectedStorage = catalog.storages[0];
  if (selectedStorage)
    receipt.push_back(selectedStorage);

  PSU *selectedPsu = nullptr;
  int requiredTdp = 0;
  if (selectedCpu)
    requiredTdp += selectedCpu->getTdp();
  if (selectedGpu)
    requiredTdp += selectedGpu->getTdp();
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
  if (selectedPsu == nullptr && !catalog.psus.empty())
    selectedPsu = catalog.psus[0];
  if (selectedPsu)
    receipt.push_back(selectedPsu);

  return receipt;
}

ExperiencedConsultant::ExperiencedConsultant(string n) : Consultant(n, "Опытный") {}

vector<Component *> ExperiencedConsultant::buildPC(double budget, int purpose, Catalog &catalog)
{
  vector<Component *> receipt;

  // Вносим случайное искажение в бюджет (от 0.8 до 1.2) - "Человеческий фактор"
  double mod = 1.0 + ((rand() % 41 - 20) / 100.0);

  double targetCpuBudget = 0, targetGpuBudget = 0, targetRamBudget = 0, targetStorageBudget = 0, targetPsuBudget = 0;

  // Выбор весов для распределения бюджета на комплектующие в зависимости от назначения ПК
  // с учетом случайного искажения
  switch (purpose)
  {
  case 1:
  {
    targetCpuBudget = budget * 0.25 * mod;
    targetGpuBudget = budget * 0.45 * mod;
    targetRamBudget = budget * 0.10 * mod;
    targetStorageBudget = budget * 0.10 * mod;
    targetPsuBudget = budget * 0.10 * mod;
  }
  break;
  case 2:
  {
    targetCpuBudget = budget * 0.30 * mod;
    targetGpuBudget = budget * 0.30 * mod;
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
    targetCpuBudget = budget * 0.40 * mod;
    targetGpuBudget = 0;
    targetRamBudget = budget * 0.20 * mod;
    targetStorageBudget = budget * 0.20 * mod;
    targetPsuBudget = budget * 0.20 * mod;
  }
  break;

  default:
    break;
  }

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
  if (selectedRam == nullptr && !catalog.rams.empty())
    selectedRam = catalog.rams[0];
  if (selectedRam)
    receipt.push_back(selectedRam);

  Storage *selectedStorage = nullptr;
  for (Storage *st : catalog.storages)
  {
    if (st->getPrice() <= targetStorageBudget)
    {
      if (selectedStorage == nullptr || st->getPrice() > selectedStorage->getPrice())
        selectedStorage = st;
    }
  }
  if (selectedStorage == nullptr && !catalog.storages.empty())
    selectedStorage = catalog.storages[0];
  if (selectedStorage)
    receipt.push_back(selectedStorage);

  PSU *selectedPsu = nullptr;
  int requiredTdp = 0;
  if (selectedCpu)
    requiredTdp += selectedCpu->getTdp();
  if (selectedGpu)
    requiredTdp += selectedGpu->getTdp();

  for (PSU *psu : catalog.psus)
  {
    if (psu->getWattage() >= requiredTdp && psu->getPrice() <= targetPsuBudget)
    {
      if (selectedPsu == nullptr || psu->getPrice() > selectedPsu->getPrice())
        selectedPsu = psu;
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
  if (selectedPsu == nullptr && !catalog.psus.empty())
    selectedPsu = catalog.psus[0];
  if (selectedPsu)
    receipt.push_back(selectedPsu);

  return receipt;
}