#pragma once
#include "iserde.h"
#include <memory>
namespace DataKinesis {
	typedef std::shared_ptr<DataKinesis::ISerializer> SerializerHandle;
	typedef std::shared_ptr<DataKinesis::IDeSerializer> DeSerializerHandle;
	extern ISerializer *createSerializer_(std::ostream &out);
	extern IDeSerializer *createDeSerializer_(std::istream &in);
	extern void freeSerializer_(ISerializer *writer);
	extern void freeDeSerializer_(IDeSerializer *reader);
	inline SerializerHandle makeSerializer(std::ostream &out) {
		return SerializerHandle(createSerializer_(out), freeSerializer_);
	}
	inline DeSerializerHandle makeDeSerializer(std::istream &in) {
		return DeSerializerHandle(createDeSerializer_(in), freeDeSerializer_);
	}
}