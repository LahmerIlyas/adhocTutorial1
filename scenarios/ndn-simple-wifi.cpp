#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/ndnSIM-module.h"
#include "../extensions/AdhocScenario.hpp"

using namespace std;
namespace ns3 {

int
main(int argc, char* argv[])
{
  Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue("2200"));
  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue("2200"));
  Config::SetDefault("ns3::WifiRemoteStationManager::NonUnicastMode",
                     StringValue("OfdmRate24Mbps"));

  CommandLine cmd;
  cmd.Parse(argc, argv);
  std::cout<<" The scenario just started "<<std::endl; 
  AdhocScenario scenario;
  scenario.installWifi();
  scenario.installMobility();
  scenario.installNDNStack();
  scenario.installApps();
  scenario.start();

  std::cout<<" The scenario just ended"<<std::endl;
  return 0;
}

} 

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
