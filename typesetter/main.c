#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* getRandomWord(){
    char str[50];                                       // Слово из словаря [длина слова]
    FILE *vocabulary;                                   // Подключение файла
    //setlocale(LC_ALL, "Russian");
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);      // Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",&str);                  // Чтение строки
        //printf("%s\n",str);

    }
    fclose(vocabulary);                                 // Закрытие потока
    return str;
}

char checkInput(playerInput){
    printf("Проверка слова%s\n",playerInput);           //[!] Без %s работает, надо впихнуть \0
}

char startGame(){
    printf(">%s<\n",getRandomWord());                   // Вывод рандомного слова
    //printf("Введите слово\n");
    char playerInput[50];                                     // Строка для ввода слова игроком
    scanf("%s\0",&playerInput);
    printf("Вы ввели слово:\n%s\n",playerInput);
    checkInput(playerInput);
}

void main() {
    srand(time(NULL));
    startGame();
}
