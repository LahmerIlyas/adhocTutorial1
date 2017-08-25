//
// Created by lahmer on 8/25/17.
//

#ifndef TUTORIAL1_BROADCASTSTRATEGY_H
#define TUTORIAL1_BROADCASTSTRATEGY_H

#include <fw/strategy.hpp>
#include "face/face.hpp"

#include <ns3-dev/ns3/ndnSIM/>
namespace nfd {
    namespace fw {

        class BroadCastStrategy : public Strategy {
        public:
            BroadCastStrategy(Forwarder& forwarder, const Name& name = STRATEGY_NAME);


            virtual void
            afterReceiveInterest(const Face& inFace, const Interest& interest,
                                 const shared_ptr<pit::Entry>& pitEntry) override;

        public:
            static const Name STRATEGY_NAME;
        };
    }
}

#endif //TUTORIAL1_BROADCASTSTRATEGY_H
