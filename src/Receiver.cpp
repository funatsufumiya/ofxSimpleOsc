#include "Receiver.h"

#include "ofMain.h"
#include "Logger.h"
#include <cctype>

using namespace std;
using namespace ofxSimpleOsc;

void ofxSimpleOsc::Receiver::update(ofEventArgs & args)
{
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		string addr = m.getAddress();

		if (enable_log) {
			printOsclog(m, print_args, logger_module_name);
		}

		ofNotifyEvent(ofxSimpleOsc::OSC_MESSAGE_RECEIVED, m);

		if (receive_func) {
			receive_func(m);
		}
	}
}

void ofxSimpleOsc::Receiver::setup(int port, bool _enable_log, std::function<void(const ofxOscMessage&)> receive_func)
{
	enable_log = _enable_log;
	if (!receiver.isListening()) {
		ofAddListener(ofEvents().update, this, &Receiver::update);
	}
	receiver.setup(port);
	this->receive_func = receive_func;
}

void ofxSimpleOsc::Receiver::setup(int port, std::function<void(const ofxOscMessage&)> receive_func)
{
	setup(port, false, receive_func);
}

void ofxSimpleOsc::Receiver::showNotHandledWarning(const std::string& module_name)
{
	ofLogWarning(module_name) << "not handled. ignored.";
}

void ofxSimpleOsc::Receiver::showNotHandledWarning(const ofxOscMessage& m, const std::string& module_name)
{
	ofLogWarning(module_name) << m.getAddress() << " (typetag: " << m.getTypeString() << ") not handled. ignored.";
}

void ofxSimpleOsc::Receiver::printOsclog(const ofxOscMessage & m, bool print_args, const std::string& module_name)
{
	ofxSimpleOsc::logger.log(m, print_args, module_name);
}

void ofxSimpleOsc::Receiver::setOscLogEnabled(bool enabled)
{
	enable_log = enabled;
}

void ofxSimpleOsc::Receiver::setOscLogEnabled(bool _enable_log, bool _print_args, const std::string & _logger_module_name)
{
	enable_log = _enable_log;
	print_args = _print_args;
	logger_module_name = _logger_module_name;
}

bool ofxSimpleOsc::Receiver::getOscLogEnabled()
{
	return enable_log;
}
