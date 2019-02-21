#pragma once

#include <string>
#include "ofxOsc.h"
#include "ofMain.h"

namespace ofxSimpleOsc {
	class Sender {
	protected:
		ofxOscSender sender;
		ofxOscMessage temp_message;

		void sendImpl(ofxOscMessage& message)
		{
			sender.sendMessage(message);
		}

		template<class Head, class ...Tail>
		void sendImpl(ofxOscMessage& message, const Head & head, const Tail & ...tail)
		{
			addArg(message, head);
			sendImpl(message, tail...);
		}

		template<class Head>
		void sendImpl(ofxOscMessage& message, const Head & head)
		{
			addArg(message, head);
			sendImpl(message);
		}

		void addArg(ofxOscMessage & m, const ofColor& c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		void addArg(ofxOscMessage & m, const ofFloatColor& c)
		{
			m.addFloatArg(c.r);
			m.addFloatArg(c.g);
			m.addFloatArg(c.b);
			m.addFloatArg(c.a);
		}

		void addArg(ofxOscMessage & m, const ofShortColor& c)
		{
			m.addIntArg(c.r);
			m.addIntArg(c.g);
			m.addIntArg(c.b);
			m.addIntArg(c.a);
		}

		void addArg(ofxOscMessage & m, const ofRectangle& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.width);
			m.addFloatArg(r.height);
		}

		void addArg(ofxOscMessage & m, const ofQuaternion& r)
		{
			m.addFloatArg(r.x());
			m.addFloatArg(r.y());
			m.addFloatArg(r.z());
			m.addFloatArg(r.w());
		}

		void addArg(ofxOscMessage & m, const ofVec2f& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
		}

		void addArg(ofxOscMessage & m, const ofVec3f& r)
		{
			m.addFloatArg(r.x);
			m.addFloatArg(r.y);
			m.addFloatArg(r.z);
		}

		void addArg(ofxOscMessage & m, int arg)
		{
			m.addIntArg(arg);
		}

		void addArg(ofxOscMessage & m, long arg)
		{
			m.addInt64Arg(arg);
		}

		void addArg(ofxOscMessage & m, long long arg)
		{
			m.addInt64Arg(arg);
		}

		void addArg(ofxOscMessage & m, float arg)
		{
			m.addFloatArg(arg);
		}

		void addArg(ofxOscMessage & m, double arg)
		{
			m.addDoubleArg(arg);
		}

		void addArg(ofxOscMessage & m, bool arg)
		{
			m.addBoolArg(arg);
		}

		void addArg(ofxOscMessage & m, char arg)
		{
			m.addCharArg(arg);
		}

		void addArg(ofxOscMessage & m, const string& arg)
		{
			m.addStringArg(arg);
		}

		void addArg(ofxOscMessage & m, char const * arg)
		{
			m.addStringArg(arg);
		}

	public:
		Sender(){}
		~Sender(){
			sender.clear();
		}

		void setup(const std::string& host, int port)
		{
			sender.setup(host, port);
		}

		void send(ofxOscMessage & message, bool wrap_in_bundle)
		{
			sender.sendMessage(message, wrap_in_bundle);
		}

		template<class ...Args>
		void send(const std::string& address, const Args&... args)
		{
			temp_message.clear();
			temp_message.setAddress(address);

			sendImpl(temp_message, args...);
		}

		template<class Arg>
		void send(const std::string& address, const Arg& arg)
		{
			temp_message.clear();
			temp_message.setAddress(address);

			sendImpl(temp_message, arg);
		}

		void send(const std::string& address)
		{
			temp_message.clear();
			temp_message.setAddress(address);
			sender.sendMessage(temp_message);
		}
	};
};
