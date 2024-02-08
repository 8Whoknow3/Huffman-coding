#include "Huffman.h"
#include "Huffman.cpp"
#include "iostream"

using namespace std;

int main(){
    char choice;
    vector<string>names;
    do {
        cout << "1)Encode\n2)Decode\n3)Exit\n";
        cin >> choice;
        if(choice == '1'){
            fstream EnNames, DeNames;
            EnNames.open("EnNames", ios :: in);
            while(!EnNames.eof()){
                string temp;
                getline(EnNames, temp);
                names.push_back(temp);
            }
            EnNames.close();

            int c;
            cout << "Available Files for Encode :\n";
            int t = 1;
            for(const auto& i : names)
                cout << t++ << ")" << i << endl;
            cin >> c;
            cout << "Choice names for output :";
            string out;
            cin >> out;

            huffman En(names[c - 1] + ".txt", out + ".comp");
            En.createPriorityqueue();
            En.createTree();
            En.calculateCodes();
            En.coding();
            cout << "Encoding successful!\n";

            names.clear();
            DeNames.open("DeNames", ios :: in);
            while(!DeNames.eof()){
                string temp;
                getline(DeNames, temp);
                names.push_back(temp);
            }
            names.push_back(out);
            DeNames.close();

            DeNames.open("DeNames", ios :: out);
            for(int i = 0; i < names.size(); i++) {
                if(i == names.size() - 1)
                    DeNames << names[i];
                else
                    DeNames << names[i] << "\n";
            }
            DeNames.close();
            names.clear();
        }
        else if(choice == '2'){
            fstream DeNames, EnNames;
            DeNames.open("DeNames", ios :: in);
            while(!DeNames.eof()){
                string temp;
                getline(DeNames, temp);
                names.push_back(temp);
            }
            DeNames.close();

            int c;
            cout << "Available Files for Encode :\n";
            int t = 1;
            for(const auto& i : names)
                cout << t++ << ")" << i << endl;
            cin >> c;
            cout << "Choice names for output :";
            string out;
            cin >> out;

            huffman De(names[c - 1] + ".comp", out + ".txt");
            De.decoding();
            cout << "Decoding successful!\n";
            names.clear();

            EnNames.open("EnNames", ios :: in);
            while(!EnNames.eof()){
                string temp;
                getline(EnNames, temp);
                names.push_back(temp);
            }
            names.push_back(out);
            EnNames.close();

            EnNames.open("EnNames", ios :: out);
            for(int i = 0; i < names.size(); i++) {
                if(i == names.size() - 1)
                    EnNames << names[i];
                else
                    EnNames << names[i] << "\n";
            }
            EnNames.close();
            names.clear();
        }
    } while (choice != 3);
    exit(0);
}