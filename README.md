# cpp-lab3-menu
### Меню:
 - [MyMenu.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/MyMenu.h)
 - - [MyWindow.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/MyWindow.h)([.cpp](https://github.com/MekhailS/cpp-labs/tree/lab3-menu))
 -  - - [MyButton.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/MyButton.h)

Связь между Menu, Window, Button реализована через smart pointer'ы

### Скрипт:
- [Script.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/Script.h)([.cpp](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/Script.cpp))
- - ScriptLine

ScriptLine описывает строчку скрипта (сущность, операция, ошибка)

### User (пользователь)
[User.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/User.h)
Позволяет "безопасно" работать с меню



### Прочее:
[input.menu](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/input.menu) — файл с описанием меню

[ParserMyMenu.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/ParserMyMenu.h)([.cpp](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/ParserMyMenu.cpp)) — функции парсинга текста в сущности скрипта

[interact.h](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/interact.h)([.cpp](https://github.com/MekhailS/cpp-labs/blob/lab3-menu/interact.cpp)) —  главный модуль с функциями Init() и Interact()
