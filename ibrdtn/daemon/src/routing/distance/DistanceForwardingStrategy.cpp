/*
 * DistanceForwardingStrategy.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: root
 */

#include"routing/distance/DistanceForwardingStrategy.h"
#include"routing/distance/DistanceTable.h"
#include"routing/distance/ContentStorage.h"
#include"routing/distance/PendingInterestTable.h"
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


		void createANewBundle(dtn::data::BundleString srcEID, dtn::data::BundleString destEID, dtn::data::Integer srcDist, dtn::data::Integer destDist,
				dtn::data::Integer bundleType, dtn::data::BundleString dataName){
			/**
			 * TODO
			 * how to create a new bundle, in this case, the input argument should be srcEID, destEID, srcDist, destDist, bundle Type, dataName, data ...
			 */
		}

		void broadcast(){
			//TODO
		}

		void flood(){
			/**
			 * TODO
			 */
		}


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
			dtn::data::BundleString payloadData; //Data ........... for testing, it would be easy ...
			dtn::data::Integer srcDist;
			dtn::data::Integer destDist;
			dtn::data::Integer bundleType;
			dtn::data::BundleString dataName;

			string eligibleMark; //0 -- ineligible, 1 -- eligible

			//-------------------------------------------------

			//create the Distance Table
			DistanceTable dt;  //at this time, dt._distanceTable is created now ???

			//create the Content Storage
			ContentStorage cs;

			//--------- on ndndtn1 -----------
			DataEmTs det_test2;
			dtn::data::BundleString dataName_test2 = "THREENODESTEST";
			det_test2._data = "it's a three nodes test!";
			det_test2._eligibleMark = 1;   //0 -- ineligible, 1 -- eligible
			det_test2._timestamp = creationTimestampTime;
			cs._contentStorage.insert(pair<dtn::data::BundleString, DataEmTs>(dataName_test2,det_test2));
			//---------------------------------


			//create the Pending Interest Table
			PendingInterestTable pit; //pit._pendingInterestTable is created now ???


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
				bundleType = 0;
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
				//it's an interest bundle;
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

			//************************ 2. Content Storage ****************************
			//check the type of the bunlde.... Data Packet or Interest Packet .....
			int type1 = getType();
			if(type1 == 0){ //The bundle is Interest Packet ...
				/**check if there's entry matches the interest ???
				 * if so, return the matched data (here we need a return method!!! with data, data name, distance, destination node, source node ...)
				 * if not, store nothing, and go to Pending Interest Table.
				 */

				std::map<dtn::data::BundleString, DataET >::iterator iter_dataName;
				iter_dataName = cs._contentStorage.find(dataName);
				if(iter != cs._contentStorage.end()){
					//could find the dataName... return the data ....
					//cs._contentStorage[dataName]._data

					//create the new bundle ... data bundle. with new src and dest ... distance ... timestamp ... at each hop ... broadcast ... not flood ...
					createANewBundle(srcEID, destEID, srcDist, destDist,
									bundleType, dataName);
				}
				else{  //Couldn't find the key, so just insert/add one new entry ...

				}

			}
			if(type1 == 1){ //The bundle is Data Packet ...

				//store the data into the CS,
				// if the node is eligible, turn to 3.   (How to confirm if the node is eligible. )
				DataET det;
				det._data = payloadData;
				det._eligibleMark = eligibleMark;
				det._timestamp = creationTimestampTime;
				//cs._contentStorage.insert(pair<dtn::data::BundleString, DataET>(srcEID,det));
				cs._contentStorage.insert(pair<dtn::data::BundleString, DataET>(dataName,det));
				if(eligibleMark == 1){
					//switch to 3. PIT.
				}

			}


			//****************** 3. Pending Interest Table ****************************
			if(type1 == 0){ //The bundle is Interest Packet
				//...Mark...
				/**
				 * check the PIT to see if there already exists entry for the same interest ...  aka dataName
				 * if so, update the entry with the source node identifier of the packet and stop flooding.
				 */

				//------------------
				std::map<dtn::data::BundleString, std::list<dtn::data::BundleString> >::iterator iter_pit;

				//iter_pit = dt._distanceTable.find(srcEID);
				iter_pit = pit._pendingInterestTable.find(dataName);
					if(iter_pit != pit._pendingInterestTable.end()){
								//could find the dataName!!!
								//add srcEID ??? to guarantee that there're not same elements existing in the list ???

								//To check if there already exists the srcEID in the list
								list<dtn::data::BundleString>::iterator iter_srcEIDList;
								int flag_srcEID = 0;
								for(iter_srcEIDList = pit._pendingInterestTable[dataName].begin(); iter_srcEIDList != pit._pendingInterestTable[dataName].end(); ++iter_srcEIDList){
									if(*iter_srcEIDList == srcEID) {flag_srcEID = 1; break;}
								}
								if (flag_srcEID == 0){ //there doesn't exist the srcEID in the list !  add one entry in List ...
									pit._pendingInterestTable[dataName].push_back(srcEID);
								}
					}
					else{  //Couldn't find the dataName, so just insert/add one new entry in Map ...
						list <dtn::data::BundleString> newSrcEIDList;
						newSrcEIDList.push_front(srcEID);
						pit._pendingInterestTable.insert(pair<dtn::data::BundleString, list<dtn::data::BundleString>>(dataName,newSrcEIDList));
					}
				//------------------
				//How to deal with the Interest Bundle to next hop ??? TODO

			}
			if(type1 == 1){ //The bundle is Data Packet
				/**
				 * checks the PIT, if there already exists entry for the interest of data
				 * If so, send the data bundle to next hop according to the in-records collection of the X entry.
				 * next hop or the source node(of interest bundle) ???
				 */
				std::map<dtn::data::BundleString, std::list<dtn::data::BundleString> >::iterator iter_pit_dataName;

				iter_pit_dataName = pit._pendingInterestTable.find(dataName);
				if(iter_pit_dataName != pit._pendingInterestTable.end()){
					//could find the dataName!!!

					pit._pendingInterestTable[dataName];  // this represents

					//To check if there already exists the srcEID in the list
					list<dtn::data::BundleString>::iterator iter_srcEIDList;
					int flag_srcEID = 0;
					for(iter_srcEIDList = pit._pendingInterestTable[dataName].begin(); iter_srcEIDList != pit._pendingInterestTable[dataName].end(); ++iter_srcEIDList){
						createANewBundle(srcEID, *iter_srcEIDList, srcDist, destDist,
															bundleType, dataName);
						broadcast();
					}

				}
				else{  //Couldn't find the dataName, no such a possibility ???


				}

			}





			}


		}


	}
}

