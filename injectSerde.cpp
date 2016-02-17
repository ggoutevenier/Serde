#include "csvserde.h"
#include "injectserde.h"
namespace DataKinesis {
	ISerializer *createSerializer_(std::ostream &out) { return new CsvSerializer(out); }
	IDeSerializer *createDeSerializer_(std::istream &in) { return new CsvDeSerializer(in); }
	void freeSerializer_(ISerializer *writer) { delete writer; }
	void freeDeSerializer_(IDeSerializer *reader) { delete reader; }
}