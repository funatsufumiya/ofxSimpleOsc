#include "Receiver.h"

#include "ofMain.h"

using namespace std;
using namespace ofxSimpleOsc;

void Receiver::update(ofEventArgs & args)
{
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		string addr = m.getAddress();

		if (enable_log) {
			printOscLog(m);
		}

		ofNotifyEvent(ofxSimpleOsc::OSC_MESSAGE_RECEIVED, m);

		if (receive_func) {
			receive_func(m);
		}
	}
}

void Receiver::setup(int port, bool _enable_log, std::function<void(const ofxOscMessage&)> receive_func)
{
	enable_log = _enable_log;
	receiver.setup(port);
	ofAddListener(ofEvents().update, this, &Receiver::update);
	this->receive_func = receive_func;
}

void ofxSimpleOsc::Receiver::setup(int port, std::function<void(const ofxOscMessage&)> receive_func)
{
	setup(port, true, receive_func);
}

void ofxSimpleOsc::Receiver::showNotHandledWarning()
{
	ofLogWarning("ofxSimpleOsc::Receiver") << "not handled (ignored.)";
}

void ofxSimpleOsc::Receiver::printOscLog(const ofxOscMessage & m, bool print_args)
{
	stringstream ss;

	ss << m.getAddress();

	int num_args = m.getNumArgs();
	for (int i = 0; i < num_args; ++i) {
		auto v = getOscArg(m, i);
		ss << " " + v;
	}

	ss << "";

	string s = ss.str();
	ofLogNotice("ofxSimpleOsc::Receiver") << s;
}

void ofxSimpleOsc::Receiver::setOscLogEnabled(bool b)
{
	enable_log = b;
}

bool ofxSimpleOsc::Receiver::getOscLogEnabled()
{
	return enable_log;
}

std::string Receiver::getOscArg(const ofxOscMessage& m, size_t i)
{
	auto type = m.getArgType(i);

	switch (type) {
	case OFXOSC_TYPE_FLOAT:
		return ofToString(m.getArgAsFloat(i), 3);
	case OFXOSC_TYPE_INT32:
		return ofToString(m.getArgAsInt32(i));
	case OFXOSC_TYPE_INT64:
		return ofToString(m.getArgAsInt64(i));
	case OFXOSC_TYPE_DOUBLE:
		return ofToString(m.getArgAsDouble(i), 3);
	case OFXOSC_TYPE_TRUE:
		return "true";
	case OFXOSC_TYPE_FALSE:
		return "false";
	case OFXOSC_TYPE_CHAR:
	{
		char c = m.getArgAsChar(i);
		string s(1, c);
		return s;
	}
	case OFXOSC_TYPE_STRING:
		return m.getArgAsString(i);
	default:
	{
		auto loglevel = ofGetLogLevel();
		ofSetLogLevel(ofLogLevel::OF_LOG_SILENT);
		string s = m.getArgAsString(i);
		ofSetLogLevel(loglevel);
		return s;
	}
	}
}

bool Receiver::is_int(const std::string & s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool Receiver::is_float(const std::string & s)
{
	std::string::const_iterator it = s.begin();
	bool decimalPoint = false;
	int minSize = 0;
	if (s.size() > 0 && (s[0] == '-' || s[0] == '+')) {
		it++;
		minSize++;
	}
	while (it != s.end()) {
		if (*it == '.') {
			if (!decimalPoint) decimalPoint = true;
			else break;
		}
		else if (!std::isdigit(*it) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint)) {
			break;
		}
		++it;
	}
	return s.size() > minSize && it == s.end();
}

bool Receiver::is_double(const std::string & s)
{
	return is_type<double>(s);
}

template<typename T>
bool Receiver::is_type(const std::string & s)
{
	T target;
	stringstream ss;
	ss << s;
	ss >> target;
	return ss.good();
}

std::vector<std::string> Receiver::split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}
