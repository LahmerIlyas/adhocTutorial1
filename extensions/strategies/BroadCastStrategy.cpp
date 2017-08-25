//
// Created by lahmer on 8/25/17.
//

#include "BroadCastStrategy.h"
namespace nfd{
    namespace fw{
        const Name BroadCastStrategy::STRATEGY_NAME("ndn:/localhost/nfd/strategy/broodcast/%FD%01");
        NFD_REGISTER_STRATEGY(BroadCastStrategy);

        BroadCastStrategy::BroadCastStrategy(Forwarder &forwarder, const Name &name) : Strategy(forwarder, name){

        }

        void BroadCastStrategy::afterReceiveInterest(const Face &inFace, const Interest &interest,
                                                     const shared_ptr <pit::Entry> &pitEntry) {


        }
    }
}