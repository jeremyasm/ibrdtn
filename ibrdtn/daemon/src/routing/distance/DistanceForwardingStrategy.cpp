/*
 * DistanceForwardingStrategy.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: root
 */

#include"routing/distance/DistanceForwardingStrategy.h"
#include"routing/distance/DistanceTable.h"
#include<map>
#include<string>

namespace dtn{
	namespace routing{


		DistanceForwardingStrategy::DistanceForwardingStrategy(){

		}

		DistanceForwardingStrategy::~DistanceForwardingStrategy(){

		}


		//get bundle's endpoint identifier...*************
		dtn::data::Integer getType(){
			return 0;   //Interest Packet
			//return 1; //Data Packet
		}

		dtn::data::BundleString getEndpointIdentifier(){
			return "identifier";
		}

		dtn::data::Integer getDistance(){
			return 2;
		}

		dtn::data::Timestamp getTimestamp(){
			return 0;
		}
		//*************************************************
		//How to get the fields of bundles??????


		int main(){

			//-------------------------------------------------
			string detect1;
			string detect2;

			//-------------------------------------------------
			// declare some variables to store the fields of bundle.
			string sourceSchemeOffset;
			string sourceSSPOffset;
			dtn::data::BundleString srcEID;
			string destinationSchemeOffset;
			string destinationSSPOffset;
			dtn::data::BundleString destEID;
			dtn::data::Timestamp creationTimestampTime;
			string creationTimestampSeqnum;
			string payloadData; //Data...
			dtn::data::Integer srcDist;
			dtn::data::Integer destDist;
			string bundleType;
			string dataName;

			string eligibleMark; //0 -- ineligible, 1 -- eligible

			//-------------------------------------------------

			//create the distance table
			DistanceTable dt;  //at this time, dt._distance table should be created ???



			//Listen to a new bundle coming .......
			while(detect1 == "there's a new bundle coming"){ //listen to a new bundle coming ...


			//read each field from the bundle .......
				sourceSchemeOffset = "";
				sourceSSPOffset = "";
				srcEID = "";
				destinationSchemeOffset = "";
				destinationSSPOffset = "";
				destEID = "";
				creationTimestampTime = 0;
				creationTimestampSeqnum = "";
				payloadData = "";
				srcDist = 0;
				destDist = 1;
				bundleType = "";
				dataName = "";

				eligibleMark = 0;



			//--------------- Distance Table ------------------

			/**
			 * Detect that if there's new bundle coming, {
			 * 	Every time when a new bundle comes to the node,
			 * 		detect if the distance table is full,
			 * 			if it's full, delete the oldest entry according to the timestamp,
			 * 			then,
			 * 				1. check the distance table, if the "source node endpoint identifier" already exist ?
			 * 				1.1 if it exists, check the timestamp, if the timestamp of the bundle is newer,
			 * 					if so, update the distance entry according to the bundle
			 * 					if not, abandon the bundle
			 * 				1.2 if it doesn't exist, add a new distance entry according to the bundle.
			 *
			 * 		}
			 */

			//if the distance table is full ??? How to detect if a map is full ??? make no sense ???  Skip!
			if(detect2 == "the Distance Table is full"){
				//delete the oldest entry ......
			}

			//read from the bundle
			//dtn::data::BundleString key = srcEID;//read endpoint identifier from the bundle
			DistanceAndTimestamp dnt;
			dnt._distance = srcDist; //read distance from the bundle
			dnt._timestamp = creationTimestampTime; //read timestamp from the bundle

			//check the distance table, if the "source node endpoint identifier" already exist ?
			//dt._distanceTable;
			//the _distanceTable in dt is already created ...

			std::map<dtn::data::BundleString, DistanceAndTimestamp >::iterator iter;
			iter = dt._distanceTable.find(srcEID);
			if(iter != dt._distanceTable.end()){

				//could find the key... compare and change ....
				//compare the timestamp .... if the bundle is fresher, update...
				if(dnt._timestamp >= dt._distanceTable[srcEID]._timestamp){
					dt._distanceTable[srcEID]._distance = dnt._distance;
				}
			}
			else{  //Couldn't find the key, so just insert/add one new entry ...

				dt._distanceTable.insert(pair<dtn::data::BundleString, DistanceAndTimestamp>(srcEID,dnt));
			}


			//confirm the bundle is interest or data
			if(bundleType == 0){
				//it's a interest bundle;
			}
			if(bundleType == 1){
				//it's a data bundle, it need to be forwarded to the requester... so we need to check if the node is eligible ...
				std::map<dtn::data::BundleString, DistanceAndTimestamp >::iterator iter_egb;
				iter_egb = dt._distanceTable.find(destEID);

				if(iter_egb != dt._distanceTable.end()){
								//could find the key... compare ...
								if(dt._distanceTable[destEID]._distance < destDist){
									eligibleMark = 1; //it's an eligible node
								}
				} //otherwise, eligibleMark is default value 0, which means it's an ineligibleMark.

			}


			//above is Distance Table Part

			//************************ Content Storage ****************************
			//check the type of the bunlde.... Data Packet or Interest Packet .....
			int type1 = getType();
			if(type1 == 0){ //The bundle is about Interest Packet ...
				/**check if there's entry matches the interest ???
				 * if so, return the matched data (here we need a return method!!! with data, data name, distance, destination node, source node ...)
				 * if not, store nothing, and go to Pending Interest Table.
				 */

			}
			if(type1 == 1){ //The bundle is about Data Packet ...

				//store the data into the CS,
				// if the node is eligible, turn to 3.   (How to confirm if the node is eligible. )

			}


			}


		}


	}
}

