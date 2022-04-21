#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

char* getRandomWord(){
    char str[50];                                       // Слово из словаря [длина слова]
    FILE *vocabulary;                                   // Подключение файла
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);      // Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",&str);                  // Чтение строки
        //printf("%s\n",str);

    }
    fclose(vocabulary);                                 // Закрытие потока
    return str;
}

/*char checkInput(playerInput){
    printf("Проверка слова%s\n",playerInput);           //[!] Без %s работает, надо впихнуть \0
}*/

char startGame(){
    char randomWord[50] = {getRandomWord()};        //[!!!] Вывод функции в переменную, strchr
    printf(">%s<\n",randomWord);                   // Вывод рандомного слова
    printf("Введите слово\n");
    char playerInput[50]={0};                              // Строка для ввода слова игроком
    scanf("%s\0",playerInput);                         // [!]При стирании символы запоминаются
    printf("Вы ввели слово: %s\n",playerInput);
    //checkInput(playerInput);
    
    for(int i=0; playerInput[i]; i++){
        printf("[%d]=%c\n",i, playerInput[i]);
        //if(strchr())
    }
}

void main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    startGame();
}
