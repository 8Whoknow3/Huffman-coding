#include "Huffman.h"

using namespace std;

void huffman::create_array() {
    for(int i = 0; i < 128; i++){
        ASCII[i] = new node;
        ASCII[i]->id = (char)i;
        ASCII[i]->freq = 0;
    }
}

void huffman::traverse(node * r, const std::string& code) {
    if (r->left == nullptr && r->right == nullptr)
        r->code = code;

    else{
        traverse(r->left, code + '0');
        traverse(r->right, code + '1') ;
    }
}

int huffman::BTD(string & code) {
    int ans = 0;
    for(char i : code)
        ans = ans * 2 + (i - '0');
    return ans;
}

string huffman::DTB(int a) {
    string temp;
    string ans;
    while(a > 0){
        temp += ('0' + a % 2);
        a /= 2;
    }

    ans.append(8 - temp.size(), '0'); // To be 8_bit

    for(int i = (int)temp.size() - 1; i >= 0; i--)
        ans += temp[i];

    return ans;
}

huffman::huffman(string in,string out) {
    in_file_name = std::move(in);
    out_file_name = std::move(out);
    create_array();
}

void huffman::createPriorityqueue() {
    in_file.open(in_file_name, ios::in);
    in_file.get(id);
    while (!in_file.eof())
    {
        ASCII[id]->freq++;
        in_file.get(id);
    }
    in_file.close();

    for(auto & i : ASCII)
        if (i->freq)
            pq.push(i);
}

void huffman::createTree()
{

    priority_queue<node *, vector<node *>, compare> temp(pq);
    while (temp.size() > 1){        // Create the huffman tree
        root = new node;
        root->freq = 0;
        root->left = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        root->right = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        temp.push(root);
    }
}

void huffman::calculateCodes()
{
    traverse(root, "");
}

void huffman ::coding() {
    in_file.open(in_file_name, ios::in);
    out_file.open(out_file_name, ios::out | ios::binary);
    string save;
    save += to_string(pq.size()) + " ";

    priority_queue<node *, vector<node *>, compare> temp(pq);
    while(!temp.empty()){
        node * curr = temp.top();
        temp.pop();
        save += curr->id + to_string(curr->freq) + " ";
    }
    in_file.get(id); // Transform text to binary
    string help, helpP;
    while(!in_file.eof()){
        help += ASCII[id]->code;
        while(help.size() > 8){
            string t = help.substr(0,8);
            helpP += ((char) BTD(t));
            help = help.substr(8);
        }
        in_file.get(id);
    }
    int count = 8 - help.size();
    if(help.size() < 8)
        help.append(count, '0');
    save += to_string(count);
    save += "\n";
    helpP += (char)BTD(help);
    save += helpP;
    out_file.write(save.c_str(), save.size());
    in_file.close();
    out_file.close();
}

void huffman::decoding() {
    in_file.open(in_file_name, ios::in | ios ::binary);
    out_file.open(out_file_name, ios :: out);
    int count = 0;
    in_file.get(id);
    while(id != ' '){
        // To get number of different characters
        count = count * 10 + id - '0';
        in_file.get(id);
    }

    while(count > 0){
        long long int f = 0; char i;
        in_file.get(id); // To get character
        i = id;
        in_file.get(id);
        f = f * 10 + id - '0';
        in_file.get(id);
        while(id != ' ') {
            f = f * 10 + id - '0';
            in_file.get(id);
        }
        count--;
        ASCII[i]->freq = f;
    }
    for(auto & i : ASCII) // Recreate priority queue
        if (i->freq)
            pq.push(i);

    createTree();
    calculatecodeDecode(); // Get every code of character

    in_file.get(id); // Number of added 0 at the end of file
    count = id - '0';
    in_file.get(id);

    string matn;
    in_file.get(id);
    while(!in_file.eof()){
        if((int) id < 0)
            matn += DTB((int) id  + 256);
        else
            matn += DTB((int)id);
        in_file.get(id);
    }
    matn = matn.substr(0, matn.size() - count);
    string help;
    for(auto i : matn){
        help += i;
        if(decode[help]){
            out_file.put(decode[help]);
            help.clear();
        }
    }
    in_file.close();
    out_file.close();
}


void huffman::calculatecodeDecode() {
    traverseDecode(root, "");
}

void huffman::traverseDecode(node * r, const string & code) {
    if (r->left == nullptr && r->right == nullptr)
        decode[code] = r->id;

    else{
        traverseDecode(r->left, code + '0');
        traverseDecode(r->right, code + '1') ;
    }
}

