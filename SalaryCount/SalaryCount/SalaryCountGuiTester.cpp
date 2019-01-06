#include "SalaryCountGuiTester.h"

void Tester::runTests(Ui_SalaryCount* ui) {
	SalaryCountGuiTester t(ui);
	char *argv[] = {"-nograb"};
	int result = QTest::qExec( &t , 1 , argv);
	emit testingFinished(result);
}


SalaryCountGuiTester::SalaryCountGuiTester(Ui_SalaryCount *ui)
{
	this->ui=ui;

}

SalaryCountGuiTester::~SalaryCountGuiTester()
{
}

void SalaryCountGuiTester::init()
{

}

void SalaryCountGuiTester::cleanup()
{

}

void SalaryCountGuiTester::exitAction()
{

	
}
void SalaryCountGuiTester::editWorkSchedule()
{

	
}
void SalaryCountGuiTester::deleteWorkSchedule()
{

	
}
void SalaryCountGuiTester::addNewWorkSchedule()
{

	
}
void SalaryCountGuiTester::addWorker()
{

	
}
void SalaryCountGuiTester::editWorkerInfo()
{
	if( ui->stackedWidget->currentWidget()->objectName() != "EmployeesPage" )
	{
		return;
	}
	


	// [0] - старые значения
	// [1] - новые тестовые значения
	// [2] - сохранённые значения
	class Rec {
	public:
		QString fio, inn, phone;
		int indexInList;

		void read(Ui_SalaryCount *ui)
		{
			this->fio	= ui->eFIO->text();
			this->inn	= ui->INN->text();
			this->phone = ui->eNumberPhone->text();
		}
		void clearAndTypeInLineEdit(QWidget* w, const QString& text)
		{
			w->setFocus();

			QTest::keyClick( w , Qt::Key_Home, Qt::NoModifier, /*delay =*/ 50);
			QTest::keyClick( w , Qt::Key_Home, Qt::NoModifier, /*delay =*/ 50);
			for (int i=0 ; i<5 ; ++i) {
				QTest::keyClick( w , Qt::Key_Right, Qt::ShiftModifier, /*delay =*/ 50);
			}
			QTest::keyClick( w , Qt::Key_End, Qt::ShiftModifier, /*delay =*/ 50);
			for (int i=0 ; i<5 ; ++i) {
				QTest::keyClick( w , Qt::Key_Right, Qt::ShiftModifier, /*delay =*/ 20);
			}
			QTest::keyClick( w , Qt::Key_Delete, Qt::NoModifier, /*delay =*/ 20);
			QTest::keyClick( w , Qt::Key_Backspace, Qt::NoModifier, /*delay =*/ 20);
			
			QTest::keyClick( w , Qt::Key_Home, Qt::NoModifier, /*delay =*/ 50);

			QTest::keyClicks( w , text, Qt::NoModifier, /*delay =*/ 50);
		}
		void simulate_write(Ui_SalaryCount *ui)
		{
			this->clearAndTypeInLineEdit(ui->eFIO , this->fio);
			this->clearAndTypeInLineEdit(ui->INN , this->inn);
			this->clearAndTypeInLineEdit(ui->eNumberPhone , this->phone);
		}
		void set(Ui_SalaryCount *ui)
		{
			ui->eNumberPhone->setText(this->phone);
			/* wait */ 	QThread::msleep(600);
			ui->INN->setText(this->inn);
			/* wait */ 	QThread::msleep(600);
			ui->eFIO->setText(this->fio);
		}
		void compareTo(Rec* other)
		{
			QCOMPARE(this->fio, other->fio);
			QCOMPARE(this->inn, other->inn);

			QRegExp extra_char("[\\s\\(\\)]");
			QCOMPARE(this->phone.replace(extra_char,""), other->phone.replace(extra_char,""));
		}

	} rec_data[3];

	// подготовить другие данные для замены
	 rec_data[1].fio	= QString("Islambekov Abubakar Noevich");
	 rec_data[1].inn	= QString("911010203040");
	 rec_data[1].phone	= QString("+44044047855");

	qDebug("Launching test `editWorkerInfo` ...");
	fflush(stdout);

	// в списке д.б. не менее 2 пунктов!
	int employees_count = ui->employeeList->count();
	QVERIFY2(employees_count >= 2, "Not enough employees in list!");

	// выбор рабочих пунктов списка
	rec_data[0].indexInList = rec_data[2].indexInList =		qrand() % employees_count;
	rec_data[1].indexInList =	employees_count-1 - rec_data[0].indexInList;

	int current_i, other_i;
	current_i = 0;

	// выбрать сотрудника из списка
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// считать и сохранить данные
	rec_data[current_i].read(ui);

	qDebug("Read data: `inn`: %s\n", rec_data[current_i].inn.toLocal8Bit().data());
	fflush(stdout);
	
	// редактировать
	QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	////QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ввести новые данные ...
	ui->statusBar->showMessage("Type new test data ...", 15*1000);

	current_i = 1;
	rec_data[current_i].simulate_write(ui);


	// сохранить
	ui->statusBar->showMessage("Saving new test data ...", 15*1000);
	////QTest::mouseClick(ui->saveEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->saveEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// перейти на другого сотрудника и вернуться
	ui->statusBar->showMessage("Change employee in list ...", 15*1000);
	current_i = 1;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// wait
	 QThread::sleep(1);

	ui->statusBar->showMessage("Go back to employee in list ...", 15*1000);
	current_i = 0;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// wait
	 QThread::sleep(1);

	// проверить, что данные сохранились
	ui->statusBar->showMessage("Check saved data ...", 15*1000);
	current_i = 2;
	other_i = 1;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );


	// wait
	 QThread::sleep(1);

	// снова редактировать
	ui->statusBar->showMessage("Revert original data ...", 15*1000);
	////QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// вернуть старые данные
	current_i = 0;
	rec_data[current_i].set(ui);

	// wait
	 QThread::sleep(2);

	// ОТМЕНИТЬ
	ui->statusBar->showMessage("Cancelling ...", 15*1000);
	QTest::mouseClick(ui->cancelEmployeeBtn, Qt::LeftButton);
	////QTest::keyClick( ui->cancelEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// перейти на другого сотрудника и вернуться
	current_i = 1;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);
	current_i = 0;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// проверить, что первоначальные данные НЕ сохранились, а остались тестовые
	current_i = 2;
	other_i = 1;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );


	// wait
	 QThread::sleep(1);

	// снова редактировать
	////QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );


	// вернуть старые данные
	ui->statusBar->showMessage("Revert original data ...", 15*1000);
	current_i = 0;
	rec_data[current_i].set(ui);

	// wait
	 QThread::sleep(2);

	// сохранить
	ui->statusBar->showMessage("Saving ...", 15*1000);
	////QTest::mouseClick(ui->saveEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->saveEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// проверить, что первоначальные данные сохранились
	current_i = 2;
	other_i = 0;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );

	qDebug("Passed to the end of test `editWorkerInfo`.\n");
	ui->statusBar->showMessage("Passed to the end of test `editWorkerInfo`.", 15*1000);

}
void SalaryCountGuiTester::editLaborSheet()
{

	
}
void SalaryCountGuiTester::showOrder()
{

	
}