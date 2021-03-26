// 9893, Росихин Александр, 
// Дисциплина ОС,
// Лабораторная работа №1

/*
По первой работе следующие задания.
1. Передать в поток число N, а поток вернёт массив размером N с числа от 1 до N
2. Программу, в запущенном потоке которой происходит исключение. Исключение необходимо успешно перехватить вне потока
3. Зачем нужны потоки?
 Ответ: Потоки нужны для превращения последовательно выполняемых функций в параллельно выполняемые и для реализации многозадачности.
*/


#include <iostream>

int except = 0;

void* showArray(void* size)
{
  int n = *((int*)size);
  if (n > 0)
  {
  	for (int i = 1; i <= n; i++)
  	std::cout << i;
  }
  else  std::cout << "Ошибка. Введено недопустимое число.\n";
  
  return 0;
}

void* tryOpenFile(void* flag3)
{
 
 while (*((int*)flag3) == 0)
 { 

 try
    {
    throw(1);
    }
 catch(...)
    {
      except = -1;
      pthread_exit(&except);
    }
 }
 
 return 0;
}


void* showException(void* flag2)
{
 
  while (*((int*)flag2) == 0)
  {
 if (except != 0 )
 {
   std::cout << "\nОбнаружено исключение в потоке\n";
   except = 0;
 }
}
 return 0;
}


int main()
{
 std::cout << "9893, Росихин. Лабораторная работа №1." 
  << " Начало работы программы.\n";
  
 int flag1 = 0;
 int flag2 = 0;
 int flag3 = 0;
 
 pthread_t id1;
 pthread_t id2;
 pthread_t id3;
 
 int n;
 std::cout << "Введите размер массива: ";
 std::cin >> n;
 
 int run1 = pthread_create(&id1, NULL, showArray, &n);
 int run2 = pthread_create(&id2, NULL, tryOpenFile, &flag2); 
 int run3 = pthread_create(&id3, NULL, showException, &flag3);
  
 if (run1 != 0 || run2 != 0 || run3 != 0 ) std::cout << "Ошибка запуска потока №1\n";
 
  
 if (run1 == EAGAIN || run2 == EAGAIN || run3 == EAGAIN)
 	std::cout << "У системы нет ресурсов\n";

 if (run1 == EINVAL || run2 == EINVAL|| run3 == EINVAL)
 	std::cout << "Неправильные атрибуты потока\n";
 
 if (run1 == EPERM || run2 == EPERM || run3 == EPERM)
 	std::cout << "Вызывающий поток не имеет прав\n";
 
 getchar();
 getchar();
 
 flag1 = 1;
 flag2 = 1;
 flag3 = 1;

 int finish1 = pthread_join(id1, NULL); 
 int finish2 = pthread_join(id2, NULL); 
 int finish3 = pthread_join(id3, NULL); 

 
 if (finish1 != 0 || finish2 != 0 || finish3 != 0) 
 	std::cout << "Ошибка завершения потока\n";
 
 if (finish1 == EINVAL || finish2 == EINVAL || finish3 == EINVAL)
 	std::cout << "Thread указывает на не объединяемый поток\n";
 	
 if (finish1 == ESRCH || finish2 == ESRCH || finish3 == ESRCH)
 	std::cout << "Не существует потока с таким идентификатором\n";
 		
 if (finish1 == EDEADLK || finish2 == EDEADLK || finish3 == EDEADLK)
 	std::cout << "Взаимная блокировка или поток указывает сам на себя\n";

 std::cout << "\nЗавершение работы программы.\n";

}
