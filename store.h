#pragma once
#include "consultants.h"
#include <string>
#include <vector>

class Store
{
private:
  Catalog catalog;
  std::vector<Consultant *> consultants;

  // Методы для загрузки каждого конкретного файла
  void loadCPUs(const std::string &filepath);
  void loadGPUs(const std::string &filepath);
  void loadMotherboards(const std::string &filepath);
  void loadRAMs(const std::string &filepath);
  void loadPSUs(const std::string &filepath);
  void loadStorages(const std::string &filepath);
  void loadConsultants(const std::string &filepath);

public:
  Store();
  ~Store();

  // Метод загрузки всех данных
  void loadAllData();

  // Метод запуска мероприятия
  void startSimulation();
};