#ifndef SALARYCOUNTDIRECTIVES_H
#define SALARYCOUNTDIRECTIVES_H

#include "delegateStates.h"

class salarycountDirectives : public delegateStates
{
    Q_OBJECT


public:
	salarycountDirectives(Ui_SalaryCount *ui, QString name="");
	~salarycountDirectives();
private:
    Ui_SalaryCount *ui;//не самый при€тный способ, зато все видно из коробки

public slots:
	void updateInfo(QString name);
};

#endif // SALARYCOUNTDIRECTIVES_H
