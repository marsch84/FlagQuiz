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

#include "highscores.h"

#define HIGHSCORES_MAX 60

Highscores::Highscores()
{
    Settings = new QSettings("Martin Scherer", "FlagQuiz");
}

Highscores::~Highscores()
{
    delete Settings;
}

QString Highscores::getSignsName(int number)
{
    return Settings->value("SignsName"+QString().setNum(number+1), "Anonymous").toString();
}

int Highscores::getSignsPoint(int number)
{
    return Settings->value("SignsPoint"+QString().setNum(number+1), HIGHSCORES_MAX - number * 10).toInt();
}

QString Highscores::getMeaningsName(int number)
{
    return Settings->value("MeaningsName"+QString().setNum(number+1), "Anonymous").toString();
}

int Highscores::getMeaningsPoint(int number)
{
    return Settings->value("MeaningsPoint"+QString().setNum(number+1), HIGHSCORES_MAX - number * 10).toInt();
}

void Highscores::setSigns(int number, QString name, int points)
{
    Settings->setValue("SignsName"+QString().setNum(number+1), name);
    Settings->setValue("SignsPoint"+QString().setNum(number+1), points);
}

void Highscores::setMeanings(int number, QString name, int points)
{
    Settings->setValue("MeaningsName"+QString().setNum(number+1), name);
    Settings->setValue("MeaningsPoint"+QString().setNum(number+1), points);
}
