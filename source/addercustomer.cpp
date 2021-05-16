#include "addercustomer.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

AdderCustomer::AdderCustomer(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout(this);
    setLayout(layout);

    QPushButton * bAddFrame = new QPushButton("add frame", this);
    QPushButton * bAddCustomer = new QPushButton("add customer", this);
    QLineEdit * lCustomerName = new QLineEdit(this);

    layout->addWidget(lCustomerName);
    layout->addWidget(bAddFrame);
    layout->addWidget(bAddCustomer);
}

void AdderCustomer::onAddFrame(std::shared_ptr<std::vector<FacePoints>> pointSet)
{
    pointsSets.push_back(pointSet);
    emit changedFramesCount(QString("frame counts: ") + QString::number(pointsSets.size()));
}

void AdderCustomer::onRestoreFrames()
{
    pointsSets.clear();
    emit changedFramesCount("frame counts: 0");
}

void AdderCustomer::onAddCustomer(QString name)
{
    //if(currentFace.isValid()){
    //    db.save(currentFace);
    //}
}
