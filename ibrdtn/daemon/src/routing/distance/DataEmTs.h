/*
 * DataEmTs.h
 *
 *  Created on: Aug 12, 2015
 *      Author: root
 */

#ifndef IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DATAEMTS_H_
#define IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DATAEMTS_H_

#include <ibrdtn/data/BundleString.h>


namespace dtn
{
	namespace routing
	{

		//A data structure... Data, Eligible Mark, Timestamp
		class DataEmTs{

		public:
			DataEmTs();
			virtual ~DataEmTs();

			dtn::data::BundleString _data;   //need modified ... to store real data, but for test, it's ok now.
			//dtn::data::Integer _eligibleMark;
			int _eligibleMark;
			dtn::data::Timestamp _timestamp; //see dtn::data::Timestamp !!!!
		};
	} /* namespace routing */
} /* namespace dtn */



#endif /* IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_DATAEMTS_H_ */
