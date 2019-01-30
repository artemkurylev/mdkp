#include "DirectiveGenerator.h"


DirectiveGenerator::DirectiveGenerator()
{
}

void DirectiveGenerator::pdf(const HireDirective* hireDirective, const QString& filename)
{
	QTextCodec * codec=QTextCodec::codecForLocale();
	QPdfWriter writer(filename);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 8));

    QRect r = painter.viewport();
   // drawing the place for name and surname
   painter.drawText(3000,5700,codec->toUnicode("(�������,���,��������)"));
   QString nameSurPat=hireDirective->fio();
   painter.drawText(3000,5400,nameSurPat);
   painter.drawText(1500,7000,codec->toUnicode("(��������� (�������������, ���������), ������, ����� (���������) ������������)"));
   painter.drawText(2500,8000,codec->toUnicode("(������� ������ �� ������, �������� ������)"));

   painter.drawText(2800,10600,codec->toUnicode("  (���������)                              (������ �������)                 (���������� �������)"));

   painter.drawText(4500,11260, codec->toUnicode("(������ �������)"));

   painter.setFont(QFont("Times", 10));
   painter.drawText(40,8500,codec->toUnicode("� �������� ������� (�������)       ___________________________ ���._____ ���."));
  
  
   painter.drawText(40,9500,codec->toUnicode("���������:"));
   painter.drawText(60,9700,codec->toUnicode("   �������� ������� �� �_____ �___________  ______ �. �_________"));
   QDate hiredate=hireDirective->hireDate();
   QString docId=QString::number(hireDirective->id());
   QString day=QString::number(hiredate.day());
   QString month=QString::number(hiredate.month());
   QString year=QString::number(hiredate.year());
   painter.drawText(2100,9700,day);
   painter.drawText(2800,9700,month);
   painter.drawText(3800,9700,year);
   painter.drawText(4800,9700,"1");
  
   painter.drawText(40,10100,codec->toUnicode("������������ �����������"));
   painter.drawText(1800,10400,codec->toUnicode("             _______________________    ________________  _______________________"));
   painter.drawText(40,11000,codec->toUnicode("� �������� (�������������) �������� ����������"));
   painter.drawText(3500,11060,codec->toUnicode("            _____________________ �_____ � __________ 20____�."));
  

   painter.drawText(3200,3000,codec->toUnicode("(������������)"));
   painter.drawText(2800,3200,codec->toUnicode("� ������ ��������� �� ������"));
   painter.drawText(3400,3600,codec->toUnicode("������� �� ������"));

   painter.setFont(QFont("Times", 12));
   painter.drawText(3500,2800,codec->toUnicode("������"));

   constructMainHeader(&painter,"0301001");


    QPen pen(Qt::black, 5, Qt::SolidLine);
    painter.setPen(pen);
	painter.drawLine(40,2000,8500,2000); // the first line on the page
    painter.drawLine(40,5500,8500,5500); // draw line for name and surname

    painter.drawLine(40,6800,8500,6800); //��������� (�������������, ���������), ������, ����� (���������) ������������

    painter.drawLine(40,7300,8500,7300);// empty line

    painter.drawLine(40,7800,8500,7800);  // ������� ������ �� ������, �������� ������

    painter.end();

}

void DirectiveGenerator::writeTextAtleftTop(QPainter* painter, QString text)
{
    setFontSmallUnderText(painter);
    QRect r=painter->viewport();
    painter->drawText(r,Qt::AlignRight, text);

}

void DirectiveGenerator::constructMainHeader(QPainter *painter,QString tableCode)
{
	QTextCodec * codec=QTextCodec::codecForLocale();
    setFontBigText(painter);
  
    painter->drawLine(40,2000,7000,2000);
    setFontSmallUnderText(painter);
    painter->drawText(3000,2200,codec->toUnicode("(������������ �����������)"));

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





