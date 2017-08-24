#include<iostream>

class AdhocScenario{
public:
	AdhocScenario();

	void installNDNStack();

	void installWifi();

	void installApps();

	void installMobility();

	void start();

private:
	double m_simulationDuration = 5000.0;

	uint32_t m_numberOfClients = 1;
	
	uint32_t m_numberOfProducers = 1;
	
	uint32_t m_numberOfNodes     = 5;
		
};


