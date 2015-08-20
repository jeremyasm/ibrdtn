/*
 * ContentStorageEntry.h
 *
 *  Created on: Jul 2, 2015
 *      Author: jeremy
 */

#ifndef IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGEENTRY_H_
#define IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGEENTRY_H_

#include "routing/NeighborDataset.h"
#include "routing/NodeHandshake.h"
#include <ibrdtn/data/EID.h>
#include <ibrcommon/thread/Mutex.h>
#include <map>

namespace dtn
{
	namespace routing
	{

		class ContentStorageEntry { //try to change the class name

		public:
			ContentStorageEntry();
			//virtual ~ContentStorageEntry();
			~ContentStorageEntry();

			dtn::data::BundleString _dataName;
			//DataET det;



		};

		/*
		//A data structure... Data, Eligible Mark, Timestamp
		class DataET{

		public:
			DataET();
			virtual ~DataET();

			dtn::data::BundleString _data;   //need modified ... to store real data, but for test, it's ok now.
			dtn::data::Integer _eligibleMark;
			dtn::data::Timestamp _timestamp; //see dtn::data::Timestamp !!!!
		};

		*/


	} /* namespace routing */
} /* namespace dtn */



#endif /* IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGEENTRY_H_ */
