#include "log_errors.h"

log_errors::log_errors()
{
	this->lastState = parse_conclusion::NONE;
	this->lastError = exception_states::UNEXIST;
	this->lastErrorText = "";
	this->journal = new QList<ex_description>();
}

log_errors::~log_errors()
{
	delete this->journal;
}

QString log_errors::getLastError() const
{
	return this->lastErrorText;
}

log_errors::exception_states log_errors::getLastErrorCode() const
{
	return this->lastError;
}

log_errors::parse_conclusion log_errors::getLastConclusion() const
{
	return this->lastState;
}

const QList<log_errors::ex_description> &log_errors::log_exceptions() const
{
	return *this->journal;
}

void log_errors::writeInJournal(ex_description exd)
{
	this->lastError = exd.errorType;
	this->lastErrorText = exd.textError;
	*(this->journal) << exd;
}

void log_errors::baseError(exception_states e, std::string text)
{
	QTextCodec* c = QTextCodec::codecForLocale();

	writeInJournal( ex_description(e, c->toUnicode(text.c_str())) );
	this->lastState = parse_conclusion::FAIL;
}

void log_errors::lastConflictResolved()
{
	int count_journal_entries = this->journal->count();

	bool isConflict = this->lastState != (parse_conclusion::NONE | parse_conclusion::SUCCESS) 
		&& this->lastError != exception_states::UNEXIST;

	if(isConflict && count_journal_entries)
	{
		this->journal->pop_back();
		this->lastState = parse_conclusion::SUCCESS;
		this->lastError = exception_states::UNEXIST;
		this->lastErrorText = "";

		if(count_journal_entries-1)
		{
			this->lastState = parse_conclusion::FAIL;
			this->lastError = this->journal->back().errorType;
			this->lastErrorText = this->journal->back().errorType;
		}
	}
}

void log_errors::lastConflictNonResolved()
{
	this->lastState = parse_conclusion::NONE;
	this->lastError = exception_states::UNEXIST;
	this->lastErrorText = "";
}

log_errors::exception_states log_errors::validateError(std::string text) throw()
{
	exception_states ex = exception_states::VALIDATE_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::updateError(std::string text) throw()
{
	exception_states ex = exception_states::UPDATE_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::insertError(std::string text) throw()
{
	exception_states ex = exception_states::INSERT_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::nullPtr(std::string text) throw()
{
	exception_states ex = exception_states::NULL_OBJ_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::notFound(std::string text) throw()
{
	exception_states ex = exception_states::NOT_FOUND_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::parseError(std::string text) throw()
{
	exception_states ex = exception_states::PARSE_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::shapeError(std::string text) throw()
{
	exception_states ex = exception_states::SHAPE_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::deletError(std::string text) throw()
{
	exception_states ex = exception_states::DELET_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::compareError(std::string text) throw()
{
	exception_states ex = exception_states::COMPARE_EX;

	baseError(ex, text);

	return ex;
}

log_errors::exception_states log_errors::fetchError(std::string text) throw()
{
	exception_states ex = exception_states::FETCH_EX;

	baseError(ex, text);

	return ex;
}