//Для вывода %c CP866 в терминале или setlocale()
//только последнее слово в словаре
//чувствительность к регистру
//Нельзя вводить данное слово
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

void getRandomWord(char str[50]){
    FILE *vocabulary;                                   // *Подключение файла
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);      // *Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",str);                   // *Чтение строки
    }
    fclose(vocabulary);                                 // *Закрытие потока
}

char checkInput(char* playerInput, char* randomWord){
    int isCorrect = 1;
    if (strcmp(playerInput, randomWord)!=0){            // *Проверка, что слова не одинаковые
        // Сравнение букв в playerInput с буквами randomWord:
        for(int i=0; playerInput[i]; i++){
            //printf("[%d]=%c\n",i, playerInput[i]);        // (Посимвольный вывод playerInput)
            if(!strchr(randomWord,playerInput[i])){   // [!] Чувствителен к регистру, капсить все слова | Поиск (в строке, символа)
                printf("Введенное вами слово \x1b[4m%s\x1b[0m \x1b[31mне подходит\x1b[0m по буквам",playerInput); // Изменить формат вывода
                isCorrect = 0;
                break;
            }
        }
    } else{
        isCorrect = 0;
        printf("Вводимое слово \x1b[31mдолжно отличаться\x1b[0m от слова \x1b[4m%s\x1b[0m",randomWord);
    }
    if(isCorrect!=0){
        // Проверка существования слова:
        printf("Слово \x1b[4m%s\x1b[0m\x1b[32m подходит\x1b[0m по буквам. Ищем его в словаре...",playerInput);
        FILE *vocabulary;
        vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
        char vocabularyStr[50];                         // *Строка из словаря
        int isFound = 0;
        while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
            //printf("%s",vocabularyStr);               // ?????? Считывает строки из файла вместе с крансой строкой после слова => при сравнеии слова получаются разные => проверка всегда false
            if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                isFound=1;
                break;
            }
        }
        if (isFound==0){
            printf("\nСлово \x1b[4m%s\x1b[0m \x1b[31mне найдено\x1b[0m в словаре",playerInput);
            printf("\n\x1b[35m isFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\x1b[0m",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        } else{
            printf("\n[+] \x1b[4m%s\x1b[0m – \x1b[32m подходит!\x1b[0m",playerInput);
            printf("\n\x1b[35misFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\x1b[0m",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        }
        fclose(vocabulary);
    }
}

char startGame(){
    char randomWord[50];
    getRandomWord(randomWord);
    printf("Случанйое слово: \x1b[4m%s\x1b[0m",randomWord);         // *Вывод рандомного слова
    printf("\nВведите слово: ");
    char playerInput[50];                               // *Строка для ввода слова игроком
    scanf("%s",playerInput);                            // [!] Проверка на пустую строку
    checkInput(playerInput,randomWord);                 // ??????
}

int main() {
    //setlocale(LC_ALL, "utf-8");
    //char vocabularyPath[60] = {"/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt"};  // [!] Путь к файлу в переменную
    srand(time(NULL));
    startGame();
}
