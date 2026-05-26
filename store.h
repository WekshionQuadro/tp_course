#pragma once
#include "consultants.h"
#include <string>

class Store
{
private:
  Catalog catalog;

  void loadCPUs(const std::string &filepath);
  void loadGPUs(const std::string &filepath);
  void loadMotherboards(const std::string &filepath);
  void loadRAMs(const std::string &filepath);
  void loadPSUs(const std::string &filepath);
  void loadStorages(const std::string &filepath);

public:
  Store();
  ~Store();

  void loadAllData();

  void startSimulation();
};