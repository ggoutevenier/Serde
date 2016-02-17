#include "record.h"
#include <sstream>
#include <iostream>
#include "injectserde.h"
#include <memory>
#include "structure.h"
using namespace DataKinesis;
// create mapping of metadata
void makeRecord(const Test &data, Record &record) {
	record.setName("Test");
	record.addField(data, data.married, "married");
	record.addField(data, data.bignumber, "bignum");
	record.addField(data, data.zip, "postal_code");
	record.addField(data, data.firstName, "first_name");
	record.addField(data, data.lastName, "last_name");
	record.addField(data, data.age, "age");
	record.addField(data, data.income, "income");
	record.addField(data, data.networth, "networth");
}
// create data
void mockData(std::iostream &io) {
	io << "age,first_name,last_name,married,postal_code,bignum,income,networth" << std::endl;
	io << "25,Joe,Smith,0,11050,123456789,49999.99,1e10" << std::endl;
	io << "30,Jane,Doe,1,11093,9876543210,99999,1e11" << std::endl;
}
int main() {
	try {
		typedef std::list<Test> DataList;
		DataList dataList;
		std::stringstream ss;
		//inject deserializer
		DeSerializerHandle reader = makeDeSerializer(ss);

		mockData(ss);
		
		reader->open<Test>();
		// read test data from stream into list using metadata record
		while (reader->next()) {
			Test test;
			reader->get(&test);
			dataList.push_back(test);
		}

		SerializerHandle writer = makeSerializer(std::cout);
		// output list to display
		writer->open<Test>();
		for (DataList::const_iterator it = dataList.begin(); it != dataList.end();++it)
			writer->set(&*it);

	}
	catch (std::exception &e) {
		std::cout << e.what();
		return 1;
	}
	return 0;
}