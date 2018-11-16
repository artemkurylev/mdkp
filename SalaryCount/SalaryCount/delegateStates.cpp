#include "delegateStates.h"

delegateStates::delegateStates()
{
	this->currentState = delegateStates::USUAL;
}
	
delegateStates::~delegateStates()
{

}

void delegateStates::error_msg(const char* short_description, const char* text)
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::critical(NULL,c->toUnicode(short_description), c->toUnicode(text));
}