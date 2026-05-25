#include <iostream>
#include <ctime>
#include <cstdlib>
#include "store.h"

using namespace std;

int main()
{
  // Настраиваем кириллицу для консоли (если ты на Windows)
  setlocale(LC_ALL, "Russian");

  // Инициализация генератора случайных чисел от текущего времени
  srand(time(0));

  // Создаем объект нашего магазина
  Store myStore;

  // 1. Загружаем данные из текстовых файлов
  myStore.loadAllData();

  // 2. Запускаем "мероприятие"
  myStore.startSimulation();

  return 0;
}