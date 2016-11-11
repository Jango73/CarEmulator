
#pragma once

// Qt
#include <QMainWindow>

// Foundations
#include "../CarEmulatorLibrary/Source/CCarEmulator.h"

//-------------------------------------------------------------------------------------------------

namespace Ui {
class CMainWindow;
}

//-------------------------------------------------------------------------------------------------

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit CMainWindow(QWidget *parent = 0);

    ~CMainWindow();

private:

    Ui::CMainWindow*            m_pUI;

    CarEmulator::CCarEmulator   m_tEmulator;
};
