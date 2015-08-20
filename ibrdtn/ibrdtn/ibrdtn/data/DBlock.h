/*
 * DBlock.h
 *
 *  Created on: Jun 30, 2015
 *      Author: jeremy
 */

#include <ibrdtn/data/Block.h>
#include <ibrdtn/data/Number.h>
#include <ibrdtn/data/BundleString.h>
#include <ibrdtn/data/ExtensionBlock.h>

#ifndef DLOCK_H_
#define DLOCK_H_

namespace dtn
{
	namespace data
	{
		class DBlock : public dtn::data::Block
		{
		public:
			class Factory : public dtn::data::ExtensionBlock::Factory
			{
			public:
				Factory() : dtn::data::ExtensionBlock::Factory(DBlock::BLOCK_TYPE) {};
				virtual ~Factory() {};
				virtual dtn::data::Block* create();
			};

			static const dtn::data::block_t BLOCK_TYPE;

			DBlock();
			virtual ~DBlock();

			virtual dtn::data::Length getLength() const;
			virtual std::ostream &serialize(std::ostream &stream, dtn::data::Length &length) const;
			virtual std::istream &deserialize(std::istream &stream, const dtn::data::Length &length);

			void setVar1(dtn::data::Integer value);
			void setVar2(dtn::data::BundleString value);

			//added by lyx
			void setSrcDist(dtn::data::Integer value);
			void setDestDist(dtn::data::Integer value);
			void setType(dtn::data::Integer value);
			void setDataName(dtn::data::BundleString value);

			//void setSrcDist(int value);
			//void setDestDist(int value);
			//void setType(int value);

			//added by lyx 2015-7-2
			dtn::data::Integer getSrcDist();
			dtn::data::Integer getDestDist() const;
			dtn::data::Integer getType() const;
			dtn::data::BundleString getDataName() const;

			//int getSrcDist() const;
			//int getDestDist() const;
			//int getType() const;

		//private:
			dtn::data::Integer _var1;
			dtn::data::BundleString _var2;

			//added by lyx
			dtn::data::Integer _srcDist;
			dtn::data::Integer _destDist;
			dtn::data::Integer _type;
			dtn::data::BundleString _dataName;

			//int _srcDist;
			//int _destDist;
			//int _type;
		};

		/**
		 * This creates a static block factory
		 */
		static DBlock::Factory __DBlockFactory__;
	}
}

#endif /* DBLOCK_H_ */
