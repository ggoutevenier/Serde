#include "csvserde.h"
#include "record.h"
#include <boost/algorithm/string/join.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
namespace DataKinesis {
	void CsvSerializer::writeHeader() {
		values.resize(record->size());
		if (record->size() == 0) {
			throw std::runtime_error("Record has no fields");
		}
		else {
			int i = 0;
			for (Record::const_iterator it = record->begin(); it != record->end(); ++it)
				values.at(i++) = it->getName();
			setRecord();
		}
	}

	CsvSerializer::CsvSerializer(std::ostream &out) :out(out) {}
	CsvSerializer::~CsvSerializer() { close(); }
	void CsvSerializer::open(const Record &record) {
		this->record = &record;
		writeHeader();
	}
	void CsvSerializer::close() {}
	void CsvSerializer::setRecord() {
		if (!values.empty())
			out << boost::algorithm::join(values, ",") << std::endl;
	}

	void CsvSerializer::set(const void *data) {
		if (record == 0)
			throw std::runtime_error("Need to open record");
		record->set(*this, data);
	}

	template<class T> void CsvSerializer::set_(T data, const Field &field) {
		values.at(field.getPosition()) = boost::lexical_cast<std::string>(data);
	}
	void CsvSerializer::set(const bool &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const char &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const std::string &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::int16_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::int32_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::int64_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::uint8_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::uint16_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::uint32_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const boost::uint64_t &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const float &data, const Field &field) { set_(data, field); }
	void CsvSerializer::set(const double &data, const Field &field) { set_(data, field); }


	CsvDeSerializer::CsvDeSerializer(std::istream &in) :in(in) {}
	CsvDeSerializer::~CsvDeSerializer() { close(); }
	void CsvDeSerializer::open(const Record &record) {
		this->record = &record;
		readHeader();
	}
	void CsvDeSerializer::close() {}
	bool CsvDeSerializer::next() {
		std::string line;
		bool rtn = false;
		values.clear();
		std::getline(in, line);
		if (!line.empty()) {
			rtn = true;
			typedef boost::tokenizer<boost::escaped_list_separator<char>> Tok;
			for (std::string value : Tok(line))
				values.push_back(value);
		}
		return rtn;
	}
	void CsvDeSerializer::get(bool &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(std::string &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(char &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::int16_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::int32_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::int64_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::uint16_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::uint32_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(boost::uint64_t &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(float &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(double &data, const Field &field) { get_(data, field); }
	void CsvDeSerializer::get(void *data) { record->get(*this, data); }

	void CsvDeSerializer::readHeader() {
		if (!next())
			std::runtime_error("Error reading header");
		transform.resize(record->size());
		for (Record::const_iterator fit = record->begin(); fit != record->end(); ++fit) {
			values_t::const_iterator vit = std::find(values.begin(), values.end(), fit->getName());
			unsigned int i, j;
			i = fit->getPosition();
			if (vit == values.end())
				j = 0;
			else
				j = std::distance(values.cbegin(), vit) + 1;

			transform.at(i) = j;
		}
	}

	template<class T>
	void CsvDeSerializer::get_(T &data, const Field &field) {
		unsigned int column = field.getPosition();
		if (values.size() <= column)
			throw std::runtime_error("No data");
		unsigned int i = transform.at(column);
		if (i != 0)
			data = boost::lexical_cast<T>(values.at(i - 1));
	}

}