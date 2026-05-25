#pragma once
#include <string>
#include <vector>
#include "components.h" // Подключаем знания о комплектующих

// Структура "Витрина", чтобы удобно передавать все списки деталей сразу
struct Catalog
{
  std::vector<CPU *> cpus;
  std::vector<GPU *> gpus;
  std::vector<Motherboard *> mobos;
  std::vector<RAM *> rams;
  std::vector<PSU *> psus;
  std::vector<Storage *> storages;
};

// === БАЗОВЫЙ КЛАСС КОНСУЛЬТАНТА ===
class Consultant
{
protected:
  std::string name;
  std::string levelName; // Уровень: Стажер, Эксперт и т.д.

public:
  Consultant(std::string n, std::string level);
  virtual ~Consultant();

  std::string getName() const;
  std::string getLevelName() const;

  // Чисто виртуальная функция сборки ПК (Полиморфизм).
  // purpose: 1 - Игры, 2 - Работа, 3 - Офис
  virtual std::vector<Component *> buildPC(double budget, int purpose, const Catalog &catalog) = 0;
};

// === НАСЛЕДНИК 1: СТАЖЕР ===
class InternConsultant : public Consultant
{
public:
  InternConsultant(std::string n);

  // Переопределяем метод сборки. Стажер собирает наугад.
  std::vector<Component *> buildPC(double budget, int purpose, const Catalog &catalog) override;
};

// === НАСЛЕДНИК 2: ЭКСПЕРТ ===
class ExpertConsultant : public Consultant
{
public:
  ExpertConsultant(std::string n);

  // Переопределяем метод сборки. Эксперт использует весовые коэффициенты.
  std::vector<Component *> buildPC(double budget, int purpose, const Catalog &catalog) override;
};

// === НАСЛЕДНИК 3: ОПЫТНЫЙ ===
class ExperiencedConsultant : public Consultant
{
public:
  ExperiencedConsultant(std::string n);

  // Переопределяем метод сборки. Опытный комбинирует логику и случайность.
  std::vector<Component *> buildPC(double budget, int purpose, const Catalog &catalog) override;
};