#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class stringGen {
public:
	string str, delim;
	stringGen(string String, string Delemiter) {
		str = String;
		delim = Delemiter;
	}
	string getNextStr() {
		if (str.length()) {
			int pos = str.find(delim);
			string token = str.substr(0, pos);
			str.erase(0, token.length() + delim.length());
			return token;
		}
		else {
			return "\0";
		}
	}
};
class Pizza {
public:
	string* ings;
	int origIndex;
	int length;
	Pizza(string* Ingredients,int Length,int Index) {
		ings = Ingredients;
		origIndex = Index;
		length = Length;
	}
};

int toInt(string s);
int wordLength(string s);
int getIntersect(string s1[], string s2[], int len1, int len2);
string* arrayConcat(string s1[], string s2[], int len1, int len2);
int main() {
	cout << "Started" << endl;
	ifstream TestFile("d_many_pizzas.in");
	ofstream outputFile("out.txt");
	vector<Pizza> pizzaVector;
	string text;
	int args[4];
	int ing, max_ing = 0,index = 0;
	bool started = false;
	while (getline(TestFile, text))
	{
		stringGen s(text, " ");
		//First line is arguments. Geting them to a array.
		if (!started) {
			for (int i = 0; i < 4; i++) {
				args[i] = toInt(s.getNextStr());
				//cout << i << " " << args[i] << endl;
			}
			started = true;
			continue;
		}
		int ing = toInt(s.getNextStr());
		if (ing > max_ing) {
			max_ing = ing;
		}
		int len = wordLength(text);
		string* ingredients = new string[len];
		for (int j = 0; j < len; j++) {
			ingredients[j] = s.getNextStr();
			//cout << ingredients[j] + " ";
		}
		Pizza p(ingredients, len, ing);
		pizzaVector.push_back(p);
		index++;
		//cout << ing << " " << len << endl;
	}
	cout << "Max ingredients" << max_ing << endl;
	TestFile.close();
	
	//Sort the Pizza
	int pizzaArray [100000];
	int k = 0;
	for (int i = max_ing; i >= 0; i--) {
		for (int j = 0; j < pizzaVector.size(); j++) {
			if (pizzaVector[j].length == i) {
				pizzaArray[k] = j;
				k++;
			}
		}
	}

	for (int i = 0 ; i < k; i++) {
		outputFile << pizzaVector[pizzaArray[i]].origIndex << " " << pizzaVector[pizzaArray[i]].length << " ";
		for (int j = 0; j < pizzaVector[pizzaArray[i]].length; j++) {
			outputFile << pizzaVector[pizzaArray[i]].ings[j] << " ";
		}
		outputFile << endl;
	}

	string a1[] = { "lol","num","sex" };
	string a2[] = { "lol","nul","num" };

	string* tot = arrayConcat(pizzaVector[pizzaArray[0]].ings, pizzaVector[pizzaArray[1]].ings, pizzaVector[pizzaArray[0]].length, pizzaVector[pizzaArray[1]].length);
	for (int i = 0; i < pizzaVector[pizzaArray[0]].length + pizzaVector[pizzaArray[1]].length; i++) {
		cout << tot[i] + " ";
	}
	cout << tot->length();
	cout << endl;
	cout << getIntersect(pizzaVector[pizzaArray[1]].ings, pizzaVector[pizzaArray[0]].ings, pizzaVector[pizzaArray[1]].length, pizzaVector[pizzaArray[0]].length) << endl;
	/*TestFile.clear();
	cout << "\n\n";
	TestFile.seekg(0, ios::beg);
	while (getline(TestFile, text))
	{
		cout << text << endl;
	}*/
}

//Cast string to int
int toInt(string s) {
	stringstream ss(s);
	int i;
	ss >> i;
	return i;
}

//Get count of words in a line
int wordLength(string s) {
	int count = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ' || s[i] == '\n') {
			count++;
		}
	}
	return count;
}

//Get intersect of two string arrays
int getIntersect(string s1[], string s2[], int len1, int len2) {
	int count = 0;
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			if (s1[i] == s2[j]) {
				cout << s1[i] + " " + s2[j] << endl;
				count++;
				//Assuming both have unique elements
				break;
			}
		}
	}
	return count;
}

string* arrayConcat(string s1[], string s2[], int len1, int len2) {
	string* tot = new string[len1 + len2];
	int i, j;
	for (i = 0; i < len1; i++) {
		tot[i] = s1[i];
	}
	for (j = 0; j < len2; j++) {
		tot[i + j] = s2[j];
	}
	return tot;
}