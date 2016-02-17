#pragma once
#include "iserde.h"
#include <string>
#include <iostream>
#include <vector>

namespace DataKinesis {
	class Record;
	class Field;
	class CsvSerializer : public ISerializer {
		const Record *record;
		typedef std::vector<std::string> values_t;
		values_t values;
		std::ostream &out;
		void writeHeader();
	public:
		CsvSerializer(std::ostream &out);
		~CsvSerializer();
		virtual void open(const Record &record);
		virtual void close();
		virtual void setRecord();
		virtual void set(const void *data);
	private:
		template<class T>
		void set_(T data, const Field &field);
		virtual void set(const bool &data, const Field &field);
		virtual void set(const char &data, const Field &field);
		virtual void set(const std::string &data, const Field &field);
		virtual void set(const boost::int16_t &data, const Field &field);
		virtual void set(const boost::int32_t &data, const Field &field);
		virtual void set(const boost::int64_t &data, const Field &field);
		virtual void set(const boost::uint8_t &data, const Field &field);
		virtual void set(const boost::uint16_t &data, const Field &field);
		virtual void set(const boost::uint32_t &data, const Field &field);
		virtual void set(const boost::uint64_t &data, const Field &field);
		virtual void set(const float &data, const Field &field);
		virtual void set(const double &data, const Field &field);
	};

	class CsvDeSerializer : public IDeSerializer {
	public:
		CsvDeSerializer(std::istream &in);
		~CsvDeSerializer();
		virtual void open(const Record &record);
		void close();
		virtual bool next();
		virtual void get(bool &data, const Field &field);
		virtual void get(std::string &data, const Field &field);
		virtual void get(char &data, const Field &field);
		virtual void get(boost::int16_t &data, const Field &field);
		virtual void get(boost::int32_t &data, const Field &field);
		virtual void get(boost::int64_t &data, const Field &field);
		virtual void get(boost::uint16_t &data, const Field &field);
		virtual void get(boost::uint32_t &data, const Field &field);
		virtual void get(boost::uint64_t &data, const Field &field);
		virtual void get(float &data, const Field &field);
		virtual void get(double &data, const Field &field);
		virtual void get(void *data);
	private:
		void readHeader();
		template<class T>void get_(T &data, const Field &field);
		std::istream &in;
		const Record *record;
		typedef std::vector<std::string> values_t;
		values_t values;
		std::vector<unsigned int> transform;
	};
}