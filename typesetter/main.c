#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

char* getRandomWord(){
    char str[50];                                       // *Слово из словаря [длина слова]
    FILE *vocabulary;                                   // *Подключение файла
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);      // *Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",&str);                  // *Чтение строки
        //printf("%s\n",str);

    }
    fclose(vocabulary);                                 // *Закрытие потока
    return str;
}

/*char checkInput(playerInput){
    printf("Проверка слова%s\n",playerInput);           // ⚠️ Segmentation fault | [!] Без %s работает, надо впихнуть \0
}*/

char startGame(){
    char randomWord[50] = "getRandomWord"/*{getRandomWord()}*/; // ⚠️ Нужен вывод функции в переменную strchr, чтобы не вызывать каждый раз getRandomWord
    printf("Случанйое слово: %s\n",getRandomWord());    // *Вывод рандомного слова
    printf("Введите слово: ");
    char playerInput[50]={0};                           // *Строка для ввода слова игроком
    scanf("%s\0",playerInput);                          // ⚠️ При стирании символы запоминаются
    printf("Вы ввели слово: %s\n",playerInput);
    //checkInput(playerInput);
    //Это перенести в checkInput:
    
    for(int i=0; playerInput[i]; i++){
        //printf("[%d]=%c\n",i, playerInput[i]);        // (Посимвольный вывод playerInput)
        if(strchr(/*getRandomWord()*/randomWord,playerInput[i])){  // ⚠️ Чувствителен к регистру | Поиск (в строке, символа)
            printf("%c – подходит!\n",playerInput[i]);  // Покрасить вывод
        }
        else{
            printf("[!] В слове %s не содержится буква %c\n",randomWord,playerInput[i]);
        }
    }
}

void main() {
    //setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    startGame();
}
