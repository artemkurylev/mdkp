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
   painter.drawText(3000,5700,"(фамилия,имя,отчество)");
   QString nameSurPat=hireDirective->fio();
   painter.drawText(3000,5400,nameSurPat);

   painter.drawText(1500,7000,"(должность (специальность, профессия), разряд, класс (категория) квалификации)");
   painter.drawText(2500,8000,"(условия приема на работу, характер работы)");

   painter.drawText(2800,10600,"  (должность)                              (личная подпись)                 (расшировка подписи)");


   painter.setFont(QFont("Times", 10));
   painter.drawText(40,8500,"с тарифной ставкой (окладом)       ___________________________ руб._____ коп.");
   painter.drawText(1600,9000,"надбавкой       ___________________________ руб._____ коп.");
   painter.drawText(40,9300,"с испытанием на срок _________________________________________________         месяца(ев)");
   painter.drawText(40,9500,"Основание:");
   painter.drawText(60,9700,"   Трудовой договор от “_____ ”___________  ______ г. №_________");
   QDate hiredate=hireDirective->hireDate();
   QString docId=QString::number(hireDirective->id());
   QString day=QString::number(hiredate.day());
   QString month=QString::number(hiredate.month());
   QString year=QString::number(hiredate.year());
   painter.drawText(2100,9700,day);
   painter.drawText(2800,9700,month);
   painter.drawText(3800,9700,year);
   painter.drawText(4800,9700,"1");
  
   painter.drawText(40,10100,"Руководитель организации");
   painter.drawText(1800,10400,"             _______________________    ________________  _______________________");
   painter.drawText(40,11000,"С приказом (распоряжением) работник ознакомлен");
   painter.drawText(3500,11060,"            _____________________ “_____ ” __________ 20____г.");

   painter.drawText(3200,3000,"(распоряжение)");
   painter.drawText(2800,3200,"о приеме работника на работу");
   painter.drawText(3200,3600,"Принять на работу");

   painter.setFont(QFont("Times", 12));
   painter.drawText(3500,2800,"ПРИКАЗ");

   constructMainHeader(&painter,"0301001");


    QPen pen(Qt::black, 5, Qt::SolidLine);
    painter.setPen(pen);
	painter.drawLine(40,2000,7000,2000); // the first line on the page
    painter.drawLine(40,5500,8500,5500); // draw line for name and surname

    painter.drawLine(40,6800,8500,6800); //должность (специальность, профессия), разряд, класс (категория) квалификации

    painter.drawLine(40,7300,8500,7300);// empty line

    painter.drawLine(40,7800,8500,7800);  // условия приема на работу, характер работы

    painter.end();

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
    painter->drawText(6700,1700,"Форма по ОКУД");
    painter->drawText(7200,2000,"по ОКПО");
    painter->drawLine(40,2000,7000,2000);
    setFontSmallUnderText(painter);
    painter->drawText(3000,2200,"(наименование организации)");
    drawTableOne(painter,"Код",tableCode);

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





