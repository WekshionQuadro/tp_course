#pragma once
#include "consultants.h"
#include <string>

class Store
{
private:
  Catalog catalog; // Наша витрина с массивами деталей

  // Скрытые методы для загрузки каждого конкретного файла
  void loadCPUs(const std::string &filepath);
  void loadGPUs(const std::string &filepath);
  void loadMotherboards(const std::string &filepath);
  void loadRAMs(const std::string &filepath);
  void loadPSUs(const std::string &filepath);
  void loadStorages(const std::string &filepath);

public:
  Store();
  ~Store();

  // Главный метод загрузки всех данных
  void loadAllData();

  // Метод запуска мероприятия (ввод пользователя, выбор консультанта, итог)
  void startSimulation();
};