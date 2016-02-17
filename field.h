#pragma once
#include "type.h"
namespace DataKinesis {
	/*! offsets void pointer before calling types serde functions*/
	class Field {
		std::string name; /*!< name of field*/
		size_t offset; /*!< mempry address offset from base */
		unsigned int position; /*!< position within the record */
		IType &type; /*!< type class */
		void *offset_(void *data) const { return (void*)(offset + (size_t)data); } /*!< member function to offset address from base*/
		const void *offset_(const void *data) const { return (const void*)(offset + (size_t)data); } /*!< member function to offset address from base*/
	public:
		Field(std::string name, size_t offset, IType &type, size_t position) :name(name), offset(offset), type(type), position(position) {}
		Field(const Field &field) : name(field.name), offset(field.offset), type(field.type), position(field.position) {}
		~Field() {};
		void set(ISerializer &out, const  void *data) const { type.set(out, offset_(data), *this); } /*!< serialization member function*/
		void get(IDeSerializer &in, void *data) const { type.get(in, offset_(data), *this); } /*!< deserialization member function */
		std::string getName() const { return name; }
		unsigned int getPosition() const { return position; }
		/*! used by std::find_if to see if field name is already in a stl container*/
		bool operator()(const Field &a) const { return getName().compare(a.getName()) == 0; }
	};
}