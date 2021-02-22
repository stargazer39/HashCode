#include <iostream>

using namespace std;

void getIntersect(string arr1[],string arr2[]);
int main()
{
    string test = "Hi";
    string a1[] = {"lol","pol","kol","nol","uol","lol"};
    string a2[] = {"lol","pol","kol","nol","uol"};

    cout << "Sizeof " << sizeof(a1)/sizeof(a1[0]) << "\n";
    getIntersect((string*)a1,(string*)a2);
    cout << "\n\n" + a1[0];
    cout << test << endl;
    cout << "Hello world!" << endl;
    return 0;
}
void getIntersect(string* arr1,string* arr2)
{
    int arrSize = *(&arr1 + 1) - arr1;
    cout << "Sizeof " << arrSize << "\n";
    /*for(int i=0; i<5; i++){
        cout << arr1[i] << arr2[i];
    }*/
}
