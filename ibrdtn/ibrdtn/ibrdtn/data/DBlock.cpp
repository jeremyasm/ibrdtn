/*
 * DBlock.cpp
 *
 *  Created on: 2015-06-10
 *      Author: jeremy
 */


#include "DBlock.h"

namespace dtn
{
	namespace data
	{
		const dtn::data::block_t DBlock::BLOCK_TYPE = 233;

		dtn::data::Block* DBlock::Factory::create()
		{
			return new DBlock();
		}

		DBlock::DBlock()
		 : dtn::data::Block(DBlock::BLOCK_TYPE)
		{
		}

		DBlock::~DBlock()
		{
		}

		void DBlock::setVar1(dtn::data::Integer value)
		{
			_var1 = value;
		}

		void DBlock::setVar2(dtn::data::BundleString value)
		{
			_var2 = value;
		}

		//added by lyx
		void DBlock::setSrcDist(dtn::data::Integer value)
		{
			_srcDist = value;
		}

		void DBlock::setDestDist(dtn::data::Integer value)
		{
			_destDist = value;
		}

		void DBlock::setType(dtn::data::Integer value)
		{
			_type = value;
		}

		void DBlock::setDataName(dtn::data::BundleString value)
		{
			_dataName = value;
		}
		//*************





		dtn::data::Length DBlock::getLength() const
		{
			//return _var1.getLength() + _var2.getLength();
			return _srcDist.getLength() + _destDist.getLength() + _type.getLength() + _dataName.getLength();
		}

		std::ostream& DBlock::serialize(std::ostream &stream, dtn::data::Length &length) const
		{
			//stream << _var1 << _var2;
			stream << _srcDist << _destDist << _type << _dataName;
			length += getLength();
			return stream;
		}

		std::istream& DBlock::deserialize(std::istream &stream, const dtn::data::Length&)
		{
			//stream >> _var1 >> _var2;
			stream >> _srcDist >> _destDist >> _type >> _dataName;
			return stream;
		}
	}
}



