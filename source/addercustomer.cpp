#include "addercustomer.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include "face.h"

AdderCustomer::AdderCustomer(std::shared_ptr<DBManager> db, QWidget *parent)
    : db(db), QWidget(parent)
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
    pointsSets.push_back(pointSet->at(0));
    emit changedFramesCount(QString("frame counts: ") + QString::number(pointsSets.size()));
}

void AdderCustomer::onRestoreFrames()
{
    pointsSets.clear();
    emit changedFramesCount("frame counts: 0");
}

void AdderCustomer::onAddCustomer(QString name)
{
    if(db){
        Face newCustomer(name, pointsSets);
        if(newCustomer.isValid()){
            db->save(newCustomer);
        }
    }
}
