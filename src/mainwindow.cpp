#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login = new login(this);       // 在此处加this，解决内存泄漏
    setCentralWidget(_login);
    // _login->show();

    // 创建和注册消息链接
    // 将witchRegiqster与SlotSwitchReg链接
    connect(_login, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    _reg = new register_dlg(this);

    _login->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _reg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _reg->hide();
}

MainWindow::~MainWindow()
{
    // 这边在注册界面点击右上角×时发生内存泄漏
    // 原因： setCentralWidget访问_login或_reg，在直接×的时候，setCentralWidget访问空地址
    delete ui;
    if (_login) {
        delete _login;
        _login = nullptr;
    }

    if (_reg) {
        delete _reg;
        _reg = nullptr;
    }
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg);
    _login->hide();
    _reg->show();
}

