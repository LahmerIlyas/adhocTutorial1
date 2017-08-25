#include"AdhocScenario.hpp"


namespace ns3{



AdhocScenario::AdhocScenario(){
  SeedManager::SetSeed(1);
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
  wifiChannel.AddPropagationLoss("ns3::RangePropagationLossModel","MaxRange",DoubleValue(30));

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
  producerHelper.SetPrefix("/");
  producerHelper.SetAttribute("PayloadSize", StringValue("1200"));
  producerHelper.Install(m_nodes.Get(2));

}

void AdhocScenario::installMobility(){
  Ptr<UniformRandomVariable> randomizerX = CreateObject<UniformRandomVariable>();
  randomizerX->SetAttribute("Min", DoubleValue(10));
  randomizerX->SetAttribute("Max", DoubleValue(100));

  Ptr<UniformRandomVariable> randomizerY = CreateObject<UniformRandomVariable>();
  randomizerY->SetAttribute("Min", DoubleValue(0));
  randomizerY->SetAttribute("Max", DoubleValue(10));

  Ptr<UniformRandomVariable> randomizerZ = CreateObject<UniformRandomVariable>();
  randomizerZ->SetAttribute("Min", DoubleValue(0));
  randomizerZ->SetAttribute("Max", DoubleValue(0));


  MobilityHelper mobility;
  mobility.SetPositionAllocator("ns3::RandomBoxPositionAllocator", "X", PointerValue(randomizerX),
                                "Y", PointerValue(randomizerY), "Z", PointerValue(randomizerZ));

  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");

  mobility.Install(m_nodes);
}

void AdhocScenario::start(){
  Simulator::Stop(Seconds(m_simulationDuration));

  Simulator::Run();
  Simulator::Destroy();

}


}
