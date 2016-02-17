#pragma once
#include "iserde.h"
namespace DataKinesis {
	class IType {
	public:
		virtual void set(ISerializer &out, const  void *data, const Field &field) const = 0;
		virtual void get(IDeSerializer &in, void *data, const Field &field) const = 0;
	};
}