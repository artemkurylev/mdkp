#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCoreApplication>

#include "companyopendialog.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "unittest/DirectiveGeneratorTest.h"
=======
#include "DirectiveGenerator.h"
>>>>>>> 3690967... Добавлен класс для тестирования расчётов
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

=======
#include "unittest/DirectiveGeneratorTest.h"
#include <CalcTest.h>

int test_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if(false) // if tests enabled
	{
		return test_main(argc, argv);
	}

	//DirectiveGenerator g;
	//HireDirective hd;

	//g.pdf( &hd, "example.pdf" );
	
	//DirectiveGeneratorTest dgt(0);
	//QTest::qExec( &dgt , NULL , NULL);
	
>>>>>>> 25c9d1b... Перенаправление стандартных потоков в файлы
    QApplication a(argc, argv);
    companyOpenDialog q;
    q.show();
    //SalaryCount w;
    //w.show();
    return a.exec();
<<<<<<< HEAD
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
	freopen ("sc_stderr.log","w",stderr); // ����� ������ 'a' ��� ��������? (����� ������� ���� �� ����������)
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
=======
}

int test_main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	freopen ("sc_stderr.log","w",stderr);
	freopen ("sc_stdout.log","w",stdout);
	

	fprintf (stderr, "This sentence is redirected to a file.");
	printf ("This sentence is redirected to a file.");
>>>>>>> 25c9d1b... Перенаправление стандартных потоков в файлы

	CalcTest t;
	QTest::qExec( &t , NULL , NULL);

<<<<<<< HEAD
    return 0; // a.exec();
}
=======
}
>>>>>>> 3690967... Добавлен класс для тестирования расчётов
=======

	fclose (stderr);
    return 0; // a.exec();
}
>>>>>>> 25c9d1b... Перенаправление стандартных потоков в файлы
