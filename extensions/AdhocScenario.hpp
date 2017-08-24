#include<iostream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/ndnSIM-module.h"

namespace ns3{

class AdhocScenario{
public:
  AdhocScenario();

  void installNDNStack();

  void installWifi();

  void installApps();

  void installMobility();

  void start();

private:
  double m_simulationDuration = 500.0;

  uint32_t m_numberOfClients = 1;
	
  uint32_t m_numberOfProducers = 1;
	
  uint32_t m_numberOfNodes     = 5;
		
  NodeContainer m_nodes;

  NetDeviceContainer m_wifiNetDevices;
};


}// namespace ns3
