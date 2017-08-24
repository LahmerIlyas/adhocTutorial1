#include"AdhocScenario.hpp"
namespace ns3{

AdhocScenario::AdhocScenario(){
  m_nodes.Create(m_numberOfNodes);
}

void AdhocScenario::installNDNStack(){
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "1000");
  ndnHelper.SetDefaultRoutes(true);
  ndnHelper.Install(m_nodes);

  ndn::StrategyChoiceHelper::Install(m_nodes, "/", "/localhost/nfd/strategy/broadcast");
}

void AdhocScenario::installWifi(){
  WifiHelper wifi = WifiHelper::Default();
  wifi.SetStandard(WIFI_PHY_STANDARD_80211a);
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",
                               StringValue("OfdmRate24Mbps"));

  YansWifiChannelHelper wifiChannel; 
  wifiChannel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss("ns3::","MaxRange",DoubleValue(50));

  YansWifiPhyHelper wifiPhyHelper = YansWifiPhyHelper::Default();
  wifiPhyHelper.SetChannel(wifiChannel.Create());
  
  NqosWifiMacHelper wifiMacHelper = NqosWifiMacHelper::Default();
  wifiMacHelper.SetType("ns3::AdhocWifiMac");

  m_wifiNetDevices = wifi.Install(wifiPhyHelper, wifiMacHelper, m_nodes);
}

void AdhocScenario::installApps(){
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix("/test/prefix");
  consumerHelper.SetAttribute("Frequency", DoubleValue(10.0));
  consumerHelper.Install(m_nodes.Get(0));

  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix("/test");
  producerHelper.SetAttribute("PayloadSize", StringValue("1200"));
  producerHelper.Install(m_nodes.Get(1));

}

void AdhocScenario::installMobility(){
  Ptr<UniformRandomVariable> randomizer = CreateObject<UniformRandomVariable>();
  randomizer->SetAttribute("Min", DoubleValue(10));
  randomizer->SetAttribute("Max", DoubleValue(100));

  MobilityHelper mobility;
  mobility.SetPositionAllocator("ns3::RandomBoxPositionAllocator", "X", PointerValue(randomizer),
                                "Y", PointerValue(randomizer), "Z", PointerValue(randomizer));

  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

  mobility.Install(m_nodes);
}

void AdhocScenario::start(){
  Simulator::Stop(Seconds(m_simulationDuration));

  Simulator::Run();
  Simulator::Destroy();

}


}
