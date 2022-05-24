/*Создайте приложение «Каталог текстов песен». 
Приложение должно иметь следующие возможности:
■ Добавление текста песни:
• Текст песни:
ӽ может быть введен с клавиатуры;
ӽ загружен из файла.
• Для каждой песни нужно указывать название песни, автора текста и 
год создания песни (если он известен).
■ Удаление текста песни.
■ Изменение текста песни.
■ Отображение текста песни на экран.
■ Сохранение текста песни в файл.
■ Поиск и отображение всех песен одного автора.
■ Поиск и отображение всех песен, содержащих слово, указанное пользователем*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <locale>
#include <windows.h>

using namespace std;

struct infomusic {
    char mname[60];
    char avtor[60];
    unsigned short int year;
    char text[512];
};
void InputMusic(infomusic* m, int size)
{
    char buf[255];
    for (int i = 0; i < size; ++i)
    {
        cout << "Ввод наименования песни: "; cin >> buf;
        strcpy(m[i].mname, buf);
        cout << "Ввод автора: "; cin >> buf;
        strcpy(m[i].avtor, buf);
        cout << "Ввод текста: "; cin >> buf;
        strcpy(m[i].text, buf);
        cout << "Ввод года: "; cin >> m[i].year;
        cout << "-------------------\n";
    }
    system("CLS");
}

void SerchAvtorMusic(infomusic* m, int size, char* initAvtor)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(m[i].avtor, initAvtor) == 0)
        {
            cout << "\n--------------------";
            cout << "\nНазвание: " << m[i].mname;
            cout << "\nАвтор: " << m[i].avtor;
            cout << "\nГод: " << m[i].year;
            cout << "\nТекст: " << m[i].text;
            cout << "\n--------------------";
        }
    }
}
int save(infomusic* m, char* list)
{
    FILE* fp;
    char* c;
    int size = sizeof(struct infomusic);

    if ((fp = fopen(list, "ab")) == NULL)
    {
        perror("Произошла ошибка при открытии файла");
        return 1;
    }
    c = (char*)m;
    for (int i = 0; i < size; i++)
    {
        putc(*c++, fp);
    }
    fclose(fp);
    return 0;
}

int load(infomusic* m, char* list)
{
    FILE* fp;
    char* c;
    int i;
    int size = sizeof(struct infomusic);
    struct infomusic* ptr = (struct infomusic*)malloc(size);

    if ((fp = fopen(list, "rb")) == NULL)
    {
        perror("Произошла ошибка при открытии файла");
        return 1;
    }
    c = (char*)ptr;
    while ((i = getc(fp)) != EOF)
    {
        *c = i;
        c++;
    }

    fclose(fp);
    cout << "Название: " << ptr->mname << "\nгГод: " << ptr->year << "\nАвтор: " << ptr->avtor << "\nТекст: \n" << ptr->text;
    free(ptr);
    return 0;
}
int firstload(infomusic* m, char* list)
{
    FILE* fp;
    char* c;
    int i;
    int size = sizeof(struct infomusic);
    struct infomusic* ptr = (struct infomusic*)malloc(size);

    if ((fp = fopen(list, "rb")) == NULL)
    {
        perror("Произошла ошибка при открытии файла");
        return 1;
    }
    c = (char*)ptr;
    while ((i = getc(fp)) != EOF)
    {
        *c = i;
        c++;
    }
    cout << "Заголовок: " << ptr->mname;
    free(ptr);
    fclose(fp);
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    char list[] = "List.dat";
    int size = 1;
    infomusic* music = new infomusic[size];
    char yn;
    do
    {
        cout << "Каталог музыки по команде #4\n\n";
        cout << "Вывод списка музыки [Y-yes/N-no]"; cin >> yn;
        if (tolower(yn) == 'y') {
            firstload(music, list);
            int a;
            cout << "\nИнформационная дорожка[1] ";
            cout << " Добавить трек[2] ";
            cout << " Удалить трек[3]";
            cout << " Сменить трек[4] ";
            cout << "Найти авторскую музыку[5] "; cin >> a;
            switch (a) {
            case 1:
            {
                a = 0;
                char inname[60];
                cout << "Введите название музыки: "; gets_s(inname, 60); break;
            }
            case 2:
            {
                a = 0;
                InputMusic(music, size); save(music, list); load(music, list); break; }
            case 3:
            {
                a = 0;
                load(music, list); cout << "Введите номер песни: "; cin >> a; }
            case 4:
            {
                a = 0;
                load(music, list); cout << "Введите номер песни: "; cin >> a; }
            case 5: {
                a = 0;
                cout << "Ввод автора: ";
                char initAvtor[60];
                gets_s(initAvtor, 60);
                SerchAvtorMusic(music, size, initAvtor);
            }
            default: cout << "Введите правильный номер";
            }
        }
    } while (tolower(yn) != 'y');
}