#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* getRandomWord(){
    char str[50];                           // Слово из словаря [длина слова]
    FILE *vocabulary;                       // Подключение файла
    //setlocale(LC_ALL, "Russian");
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);    // Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",&str);      // Чтение строки
        //printf("%s\n",str);                 // Печать слова

    }
    fclose(vocabulary);                     // Закрытие потока
    return &str;
}

void startGame(){
    printf(">%s<\n",getRandomWord());
    printf("Введите слово\n");
    char str[50];
    scanf("%s",&str);
    printf("Вы ввели слово:\n%s\n",str);
    
}

int main() {
    srand(time(NULL));
    startGame();
}
