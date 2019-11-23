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

#ifndef MainWindow_H
#define MainWindow_H

#include <game.h>
#include <start.h>
#include <QDir>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setAppDataPath(QDir);
signals:
    void sigOpenBrowser(QString url);
    void sigStartNativeApp(QString executablePath, QStringList arguments);
public slots:
    void handleOnlineModeChanged(bool);
    void handleOpenBrowser();
    void handleStartNativeApp();
private:
    Ui::MainWindow *ui;
    QDir appDataPath;
    Start *StartWidget;
    Game *GameWidget;
    Data *DataSet;
    Highscores *Settings;
    static const QString DirPrefix;
    void startGame(bool signs);
    bool checkFiles();
private slots:
    void startSigns();
    void startMeanings();
    void stopGame();
};

#endif // MainWindow_H
