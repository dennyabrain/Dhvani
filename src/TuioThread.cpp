#include "TuioThread.h"
#include "TuioDump.h"

void TuioThread::threadedFunction()
{
//  TuioDump dump;
	//int port = 3333;
//    TuioClient client(port);
	client.addTuioListener(&dump);
	client.connect(true);
//	list <TuioObject *> temp = client.getTuioObjects();
//	cout<<*temp->getX();
}
