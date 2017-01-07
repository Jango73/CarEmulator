
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
    connect(m_pUI->startEngine, SIGNAL(clicked(bool)), this, SLOT(onActionStartEngine(bool)));
    connect(m_pUI->stopEngine, SIGNAL(clicked(bool)), this, SLOT(onActionStopEngine(bool)));
    connect(m_pUI->AutoClutch, SIGNAL(toggled(bool)), this, SLOT(onAutoClutchChanged(bool)));
    connect(m_pUI->AutoGear, SIGNAL(toggled(bool)), this, SLOT(onAutoGearChanged(bool)));
    connect(m_pUI->AutoGas, SIGNAL(toggled(bool)), this, SLOT(onAutoGasChanged(bool)));
    connect(m_pUI->AccelSlow, SIGNAL(clicked(bool)), this, SLOT(onAccelSlow(bool)));
    connect(m_pUI->AccelNormal, SIGNAL(clicked(bool)), this, SLOT(onAccelNormal(bool)));
    connect(m_pUI->AccelFast, SIGNAL(clicked(bool)), this, SLOT(onAccelFast(bool)));

    m_tTimer.setInterval(50);
    m_tTimer.start();

    m_pUI->Cluster->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_pUI->Cluster->engine()->rootContext()->setContextProperty("car", &m_tCar);
    m_pUI->Cluster->setSource(QUrl("qrc:/Cluster.qml"));

    m_pUI->MechanicalControls->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_pUI->MechanicalControls->engine()->rootContext()->setContextProperty("car", &m_tCar);
    m_pUI->MechanicalControls->setSource(QUrl("qrc:/MechanicalControls.qml"));
}

CMainWindow::~CMainWindow()
{
    delete m_pUI;
}

void CMainWindow::onTimeout()
{
    m_tCar.process(50);

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

    double dSpeedDemand = m_tCar.speedDemand();
    m_pUI->SpeedDemand->setText(QString::number(dSpeedDemand, 'g', 4));

    double dAccelDemand = m_tCar.accelDemand();
    m_pUI->AccelDemand->setText(QString::number(dAccelDemand, 'g', 4));

    double dAccelerationKMHS = m_tCar.sensors().accelerationKMHS().value();
    m_pUI->Acceleration->setText(QString::number(dAccelerationKMHS, 'g', 4));
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

void CMainWindow::onAutoClutchChanged(bool bValue)
{
    m_tCar.setAutoClutch(bValue);
}

void CMainWindow::onAutoGearChanged(bool bValue)
{
    m_tCar.setAutoGear(bValue);
}

void CMainWindow::onAutoGasChanged(bool bValue)
{
    m_tCar.setAutoGas(bValue);
    m_tCar.setAutoBreak(bValue);
}

void CMainWindow::onAccelSlow(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.setBehavior(CarEmulator::CCarAI::eSlow);
}

void CMainWindow::onAccelNormal(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.setBehavior(CarEmulator::CCarAI::eNormal);
}

void CMainWindow::onAccelFast(bool bValue)
{
    Q_UNUSED(bValue);

    m_tCar.setBehavior(CarEmulator::CCarAI::eFast);
}
