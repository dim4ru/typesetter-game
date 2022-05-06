//Для вывода %c CP866 в терминале или setlocale()
//Для работы с Windows нужна CP866 + заменить"–" на "-"
//Чувствительность к регистру в checkInput
//Фильтрация слов для getRandomWord
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>

clearScreen(){                                          // *Кроссплатформенная очистка экрана
    #if defined(_WIN32)
        return system("cls");
    #elif defined(__linux__)
        return system("clear");
    #elif defined(__APPLE__)
        return system("clear");
    #endif
}

void getRandomWord(char str[50]){
    FILE *vocabulary;                                   // *Подключение файла
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
    fseek(vocabulary, rand() % 8366227, SEEK_SET);      // *Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(str, 100, vocabulary)){
        fscanf(vocabulary, "%s",str);                   // *Чтение строки
    }
    fclose(vocabulary);                                 // *Закрытие потока
}

void checkInput(char* playerInput, char* randomWord){
    int isCorrect = 1;
    if (strcmp(playerInput, randomWord)!=0){            // *Проверка, что слова не одинаковые
        // Сравнение букв в playerInput с буквами randomWord:
        for(int i=0; playerInput[i]; i++){
            //printf("[%d]=%c\n",i, playerInput[i]);        // (Посимвольный вывод playerInput)
            if(!strchr(randomWord,playerInput[i])){   // [!] Чувствителен к регистру, капсить все слова | Поиск (в строке, символа)
                printf("Введенное вами слово \x1b[4m%s\x1b[0m \x1b[31mне подходит\x1b[0m по буквам\n",playerInput); // Изменить формат вывода
                isCorrect = 0;
                break;
            }
        }
    } else{
        isCorrect = 0;
        printf("Вводимое слово \x1b[31mдолжно отличаться\x1b[0m от слова \x1b[4m%s\x1b[0m\n",randomWord);
    }
    if(isCorrect!=0){
        // Проверка существования слова:
        printf("Слово \x1b[4m%s\x1b[0m\x1b[32m подходит\x1b[0m по буквам. Ищем его в словаре...\n",playerInput);
        FILE *vocabulary;
        vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r"); //[!]Сделать относительный путь
        char vocabularyStr[50];                         // *Строка из словаря
        int isFound = 0;
        while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
            fscanf(vocabulary, "%s",vocabularyStr);
            if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                isFound=1;
                break;
                fclose(vocabulary);
            }
        }
        if (isFound == 1){
            printf("[+] \x1b[4m%s\x1b[0m – \x1b[32m подходит!\x1b[0m\n",playerInput);
            // Добавить слово в созданный в startGame двумерный массив отгаданных слов
        } else{
            printf("Слово \x1b[4m%s\x1b[0m \x1b[31mне найдено\x1b[0m в словаре\n",playerInput);
        }
    }
}

char startGame(){
    char randomWord[50];
    getRandomWord(randomWord);
    printf("Случанйое слово: \x1b[4m%s\x1b[0m\n",randomWord);   // *Вывод рандомного слова
    printf("Введите слово: ");
    char playerInput[50];                               // *Строка для ввода слова игроком
    scanf("%s",playerInput);                            // [!] Проверка на пустую строку
    checkInput(playerInput,randomWord);                 // ??????
}

void menu(){
    char input[6];
    clearScreen();
    printf("Для продолжения введите соответствующую команду\n");
    printf("/start – начать игру\n");
    printf("/rules – правила игры\n");
    printf("/exit – выход из игры\n");
    scanf("%s",input);
    if (strcmp("/start",input)==0){
        clearScreen();
        startGame();
    }
    else if(strcmp("/rules",input)==0){
        clearScreen();
        printf("Правила игры \"Наборщик\":\n");
        printf("Игроку дается случайно выбранное компьютером слово, задача игрока составить из букв этого слова как можно больше других слов.\n");
        printf("Допускается располагать буквы в любом порядке, однако повторяться они могут столько раз, сколько содержатся в исходном слове.\n");
        printf("\n/menu – вернуться в меню\n");
        scanf("%s",input);
        if (strcmp("/menu",input)==0){
            menu();
        }
    }
    else if(strcmp("/exit",input)==0){
        clearScreen();
        _Exit(1337);
        }
    else{
        printf("\x1b[31mНеизвестная команда!\x1b[0m\n");
        sleep(2);
        menu();
    }
};

int main() {
    //setlocale(LC_ALL, "utf-8");
    //char vocabularyPath[60] = {"/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt"};  // [!] Путь к файлу в переменную
    srand(time(NULL));
    menu();
}
