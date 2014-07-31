#include "FrmOptions.h"
#include "ui_FrmOptions.h"
#include "../../Global.h"

CFrmOptions::CFrmOptions(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CFrmOptions)
{
    ui->setupUi(this);
    m_pParent = parent;
    
    ui->cbNotificationFlash->setChecked(CGlobal::Instance()->IsNotifiationFlashs());
    ui->cbNotificationShowMessage->setChecked(CGlobal::Instance()->IsNotifiationBarShowMessage());
    
    CGlobal::E_ROSTER_SHOW_TYPE type = CGlobal::Instance()->GetRosterShowType();
    switch (type) {
    case CGlobal::E_ROSTER_SHOW_JID:
        ui->rbJID->setChecked(true);
        break;
    case CGlobal::E_ROSTER_SHOW_NAME:
        ui->rbName->setChecked(true);
        break;
    case CGlobal::E_ROSTER_SHOW_NICK:
    default:
        ui->rbNick->setChecked(true);
        break;
    }
}

CFrmOptions::~CFrmOptions()
{
    delete ui;
}

CFrmOptions* CFrmOptions::Instance()
{
    static CFrmOptions* p = NULL;
    if(!p)
        p = new CFrmOptions;

    return p;
}

void CFrmOptions::on_pbCancel_clicked()
{
    close();
}

void CFrmOptions::on_pbOK_clicked()
{
    CGlobal::Instance()->SetNotifiationBarShowMessage(ui->cbNotificationShowMessage->isChecked());
    CGlobal::Instance()->SetNotifiationFlashs(ui->cbNotificationFlash->isChecked());

    CGlobal::E_ROSTER_SHOW_TYPE type = CGlobal::Instance()->GetRosterShowType();
    if(ui->rbJID->isChecked())
        type = CGlobal::E_ROSTER_SHOW_JID;
    else if(ui->rbName->isChecked())
        type = CGlobal::E_ROSTER_SHOW_NAME;
    else //if(ui->rbNick->isChecked())
        type = CGlobal::E_ROSTER_SHOW_NICK;
    CGlobal::Instance()->SetRosterShowType(type);

    close();
}
