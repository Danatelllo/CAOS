|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku04-2: kr04-2 (дореш)

Напишите функцию

    
    
    int separate(int fd_in, int fd_out_even, int fd_out_odd);

Функция считывает числа типа int в бинарном виде из fd_in и отправляет (записывая в том же бинарном
виде) четные в fd_even, а нечетные в fd_odd

В случае успеха функция возвращает `0`. В случае ошибки чтения / записи функция должна вернуть `-1`.

Используйте системные вызовы read и write.

Ваша программа не должна содержать функции main

