#pragma once
#include <string>

class Component
{
protected:
  std::string name;
  double price;

public:
  Component(std::string n, double p);
  virtual ~Component();

  std::string getName();
  double getPrice();

  virtual void printInfo();
};

class CPU : public Component
{
private:
  std::string socket;
  int cores;
  int threads;
  double frequency;
  int tdp;

public:
  CPU(std::string n, double p, std::string s, int c, int th, double f, int t);
  void printInfo() override;

  std::string getSocket();
  int getTdp();
};

class GPU : public Component
{
private:
  int powerScore;
  int tdp;

public:
  GPU(std::string n, double p, int pScore, int t);
  void printInfo() override;

  int getPowerScore();
  int getTdp();
};

class Motherboard : public Component
{
private:
  std::string socket;
  double maxRamFreq;

public:
  Motherboard(std::string n, double p, std::string s, double maxFreq);
  void printInfo() override;

  std::string getSocket();
  double getMaxRamFreq();
};

class RAM : public Component
{
private:
  double frequency;

public:
  RAM(std::string n, double p, double freq);
  void printInfo() override;

  double getFrequency();
};

class PSU : public Component
{
private:
  int wattage;

public:
  PSU(std::string n, double p, int w);
  void printInfo() override;

  int getWattage();
};

class Storage : public Component
{
private:
  int capacity;
  std::string type;

public:
  Storage(std::string n, double p, int cap, std::string t);
  void printInfo() override;
};