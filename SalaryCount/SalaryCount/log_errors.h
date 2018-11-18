#ifndef LOG_ERRORS
#define LOG_ERRORS

#include <qstring.h>
#include<qtextcodec.h>
#include <qlist.h>

#include <exception>


class log_errors : public std::exception
{

public:
	enum parse_conclusion { NONE=-1, FAIL, SUCCESS };
	enum exception_states { UNEXIST, VALIDATE_EX, UPDATE_EX, INSERT_EX, NULL_OBJ_EX, NOT_FOUND_EX, 
							PARSE_EX, SHAPE_EX, DELET_EX, COMPARE_EX, FETCH_EX};

	struct ex_description {

		exception_states errorType;
		QString textError;

		ex_description() : errorType(exception_states::UNEXIST), textError("") {}
		ex_description(exception_states e, QString t) : errorType(e), textError(t) {}
	};

private:
	parse_conclusion lastState;

	exception_states lastError;
	QString lastErrorText;

	QList<ex_description> *journal;

public:
	log_errors();
	~log_errors();

	QString getLastError() const;
	exception_states getLastErrorCode() const;
	parse_conclusion getLastConclusion() const;

	const QList<ex_description> &log_exceptions() const;

	void lastConflictResolved();
	void lastConflictNonResolved();

private:
	void writeInJournal(ex_description exd);
	void baseError(exception_states e, std::string text);

public:
	exception_states validateError(std::string text="") throw();
	exception_states updateError(std::string text="") throw();
	exception_states insertError(std::string text="") throw();
	exception_states nullPtr(std::string text="") throw();
	exception_states notFound(std::string text="") throw();
	exception_states parseError(std::string text="") throw();
	exception_states shapeError(std::string text="") throw();
	exception_states deletError(std::string text="") throw();
	exception_states compareError(std::string text="") throw();
	exception_states fetchError(std::string text="") throw();
};

#endif // LOG_ERRORS