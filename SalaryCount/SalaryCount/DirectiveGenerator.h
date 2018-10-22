#include "HireDirective.h"

#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QDate>

class DirectiveGenerator 
{
   

public:
	DirectiveGenerator();
  
	void pdf(const HireDirective* hireDirective, const QString& filename);

	// Tables and Headers
    void writeTextAtleftTop(QPainter *painter, QString text);
    void drawTableOne(QPainter *painter,QString text1,QString text2);
    void constructMainHeader(QPainter *painter,QString tableCode);

    //Font setting
    void setFontSmallUnderText(QPainter*painter);
    void setFontBigText(QPainter*painter);
    void setFontRectangle(QPainter*painter);

private:
    
};
