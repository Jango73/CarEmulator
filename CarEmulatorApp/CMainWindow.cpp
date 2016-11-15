
// Qt
#include <QQmlEngine>
#include <QQmlContext>

// Application
#include "CMainWindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pUI(new Ui::CMainWindow)
    , m_tCar(true)
{
    m_pUI->setupUi(this);

    connect(&m_tTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(m_pUI->actionStartEngine, SIGNAL(triggered(bool)), this, SLOT(onActionStartEngine(bool)));
    connect(m_pUI->actionStopEngine, SIGNAL(triggered(bool)), this, SLOT(onActionStopEngine(bool)));
    connect(m_pUI->GearUp, SIGNAL(clicked(bool)), this, SLOT(onGearUpClicked(bool)));
    connect(m_pUI->GearDown, SIGNAL(clicked(bool)), this, SLOT(onGearDownClicked(bool)));
    connect(m_pUI->Clutch, SIGNAL(valueChanged(int)), this, SLOT(onClutchChanged(int)));
    connect(m_pUI->Break, SIGNAL(valueChanged(int)), this, SLOT(onBreakChanged(int)));
    connect(m_pUI->Gas, SIGNAL(valueChanged(int)), this, SLOT(onGasChanged(int)));
    connect(m_pUI->AutoGear, SIGNAL(toggled(bool)), this, SLOT(onAutoGearChanged(bool)));

    m_tTimer.setInterval(50);
    m_tTimer.start();

    m_pUI->Cluster->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_pUI->Cluster->engine()->rootContext()->setContextProperty("car", &m_tCar);
    m_pUI->Cluster->setSource(QUrl("qrc:/Cluster.qml"));
}

CMainWindow::~CMainWindow()
{
    delete m_pUI;
}

void CMainWindow::onTimeout()
{
    m_tCar.process(50);

    int iCurrentGear = m_tCar.gearBox().currentGear();
    m_pUI->CurrentGear->setText(QString::number(iCurrentGear));

    double dEngineRPM = m_tCar.sensors().currentRPM().value();
    m_pUI->EngineRPM->setText(QString::number(dEngineRPM, 'g', 4));

    double dSpeed = m_tCar.sensors().currentSpeedKMH().value();
    m_pUI->Speed->setText(QString::number(dSpeed, 'g', 4));

    double dFuelLevel = m_tCar.sensors().currentFuelLevelL().value();
    m_pUI->FuelLevel->setText(QString::number(dFuelLevel, 'g', 4));

    double dEngineTemp = m_tCar.sensors().currentEngineTempC().value();
    m_pUI->EngineTemperature->setText(QString::number(dEngineTemp, 'g', 4));

    double dFuelCons = m_tCar.sensors().fuelConsumptionL100KM().value();
    m_pUI->FuelConsumption->setText(QString::number(dFuelCons, 'g', 4));

    double dTorqueTransferFactor = m_tCar.torqueTransferFactor();
    m_pUI->TorqueTransfer->setText(QString::number(dTorqueTransferFactor, 'g', 4));
}

void CMainWindow::onActionStartEngine(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.startEngine();
}

void CMainWindow::onActionStopEngine(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.stopEngine();
}

void CMainWindow::onGearUpClicked(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.gearBox().up();
}

void CMainWindow::onGearDownClicked(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.gearBox().down();
}

void CMainWindow::onClutchChanged(int iValue)
{
    m_tCar.clutchPedal().setValue(1.0 - ((double) iValue / 100.0));
}

void CMainWindow::onBreakChanged(int iValue)
{
    m_tCar.breakPedal().setValue((double) iValue / 100.0);
}

void CMainWindow::onGasChanged(int iValue)
{
    m_tCar.gasPedal().setValue((double) iValue / 100.0);
}

void CMainWindow::onAutoGearChanged(bool bValue)
{
    m_tCar.setAutoGear(bValue);
}
