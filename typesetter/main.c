//Для вывода %c CP866 в терминале или setlocale()
//Для работы с Windows нужна CP866 + заменить"–" на "-"

//toupperString() чувствительность к регистру в checkInput
//Проверка на пустую строку playerInput

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

char* vocabularyPath = "..//russian.txt";                   // *Путь к файлу со словарем
int score;                                                  // *Счет игрока
char randomWord[50];                                        // *Случайное слово

void doInput();                                             // *Прототипы функций для рекурсии
void menu();

char clearScreen(){                                         // *Кроссплатформенная очистка экрана
#if defined(_WIN32)
    return system("cls");
#elif defined(__linux__)
    return system("clear");
#elif defined(__APPLE__)
    return system("clear");
#endif
}

void error(int code){                                       //Вывод ошибки в соответствии с переданным (кодом)
    switch (code){
        case 1:
            printf("\x1b[31m[!]Вводимое слово должно отличаться от слова \x1b[4m%s\x1b[0m\x1b[0m\n",randomWord);
            sleep(1);
            doInput();
        case 2: //Неподходящие буквы или их количество
            printf("\x1b[31m[!]Слово не подходит по буквам или их количеству\x1b[0m\n");
            sleep(1);
            doInput();
        case 3: //Раннее использованное слово
            printf("\x1b[31m[!]Вы уже использовали это слово\x1b[0m\n");
            sleep(1);
            doInput();
        case 4: //Слово не существует
            printf("\x1b[31m[!]Такое слово не существует!\x1b[0m\n");
            sleep(1);
            doInput();

    }
}

struct node{
    char* word;
    struct node* next;
};
typedef struct node list;                                   // *Синоним для структуры
list* head = NULL;

list* addScore(list* head, char* word){
    list* tmp = (list*) malloc(sizeof(list));
    tmp->word  = word;
    tmp->next  = head;
    return tmp;
}

void printScore(list* head){
    if(head){                               //Если передан ненулевой указатель
        while(head->next){                  //Пока элемент не последний
            printf("%s | ", head->word);    //Печатаем его word
            head=head->next;                //И переходим к следующему
        }
        printf("%s\n", head->word);         //Печатаем последний элемент
        score++;
    }
    else
        printf("empty list\n");
    printf("Ваш счет: %d\n",score);
    printf("_________________\n");
}

int alreadyUsed(list* head, char* word) {                   // *Проверка ввода ранее использованного слова
    if(head){
        while (head->next && strcmp(head->word,word)!=0){
            head=head->next;
        }
        if(strcmp(head->word,word)==0){
            return 1;
        } else return 0;
    }
    return 0;
}

int repetitionCount(char string[50],char substring){        // *Количество повторов в (строке,символа)
    int count = 0;
    for(int i = 0; string[i]!='\0'; i++){
        if(string[i]==substring){
            count++;
        }
    }
    return count;
}

void checkInput(char* playerInput){
    if(strcmp(playerInput,"/menu")==0){                     // *Проверка ввода для выхода в меню
        menu();
    }
    if (strcmp(playerInput, randomWord)!=0){                // *Проверка, что слова не одинаковые
        // Сравнение букв в playerInput с буквами randomWord:
        for(int i=0; playerInput[i]!='\0';i++){
            if(repetitionCount(randomWord,playerInput[i])<repetitionCount(playerInput,playerInput[i])){
                error(2);                           // *Ошибка: В слове неподходящие буквы или они повторяются чаще допустимого
            }
        }
        // *Проверка существования слова:
        FILE *vocabulary;
        vocabulary = fopen(vocabularyPath,"r");
        char vocabularyStr[50];                         // *Строка из словаря
        while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
            fscanf(vocabulary, "%s",vocabularyStr);
            if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                fclose(vocabulary);
                if(alreadyUsed(head,playerInput)==0){   // *Проверка, что слово не вводилось раньше
                    printf("[+1] Cлово \x1b[4m%s\x1b[0m \x1b[32mподходит!\x1b[0m\n",playerInput);
                    sleep(1);
                    clearScreen();
                    head = addScore(head, playerInput); // *Добавление слова в список и score++
                    printScore(head);
                    doInput();
                } else{
                    error(3);                   // *Ошибка: Повторный ввод слова
                }
            }
        }
        error(4);                               // *Ошибка: Несуществующее слово
    }
    else{
        error(1);                                   // *Ошибка: Одинаковые слова
    }
}

void doInput(){
    char playerInput[50];
    printf("\x1b[4m%s\x1b[0m\n\n",randomWord);              // *Вывод рандомного слова
    printf(":");
    scanf("%s",playerInput);
    checkInput(playerInput);                                // *Запуск проверки слова
}

void getRandomWord(){
    FILE *vocabulary;                                       // *Подключение файла
    vocabulary = fopen(vocabularyPath,"r");
    fseek(vocabulary, rand() % 8366227, SEEK_SET);          // *Смещение указателя на случайное количество байт !> 8366227 – число байт
    if (NULL != fgets(randomWord, 100, vocabulary)){
        fscanf(vocabulary, "%s",randomWord);                // *Чтение строки
        if (strlen(randomWord)<30){
            getRandomWord();
        }
    }
    fclose(vocabulary);                                     // *Закрытие потока
}

void startGame(){
    clearScreen();                                          // *Очистить консоль
    getRandomWord();                                        // *Сгенерировать случайное слово
    doInput();
}

void menu(){
    char input[6];
    clearScreen();
    printf("Для продолжения введите соответствующую команду\n");
    printf("/start – начать игру\n");
    printf("/menu – вернуться в меню\n");
    printf("/rules – правила игры\n");
    printf("/exit – выход из игры\n");
    printf(":");
    scanf("%s",input);
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
        printf(":");
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
    srand(time(NULL));
    menu();

}
