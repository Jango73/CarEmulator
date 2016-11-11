
#include "CMainWindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::CMainWindow)
{
    m_pUI->setupUi(this);

    m_tTimer.setInterval(100);
    connect(&m_tTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    connect(m_pUI->actionStart, SIGNAL(triggered(bool)), this, SLOT(onActionStart(bool)));
    connect(m_pUI->GearUp, SIGNAL(clicked(bool)), this, SLOT(onGearUpClicked(bool)));
    connect(m_pUI->GearDown, SIGNAL(clicked(bool)), this, SLOT(onGearDownClicked(bool)));
    connect(m_pUI->Clutch, SIGNAL(valueChanged(int)), this, SLOT(onClutchChanged(int)));
    connect(m_pUI->Break, SIGNAL(valueChanged(int)), this, SLOT(onBreakChanged(int)));
    connect(m_pUI->Gas, SIGNAL(valueChanged(int)), this, SLOT(onGasChanged(int)));
}

CMainWindow::~CMainWindow()
{
    delete m_pUI;
}

void CMainWindow::onTimeout()
{
    m_tEmulator.process(100);

    int iCurrentGear = m_tEmulator.vehicle().gearBox().currentGear();
    m_pUI->CurrentGear->setText(QString::number(iCurrentGear));

    double dEngineRPM = m_tEmulator.vehicle().sensors().currentRPM().value();
    m_pUI->EngineRPM->setText(QString::number(dEngineRPM, 'g', 4));

    double dSpeed = m_tEmulator.vehicle().sensors().currentSpeedKMH().value();
    m_pUI->Speed->setText(QString::number(dSpeed, 'g', 4));

    double dEngineTemp = m_tEmulator.vehicle().sensors().currentEngineTempC().value();
    m_pUI->EngineTemperature->setText(QString::number(dEngineTemp, 'g', 4));

    double dFuelCons = m_tEmulator.vehicle().sensors().fuelConsumptionL100KM().value();
    m_pUI->FuelConsumption->setText(QString::number(dFuelCons, 'g', 4));
}

void CMainWindow::onActionStart(bool bValue)
{
    Q_UNUSED(bValue);

    m_tTimer.start();
}

void CMainWindow::onGearUpClicked(bool bValue)
{
    Q_UNUSED(bValue);

    m_tEmulator.vehicle().gearBox().up();
}

void CMainWindow::onGearDownClicked(bool bValue)
{
    Q_UNUSED(bValue);

    m_tEmulator.vehicle().gearBox().down();
}

void CMainWindow::onClutchChanged(int iValue)
{
    m_tEmulator.vehicle().clutchPedal().setValue(1.0 - ((double) iValue / 100.0));
}

void CMainWindow::onBreakChanged(int iValue)
{
    m_tEmulator.vehicle().breakPedal().setValue((double) iValue / 100.0);
}

void CMainWindow::onGasChanged(int iValue)
{
    m_tEmulator.vehicle().gasPedal().setValue((double) iValue / 100.0);
}
