#pragma once
#include <string>
#include <vector>
#include "components.h"

// Структура для хранения загруженных товаров магазина
struct Catalog
{
  std::vector<CPU *> cpus;          // Массив процессоров
  std::vector<GPU *> gpus;          // Массив видеокарт
  std::vector<Motherboard *> mobos; // Массив материнских плат
  std::vector<RAM *> rams;          // Массив оперативной памяти
  std::vector<PSU *> psus;          // Массив блоков питания
  std::vector<Storage *> storages;  // Массив накопителей
  std::vector<Case *> cases;        // Массив корпусов
};

// Базовый абстрактный класс для всех консультантов
class Consultant
{
protected:
  std::string name;      // Имя
  std::string levelName; // Название уровня квалификации

  // Функции проверок на совместимость комплектующих
  bool checkMobo(CPU *cpu, Motherboard *mobo);
  bool checkRam(Motherboard *mobo, RAM *ram);
  bool checkPsu(int requiredTdp, PSU *psu);
  bool checkCase(Motherboard *mobo, Case *pcCase);

public:
  Consultant(std::string n, std::string level);
  virtual ~Consultant();

  std::string getName();
  std::string getLevelName();

  // Главная виртуальная функция для подбора ПК (работает по-разному у каждого наследника)
  virtual std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) = 0;
};

// Класс консультанта-стажера
class InternConsultant : public Consultant
{
public:
  InternConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};

// Класс опытного констультанта
class ExperiencedConsultant : public Consultant
{
public:
  ExperiencedConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};

// Класс консультанта-эксперта
class ExpertConsultant : public Consultant
{
public:
  ExpertConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};