/*
 * DistanceEntry.cpp
 *
 *  Created on: 02-07-2015
 *      Author: jeremy
 */

#include "DistanceEntry.h"

namespace dtn
{
	namespace routing
	{
		/**
		 *
		 * implementation of the DistanceEntry class
		 */

			DistanceEntry::DistanceEntry(){
			}

			virtual DistanceEntry::~DistanceEntry(){
			}

			DistanceAndTimestamp::DistanceAndTimestamp(){

			}

			virtual DistanceAndTimestamp::~DistanceAndTimestamp(){

			}


			/*
			void DistanceEntry::setEndpointIdentifier(dtn::data::BundleString value){

				_endpointIdentifier = value;
			}

			void DistanceEntry::setDistance(dtn::data::Integer value){

				_distance = value;

			}

			void DistanceEntry::setTimestamp(dtn::data::Timestamp value){

				_timestamp = value;

			}


			dtn::data::BundleString DistanceEntry::getEndpointIdentifier(){

				return _endpointIdentifier;
			}

			dtn::data::Integer DistanceEntry::getDistance(){

				return _distance;
			}

			dtn::data::Timestamp DistanceEntry::getTimestamp(){

				return _timestamp;
			}
			*/


	} /* namespace routing */
} /* namespace dtn */








