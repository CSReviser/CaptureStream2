#pragma once
#include <QMap>
#include <QString>

class MainWindow;

struct GuiState
{
    QMap<QString,bool> flags;

    static GuiState fromMainWindow(const MainWindow& w);
};
