//Для вывода %c CP866 в терминале или setlocale()
//только последнее слово в словаре
//getRandomWord в переменную в checkInput
//чувствительность к регистру
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
        fscanf(vocabulary, "%s",str);                   // *Чтение строки
        //printf("%s\n",str);

    }
    fclose(vocabulary);                                 // *Закрытие потока
    return str;
}

char* saveRandomWord(){
    char randomWord[50];
    getRandomWord();
    printf("%c",getRandomWord()[2]);
    for(int i=0; i<=50; i++){
        randomWord[i]=getRandomWord()[i];
        printf("%s",randomWord);
    }
}

char checkInput(char* playerInput, char* randomWord){
    //printf("Проверка слова%s\n",playerInput);         // ?? Segmentation fault | [!] Без %s работает, надо впихнуть \0
    // Сравнение букв в playerInput с буквами randomWord
    int isCorrect = 1;
    for(int i=0; playerInput[i]; i++){
        //printf("[%d]=%c\n",i, playerInput[i]);        // (Посимвольный вывод playerInput) // ??
        if(!strchr(/*getRandomWord()*/randomWord,playerInput[i])){  // [!] Чувствителен к регистру, капсить все слова | Поиск (в строке, символа)
            printf("В слове %s не содержится буква %c\n",randomWord,playerInput[i]); // Изменить формат вывода
            isCorrect = 0;
            break;
        }
    }
    if(isCorrect==0){
        printf("[-] %s не подходит\n",playerInput);
    }
    else{
        //Проверка существования слова
        printf("Ищем слово в словаре...\n");
        FILE *vocabulary;
        vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
        char vocabularyStr[50];                         // *Строка из словаря
        int isFound = 0;
        while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
            //printf("%s",vocabularyStr);               // ?????? Считывает строки из файла вместе с крансой строкой после слова => при сравнеии слова получаются разные => проверка всегда false
            if(strcmp(playerInput, vocabularyStr)==0){   // *Сравнение слов, если идентичны, то возвращается 0
                isFound++;
                break;
            }
        }
        if (isFound==0){
            printf("Слово %s не найдено в словаре\n",playerInput);
            printf("isFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\n",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        } else{
            printf("[+] %s – подходит!\n",playerInput);
            printf("isFound=[%d], scrcmp=[%d], последнее обработанное слово=[%s], input=[%s]\n",isFound, strcmp(vocabularyStr,playerInput),vocabularyStr,playerInput);
        }
        fclose(vocabulary);
    }
}

char startGame(){
    char randomWord[50] = "привет"/*{getRandomWord()}*/; // ?? Нужен вывод функции в переменную strchr, чтобы не вызывать каждый раз getRandomWord
    //randomWord = getRandomWord()
    printf("Случанйое слово: %s\n",getRandomWord());  // *Вывод рандомного слова
    printf("Введите слово: ");
    char playerInput[50];                               // *Строка для ввода слова игроком
    scanf("%s",playerInput);                            // [!] Проверка на пустую строку
    printf("Вы ввели слово: %s\n",playerInput);
    checkInput(playerInput,randomWord);                 // ??????
}

int main() {
    //setlocale(LC_ALL, "utf-8");
    //char vocabularyPath[60] = {"/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt"};  // [!] Путь к файлу в переменную
    srand(time(NULL));
    startGame();
}
