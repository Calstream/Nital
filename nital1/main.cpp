#include<string>
#include<fstream>
#include<vector>
using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";
int main()
{
	vector<string> dict;
	ifstream input;
	input.open(iname);
	string s = "";
	int n_words = 0;
	input >> n_words;
	input.ignore();
	while (getline(input, s))
	{
		dict.push_back(s);
	}
	input.close();

	system("pause");
}