/*
 * ContentStorage.h
 *
 *  Created on: Jul 2, 2015
 *      Author: jeremy
 */

#ifndef IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGE_H_
#define IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGE_H_

#include <vector>
#include <map>
#include <string>
#include <ibrdtn/data/BundleString.h>
#include "routing/distance/ContentStorageEntry.h"
#include "routing/distance/DataEmTs.h"

namespace dtn
{
	namespace routing
	{
		class ContentStorage{

		public:
			ContentStorage();
			//virtual ~ContentStorage();
			~ContentStorage();

			std::map<dtn::data::BundleString, dtn::routing::DataEmTs > _contentStorage;
			//std::map<std::string, DataET > _contentStorage;

		};
	}

}



#endif /* IBRDTN_DAEMON_SRC_ROUTING_DISTANCE_CONTENTSTORAGE_H_ */
