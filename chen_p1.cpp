#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

static signed int currentNum = 0;

typedef struct s{
    s(): stateNum(currentNum++), isAccept(0), isReject(0), isStart(0){}
    void print(){
        std::string transInput, transOutput;
        for(int i = 0; i < this->transInput.size(); i++){
            transInput = transInput + this->transInput.at(i);
        }
        for(int i = 0; i < this->transOutput.size(); i++){
            transOutput = transOutput + std::to_string(this->transOutput.at(i));
        }
        std::cout   << "stateNum: " << stateNum << std::endl
                    << "\ttransInput: " << transInput << std::endl
                    << "\ttransOutput: " << transOutput << std::endl
                    << "\ttransDirection: " << transDirection << std::endl
                    << "\ttransrepl: " << transrepl << std::endl
                    << "\tisAccept: " << isAccept << std::endl
                    << "\tisReject: " << isReject << std::endl
                    << "\tisStart: " << isStart << std::endl;
    }
    int stateNum;
    std::vector<char> transInput;
    std::vector<int> transOutput;
    std::string transDirection;
    std::string transrepl;
    bool isAccept;
    bool isReject;
    bool isStart;
}state;

int main(int argc, char* argv[]){
    using namespace std;

    if (argc != 4){
        std::cerr << "Usage: ./chen_p1 <inputfile> '<input string>' <transition limit>\n";
        return 1;
    }
    /*
    for(int i = 0; i < sizeof(argv[2]); i++)
        cout << argv[2][i] << " ";
    for(int i = 0; i < argc; i++)
        cout << argv[i] << endl << flush;
        */
    int startState = -1;
    state states[1000];
    string inputFile(argv[1]);
    string inputStr(argv[2]);
    string size(argv[3]);
    int transLimit = stoi(size);

    //cout << "Test: " << inputFile << " " << inputStr << " " << transLimit << endl;
    ifstream file;
    file.open(inputFile);
    if(!file.is_open()){
        std::cerr << "File " << argv[1] << " was not found.\n";
        return 1;
    }

    for(int i = 0; i < 3; i++){
        string temp;
        int state;
        file >> temp;

        file >> temp;

        //cout << temp;
        state = stoi(temp);
        file >> temp;
        if(temp == "accept") states[state].isAccept = true;
        else if (temp == "reject") states[state].isReject = true;
        else{
            states[state].isStart = true;
            startState = state;
        }
    }

    //FUCK C++ FILE I/O IT TOOK ME 1 HR TO REALIZE MY SHIT WASN'T WORKING CAUSE I DIDN'T READ A ENDLINE CHAR
    string temp;
    getline(file, temp);
    //cout << temp;
    /*states[3].print();
    states[4].print();
    states[5].print();
    */

    /*
    while(file){
        //format: transition  q a r b x
        string temp;
        file >> temp;
        cout << temp << " " << flush;

        file >> temp;
        cout << temp << " " << flush;
        int state = stoi(temp);
        file >> temp;
        cout << temp << " ";
        states[state].transInput += temp;
        file >> temp;
        cout << temp << " ";
        states[state].transOutput += temp;
        file >> temp;
        cout << temp << " ";
        states[state].transrepl += temp;
        file >> temp;
        cout << temp << " ";
        states[state].transDirection += temp;
        cout << endl;
    } */
    //int smth = 0;
    string line;
    while(getline(file, line)){
        //cout << line << endl;
        istringstream iss(line);
        int state;
        string temp,a,r,b,x;
        if(!(iss >> temp >> state >> a >> r >> b >> x)){
            //cout << smth++ << flush;
            break;
        }
        states[state].transInput.push_back(a[0]);
        states[state].transOutput.push_back(stoi(r));
        states[state].transrepl += b;
        states[state].transDirection += x;
    }
    /*for (auto &x : states){
        if (x.transInput.size() == 0)
            continue;
        else x.print();
    }*/
    /*
    while(file){
        string temp;
        file >> temp;
        if(temp == "\n"){
            cout <<"asdf";
        }
        cout << temp << endl;
    }*/

    //for some reason the actual first symbol, inputStr[0] is '\'
    int curSymbol = 0;
    int curState = startState;
    string stateTransitions(to_string(curState));

    for(int i = 0; i < transLimit; i++){
        if(states[curState].isReject || states[curState].isAccept){
            break;
        }
        if(curSymbol < 0 || curSymbol >= inputStr.length()){
            char symbol = '_';

            //index of the location of everything within the string arrays
            auto it = std::find(states[curState].transInput.begin(), states[curState].transInput.end(), symbol);
            int location = distance(states[curState].transInput.begin(), it);
            //int location = states[curState].transInput.find(symbol);
            //index of the next state
            int index = states[curState].transOutput[location];

            //inputStr[curSymbol] = states[curState].transrepl[location];
            curSymbol += (states[curState].transDirection[location] == 'R')? 1:-1;
            curState = index;
            stateTransitions.append("->" + to_string(curState));
            //sprintf(stateTransitions, "%s->%d", stateTransitions, curState);
            //cout << stateTransitions << endl;
            continue;
        }
        char symbol = inputStr[curSymbol];

        //index of the location of everything within the string arrays
        auto it = std::find(states[curState].transInput.begin(), states[curState].transInput.end(), symbol);
        int location = distance(states[curState].transInput.begin(), it);
        //int location = states[curState].transInput.find(symbol);
        //index of the next state
        int index = states[curState].transOutput[location];


        inputStr[curSymbol] = states[curState].transrepl[location];
        curSymbol += (states[curState].transDirection[location] == 'R')? 1:-1;
        curState = index;
        stateTransitions.append("->" + to_string(curState));
        //sprintf(stateTransitions, "%s->%d", stateTransitions, curState);
        //cout << stateTransitions << endl;
    }
    cout << stateTransitions;
    if(states[curState].isAccept)
        cout << " accept\n";
    else if(states[curState].isReject)
        cout << " reject\n";
    else
        cout << " quit\n";

}
