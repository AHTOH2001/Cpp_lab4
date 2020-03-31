#include "mainwindow.h"
#include "ui_mainwindow.h"
QString infiks,postfiks;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(400,280);
    this->setFixedSize(400,280);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int rec (int i,bool flag)
{
    QChar zn;
    if (infiks.length()-1<i) return -1;
    if (flag)
    {
    if (infiks[i]=='(')
    {
        i=rec(i+1,true);
        if (i==-1) return -1;
    }
    else
        if (infiks[i]>='a' && infiks[i]<='z') postfiks+=infiks[i];
    else return -1;
    i+=2;
    }
    else i++;
    if (infiks.length()-1<i) return -1;
    if (infiks[i-1]=='*' || infiks[i-1]=='/' || infiks[i-1]=='+' || infiks[i-1]=='-') zn = infiks[i-1];
    else return -1;
    if (infiks[i]=='(')
    {
        i=rec(i+1,true);
        if (i==-1) return -1;
    }
    else
        if (infiks[i]>='a' && infiks[i]<='z') postfiks+=infiks[i];
    else return -1;
    i++;
    if ((zn=='+' || zn=='-') && (infiks[i]=='*' || infiks[i]=='/'))
    {
        i=rec(i,false);
        if (i==-1) return -1;
    }
    postfiks+=zn;
    if (infiks.length()-1>=i && infiks[i]!=')')
    {
        i=rec(i,false);
        if (i==-1) return -1;
    }
    return i;


}


void MainWindow::on_convert_button_clicked()
{
    infiks = ui->infiks->text();
    postfiks = "";
    if (infiks.length()==0)
    {
        QMessageBox::critical(this, "Error","Infiks is empty");
        return;
    }
    int i = 0;
    if (rec (i,true)==-1)
    {
        QMessageBox::critical(this, "Error","Invalid infiks");
        return;
    }

    ui->postfiks->setText(postfiks);
}


void MainWindow::on_calculate_button_clicked()
{
    double a = ui->a->text().toDouble();
    double b = ui->b->text().toDouble();
    double c = ui->c->text().toDouble();
    double d = ui->d->text().toDouble();
    double e = ui->e->text().toDouble();
    QStack<double> st;
    for (int i = 0;i<postfiks;i++)
    {
        if (postfiks[i]=='a') st.push(a);
        else
        if (postfiks[i]=='b') st.push(b);
        else
        if (postfiks[i]=='c') st.push(c);
        else
        if (postfiks[i]=='d') st.push(d);
        else
        if (postfiks[i]=='e') st.push(e);
        else
        if (postfiks[i]=='-') st.push(-(st.pop()-st.pop()));
        else
        if (postfiks[i]=='+') st.push(st.pop()+st.pop());
        else
        if (postfiks[i]=='*') st.push(st.pop()*st.pop());
        else
        if (postfiks[i]=='/')
        {
            double x = st.pop();
            st.push(st.pop()/x);
        }
    }
    ui->result->setText(QString::number(st.top()));
    QMessageBox::information(this, "Well done","Result is: " + QString::number(st.pop()));

}








