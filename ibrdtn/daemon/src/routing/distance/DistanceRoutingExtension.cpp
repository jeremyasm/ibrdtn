#include "routing/distance/DistanceRoutingExtension.h"
#include "routing/QueueBundleEvent.h"
#include "core/NodeEvent.h"
#include "net/TransferCompletedEvent.h"
#include "net/TransferAbortedEvent.h"
#include "net/ConnectionEvent.h"
#include "core/Node.h"
#include "net/ConnectionManager.h"
#include "Configuration.h"
#include "core/BundleCore.h"

//----------------
#include "PendingInterestTable.h"
#include "ContentStorage.h"
#include "DistanceTable.h"
#include "routing/distance/DataEmTs.h"
#include <ibrdtn/utils/Clock.h>
//----------------

#include <ibrdtn/data/MetaBundle.h>
#include <ibrcommon/thread/MutexLock.h>
#include <ibrcommon/Logger.h>

#include <functional>
#include <list>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>

#include <stdlib.h>
#include <typeinfo>

namespace dtn
{
	namespace routing
	{
		const std::string DistanceRoutingExtension::TAG = "DistanceRoutingExtension";

		int itest = 0;  //for test, lyx

		//create the Distance Table
		DistanceTable dt;
		//create the Content Storage
		ContentStorage cs;
		//create the Pending Interest Table
		PendingInterestTable pit;

		DistanceRoutingExtension::DistanceRoutingExtension()
		{
			// write something to the syslog
			IBRCOMMON_LOGGER_TAG(DistanceRoutingExtension::TAG, info) << "Initializing distance routing module" << IBRCOMMON_LOGGER_ENDL;
		}

		DistanceRoutingExtension::~DistanceRoutingExtension()
		{
			join();
		}

		void DistanceRoutingExtension::eventDataChanged(const dtn::data::EID &peer) throw ()
		{
			// transfer the next bundle to this destination
			_taskqueue.push( new SearchNextBundleTask( peer ) );
		}

		void DistanceRoutingExtension::eventBundleQueued(const dtn::data::EID &peer, const dtn::data::MetaBundle &meta) throw ()
		{
			// new bundles trigger a recheck for all neighbors
			const std::set<dtn::core::Node> nl = dtn::core::BundleCore::getInstance().getConnectionManager().getNeighbors();

			//******************************************************************************************
			cout<<"********************"<<endl;
			cout<<"---- receive a Bundle ----"<<endl;
			itest++;
			cout<<"Bundle No."<<itest<<endl;

			dtn::data::Bundle bundle2 = dtn::core::BundleCore::getInstance().getStorage().get(meta);
			// Read from Primary Bundle Block
			cout<<"----- print Primary Bundle Block -----"<<endl;
			cout<<"Bundle-Flags: "<<bundle2.procflags.toString()<<endl;
			cout<<"Bundle-Destination: "<<bundle2.destination.getString()<<endl;
			cout<<"Bundle-Source: "<<bundle2.source.getString()<<endl;

			for (dtn::data::Bundle::const_iterator iter = bundle2.begin(); iter != bundle2.end(); ++iter) {

				// Payload Block
				try {
					const dtn::data::PayloadBlock &payload =
							dynamic_cast<const dtn::data::PayloadBlock&>(**iter);
					cout<<"-- print Payload Block --"<<endl;
					// Create payload attachment
					ibrcommon::BLOB::iostream data = payload.getBLOB().iostream();
					std::stringstream ss;
					ss << data->rdbuf();

				} catch(const std::bad_cast&) {};

				//DBlock
				try {
					const dtn::data::DBlock &ddblock =
							dynamic_cast<const dtn::data::DBlock&>(**iter);
					cout<<"-- print DBlock --"<<endl;
					cout<<"Bundle-Data Name: "<< ddblock.getDataName()<<endl;
					cout<<"Bundle-Type: " << ddblock.getType().get()<<endl;
					cout<<"Bundle-Dest Distance:  "<< ddblock.getDestDist().get() <<endl;

					cout<<"......"<<endl;
					cout<<"---- Searching in CS ----"<<endl;

					BundleString dataName817 = ddblock.getDataName(); //read dataName from DBlock of the recieved bundle

					std::map<dtn::data::BundleString, DataEmTs >::iterator iter_dataName;
					iter_dataName = cs._contentStorage.find(dataName817);
					if(iter_dataName != cs._contentStorage.end()){

						cout<<"The data is : "<< cs._contentStorage[dataName817]._data<<endl;
						cout<<"The eligible mark is : "<<cs._contentStorage[dataName817]._eligibleMark<<endl;
						cout<<"The timestamp is : "<<cs._contentStorage[dataName817]._timestamp.toString()<<endl;

					}
					else{  //Couldn't find the key, so just insert/add one new entry ...
						cout<<"Couldn't find the matching entry for * "<<dataName817<<"* !"<< endl;
					}
					cout<<"********************"<<endl;

					//---------------

					// Get EIDs
					if(ddblock.get(dtn::data::Block::BLOCK_CONTAINS_EIDS))
					{
						const Block::eid_list &eids = ddblock.getEIDList();
						for(Block::eid_list::const_iterator eidIt = eids.begin(); eidIt != eids.end(); eidIt++)
						{

						}
					}

					continue;
				} catch(const std::bad_cast&) {};

			}

			//*****************************************************************************************


			for (std::set<dtn::core::Node>::const_iterator iter = nl.begin(); iter != nl.end(); ++iter)
			{
				const dtn::core::Node &n = (*iter);

				if (n.getEID() != peer)
				{
					// trigger all routing modules to search for bundles to forward
					eventDataChanged(n.getEID());
				}
			}
		}

		void DistanceRoutingExtension::componentUp() throw ()
		{
			// reset the task queue
			_taskqueue.reset();

			//Some initialization of data structures
			cout<<"---------------- Initializing the Distance Routing Approach ------------------"<<endl;

			cout<<"......"<<endl;
			//clear the data structures
			dt._distanceTable.clear();
			cs._contentStorage.clear();
			pit._pendingInterestTable.clear();

			cout<<"---- Insert some data in Content Storage ----"<<endl;
			//enrty-1
			dtn::routing::DataEmTs det_test1;
			dtn::data::BundleString dataName_test1 = BundleString("DataName1"); //data name of the content entry
			det_test1._data = BundleString("data content for DataName1"); //data content of the content entry
			det_test1._eligibleMark = 1;   //0 -- ineligible, 1 -- eligible (default)
			det_test1._timestamp = dtn::utils::Clock::getTime();
			cs._contentStorage.insert(pair<dtn::data::BundleString, DataEmTs>(dataName_test1,det_test1));

			cout<<"-- content entry-1 --"<<endl;
			cout<<"data name | "<<dataName_test1<<endl;
			cout<<"data content | "<<det_test1._data<<endl;
			cout<<"eligible mark | "<<det_test1._eligibleMark<<endl;
			cout<<"timestamp | "<<det_test1._timestamp.toString()<<endl;


			//entry-2
			dtn::routing::DataEmTs det_test2;
			dtn::data::BundleString dataName_test2 = BundleString("DataName2"); //data name of the content entry
			det_test2._data = BundleString("data content for DataName2"); //data content of the content entry
			det_test2._eligibleMark = 1;   //0 -- ineligible, 1 -- eligible (default)
			det_test2._timestamp = dtn::utils::Clock::getTime();
			cs._contentStorage.insert(pair<dtn::data::BundleString, DataEmTs>(dataName_test2,det_test2));

			cout<<"-- content entry-2 --"<<endl;
			cout<<"data name | "<<dataName_test2<<endl;
			cout<<"data content | "<<det_test2._data<<endl;
			cout<<"eligible mark | "<<det_test2._eligibleMark<<endl;
			cout<<"timestamp | "<<det_test2._timestamp.toString()<<endl;

			//entry-3
			dtn::routing::DataEmTs det_test3;
			dtn::data::BundleString dataName_test3 = BundleString("DataName3"); //data name of the content entry
			det_test3._data = BundleString("data content for DataName3"); //data content of the content entry
			det_test3._eligibleMark = 1;   //0 -- ineligible, 1 -- eligible (default)
			det_test3._timestamp = dtn::utils::Clock::getTime();
			cs._contentStorage.insert(pair<dtn::data::BundleString, DataEmTs>(dataName_test3,det_test3));

			cout<<"-- content entry-3 --"<<endl;
			cout<<"data name | "<<dataName_test3<<endl;
			cout<<"data content | "<<det_test3._data<<endl;
			cout<<"eligible mark | "<<det_test3._eligibleMark<<endl;
			cout<<"timestamp | "<<det_test3._timestamp.toString()<<endl;

			cout<<"------------------------------------------------------------------------------"<<endl;
			cout<<"......"<<endl;

			// routine checked for throw() on 15.02.2013
			try {
				// run the thread
				start();
			} catch (const ibrcommon::ThreadException &ex) {
				IBRCOMMON_LOGGER_TAG(DistanceRoutingExtension::TAG, error) << "componentUp failed: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
			}
		}

		void DistanceRoutingExtension::componentDown() throw ()
		{
			try {
				// stop the thread
				stop();
				join();
			} catch (const ibrcommon::ThreadException &ex) {
				IBRCOMMON_LOGGER_TAG(DistanceRoutingExtension::TAG, error) << "componentDown failed: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
			}
		}

		const std::string DistanceRoutingExtension::getTag() const throw ()
		{
			return "distance";
		}

		void DistanceRoutingExtension::__cancellation() throw ()
		{
			_taskqueue.abort();
		}

		void DistanceRoutingExtension::run() throw ()
		{
			class BundleFilter : public dtn::storage::BundleSelector
			{
			public:
				BundleFilter(const NeighborDatabase::NeighborEntry &entry, const std::set<dtn::core::Node> &neighbors, const dtn::core::FilterContext &context, const dtn::net::ConnectionManager::protocol_list &plist)
				 : _entry(entry), _neighbors(neighbors), _plist(plist), _context(context)
				{};

				virtual ~BundleFilter() {};

				virtual dtn::data::Size limit() const throw () { return _entry.getFreeTransferSlots(); };

				virtual bool addIfSelected(dtn::storage::BundleResult &result, const dtn::data::MetaBundle &meta) const throw (dtn::storage::BundleSelectorException)
				{
					// check Scope Control Block - do not forward bundles with hop limit == 0
					if (meta.hopcount == 0)
					{
						return false;
					}

					// do not forward local bundles
					if ((meta.destination.getNode() == dtn::core::BundleCore::local)
							&& meta.get(dtn::data::PrimaryBlock::DESTINATION_IS_SINGLETON)
						)
					{
						return false;
					}

					// check Scope Control Block - do not forward non-group bundles with hop limit <= 1
					if ((meta.hopcount <= 1) && (meta.get(dtn::data::PrimaryBlock::DESTINATION_IS_SINGLETON)))
					{
						return false;
					}

					// do not forward bundles addressed to this neighbor,
					// because this is handled by neighbor routing extension
					if (_entry.eid == meta.destination.getNode())
					{
						return false;
					}

					// if this is a singleton bundle ...
					if (meta.get(dtn::data::PrimaryBlock::DESTINATION_IS_SINGLETON))
					{
						const dtn::core::Node n(meta.destination.getNode());

						// do not forward the bundle if the final destination is available
						if (_neighbors.find(n) != _neighbors.end())
						{
							return false;
						}
					}

					// do not forward bundles already known by the destination
					if (_entry.has(meta))
					{
						return false;
					}

					// update filter context
					dtn::core::FilterContext context = _context;
					context.setMetaBundle(meta);

					// check bundle filter for each possible path
					for (dtn::net::ConnectionManager::protocol_list::const_iterator it = _plist.begin(); it != _plist.end(); ++it)
					{
						const dtn::core::Node::Protocol &p = (*it);

						// update context with current protocol
						context.setProtocol(p);

						// execute filtering
						dtn::core::BundleFilter::ACTION ret = dtn::core::BundleCore::getInstance().evaluate(dtn::core::BundleFilter::ROUTING, context);

						if (ret == dtn::core::BundleFilter::ACCEPT)
						{
							// put the selected bundle with targeted interface into the result-set
							static_cast<RoutingResult&>(result).put(meta, p);
							return true;
						}
					}

					return false;
				};

			private:
				const NeighborDatabase::NeighborEntry &_entry;
				const std::set<dtn::core::Node> &_neighbors;
				const dtn::net::ConnectionManager::protocol_list &_plist;
				const dtn::core::FilterContext &_context;
			};

			// list for bundles
			RoutingResult list;

			// set of known neighbors
			std::set<dtn::core::Node> neighbors;

			while (true)
			{
				try {
					Task *t = _taskqueue.poll();
					std::auto_ptr<Task> killer(t);

					IBRCOMMON_LOGGER_DEBUG_TAG(DistanceRoutingExtension::TAG, 50) << "processing task " << t->toString() << IBRCOMMON_LOGGER_ENDL;

					try {
						try {
							SearchNextBundleTask &task = dynamic_cast<SearchNextBundleTask&>(*t);

							// clear the result list
							list.clear();

							// lock the neighbor database while searching for bundles
							{
								NeighborDatabase &db = (**this).getNeighborDB();

								ibrcommon::MutexLock l(db);
								NeighborDatabase::NeighborEntry &entry = db.get(task.eid, true);

								// check if enough transfer slots available (threshold reached)
								if (!entry.isTransferThresholdReached())
									throw NeighborDatabase::NoMoreTransfersAvailable();

								if (dtn::daemon::Configuration::getInstance().getNetwork().doPreferDirect()) {
									// get current neighbor list
									neighbors = dtn::core::BundleCore::getInstance().getConnectionManager().getNeighbors();
								} else {
									// "prefer direct" option disabled - clear the list of neighbors
									neighbors.clear();
								}

								// get a list of protocols supported by both, the local BPA and the remote peer
								const dtn::net::ConnectionManager::protocol_list plist =
										dtn::core::BundleCore::getInstance().getConnectionManager().getSupportedProtocols(entry.eid);

								// create a filter context
								dtn::core::FilterContext context;
								context.setPeer(entry.eid);
								context.setRouting(*this);

								// get the bundle filter of the neighbor
								BundleFilter filter(entry, neighbors, context, plist);

								// some debug
								IBRCOMMON_LOGGER_DEBUG_TAG(DistanceRoutingExtension::TAG, 40) << "search some bundles not known by " << task.eid.getString() << IBRCOMMON_LOGGER_ENDL;

								// query all bundles from the storage
								(**this).getSeeker().get(filter, list);
							}

							// send the bundles as long as we have resources
							for (RoutingResult::const_iterator iter = list.begin(); iter != list.end(); ++iter)
							{
								try {
									// transfer the bundle to the neighbor
									transferTo(task.eid, (*iter).first, (*iter).second);
								} catch (const NeighborDatabase::AlreadyInTransitException&) { };
							}
						} catch (const NeighborDatabase::NoMoreTransfersAvailable &ex) {
							IBRCOMMON_LOGGER_DEBUG_TAG(TAG, 10) << "task " << t->toString() << " aborted: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
						} catch (const NeighborDatabase::EntryNotFoundException &ex) {
							IBRCOMMON_LOGGER_DEBUG_TAG(TAG, 10) << "task " << t->toString() << " aborted: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
						} catch (const NodeNotAvailableException &ex) {
							IBRCOMMON_LOGGER_DEBUG_TAG(TAG, 10) << "task " << t->toString() << " aborted: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
						} catch (const dtn::storage::NoBundleFoundException &ex) {
							IBRCOMMON_LOGGER_DEBUG_TAG(TAG, 10) << "task " << t->toString() << " aborted: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
						} catch (const std::bad_cast&) { };
					} catch (const ibrcommon::Exception &ex) {
						IBRCOMMON_LOGGER_DEBUG_TAG(DistanceRoutingExtension::TAG, 20) << "task failed: " << ex.what() << IBRCOMMON_LOGGER_ENDL;
					}
				} catch (const std::exception &ex) {
					IBRCOMMON_LOGGER_DEBUG_TAG(DistanceRoutingExtension::TAG, 15) << "terminated due to " << ex.what() << IBRCOMMON_LOGGER_ENDL;
					return;
				}

				yield();
			}
		}

		/****************************************/

		DistanceRoutingExtension::SearchNextBundleTask::SearchNextBundleTask(const dtn::data::EID &e)
		 : eid(e)
		{ }

		DistanceRoutingExtension::SearchNextBundleTask::~SearchNextBundleTask()
		{ }

		std::string DistanceRoutingExtension::SearchNextBundleTask::toString()
		{
			return "SearchNextBundleTask: " + eid.getString();
		}
	}
}
