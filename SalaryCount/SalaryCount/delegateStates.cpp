#include "delegateStates.h"

delegateStates::delegateStates()
{
	this->currentState = delegateStates::USUAL;
	this->journal = new log_errors();//журнал ошибок 
}
	
delegateStates::~delegateStates()
{

}

void delegateStates::error_msg(const char* short_description, const char* text)
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::critical(NULL,c->toUnicode(short_description), c->toUnicode(text));
}

void delegateStates::show_last_error()
{
	QByteArray code = QString::fromWCharArray(L"Ошибка (код %1)")
			.arg(QString::number(this->journal->getLastErrorCode())).toLocal8Bit();
	QByteArray msg = this->journal->getLastError().toLocal8Bit();

	error_msg(code.data(),msg.data());//cообщили об ошибке
}