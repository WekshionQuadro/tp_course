#include <iostream>
#include <ctime>
#include <cstdlib>
#include "store.h"

using namespace std;

int main()
{
  srand(time(0));

  // Создаем объект нашего магазина
  Store myStore;

  // 1. Загружаем данные из текстовых файлов
  myStore.loadAllData();

  // 2. Запускаем "мероприятие"
  myStore.startSimulation();

  return 0;
}