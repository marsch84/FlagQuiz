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

#include "data.h"

Data::Data(QDomDocument *Document)
{
    QString code;
    QString name;
    QDomElement docElem = Document->documentElement();
    QDomNode n1 = docElem.firstChild();

    while(!n1.isNull()) {
        QDomElement e1 = n1.toElement();
        if(!e1.isNull()) {
            code = e1.attribute("CODE");
            name = e1.attribute("SHORT");
            Filenames.append(+":/flags/"+code+"-lgflag.gif");
            Meanings.append(name);
        }
        n1 = n1.nextSibling();
    }
}

QString Data::getMeaning(int pos)
{
    return Meanings.at(pos);
}

QString Data::getFilename(int pos)
{
    return Filenames.at(pos);
}

int Data::getLength()
{
    return Meanings.size();
}
