/*
 * PendingInterestTable.h
 *
 *  Created on: Jul 3, 2015
 *      Author: jeremy
 */

#ifndef IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_PENDINGINTERESTTABLE_H_
#define IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_PENDINGINTERESTTABLE_H_

#include "routing/distance/PendingInterestEntry.h"
#include <ibrdtn/data/BundleString.h>
#include <map>
#include <list>

namespace dtn
{
	namespace routing
	{
		class PendingInterestTable{

		public:
			PendingInterestTable();
			virtual ~PendingInterestTable();


			std::map<dtn::data::BundleString, std::list<dtn::data::BundleString> > _pendingInterestTable;

		};
	}

}

#endif /* IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_PENDINGINTERESTTABLE_H_ */
