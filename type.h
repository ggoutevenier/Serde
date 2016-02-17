#pragma once
#include "itype.h"
namespace DataKinesis {
	/*! recasts void pointer to correct data type and calls serde
	*/
	template<class T>
	class Type : public IType {
		T &typed_(void *v) const { return *(T *)v; }
		const T &typed_(const void *v) const { return *(const T *)v; }
	public:
		void set(ISerializer &writer, const  void *data, const Field &field) const { writer.set(typed_(data), field); }
		void get(IDeSerializer &reader, void *data, const Field &field) const { reader.get(typed_(data), field); }
	};
}