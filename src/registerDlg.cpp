#include "registerDlg.h"
#include "ui_registerDlg.h"
#include "global.h"
#include "httpmgr.h"
register_dlg::register_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_dlg)
{
    ui->setupUi(this);
    ui->psd_edit->setEchoMode(QLineEdit::Password);
    ui->ensure_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
    // 连接http发送的通知
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &register_dlg::slot_reg_mod_finish);
}

register_dlg::~register_dlg()
{
    delete ui;
}

void register_dlg::on_verify_btn_clicked()
{
    auto email = ui->email_edit->text();
    // silent0clown@qq.com
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match =regex.match(email).hasMatch();
    if (match) {
        // send http 验证码
    }
    else {
        showTip(tr("邮箱格式不正确"), false);
    }
}

void register_dlg::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }
    // 解析json字符串，res转换为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        showTip(tr("json解析失败"), false);
        return;
    }
    // json解析错误
    if(!jsonDoc.isObject()) {
        showTip(tr("json解析错误"), false);
    }
    // 转出json对象
    jsonDoc.object();
    _handlers[id](jsonDoc.object());   // 根据id调用相应回调函数
    return;

}

void register_dlg::initHttpHandles()
{
    // 注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送到邮箱，注意查收"), true);
        qDebug() << "email is " << email;
    });
}

void register_dlg::showTip(QString str, bool b_ok) {
    if (b_ok) {
        ui->err_tip->setProperty("state", "normal");
    }
    else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(str);

    repolish(ui->err_tip);
}
