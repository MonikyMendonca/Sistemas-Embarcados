# Implementação do Kernel FreeRTOS baseado em POSIX

A aplicação implementa a manipulação de tarefas baseadas no Kernel do FreeRTOS baseado em POSIX para a introdução dos alunos da disciplina de Sistemas Embarcados da Universidade Federal do Ceará (UFC).

### 1. Incluir o path do FreeRTOS na distro Linux (Ubuntu 22.04 LTS)

`$ export FREERTOS_PATH=~/Documents/FreeRTOSv202212.01`

`$ echo $FREERTOS_PATH`

## 2. Compilar com CLANG o Makefile

`$ make CC=clang`

## 3. Executar o build

`$ ./build/tasks-posix-c`

## Done!
