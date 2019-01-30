#include "DirectiveGenerator.h"


DirectiveGenerator::DirectiveGenerator()
{
}

void DirectiveGenerator::pdf(QString filename)
{
	QPdfWriter writer(filename);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 8));

    QRect r = painter.viewport();

    QString citydate = "City, ";
   // citydate += currDate;

    //connect( ui->okbtn,	SIGNAL( clicked() ), this,		SLOT( onSaveRecord() ) );

    QString blockA="��������������� ����� � �-1\n���������� �������������� �����������\n������\n�� 05.01.2004 � 1";

    writeTextAtleftTop(&painter,blockA);

    QString currDate=currentDateNow();

    painter.drawText(r, Qt::AlignLeft, currDate);
    // constructMainHeader(&painter,"0301001");

   //painter.drawText(3000,2200,"(������������ �����������)");

   // drawing the pplace for name and surname
   painter.drawText(3000,5700,"(�������,���,��������)");
  /* QString sn=ui.surname->text();
   QString n=ui->name->text();
   QString pt=ui->patronymic->text();*/

   //painter.drawText(3600,5700,sn);
   painter.drawText(3000,6500,"(����������� �������������)");
   painter.drawText(1500,7000,"(��������� (�������������, ���������), ������, ����� (���������) ������������)");
   painter.drawText(2500,8000,"(������� ������ �� ������, �������� ������)");

   painter.drawText(2800,10600,"  (���������)                              (������ �������)                 (���������� �������)");





   painter.setFont(QFont("Times", 10));
   painter.drawText(40,8500,"� �������� ������� (�������)       ___________________________ ���._____ ���.");
   painter.drawText(1600,9000,"���������       ___________________________ ���._____ ���.");
   painter.drawText(40,9300,"� ���������� �� ���� _________________________________________________         ������(��)");
   painter.drawText(40,9500,"���������:");
   painter.drawText(60,9700,"   �������� ������� �� �_____ �___________ 20_____ �. �_________");

   painter.drawText(40,10100,"������������ �����������");
   painter.drawText(1800,10400,"             _______________________    ________________  _______________________");
   painter.drawText(40,11000,"� �������� (�������������) �������� ����������");
   painter.drawText(3500,11060,"            _____________________ �_____ � __________ 20____�.");



   painter.drawText(100,6300,"�");

   painter.drawText(3200,3000,"(������������)");
   painter.drawText(2800,3200,"� ������ ��������� �� ������");
   painter.drawText(3200,3600,"������� �� ������");


   painter.setFont(QFont("Times", 12));
   //painter.drawText(6700,1700,"����� �� ����");
   //painter.drawText(7200,2000,"�� ����");

   painter.drawText(3500,2800,"������");


   //drawTableOne(&painter,"���","0301001");
   constructMainHeader(&painter,"0301001");


    QPen pen(Qt::black, 5, Qt::SolidLine);
    painter.setPen(pen);
   // painter.drawLine(40,2000,7000,2000);
    painter.drawLine(40,5500,8500,5500); // draw line for name and surname


    painter.drawLine(200,6300,8500,6300);// for ����������� �������������

    painter.drawLine(40,6800,8500,6800); //��������� (�������������, ���������), ������, ����� (���������) ������������

    painter.drawLine(40,7300,8500,7300);// empty line

    painter.drawLine(40,7800,8500,7800);  // ������� ������ �� ������, �������� ������



    writer.newPage();
    //painter(&writer);
    QString blockB="��������������� ����� � �-2\n���������� �������������� �����������\n������\n�� 05.01.2004 � 1";

    writeTextAtleftTop(&painter,blockB);

    constructMainHeader(&painter,"0301002");
    drawTableFive(&painter,"uy","uy");
    drawHeaderTitlePageTwo(&painter);
    writeInfoPagetwo(&painter);
    drawTableEight(&painter);
    drawTableNine(&painter);
    drawTableTen(&painter);

    painter.end();

}
QString DirectiveGenerator::currentDateNow()
{
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}

void DirectiveGenerator::drawTableOne(QPainter *painter,QString text1,QString text2)
{
    setFontRectangle(painter);
    QRectF r1(8300,1200,1000,300);
    QRectF r2(8300,1500,1000,300);
    QRectF r3(8300,1800,1000,300);
    painter->drawRect(r1);
    painter->drawRect(r2);
    painter->drawRect(r3);
    setFontBigText(painter);
    painter->drawText(8500,1400,text1);
    painter->drawText(8350,1700,text2);


}
void DirectiveGenerator::writeTextAtleftTop(QPainter* painter, QString text)
{
    setFontSmallUnderText(painter);
    QRect r=painter->viewport();
    painter->drawText(r,Qt::AlignRight, text);

}

void DirectiveGenerator::constructMainHeader(QPainter *painter,QString tableCode)
{
    setFontBigText(painter);
    painter->drawText(6700,1700,"����� �� ����");
    painter->drawText(7200,2000,"�� ����");
    painter->drawLine(40,2000,7000,2000);
    setFontSmallUnderText(painter);
    painter->drawText(3000,2200,"(������������ �����������)");
    drawTableOne(painter,"���",tableCode);

}

void DirectiveGenerator::setFontRectangle(QPainter*painter)
{
    painter->setPen(Qt::black);
    painter->setFont(QFont("Times", 8));
}
void DirectiveGenerator::setFontBigText(QPainter*painter)
{
    painter->setFont(QFont("Times", 12));
}
void DirectiveGenerator::setFontSmallUnderText(QPainter*painter)
{
    painter->setPen(Qt::black);
    painter->setFont(QFont("Times", 8));
}
void DirectiveGenerator::drawTableFive(QPainter *painter,QString text1,QString text2)
{
    setFontRectangle(painter);
    QRectF r1(40,2500,9000,1000);

//    QRectF r2(8300,1500,1000,300);
//    QRectF r3(8300,1800,1000,300);
    painter->drawRect(r1);
    painter->drawLine(40,3200,9040,3200);

    painter->drawLine(1040,2500,1040,3500);
    painter->drawLine(2040,2500,2040,3500);

    painter->drawLine(4000,2500,4000,3500);
    painter->drawLine(6000,2500,6000,3500);
    painter->drawLine(6500,2500,6500,3500);
    painter->drawLine(7100,2500,7100,3500);
    painter->drawLine(7900,2500,7900,3500);
   // painter->drawLine(9040,3200,9040,3200);
//    painter->drawRect(r2);
//    painter->drawRect(r3);
//    setFontBigText(painter);
//    painter->drawText(8500,1400,text1);
//    painter->drawText(8350,1700,text2);


}
void DirectiveGenerator::drawHeaderTitlePageTwo(QPainter *painter)
{
    painter->setPen(Qt::black);
    painter->setFont(QFont("Times", 12));

    painter->drawText(3700,3700,"������ ��������");
    painter->drawText(4200,4000,"���������");
    painter->drawText(3700,4300,"I. ����� ��������");
}

void DirectiveGenerator::writeInfoPagetwo(QPainter* painter)
{
    painter->setFont(QFont("Times", 10));
    painter->drawText(40,4800,"1. ������� ___________________________  ��� ______________________ �������� _________________________");
    painter->drawText(40,5300,"2. ���� �������� ___________________________________________________________________________________");

    painter->drawText(40,5700,"3. ����� �������� ____________________________________________________________");
    painter->drawText(40,6000,"4. ����������� _______________________________________________________________");
    painter->drawText(40,6300,"5. ������ ������������ �����     _______________________________________________");
    painter->drawText(40,7300,"6. ����������� _________________________________________________________________");
    painter->drawText(40,11950,"7. ���������       _________________________________________________________________  �� �� ����");
    painter->drawLine(2800,6900,7000,6900);  // line for extra language

     painter->setFont(QFont("Times", 8));

    painter->drawText(4500,5450,"(����, �����, ���)");
    painter->drawText(4100,6450,"(������������)               (������� ������)");
    painter->drawText(1500,7450,"(������� (������) �����, ��������� ����������������, ������� ����������������, ������ ����������������)");

}

void DirectiveGenerator::drawTableEight(QPainter *painter)
{
    setFontRectangle(painter);
    QRectF r1(40,7650,8300,1300);
    painter->drawRect(r1);


}
void DirectiveGenerator::drawTableNine(QPainter *painter)
{
    setFontRectangle(painter);
    QRectF r1(40,9150,8300,1100);
    painter->drawRect(r1);


}
void DirectiveGenerator::drawTableTen(QPainter *painter)
{
    setFontRectangle(painter);
    QRectF r1(40,10550,8300,1100);
    painter->drawRect(r1);
}

