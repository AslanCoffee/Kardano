#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>

#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

QString** kardanocreate(int size, int** key, QString word)
{

    QString** kardano = new QString* [size * 2];
    for (int i = 0; i < size * 2; i++)
        kardano[i] = new QString[size * 2];

    int count = 0;

    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[i][j] == 1 && count < word.size())
            {
                kardano[i][j] = word[count];
                count++;
            }
            else if (key[i][j] == 1 && count >= word.size())
            {
                char c = 97 + rand() % (122 - 97 - 1);
                kardano[i][j] = c;
            }
        }
    }

    // поворот решетки на 90 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[size * 2 - j - 1][i] == 1 && count < word.size())
            {
                kardano[i][j] = word[count];
                count++;
            }
            else if (key[size * 2 - j - 1][i] == 1 && count >= word.size())
            {
                char c = 97 + rand() % (122 - 97 - 1);
                kardano[i][j] = c;
            }
        }
    }
    // поворот решетки на 180 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[size * 2 - i - 1][size * 2 - j - 1] == 1 && count < word.size())
            {
                kardano[i][j] = word[count];
                count++;
            }
            else if (key[size * 2 - i - 1][size * 2 - j - 1] == 1 && count >= word.size())
            {
                char c = 97 + rand() % (122 - 97 - 1);
                kardano[i][j] = c;
            }
        }
    }

    // поворот решетки на 270 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[j][size * 2 - i - 1] == 1 && count < word.size())
            {
                kardano[i][j] = word[count];
                count++;
            }
            else if (key[j][size * 2 - i - 1] == 1 && count >= word.size())
            {
                char c = 97 + rand() % (122 - 97 - 1);
                kardano[i][j] = c;
            }
        }
    }
    return kardano;
}

QChar** keycreate(int size, int** reshetka)
{
    //key create
    int** key = new int* [size * 2];
    for (int i = 0; i < size * 2; i++)
        key[i] = new int[size * 2];
    //key = 0
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
            key[i][j] = 0;
    }
    int* number = new int[size * size + 1];
    //number = 0
    for (int i = 0; i <= size * size; i++)
    {
        number[i] = 0;
    }
    //key zapolnenye
    for (int i = 1; i <= size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        for (int j = x; j < size * 2; j++)
        {
            for (int k = y; k < size * 2; k++)
            {
                if (reshetka[j][k] == i)
                {
                    key[j][k] = 1;
                    number[i] = 1;
                    break;
                }
            }
            if (number[i] == 1) break;
        }
    }
    QChar** Ckey = new QChar* [size * 2];
    for (int i = 0; i < size * 2; i++)
        Ckey[i] = new QChar[size * 2];
    //key cout
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if(key[i][j]==1)Ckey[i][j]='1';
            else Ckey[i][j]='0';
        }
    }

    //kardano create
    return Ckey;
}

int** shifrovka(int size)
{
    int** reshetka = new int* [size * 2];
    for (int i = 0; i < size * 2; i++)
        reshetka[i] = new int[size * 2];
    //reshetka = 0
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
            reshetka[i][j] = 0;
    }
    //вверх влево
    int count = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            reshetka[i][j] = count;
            count++;
        }
    }
    count = size * (size - 1) + 1;
    //вверх вправо
    for (int i = 0; i < size; i++)
    {
        for (int j = size; j < size * 2; j++)
        {
            reshetka[i][j] = count;
            count = count - size;
        }
        count = size * (size - 1) + i + 2;
    }
    count = size * size;
    //вниз вправо
    for (int i = size; i < size * 2; i++)
    {
        for (int j = size; j < size * 2; j++)
        {
            reshetka[i][j] = count;
            count--;
        }
        count = size * (size - (i - size + 1));
    }
    //вниз влево
    count = size;
    for (int i = size; i < size * 2; i++)
    {
        for (int j = 0; j < size; j++)
        {
            reshetka[i][j] = count;
            count += size;
        }
        count = size - (i - size + 1);
    }
    return reshetka;
}

QString answerout(int** key, int size, QString Text)
{
    QChar** word = new QChar* [size * 2];
    for (int i = 0; i < size * 2; i++)
        word[i] = new QChar[size * 2];

    QString str;

    int x = 0, y = 0;
    for (int i = 0; i < size * size * 2 * 2; i++)
    {
        word[x][y] = Text[i];
        y++;
        if (y == size * 2)
        {
            x++;
            y = 0;
        }
    }
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[i][j] == 1) str = str + word[i][j];
        }
    }

    // поворот решетки на 90 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[size * 2 - j - 1][i] == 1) str = str + word[i][j];
        }
    }
    // поворот решетки на 180 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[size * 2 - i - 1][size * 2 - j - 1] == 1) str = str + word[i][j];
        }
    }

    // поворот решетки на 270 градусов по часовой стрелке
    for (int i = 0; i < size * 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            if (key[j][size * 2 - i - 1] == 1) str = str + word[i][j];
        }
    }
    return str;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
