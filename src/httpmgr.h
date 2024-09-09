#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

// CRTP ? 类对象继承类模板
class HttpMgr:public QObject, public Singleton<HttpMgr>, public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();      // 为什么析构是Public
 /*
  * 因为HttpMgr析构的时候需要析构Singleton类，Singleton中成员变量_instance是一个智能指针
  * static std::shared_ptr<T> _instance;
  * 智能指针析构时需要访问T的析构，即HttpMgr，所以需要是public类型，否则析构失败
*/
private:
    friend class Singleton<HttpMgr>;  // 为了让基类能够访问HttpMgr的构造函数，所以声明为友元
    HttpMgr();
    QNetworkAccessManager _manager;
    void PostHttpReq(QUrl url,  QJsonObject json, ReqId req_id, Modules mod);

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMGR_H
