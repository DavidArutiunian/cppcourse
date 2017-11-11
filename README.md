# cppcourse
Курсы по С++

## Форматирование

`format.sh` - форматирует все файлы с раширением `.cpp` и `.hpp` согласно конфигурации `.clang-format`

`register-hook.sh` - создаёт файл `pre-commit` в `./.git/hooks/`, содержащий код `format.sh`

## Требования

Библиотека `SFML`  должна находиться в папке `lib/sfml`

[Clang](https://clang.llvm.org/) - содержит `clang-format`

[CMake](https://cmake.org/) - система автоматизации сборки

[MinGW](https://nuwen.net/) - компилятор