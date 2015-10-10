#ifndef DISTANCEROUTINGEXTENSION_H_
#define DISTANCEROUTINGEXTENSION_H_

#include "core/Node.h"

#include "routing/RoutingExtension.h"
#include "routing/NeighborDatabase.h"

#include <ibrdtn/data/Block.h>
#include <ibrdtn/data/SDNV.h>
#include <ibrdtn/data/BundleString.h>

#include <ibrcommon/thread/Queue.h>

#include <list>
#include <queue>

namespace dtn
{
	namespace routing
	{
		class DistanceRoutingExtension : public RoutingExtension, public ibrcommon::JoinableThread
		{
			static const std::string TAG;
			//int itest = 0;  //for test, lyx

		public:
			DistanceRoutingExtension();
			virtual ~DistanceRoutingExtension();

			virtual const std::string getTag() const throw ();

			virtual void eventDataChanged(const dtn::data::EID &peer) throw ();

			virtual void eventBundleQueued(const dtn::data::EID &peer, const dtn::data::MetaBundle &meta) throw ();

			void componentUp() throw ();
			void componentDown() throw ();

		protected:
			void run() throw ();
			void __cancellation() throw ();

		private:
			class Task
			{
			public:
				virtual ~Task() {};
				virtual std::string toString() = 0;
			};

			class SearchNextBundleTask : public Task
			{
			public:
				SearchNextBundleTask(const dtn::data::EID &eid);
				virtual ~SearchNextBundleTask();

				virtual std::string toString();

				const dtn::data::EID eid;
			};

			/**
			 * hold queued tasks for later processing
			 */
			ibrcommon::Queue<DistanceRoutingExtension::Task* > _taskqueue;
		};
	}
}

#endif /* EPIDEMICROUTINGEXTENSION_H_ */
