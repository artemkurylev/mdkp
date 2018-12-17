#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCoreApplication>

#include "companyopendialog.h"
<<<<<<< HEAD
#include "unittest/DirectiveGeneratorTest.h"
=======
#include "DirectiveGenerator.h"
>>>>>>> 3690967... –î–æ–±–∞–≤–ª–µ–Ω –∫–ª–∞—Å—Å –¥–ª—è —Ç–µ—Å—Ç–∏—Ä–æ–≤–∞–Ω–∏—è —Ä–∞—Å—á—ë—Ç–æ–≤
#include <CalcTest.h>

int test_main(int argc, char *argv[]);
void redirect_output_streams();

int main(int argc, char *argv[])
{

	redirect_output_streams();

	if(false) // if tests enabled
	{
		return test_main(argc, argv);
	}

    QApplication a(argc, argv);
    companyOpenDialog q;
    q.show();
    //SalaryCount w;
    //w.show();
    return a.exec();
<<<<<<< HEAD
}

void MyMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString &message)
{
	switch (type) {

        case QtDebugMsg:
        case QtWarningMsg:

			printf( message.toLocal8Bit().data() );
			fflush(stdout);
            break;

        case QtCriticalMsg:
        case QtFatalMsg:

			fprintf(stderr, message.toLocal8Bit().data() );
			fflush(stderr);
            break;
    }
}

void redirect_output_streams()
{
	freopen ("sc_stderr.log","w",stderr); // ÏÓÊÌÓ Á‡‰‡Ú¸ 'a' ‰Îˇ ‰ÓÁ‡ÔËÒË? (˜ÚÓ·˚ ÔÓ¯Î˚Â ÎÓ„Ë ÌÂ Á‡ÚË‡ÎËÒ¸)
	freopen ("sc_stdout.log","w",stdout);
	
	fprintf(stderr, "Begin of STDERR log.\n");
	printf ("Begin of STDOUT log.\n");

    // Custom handler
    qInstallMessageHandler(MyMessageOutput);
    //qDebug() << "Printed in the console using my message handler in a windows GUI application\n";
}

int test_main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	CalcTest t;
	QTest::qExec( &t , NULL , NULL);

    return 0; // a.exec();
}
=======
}
>>>>>>> 3690967... –î–æ–±–∞–≤–ª–µ–Ω –∫–ª–∞—Å—Å –¥–ª—è —Ç–µ—Å—Ç–∏—Ä–æ–≤–∞–Ω–∏—è —Ä–∞—Å—á—ë—Ç–æ–≤
