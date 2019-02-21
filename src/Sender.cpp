#include "Sender.h"

#include "ofMain.h"

using namespace std;
using namespace ofxSimpleOsc;

void Sender::setup(const std::string& host, int port)
{
	sender.setup(host, port);
}

void Sender::send(ofxOscMessage & message, bool wrap_in_bundle)
{
	sender.sendMessage(message, wrap_in_bundle);
}

void Sender::sendImpl(ofxOscMessage& message)
{
	sender.sendMessage(message);
}

template<class Head, class ...Tail>
void Sender::sendImpl(ofxOscMessage& message, const Head & head, const Tail & ...tail)
{
	addArg(message, head);
	sendImpl(message, tail...);
}

template<class ...Args>
void Sender::send(const std::string& address, const Args&... args)
{
	temp_message.clear();
	temp_message.setAddress(address);

	sendImpl(message, args...);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, int arg)
{
	m.addIntArg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, long arg)
{
	m.addInt64Arg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, long long arg)
{
	m.addInt64Arg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, float arg)
{
	m.addFloatArg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, double arg)
{
	m.addDoubleArg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, bool arg)
{
	m.addBoolArg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, char arg)
{
	m.addCharArg(arg);
}

template<>
void ofxSimpleOsc::Sender::addArg(ofxOscMessage & m, const string& arg)
{
	m.addStringArg(arg);
}
