#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    // 点击reg_btn后，将会触发switchRegister
    connect(ui->reg_btn, &QPushButton::clicked, this, &login::switchRegister);
}

login::~login()
{
    delete ui;
}
