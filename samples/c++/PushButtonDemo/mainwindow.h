//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <kdrive/baos/core/Forwards.h>
#include <kdrive/baos/BaosEvent.h>
#include <kdrive/baos/BaosEnumerator.h>
#include <memory>

namespace Ui
{
class MainWindow;
}

namespace kdrive
{
namespace baos
{

class ScopedBaosConnection;

}
} // end namespace kdrive::baos

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0);
	virtual ~MainWindow();

signals:
	void receivedBoolean(int id, bool enabled);
	void receivedFloat(int id, float value);
	void disconnected();

private slots:
	void on_scan_clicked();
	void on_connect_clicked();
	void on_disconnect_clicked();
	void on_channel1On_clicked();
	void on_channel1Off_clicked();
	void on_channel2On_clicked();
	void on_channel2Off_clicked();
	void on_floatRead_clicked();
	void onReceivedBoolean(int id, bool enabled);
	void onReceivedFloat(int id, float value);

private:
	void switchLight(int coNo, bool enabled);
	void send(unsigned int coNo, bool enabled);
	void createConnection();
	void destroyConnection();
	void readStatus();
	void readParameters();
	void onIndication(kdrive::baos::BaosDatapoint& baosDatapoint);
	void onDisconnected();
	void updateTimer(int coNo);
	bool isChannel1(int coNo) const;
	bool isChannel2(int coNo) const;
	void enableGui();

private:
	Ui::MainWindow* ui_;
	QTimer ch1Timer_;
	QTimer ch2Timer_;
	std::unique_ptr<kdrive::baos::ScopedBaosConnection> baosConnection_;
	kdrive::baos::BaosEvent baosEvent_;
	kdrive::baos::BaosEnumerator::Devices devices_;
	enum CommunicationObjects { Ch1Request = 1, Ch1Status, Ch2Request, Ch2Status, TwoByteFloat };
};

#endif // MAINWINDOW_H
