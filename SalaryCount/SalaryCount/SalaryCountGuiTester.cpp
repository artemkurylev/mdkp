#include "SalaryCountGuiTester.h"

#include <QMessageBox>

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
	


	// [0] - ������ ��������
	// [1] - ����� �������� ��������
	// [2] - ���������� ��������
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

	// ����������� ������ ������ ��� ������
	 rec_data[1].fio	= QString("Islambekov Abubakar Noevich");
	 rec_data[1].inn	= QString("911010203040");
	 rec_data[1].phone	= QString("+44044047855");

	qDebug("Launching test `editWorkerInfo` ...");

	// � ������ �.�. �� ����� 2 �������!
	int employees_count = ui->employeeList->count();
	QVERIFY2(employees_count >= 2, "Not enough employees in list!");

	// ����� ������� ������� ������
	rec_data[0].indexInList = rec_data[2].indexInList =		qrand() % employees_count;
	rec_data[1].indexInList =	employees_count-1 - rec_data[0].indexInList;

	int current_i, other_i;
	current_i = 0;

	// ������� ���������� �� ������
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// ������� � ��������� ������
	rec_data[current_i].read(ui);

	qDebug("Read data: `inn`: %s\n", rec_data[current_i].inn.toLocal8Bit().data());
	fflush(stdout);
	
	// �������������
	QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	////QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ������ ����� ������ ...
	ui->statusBar->showMessage("Type new test data ...", 15*1000);

	current_i = 1;
	rec_data[current_i].simulate_write(ui);


	// ���������
	ui->statusBar->showMessage("Saving new test data ...", 15*1000);
	////QTest::mouseClick(ui->saveEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->saveEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ������� �� ������� ���������� � ���������
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

	// ���������, ��� ������ �����������
	ui->statusBar->showMessage("Check saved data ...", 15*1000);
	current_i = 2;
	other_i = 1;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );


	// wait
	 QThread::sleep(1);

	// ����� �������������
	ui->statusBar->showMessage("Revert original data ...", 15*1000);
	////QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ������� ������ ������
	current_i = 0;
	rec_data[current_i].set(ui);

	// wait
	 QThread::sleep(2);

	// ��������
	ui->statusBar->showMessage("Cancelling ...", 15*1000);
	QTest::mouseClick(ui->cancelEmployeeBtn, Qt::LeftButton);
	////QTest::keyClick( ui->cancelEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ������� �� ������� ���������� � ���������
	current_i = 1;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);
	current_i = 0;
	ui->employeeList->setCurrentRow(rec_data[current_i].indexInList);

	// ���������, ��� �������������� ������ �� �����������, � �������� ��������
	current_i = 2;
	other_i = 1;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );


	// wait
	 QThread::sleep(1);

	// ����� �������������
	////QTest::mouseClick(ui->editEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->editEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );


	// ������� ������ ������
	ui->statusBar->showMessage("Revert original data ...", 15*1000);
	current_i = 0;
	rec_data[current_i].set(ui);

	// wait
	 QThread::sleep(2);

	// ���������
	ui->statusBar->showMessage("Saving ...", 15*1000);
	////QTest::mouseClick(ui->saveEmployeeBtn, Qt::LeftButton);
	QTest::keyClick( ui->saveEmployeeBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );

	// ���������, ��� �������������� ������ �����������
	current_i = 2;
	other_i = 0;
	rec_data[current_i].read(ui);
	qDebug("Comparing rec #%d to rec #%d ...", current_i, other_i);
	rec_data[current_i].compareTo( &rec_data[other_i] );

	qDebug("Passed to the end of test `editWorkerInfo`.\n");
	ui->statusBar->showMessage("Passed to the end of test `editWorkerInfo`.", 15*1000);

}

void CbxSetIndex(QComboBox* cbx, int val)
{
	cbx->setFocus();

	QTest::keyClick( cbx , Qt::Key_Down, Qt::NoModifier, /*delay =*/ 50);
	QTest::keyClick( cbx , Qt::Key_Down, Qt::NoModifier, /*delay =*/ 50);
	QTest::keyClick( cbx , Qt::Key_Up, Qt::ShiftModifier, /*delay =*/ 50);
	
	cbx->setCurrentIndex(val);
}

void SalaryCountGuiTester::editLaborSheet()
{
	if( ui->stackedWidget->currentWidget()->objectName() != "LaborSheetsPage" )
	{
		return;
	}
	
	QMap<QComboBox*, int> original_values;
	
	qDebug("Launching test `editLaborSheet` ...");
	
	// � ������ �.�. �� ����� 1 ������!
	int sheets_count = ui->employeeLaborSheetTable->rowCount();
	QVERIFY2(sheets_count >= 1, "Not enough labor_sheets in table!");

	QVERIFY2(ui->employeeLaborSheetTable->currentRow() >= 0, "No labor_sheet selected!");
	
	// ������� � ����� �������������� ������, ���� ��� �� � ��
	if( ui->updateLaborBtn->isEnabled() )
	{
		ui->statusBar->showMessage("Entering edit mode ...", 15*1000);
		QTest::mouseClick(ui->updateLaborBtn, Qt::LeftButton);
	}
	
	for(int i=0 ; i<6 ; ++i)
	for(int j=0 ; j<7 ; ++j)
	{
		QWidget* w = ui->laborSheet->cellWidget(i,j);
		if( dynamic_cast<QComboBox*>(w) == nullptr ) {
			continue;
		}

		QComboBox* cbx;
		cbx = ((QComboBox*) w);
		// qDebug("combo at (%d,%d)", i,j);
		original_values[cbx] = cbx->currentIndex();
	}

	if( ! ui->laborSheet->cellWidget(1,0)->isEnabled() )
	{
		ui->statusBar->showMessage("Cannot edit marks: period is closed. PLEASE GO to opened period!", 45*1000);
		QMessageBox::information(0, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"������ ��������� ������� ��� ������������ �������� �������: ������� ������ ������. ��������� � ��������� (��������) ���������� �������.")); 
	}
	
	QVERIFY2( ui->laborSheet->cellWidget(1,0)->isEnabled(), "Cannot edit marks: period is closed." );
	
	
	// ������ ����� ������ ...
	ui->statusBar->showMessage("Type new test marks ...", 15*1000);
	
	int v = 0, inc = +1;
	foreach(QComboBox* cbx , original_values.keys())
	{
		CbxSetIndex(cbx, v);
		
		v += inc;
		if(v<=0 || v>=12) inc *= -1;
	}
	
	// ���������
	ui->statusBar->showMessage("Saving new test data ...", 15*1000);
	QTest::keyClick( ui->saveEditedLaborBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );
	
	// wait
	 QThread::sleep(2);

	// ����� �������������
	ui->statusBar->showMessage("Entering edit mode again ...", 15*1000);
	QTest::mouseClick(ui->updateLaborBtn, Qt::LeftButton);
	
	ui->statusBar->showMessage("Revert original data ...", 15*1000);
	foreach(QComboBox* cbx , original_values.keys())
	{
		CbxSetIndex(cbx, original_values[cbx]);
	}
	
	// ���������
	ui->statusBar->showMessage("Saving ...", 15*1000);
	QTest::keyClick( ui->saveEditedLaborBtn , Qt::Key_Space, Qt::NoModifier, /*delay =*/ 100 );
	
	
}
void SalaryCountGuiTester::showOrder()
{

	
}