//без: проверки повтора слов, проверки количество повторяющихся букв в слове, вывода списка введенных слов...
//Для вывода %c CP866 в терминале или setlocale()
//Для работы с Windows нужна CP866 + заменить"–" на "-"

//Отдельная функция error, по коду ошибки выводить ее текст и перезапрашивать слово
//Чтобы список слов не сбрасывался
//Вызов printScore в doInput, чтобы он исчезал с очисткой экрана
//Убрать sleep() для первого запуска
//Проверка повтора слов в списке
//Не запускать sleep при первом вызове doInput
//Сделать выход во время игры
//toupperString() чувствительность к регистру в checkInput
//Относительный путь к словарю
//Фильтрация слов для getRandomWord
//Проверка на пустую строку playerInput

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

int score;                                                  // *Счет игрока
char randomWord[50];                                        // *Случайное слово

char clearScreen(){                                     // *Кроссплатформенная очистка экрана
#if defined(_WIN32)
    return system("cls");
#elif defined(__linux__)
    return system("clear");
#elif defined(__APPLE__)
    return system("clear");
#endif
}

struct node{
    char* word;
    struct node* next;
};
typedef struct node list;
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
    printf("Введено слов: %d\n",score);
    printf("_________________\n");
}

int alreadyUsed(list* head, char* word) {                    // *Проверка ввода ранее использованного слова
    if(head){                               //Если передан ненулевой указатель
        while(head->next){                  //Пока элемент не последний
            if(strcmp(head->word,word)!=0){
                head=head->next;            //И переходим к следующему
            }
            else{
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}
/*
void repetitionCount(){
    #include <stdio.h>
#include <string.h>

int meetings_count(const char * str, const char * substr) {
    return ( str = strstr(str, substr) ) ? 1 + meetings_count(str + 1, substr) : 0;
}

#define STR_SIZE 256
#define GET_STRING(str) ( scanf("%255[^\n]%*c", (str)) == 1 )

int main(void) {
    char string[STR_SIZE], substring[STR_SIZE];

    while ( printf("String: ") && GET_STRING(string) && printf("Substring: ") && GET_STRING(substring) )
        printf("%d meetings.\n", meetings_count(string, substring));

    return 0;
}
}*/

void doInput();                                             // *Прототип функции для рекурсии

void checkInput(char* playerInput){
    int isCorrect = 1;
    if (strcmp(playerInput, randomWord)!=0){                // *Проверка, что слова не одинаковые
        // Сравнение букв в playerInput с буквами randomWord:
        for(int i=0; playerInput[i]; i++){
            if(!strchr(randomWord,playerInput[i])){   // *Поиск (в строке, символа)
                printf("Слово \x1b[4m%s\x1b[0m \x1b[31mне подходит\x1b[0m по буквам\n",playerInput);
                sleep(1);
                clearScreen();
                doInput();
                isCorrect = 0;
                break;
            }
        }
        if(isCorrect!=0){
            // *Проверка существования слова:
            FILE *vocabulary;
            vocabulary = fopen("/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt","r");
            char vocabularyStr[50];                         // *Строка из словаря
            while (fgets(vocabularyStr,50,vocabulary)) {    // *Запись в vocabularyStr строки из vocabulary(файла)
                fscanf(vocabulary, "%s",vocabularyStr);
                if(strcmp(playerInput, vocabularyStr)==0){  // *Сравнение слов, если идентичны, то возвращается 0
                    fclose(vocabulary);
                    //printf("\x1b[35maU returned %d\x1b[0m\n",alreadyUsed(head,playerInput));
                    if(alreadyUsed(head,playerInput)==0){
                        printf("[+1] Cлово \x1b[4m%s\x1b[0m \x1b[32mподходит!\x1b[0m\n",playerInput);
                        sleep(1);
                        clearScreen();
                        head = addScore(head, playerInput);
                        printScore(head);
                        doInput();
                    } else{
                        printf("Вы \x1b[31mуже использовали\x1b[0m это слово\n");
                        sleep(1);
                        clearScreen();
                        doInput();
                    }
                }
            }
            printf("Слово \x1b[4m%s\x1b[0m \x1b[31mне существует!\x1b[0m\n",playerInput);
            sleep(1);
            clearScreen();
            doInput();
        }
    }
    else{
        printf("Вводимое слово \x1b[31mдолжно отличаться\x1b[0m от слова \x1b[4m%s\x1b[0m\n",randomWord);
        sleep(1);
        clearScreen();
        doInput();
    }

}

void doInput(){
    //sleep(4);
    //printScore();
    char playerInput[50];
    //printf("[Ваш счет: %d]\n",score);
    printf("Случанйое слово: \x1b[4m%s\x1b[0m\n",randomWord);// *Вывод рандомного слова
    printf("Введите слово: ");
    scanf("%s",playerInput);
    checkInput(playerInput);                                           // Запуск проверки слова
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
    //char vocabularyPath[60] = {"/Users/dmitry/Desktop/ОмГУПС/typesetter/russian.txt"};  // [!] Путь к файлу в переменную
    srand(time(NULL));
    //menu();
    //Для быстрого старта
    startGame();
}
