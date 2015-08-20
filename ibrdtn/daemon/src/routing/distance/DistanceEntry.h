/*
 * DistanceEntry.h
 *
 *  Created on: 02-07-2015
 *      Author: Jeremy
 */


#ifndef DistanceEntry_H_
#define DistanceEntry_H_

#include "routing/NeighborDataset.h"
#include "routing/NodeHandshake.h"
#include <ibrdtn/data/EID.h>
#include <ibrcommon/thread/Mutex.h>
#include <map>

namespace dtn
{
	namespace routing
	{

		//class DistanceEntry: public NeighborDataSetImpl, public NodeHandshakeItem, public ibrcommon::Mutex {
		class DistanceEntry {

		public:
			DistanceEntry();
			~DistanceEntry(); //virtual

			//void setEndpointIdentifier(dtn::data::BundleString value);
			//void setDistance(dtn::data::Integer value);
			//void setTimestamp(dtn::data::Timestamp value);

			//dtn::data::BundleString getEndpointIdentifier();
			//dtn::data::Integer getDistance();
			//dtn::data::Timestamp getTimestamp();

			dtn::data::BundleString _endpointIdentifier;
			//?????????????????? if we need a DistanceAndTimestamp type variable here ???????????????????
			//DistanceAndTimestamp dnt;

		};

		class DistanceAndTimestamp{

		public:
			DistanceAndTimestamp();
			virtual ~DistanceAndTimestamp();

			//dtn::data::Integer _distance;
			int _distance;
			dtn::data::Timestamp _timestamp; //see dtn::data::Timestamp !!!!
		};
	} /* namespace routing */
} /* namespace dtn */
#endif /* DistanceEntry_H_ */

