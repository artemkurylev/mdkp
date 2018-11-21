#pragma once
#include "HireDirective.h"

#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QDate>
#include <qtextcodec.h>

class DirectiveGenerator 
{
   

public:
	DirectiveGenerator();
  
	void pdf(const HireDirective* hireDirective, const QString& filename);

	// Tables and Headers
    void writeTextAtleftTop(QPainter *painter, QString text);
    void constructMainHeader(QPainter *painter,QString tableCode);

    //Font setting
    void setFontSmallUnderText(QPainter*painter);
    void setFontBigText(QPainter*painter);
    void setFontRectangle(QPainter*painter);

private:
    
};
