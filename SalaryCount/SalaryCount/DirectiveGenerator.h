#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QDate>

class DirectiveGenerator 
{
   

public:
	DirectiveGenerator();
  
	void pdf(QString filename);
    QString currentDateNow();
    void writeTextAtleftTop(QPainter *painter, QString text);
    void drawTableOne(QPainter *painter,QString text1,QString text2);
    void constructMainHeader(QPainter *painter,QString tableCode);

    void drawTableFive(QPainter *painter,QString text1,QString text2);

    //Font setting
    void setFontSmallUnderText(QPainter*painter);
    void setFontBigText(QPainter*painter);
    void setFontRectangle(QPainter*painter);

    void drawHeaderTitlePageTwo(QPainter *painter);
    void writeInfoPagetwo(QPainter* painter);

    void drawTableEight(QPainter *painter);
    void drawTableNine(QPainter *painter);
    void drawTableTen(QPainter *painter);

private:
    
};
