#include<bits/stdc++.h>
using namespace std;

int numPage, numframe;
string s = "";

struct Node {
    int data;
    Node* next;

    Node(int d) {
        data = d;
        next = NULL;
    }
};

int fifo() {
    int hit=0, miss=0;
    vector<int> v(numframe, -1);

    int i,j,index = 0;
    for(int i=0; i<s.length(); i++) {
        for(j=0; j<numframe; j++) {
            if(v[j] == (s[i]-'0')) {
                hit++;
                break;
            }
        }
        if(j == numframe) {
            v[index] = s[i]-'0';
            miss++;
            index = (index+1)%numframe;
        }
    }

    return miss;

}

int lru() {
    int hit=0, miss=1;

    Node* temp = new Node((s[0]-'0'));
    Node* rear = temp;
    Node* front = temp;
    Node* temp2;

    int listSize = 1;
    for(int i=1; i<s.length(); i++) {
        temp = front;
        temp2 = NULL;
        while(temp != NULL) {
            if(temp->data == (s[i]-'0')) {
                hit++;
                break;
            }
            temp2 = temp;
            temp = temp->next;
        }

        //Miss
        if(temp == NULL) {
            temp = new Node((s[i]-'0'));
            //Direct insert --> Memory Frame are empty.
           if(listSize != numframe) {
                listSize++;
            }
            //LRU Algorithm --> memory Frame Full.
            else {
                temp2 = front;
                front = front->next;
                delete temp2;
            }
            rear->next = temp;
            rear = temp;
            miss++;
        }
       // Hit
        else {
            if(temp->next == NULL) 
                continue;
            if(temp2 != NULL)
                temp2->next = temp->next;
            else
                front = front->next;
            temp->next = NULL;
            rear->next = temp;
            rear = temp;
        }
    }

    return miss;
}

int lfu() {
    unordered_map<int,int> m;
    int hit=0, miss=0;
    vector<int> v(numframe, -1);
    
    //Getting all the unique values out of the reference string
    set<int> se;
    for(int i=0; i<s.length(); i++) {
        if(!se.count((s[i]-'0'))) {
            se.insert((s[i]-'0'));
        }
    }

    //Adding all the unique values to map m with initial values 0.
    set<int>::iterator it = se.begin();
    while(it != se.end()) {
        m.insert({*it, 0});
        it++;
    }

    int i,j,x=0,index = 0;
    for(int i=0; i<s.length(); i++) {
        for(j=0; j<numframe; j++) {
            if(v[j] == (s[i]-'0')) {
                m[(s[i]-'0')]++;
                hit++;
                break;
            }
        }
        //Miss
        if(j == numframe) {
            //Directly insert-->space in memory frame
            miss++;
            if(x < numframe) {
                v[index] = s[i]-'0';
                m[(s[i]-'0')]++;
                x = x+1;
            }
            //Perform LFU Algorithm-->Memory space is full.
            else {
                vector<int> tempVec;
                //Find out all the elements with minimum frequency.
                int minfreq = m[v[0]];
                for(int t=1; t<numframe; t++) {
                    if(m[v[t]] < minfreq) {
                        minfreq = m[v[t]];
                    }
                }
                for(int t=0; t<numframe; t++) {
                    if(m[v[t]] == minfreq) {
                        tempVec.push_back(t);
                    }
                }

                //If exactly 1 then replace.
                if(tempVec.size() == 1) {
                    m[v[tempVec[0]]] = 0;
                    v[tempVec[0]] = s[i]-'0';
                    m[v[tempVec[0]]]++; 
                }     
                //If more then 1 then apply FIFO.  
                else {
                    if(find(tempVec.begin(), tempVec.end(), index) == tempVec.end()) {
                        index = (index + 1)%numframe;
                    }
                    m[v[index]] = 0;
                    v[index] = s[i]-'0';
                    m[v[index]]++;
                }
            }
            index = (index+1)%numframe;
        }
    }

    return miss;
}


int main(int argc, char** argv) {

    //Reading first line from input file
    ifstream fin;
    string fileName = argv[1];
    fileName +=".txt";
    fin.open(fileName);
    
    string line;
    getline(fin, line);

    //Taking Number of pages and number of frames as Input.
    char* str;
    str = &line[0];
    char *token = strtok(str, " ");
    numPage = stoi(token);
    token = strtok(NULL, " ");
    numframe = stoi(token);

    //Taking reference strings as input.
    int j = 0;
    getline(fin, line);
    while(fin) {
        for(int i=0; i<line.length(); i++) {
            if(line[i] != ' ') {
                s += line[i];
            }
        }
        cout<<"\n--------------------------------------------------------------------------\n";
        string sequence;
        cout<<"For Reference string "<<j+1<<endl;
        for(int i=2; i<argc; i++) {
            sequence = argv[i];
            if(sequence == "FF") {
                cout<<"FIFO : Page Fault --> "<<fifo()<<endl;
            }
            else if(sequence == "LF") {
                cout<<"LFU : Page Fault  --> "<<lfu()<<endl;
            }
            else if(sequence == "LR") {
                cout<<"LRU : Page Fault --> "<<lru()<<endl;
            }
            else {
                cout<<"Wrong string in command line argument"<<endl;
            }
        }
        cout<<"--------------------------------------------------------------------------\n";
        j++;
        s = "";
        getline(fin, line);
    }

    fin.close();
    return 0;
}