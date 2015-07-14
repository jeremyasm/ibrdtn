/*
 * DistanceTable.h
 *
 *  Created on: Jul 2, 2015
 *      Author: jeremy
 */

#ifndef IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DISTANCETABLE_H_
#define IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DISTANCETABLE_H_


#include <vector>
#include <map>

namespace dtn
{
	namespace routing
	{
		class DistanceTable{

		public:
			DistanceTable();
			virtual ~DistanceTable();


			std::map<dtn::data::BundleString, DistanceAndTimestamp > _distanceTable;

		};
	}

}





#endif /* IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DISTANCETABLE_H_ */
