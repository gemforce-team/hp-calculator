#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;

class field
{
	public:
	pair<char, int> name;
	int wavesNum;
	int giantWavesNum;
	int swarmlingWavesNum;
	int hpFirstWave;
	double hpMult;
	int armorFirstWave;
	double armorIncrement;
	double rainChance;
	double snowChance;
};

ostream& operator<< (ostream& str, field& fld)
{
	str << "name "              << fld.name.first << fld.name.second << endl;
	str << "wavesNum "          << fld.wavesNum                      << endl;
	str << "giantWavesNum "     << fld.giantWavesNum                 << endl;
	str << "swarmlingWavesNum " << fld.swarmlingWavesNum             << endl;
	str << "hpFirstWave "       << fld.hpFirstWave                   << endl;
	str << "hpMult "            << fld.hpMult                        << endl;
	str << "armorFirstWave "    << fld.armorFirstWave                << endl;
	str << "armorIncrement "    << fld.armorIncrement                << endl;
	str << "rainChance "        << fld.rainChance                    << endl;
	str << "snowChance "        << fld.snowChance                    << endl;
	return str;
}

ostream& operator<< (ostream& str, vector<field>& fields)
{
	for (size_t i=0; i != fields.size(); ++i) {
		str << fields[i] << endl;
	}
	return str;
}

#define nnf 9
#define nvf 23
#define nhx 25

void write_tableHFW(vector<field> fields)
{
	string table[nvf][nhx];
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		int col = (int)(fld.name.first - 'A');
		int row = fld.name.second-1;
		string& entry=table[row][col];
		if (fld.name.first != 'V') {
			entry = "=if(Hp!C16=2,333," + to_string(fld.hpFirstWave);
			entry += "+40*Hp!C16)";
		}
		else entry = to_string(fld.hpFirstWave);
	}
	for (int i=0; i<nvf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableAFW(vector<field> fields)
{
	string table[nvf][nhx];
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		int col = (int)(fld.name.first - 'A');
		int row = fld.name.second-1;
		string& entry=table[row][col];
		
		entry = "=" + to_string(fld.hpFirstWave);
		entry += "+15*Hp!C16";
	}
	for (int i=0; i<nvf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableHM(vector<field> fields)
{
	double table[nvf][nhx]={1};
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		int col = (int)(fld.name.first - 'A');
		int row = fld.name.second-1;
		double& entry=table[row][col];
		
		entry = fld.hpMult;
	}
	for (int i=0; i<nvf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << setprecision(5) << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableAI(vector<field> fields)
{
	double table[nvf][nhx]={1};
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		int col = (int)(fld.name.first - 'A');
		int row = fld.name.second-1;
		double& entry=table[row][col];
		
		entry = fld.armorIncrement;
	}
	for (int i=0; i<nvf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << setprecision(5) << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableWN(vector<field> fields)
{
	string table[nvf][nhx];
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		int col = (int)(fld.name.first - 'A');
		int row = fld.name.second-1;
		string& entry=table[row][col];
		if (fld.name.first != 'V')
			entry = "=ceiling(" + to_string(fld.wavesNum) + "*(1+0.5*Hp!C16),1)+Hp!C18+Hp!C19+Hp!C20";
		else entry = to_string(fld.wavesNum);
	}
	for (int i=0; i<nvf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableH(vector<field> fields)
{
	string table[nnf][nhx];
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		if (fld.name.first != 'V') {
			int col = (int)(fld.name.first - 'A');
			int row = fld.name.second-1;
			string fn = fld.name.first + to_string(fld.name.second);
			
			string& entry=table[row][col];
			
			entry  = "=round(if(C17>wavesNum!" + fn;
			entry += ",(HpFirstWave!" + fn;
			entry += "*(((HpMult!" + fn;
			entry += "-0.003)*(1+0.02*C16)*(1+0.007*C18))^(C17-1))+6)*1.12*1.042^(C17-1-wavesNum!" + fn;
			entry += ")+(C17-1-wavesNum!" + fn;
			entry += ")*10,HpFirstWave!" + fn;
			entry += "*(((HpMult!" + fn;
			entry += "-0.003)*(1+0.02*C16)*(1+0.007*C18))^(C17-1)))*K16*if(C21=0,1,if(C21=1,0.187,5/C22*0.67*37.3*(1+K17))))";
			
		}
	}
	for (int i=0; i<nnf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

void write_tableA(vector<field> fields)
{
	string table[nnf][nhx];
	for (size_t f=0; f != fields.size(); ++f) {
		field fld = fields[f];
		if (fld.name.first != 'V') {
			int col = (int)(fld.name.first - 'A');
			int row = fld.name.second-1;
			string fn = fld.name.first + to_string(fld.name.second);
			
			string& entry=table[row][col];
			
			entry  = "=ArmorFirstWave!" + fn;
			entry += "+round(1.5*ArmorIncrement!" + fn;
			entry += "*if(C16=0,1,if(C16=1,1.25,1.4))*max(0,wavesNum!" + fn;
			entry += "-3))*if(C17>wavesNum!" + fn;
			entry += ",1.36*1.025^(C17-1-wavesNum!" + fn;
			entry += "),1)";
			
		}
	}
	for (int i=0; i<nnf; ++i) {
		for (int j=0; j<nhx; ++j) {
			cout << table[i][j] << "\t";
		}
		cout << "\n";
	}
}

int main(int, char **argv)
{
	ifstream file(argv[1]);
	if (!file) exit(1);
	
	vector<field> fields;
	
	while (1) {
		char hex;
		int num;
		file >> hex >> num;
		if (file.eof()) break;
		field newfield;
		newfield.name={hex, num};
		for (int i=0; i<12; ++i) {
			string var;
			double value;
			file >> var >> value;
			
			if (var=="wavesNum")          newfield.wavesNum = value;
			if (var=="giantWavesNum")     newfield.giantWavesNum = value;
			if (var=="swarmlingWavesNum") newfield.swarmlingWavesNum = value;
			if (var=="hpFirstWave")       newfield.hpFirstWave = value;
			if (var=="hpMult")            newfield.hpMult = value;
			if (var=="armorFirstWave")    newfield.armorFirstWave = value;
			if (var=="armorIncrement")    newfield.armorIncrement = value;
			if (var=="snowChance")        newfield.snowChance = value;
			if (var=="rainChance")        newfield.rainChance = value;
		}
		fields.push_back(newfield);
	}
	//cout << fields;
	
	write_tableWN(fields);
	
	return 0;
}

