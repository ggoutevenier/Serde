#ifndef RECORD_H_
#define RECORD_H_
#include <string>
#include <list>
#include <vector>
#include <boost/cstdint.hpp>
#include <algorithm>
#include "field.h"
namespace DataKinesis {
	/*! record class
	holds list of fields 
	*/
	class Record : public std::list<Field > {
		std::string name;
	public:
		void setName(std::string name) { this->name = name; }
		Record():name("") {}
		~Record() {	}
		void set(ISerializer &writer, const void *data) const { /*!< serialization member function*/
			for (const_iterator it = begin(); it != end(); ++it) 
				it->set(writer, data);
			writer.setRecord();
		}
		
		void get(IDeSerializer &reader, void *data) const { /*!< deserialization function */
			for (const_iterator it = begin(); it != end(); ++it)
				it->get(reader, data);
		}
		/*! add new field to record*/
		template<class S,class T>
		Field &addField(const S &base, const T &offset, const std::string name) {
			static Type<T> type;
			size_t i = (size_t)&offset - (size_t)&base;
			if (i >= sizeof(S)) // bound check
				throw std::runtime_error("Bounds error " + name);
			Field field(name, i, type,size());
			if (std::find_if(begin(), end(), field) != end()) // make sure field is only added once
				throw std::runtime_error("Field already added " + name);
			push_back(field);
			return back();
		}
	};

	// Metaclass used to hold the static mapping c structure to meta record
	// assumes the actual mapping is in a function called makeRecord(T &,Record &)
	template<class T>
	class MetaData {
		static Record r;
	public:
		static const Record &record() {	
			if (r.size() == 0) {
				makeRecord(T(), r);
			}
			return r;
		}
	};
	template<class T> Record MetaData<T>::r;
}
#endif 
