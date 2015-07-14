/*
 * DistanceTable.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: jeremy
 */


#include <vector>
#include <map>

namespace dtn
{
	namespace routing
	{
		void DistanceTable(){

		}

		virtual void  ~DistanceTable(){

		}


		std::map<dtn::data::BundleString, DistanceAndTimestamp > _distanceTable;


	}

}

