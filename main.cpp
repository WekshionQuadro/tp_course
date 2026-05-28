#include <iostream>
#include <ctime>
#include <cstdlib>
#include "store.h"

using namespace std;

int main()
{
  srand(time(0));

  // Зоздание объект магазина
  Store myStore;

  // Загрузка данных из текстовых файлов
  myStore.loadAllData();

  // Запуск мероприятия
  myStore.startSimulation();

  return 0;
}