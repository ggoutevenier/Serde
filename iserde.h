#pragma once
#include <boost/cstdint.hpp>
#include <string>

namespace DataKinesis {
	class Record;
	class Field;
	class ISerializer {
	public:
		virtual void set(const bool &data, const Field &field) = 0;
		virtual void set(const std::string &data, const Field &field) = 0;
		virtual void set(const char &data, const Field &field) = 0;
		virtual void set(const boost::int16_t &data, const Field &field) = 0;
		virtual void set(const boost::int32_t &data, const Field &field) = 0;
		virtual void set(const boost::int64_t &data, const Field &field) = 0;
		virtual void set(const boost::uint8_t &data, const Field &field) = 0;
		virtual void set(const boost::uint16_t &data, const Field &field) = 0;
		virtual void set(const boost::uint32_t &data, const Field &field) = 0;
		virtual void set(const boost::uint64_t &data, const Field &field) = 0;
		virtual void set(const float &data, const Field &field) = 0;
		virtual void set(const double &data, const Field &field) = 0;
		virtual void setRecord() = 0;
		ISerializer() {}
		virtual ~ISerializer() {}
		virtual void open(const Record &record) = 0;
		template<class T> void open() { return open(MetaData<T>::record()); }
		virtual void close() = 0;
		virtual void set(const void *data) = 0;
	};

	class IDeSerializer
	{
	public:
		IDeSerializer() {}
		virtual ~IDeSerializer() {}
		virtual void close() = 0;
		virtual bool next() = 0;
		virtual void open(const Record &record) = 0;
		template<class T> void open() { return open(MetaData<T>::record()); }
		virtual void get(bool &data, const Field &field) = 0;
		virtual void get(std::string &data, const Field &field) = 0;
		virtual void get(char &data, const Field &field) = 0;
		virtual void get(boost::int16_t &data, const Field &field) = 0;
		virtual void get(boost::int32_t &data, const Field &field) = 0;
		virtual void get(boost::int64_t &data, const Field &field) = 0;
		virtual void get(boost::uint16_t &data, const Field &field) = 0;
		virtual void get(boost::uint32_t &data, const Field &field) = 0;
		virtual void get(boost::uint64_t &data, const Field &field) = 0;
		virtual void get(float &data, const Field &field) = 0;
		virtual void get(double &data, const Field &field) = 0;
		virtual void get(void *data) = 0;
	};
}