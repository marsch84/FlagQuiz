/*
    Copyright 2019 Martin Scherer

    This file is part of FlagQuiz.

    FlagQuiz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FlagQuiz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FlagQuiz.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QSettings>
#include <QStringList>

class Highscores
{
public:
    Highscores();
    ~Highscores();
    QString getSignsName(int number);
    int getSignsPoint(int number);
    QString getMeaningsName(int number);
    int getMeaningsPoint(int number);
    void setSigns(int number, QString name, int points);
    void setMeanings(int number, QString name, int points);

private:
    QSettings *Settings;
};

#endif // HIGHSCORES_H
