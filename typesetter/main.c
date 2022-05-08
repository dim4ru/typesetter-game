//Для вывода %c CP866 в терминале или setlocale()
//Для работы с Windows нужна CP866 + заменить"–" на "-"

//Чтобы список слов не сбрасывался
//Вызов printScore в doInput, чтобы он исчезал с очисткой экрана
//Убрать sleep() для первого запуска
//Проверка повтора слов в списке
//Не запускать sleep при первом вызове doInput
//Сделать выход во время игры
//toupperString() чувствительность к регистру в checkInput
//Проверка на пустую строку playerInput
//Счет игрока
//Относительный путь к словарю
//Фильтрация слов для getRandomWord
//Вывод ошибок в меню без перемещения

//65: Текст не выводится, если нет \n на конце, который вроде там не нужен.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

int score;                                                  // *Счет игрока
char randomWord[50];                                        // *Случайное слово
char playerInput[50];                                       // *Ввод игрока

void doInput();                                             // *Прототип функции для рекурсии

char clearScreen(){                                     // *Кроссплатформенная очистка экрана
#if defined(_WIN32)
    return system("cls");
#elif defined(__linux__)
    return system("clear");
#elif defined(__APPLE__)
    return system("clear");
#endif
}

void checkInput(){
    int isCorrect = 1;
    if (strcmp(playerInput, randomWord)!=0){                // *Проверка, что слова не одинаковые
        // Сравнение букв в playerInput с буквами randomWord:
        for(int i=0; playerInput[i]; i++){
            if(!strchr(randomWord,playerInput[i])){   // *Поиск (в строке, символа)
                printf("Слово \x1b[4m%s\x1b[0m \x1b[31mне подходит\x1b[0m по буквам\n",playerInput);
                sleep(2);
                doInput();
                isCorrect = 0;
                break;
            }
        }
        if(isCorrect!=0){
            // Проверка существования слова:
            //printf("Слово \x1b[4m%s\x1b[0m\x1b[32m подходит\x1b[0m по буквам.\n",playerInput);
            FILE *vocabulary;
            vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r");
            char vocabularyStr[50];                         // *Строка из словаря
            while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
                fscanf(vocabulary, "%s",vocabularyStr);
                if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                    fclose(vocabulary);
                    printf("[+1] Cлово \x1b[4m%s\x1b[0m \x1b[32mподходит!\x1b[0m\n",playerInput);
                    score++;
                    sleep(2);
                    doInput();
                }
            }
            printf("Слово \x1b[4m%s\x1b[0m \x1b[31mне существует!\x1b[0m\n",playerInput);
            sleep(2);
            doInput();
            //Текст не выводится, если нет \n на конце, который вроде там не нужен.
            //Сделать возврат к вводу
        }
    }
    else{
        isCorrect = 0;
        printf("Вводимое слово \x1b[31mдолжно отличаться\x1b[0m от слова \x1b[4m%s\x1b[0m\n",randomWord);
        sleep(2);
        doInput();
    }

}

void doInput(){
    //sleep(4);
    clearScreen();
    //printScore();
    printf("[Ваш счет: %d]\n",score);
    printf("Случанйое слово: \x1b[4m%s\x1b[0m\n",randomWord);// *Вывод рандомного слова
    printf("Введите слово: ");
    scanf("%s",playerInput);
    checkInput();                 // Запуск проверки слова
}

void getRandomWord(){
    FILE *vocabulary;                                       // *Подключение файла
    vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r");
    fseek(vocabulary, rand() % 8366227, SEEK_SET);          // *Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(randomWord, 100, vocabulary)){
        fscanf(vocabulary, "%s",randomWord);                // *Чтение строки
    }
    fclose(vocabulary);                                     // *Закрытие потока
}

void startGame(){
    getRandomWord();
    doInput();
}

void menu(){
    char input[6];
    clearScreen();
    printf("Для продолжения введите соответствующую команду\n");
    printf("/start – начать игру\n");
    printf("/rules – правила игры\n");
    printf("/exit – выход из игры\n");
    printf(":");
    scanf("%s",input);                                      //Поставить / в начале строки за игрока
    if (strcmp("/menu",input)==0){
        printf("\x1b[31mВы уже находитесьв в меню!\x1b[0m\n");
        sleep(2);
        menu();
    }

    else if (strcmp("/start",input)==0){
        clearScreen();
        startGame();
    }
    else if(strcmp("/rules",input)==0){
        clearScreen();
        printf("Правила игры \"Наборщик\":\n");
        printf("Игроку дается случайно выбранное компьютером слово, задача игрока составить из букв этого слова как можно больше других слов.\n");
        printf("Допускается располагать буквы в любом порядке, однако повторяться они могут столько раз, сколько содержатся в исходном слове.\n");
        printf("При проверке слов учитывается регистр.\n");
        printf("\n/menu – вернуться в меню\n");
        printf(": ");
        scanf("%s",input);
        if (strcmp("/menu",input)==0){
            menu();
        }
        else{
            printf("\x1b[31mНеизвестная команда! Возвращение в меню.\x1b[0m\n");
            sleep(2);
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
    //Для быстрого старта
    //startGame();
}
