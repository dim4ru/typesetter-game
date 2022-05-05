//Для вывода %c CP866 в терминале или setlocale()
//только последнее слово в словаре
//чувствительность к регистру
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
    // Сравнение букв в playerInput с буквами randomWord:
    int isCorrect = 1;
    for(int i=0; playerInput[i]; i++){
        //printf("[%d]=%c\n",i, playerInput[i]);        // (Посимвольный вывод playerInput)
        if(!strchr(randomWord,playerInput[i])){   // [!] Чувствителен к регистру, капсить все слова | Поиск (в строке, символа)
            printf("Введенное вами слово \"%s\" \x1b[31mне подходит\x1b[0m по буквам\n",playerInput); // Изменить формат вывода
            isCorrect = 0;
            break;
        }
    }
    if(isCorrect!=0){
        // Проверка существования слова:
        printf("Слово \"%s\" \x1b[32m подходит\x1b[0m по буквам. Ищем его в словаре...\n",playerInput);
        FILE *vocabulary;
        vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
        char vocabularyStr[50];                         // *Строка из словаря
        int isFound = 0;
        while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
            //printf("%s",vocabularyStr);               // ?????? Считывает строки из файла вместе с крансой строкой после слова => при сравнеии слова получаются разные => проверка всегда false
            if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                isFound++;
                break;
            }
        }
        if (isFound==0){
            printf("Слово \"%s\" \x1b[31mне найдено\x1b[0m в словаре\n",playerInput);
            printf("isFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\n",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        } else{
            printf("[+] \"%s\" – \x1b[32m подходит!\x1b[0m\n",playerInput);
            printf("isFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\n",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        }
        fclose(vocabulary);
    }
}

char startGame(){
    char randomWord[50];
    getRandomWord(randomWord);
    printf("Случанйое слово: %s\n",randomWord);         // *Вывод рандомного слова
    printf("Введите слово: ");
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
