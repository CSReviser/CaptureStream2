#include "guistate.h"
#include "mainwindow.h"
#include "constants_flags.h"

GuiState GuiState::fromMainWindow(const MainWindow& w)
{
    GuiState s;

    // FlagTableを使って全部まとめて収集
    for (int i = 0; i < Constants::getFlagCount(); ++i) {
        const auto &f = Constants::FlagTable[i];
        s.flags[f.keyFlag] = w.guiFlagValue(f.keyFlag);
    }

    return s;
}
