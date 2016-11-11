
#pragma once

// Qt
#include <QMainWindow>
#include <QTimer>

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

protected slots:

    void onTimeout();

    void onActionStart(bool);

    void onGearUpClicked(bool bValue);

    void onGearDownClicked(bool bValue);

    void onClutchChanged(int iValue);

    void onBreakChanged(int iValue);

    void onGasChanged(int iValue);

private:

    Ui::CMainWindow*            m_pUI;

    CarEmulator::CCarEmulator   m_tEmulator;

    QTimer                      m_tTimer;
};
