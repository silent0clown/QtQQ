#ifndef GLOBAL_H
#define GLOBAL_H


// 用来刷新qss
#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include "Qstyle"
#include <QByteArray>
#include <QNetworkReply>


extern std::function<void(QWidget*)> repolish;

enum ReqId {
    ID_GET_VERIFY_CODE = 1001,   // 获取验证码
    ID_REG_USER        = 1002,   // 注册用户

};

enum Modules {
    REGISTERMOD  = 0,
};

enum ErrorCodes {
    SUCCESS     = 0,
    ERR_JSON    = 1,
    ERR_NETWORK = 2,

};


#endif // GLOBAL_H
