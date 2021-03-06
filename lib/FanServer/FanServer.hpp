#ifndef FanServer_h
#define FanServer_h

#define FANSERVER_PATH "fans"
#define MAX_FAN_COUNT 3

#include <EthernetClient.h>
#include <ArduinoJson.h>
#include "ArduinoServerInterface.hpp"
#include "Fan.hpp"
#include "HTTP.hpp"


class FanServer : public ArduinoServerInterface
{
public:
	FanServer();
	~FanServer();

	void handleRequest(const String& request, EthernetClient& client);

	void addFan(EthernetClient& client, const String& request);
	void removeFan(EthernetClient& client, const String& request);
	void sendFansJson(EthernetClient& client, const String& request);
	void sendSingleFan(EthernetClient& client, int pin, HTTPResponseType responseType);
	void sendConfigJson(EthernetClient& client);
	void setFanProperties(EthernetClient& client, const String& request);

private:
	Fan _fans[MAX_FAN_COUNT];
	int _allowedFanPins[3] = {3,9,10};
	int _fanCount;

	int findIndex(int pin);
	Fan* findFan(int pin);
	bool isfreePin(int pin);

	void addFanInfoToJsonObj(Fan& fan, JsonObject& outObject);
	bool addFan(int pin, int frequency = DEFAULT_FREQUENCY, int dutyCycle = DEFAULT_DUTYCYCLE);
	bool removeFan(int pin);
	bool setFrequency(int pin, int frequency);
	bool setDutyCycle(int pin, int dutyCycle);
};

#endif
