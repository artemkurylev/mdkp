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
    
};

#endif // SALARYCOUNTDIRECTIVES_H
