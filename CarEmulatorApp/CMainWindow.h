
#pragma once

// Qt
#include <QMainWindow>
#include <QTimer>

// Foundations
#include "../CarEmulatorLibrary/Source/CCarAI.h"

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

    void onActionStartEngine(bool);

    void onActionStopEngine(bool);

    void onAutoClutchChanged(bool bValue);

    void onAutoGearChanged(bool bValue);

    void onAutoGasChanged(bool bValue);

private:

    Ui::CMainWindow*            m_pUI;

    CarEmulator::CCarAI         m_tCar;

    QTimer                      m_tTimer;
};
