#ifndef ADDERCUSTOMER_H
#define ADDERCUSTOMER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

#include "facepoints.h"
#include "dbmanager.h"

class AdderCustomer : public QWidget
{
    Q_OBJECT
public:
    AdderCustomer(std::shared_ptr<DBManager> db, QWidget *parent = nullptr);

signals:
    void changedFramesCount(QString count);

public slots:
    void onAddFrame(std::shared_ptr<std::vector<FacePoints>> pointSet);
    void onRestoreFrames();
    void onAddCustomer(QString name);

private:
    QLineEdit lCustomerName;
    QPushButton bAddFrame;
    QPushButton bAddCustomer;

    std::vector<FacePoints> pointsSets;
    std::shared_ptr<DBManager> db;
};

#endif // ADDERCUSTOMER_H
