#ifndef DELEGATESTATES_H
#define DELEGATESTATES_H

#include <QtTest/QtTest>
#include <qmessagebox.h>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"
#include "ui_salarycount.h"

/*! Ќужно описание класса и его предназначени€
*/
class delegateStates : public QObject
{
	Q_OBJECT

public:
	delegateStates();
	~delegateStates();

protected:
	enum app_states { USUAL, ADD, EDIT};
	app_states currentState;

protected:

	template <class T>
	T* shapeDataObject() = 0;

	template <class T>
	void parseDataObject(T *obj) = 0;

	void error_msg(const char* short_description, const char* text);
signals:
	void changeState(bool isChanging);

public slots:
	virtual void updateInfo(QString name) = 0;
};

#endif // DELEGATESTATES_H