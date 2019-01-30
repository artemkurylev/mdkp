#include "DirectiveGenerator.h"


DirectiveGenerator::DirectiveGenerator()
{
}

void DirectiveGenerator::pdf(const HireDirective* hireDirective, const QString& filename)
{
	QPdfWriter writer(filename);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 8));

    QRect r = painter.viewport();

   // drawing the place for name and surname
   painter.drawText(3000,5700,"(�������,���,��������)");
   QString nameSurPat=hireDirective->fio();
   painter.drawText(3000,5400,nameSurPat);

   painter.drawText(1500,7000,"(��������� (�������������, ���������), ������, ����� (���������) ������������)");
   painter.drawText(2500,8000,"(������� ������ �� ������, �������� ������)");

   painter.drawText(2800,10600,"  (���������)                              (������ �������)                 (���������� �������)");


   painter.setFont(QFont("Times", 10));
   painter.drawText(40,8500,"� �������� ������� (�������)       ___________________________ ���._____ ���.");
   painter.drawText(1600,9000,"���������       ___________________________ ���._____ ���.");
   painter.drawText(40,9300,"� ���������� �� ���� _________________________________________________         ������(��)");
   painter.drawText(40,9500,"���������:");
   painter.drawText(60,9700,"   �������� ������� �� �_____ �___________  ______ �. �_________");
   QDate hiredate=hireDirective->hireDate();
   QString docId=QString::number(hireDirective->id());
   QString day=QString::number(hiredate.day());
   QString month=QString::number(hiredate.month());
   QString year=QString::number(hiredate.year());
   painter.drawText(2100,9700,day);
   painter.drawText(2800,9700,month);
   painter.drawText(3800,9700,year);
   painter.drawText(4800,9700,"1");
  
   painter.drawText(40,10100,"������������ �����������");
   painter.drawText(1800,10400,"             _______________________    ________________  _______________________");
   painter.drawText(40,11000,"� �������� (�������������) �������� ����������");
   painter.drawText(3500,11060,"            _____________________ �_____ � __________ 20____�.");

   painter.drawText(3200,3000,"(������������)");
   painter.drawText(2800,3200,"� ������ ��������� �� ������");
   painter.drawText(3200,3600,"������� �� ������");

   painter.setFont(QFont("Times", 12));
   painter.drawText(3500,2800,"������");

   constructMainHeader(&painter,"0301001");


    QPen pen(Qt::black, 5, Qt::SolidLine);
    painter.setPen(pen);
	painter.drawLine(40,2000,7000,2000); // the first line on the page
    painter.drawLine(40,5500,8500,5500); // draw line for name and surname

    painter.drawLine(40,6800,8500,6800); //��������� (�������������, ���������), ������, ����� (���������) ������������

    painter.drawLine(40,7300,8500,7300);// empty line

    painter.drawLine(40,7800,8500,7800);  // ������� ������ �� ������, �������� ������

    painter.end();

}

void DirectiveGenerator::insertDataToPdf(const HireDirective* hireDirective,QPainter)
{
	QString fio=hireDirective->fio();
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





