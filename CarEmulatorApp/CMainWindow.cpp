
#include "CMainWindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::CMainWindow)
{
    m_pUI->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete m_pUI;
}
