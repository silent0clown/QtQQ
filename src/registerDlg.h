#ifndef REGISTER_DLG_H
#define REGISTER_DLG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class register_dlg;
}

class register_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit register_dlg(QWidget *parent = nullptr);
    ~register_dlg();

private slots:
    void on_verify_btn_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

private:
    void initHttpHandles();
    Ui::register_dlg *ui;
    void showTip(QString str, bool b_ok);
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
};

#endif // REGISTER_H
