#pragma once
#include <string>
#include <vector>
#include "components.h"

struct Catalog
{
  std::vector<CPU *> cpus;
  std::vector<GPU *> gpus;
  std::vector<Motherboard *> mobos;
  std::vector<RAM *> rams;
  std::vector<PSU *> psus;
  std::vector<Storage *> storages;
};

class Consultant
{
protected:
  std::string name;
  std::string levelName;

public:
  Consultant(std::string n, std::string level);
  virtual ~Consultant();

  std::string getName();
  std::string getLevelName();

  virtual std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) = 0;
};

class InternConsultant : public Consultant
{
public:
  InternConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};

class ExpertConsultant : public Consultant
{
public:
  ExpertConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};

class ExperiencedConsultant : public Consultant
{
public:
  ExperiencedConsultant(std::string n);

  std::vector<Component *> buildPC(double budget, int purpose, Catalog &catalog) override;
};