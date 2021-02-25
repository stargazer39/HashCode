#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


int toInt(string s);
int wordLength(string s);
int getIntersect(string s1[], string s2[], int len1, int len2);
string* arrayConcat(string s1[], string s2[], int len1, int len2);
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
	bool expired = false;
	Pizza(string* Ingredients,int Length,int Index) {
		ings = Ingredients;
		origIndex = Index;
		length = Length;
	}
};

class pizzaGen {
public:
	vector<Pizza> pVector;
	string* unionArray;
	int uArrayLen = 0,min_intersect = -1,nextIndex = 0;
	bool flag_a = false;
	int getNext() {
		return pVector.size();
		//int return_;
		/*if (!flag_a) {
			flag_a = true;
			unionArray = new string[pVector[0].length];
			unionArray = pVector[0].ings;
			return_ = pVector[0].origIndex;
			pVector.erase(pVector.begin());
			return return_;
		}
		else
		{
			for (int i = 0; i < pVector.size(); i++) {
				int intersect = getIntersect(unionArray, pVector[i].ings, uArrayLen, pVector[i].length);
				if (min_intersect == -1) {
					min_intersect = intersect;
					if (intersect == 0) {
						return_ = pVector[0].origIndex;
						pVector.erase(pVector.begin());
						return return_;
					}
					continue;
				}
				if (intersect == 0) {
					return_ = pVector[i].origIndex;
					pVector.erase(pVector.begin() + i);
					return return_;
				}
				else if (intersect < min_intersect) {
					min_intersect = intersect;
					nextIndex = i;
				}
			}
			if (pVector.size() == 1) {
				return_ = pVector[0].origIndex;
				pVector.erase(pVector.begin());
				return return_;
			}
			return_ = pVector[nextIndex].origIndex;
			pVector.erase(pVector.begin() + nextIndex);
			return return_;
		*/
	}
	void reset() {
		unionArray = NULL;
	}
};

int main() {
	cout << "Started" << endl;
	ifstream TestFile("d_many_pizzas.in");
	ofstream outputFile("out.out");
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
	std::sort(pizzaVector.begin(), pizzaVector.end(), [](const Pizza& p1, const Pizza& p2) { return p1.length < p2.length; });

	cout << endl;
	pizzaGen pGenerator(pizzaVector);
	for (int i = 0; i < 4; i++) {
		cout << pGenerator.getNext() + " ";
	}
	
	//Debug write to file
	for (int i = 0 ; i < pizzaVector.size(); i++) {
		outputFile << pizzaVector[i].origIndex << " " << pizzaVector[i].length << " ";
		for (int j = 0; j < pizzaVector[i].length; j++) {
			outputFile << pizzaVector[i].ings[j] << " ";
		}
		outputFile << endl;
	}

	/*string a1[] = { "lol","num","sex" };
	string a2[] = { "lol","nul","num" };*/

	//string* tot = arrayConcat(pizzaVector[pizzaArray[0]].ings, pizzaVector[pizzaArray[1]].ings, pizzaVector[pizzaArray[0]].length, pizzaVector[pizzaArray[1]].length);
	/*for (int i = 0; i < pizzaVector[pizzaArray[0]].length + pizzaVector[pizzaArray[1]].length; i++) {
		cout << tot[i] + " ";
	}*/
	/*cout << endl;
	cout << getIntersect(pizzaVector[pizzaArray[1]].ings, pizzaVector[pizzaArray[0]].ings, pizzaVector[pizzaArray[1]].length, pizzaVector[pizzaArray[0]].length) << endl;*/
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

//Concatenate 2 string arrays
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

