#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>

#define LAMBDA '^'

struct Edge{
    int to;
    char acceptedLetter;
    char poppedLetter;
    char pushedLetter;

    friend std::istream& operator >> (std::istream &in, Edge &crrEdge){
        in >> crrEdge.to;
        in >> crrEdge.acceptedLetter;
        in >> crrEdge.poppedLetter;
        in >> crrEdge.pushedLetter;
        return in;
    }

    friend std::ostream& operator << (std::ostream &out, Edge &crrEdge){
        out << "(";
        out << " -> " << crrEdge.to << ", ";
        out << "acc '" << crrEdge.acceptedLetter << "', ";
        out << "pop '" << crrEdge.poppedLetter << "', ";
        out << "push '" << crrEdge.pushedLetter << "'";
        out << ")";
    }
};

class PDA{
    private:
        int source;
        std::vector<int> nodeList;
        std::unordered_map<int, std::vector<Edge> > edgeList;
        std::unordered_map<int, bool> isFinish;
        std::unordered_map<int, int> hashMap;
        std::stack <char> myStack;

        void DFS(int crrNode, std::string const &message, int crrIdxMessage, bool &result, bool lastWasLambda, int firstLambda){

            if(crrIdxMessage == message.size() && isFinish[crrNode]){
                result = true;
                return;
            }

            ///the new edge has to either be epsilon or accept message[crrIdxMessage]
            /// + THE STACK CONDITIONS!!!!!!
            /// + careful not to find a cycle
            for(int itrEdges = 0; itrEdges < edgeList[crrNode].size(); itrEdges++){

                if(result == true){
                    ///aready found it's true, no need to continue!
                    return;
                }

                Edge const &crrEdge = edgeList[crrNode][itrEdges];

                ///verify lambda cycle
                if(lastWasLambda && crrEdge.to == firstLambda){
                    ///big nono
                    continue;
                }


                ///see if i should go through this edge or not
                if( (crrEdge.acceptedLetter == LAMBDA || crrEdge.acceptedLetter == message[crrIdxMessage])
                    && ( crrEdge.poppedLetter == LAMBDA || ( (!myStack.empty()) && crrEdge.poppedLetter == myStack.top() ))
                    ){
                    ///go through
                    if(crrEdge.poppedLetter != LAMBDA){
                        myStack.pop();
                    }
                    if(crrEdge.pushedLetter != LAMBDA){
                        myStack.push(crrEdge.pushedLetter);
                    }

                    if(crrEdge.acceptedLetter != LAMBDA){
                        DFS(crrEdge.to, message, crrIdxMessage + 1, result, false, -1);
                    }
                    else {
                        if(lastWasLambda == false){
                            ///firstLambda becomes crrNode
                            DFS(crrEdge.to, message, crrIdxMessage, result, true, crrNode);
                        }
                        else {
                            ///firstLambda stays the same
                            DFS(crrEdge.to, message, crrIdxMessage, result, true, firstLambda);
                        }
                    }
                }
            }
        }

    public:

        int getNrNodes(){
            return nodeList.size();
        }

        bool admits(std::string const &message){
            bool result = false;
            DFS(source, message, 0, result, false, -1);
            return result;
        }

        friend std::istream& operator >> (std::istream &in, PDA &crrPDA){
            crrPDA.nodeList.clear();
            crrPDA.hashMap.clear();
            ///crrPDA.myStack.clear();
            while(crrPDA.myStack.empty() == false){
                crrPDA.myStack.pop();
            }

            int numberNodes;
            in >> numberNodes;

            for(int itr = 0; itr < numberNodes; itr++){
                int newNode;
                in >> newNode;

                crrPDA.isFinish[newNode] = false;
                crrPDA.hashMap[newNode] = itr;
                crrPDA.nodeList.push_back(newNode);
            }

            in >> crrPDA.source;
            crrPDA.source = crrPDA.hashMap[crrPDA.source];

            int numberOfFinishes;
            in >> numberOfFinishes;
            for(int itr = 0; itr < numberOfFinishes; itr++){
                int newNodeFinish;
                in >> newNodeFinish;
                newNodeFinish = crrPDA.hashMap[newNodeFinish];
                crrPDA.isFinish[newNodeFinish] = true;
            }

            int numberOfEdges;
            in >> numberOfEdges;

            for(int itr = 0; itr < numberOfEdges; itr++){
                int baseNode;
                in >> baseNode;
                baseNode = crrPDA.hashMap[baseNode];

                Edge newEdge;
                in >> newEdge;
                newEdge.to = crrPDA.hashMap[newEdge.to];

                crrPDA.edgeList[baseNode].push_back(newEdge);
            }

            return in;
        }

        friend std::ostream& operator << (std::ostream& out, PDA &crrPDA){
            out << crrPDA.getNrNodes() << " nodes: ";
            for(auto it : crrPDA.nodeList){
                out << it << " ";
            }
            out << "\n";
            out << "Hashed values: ";
            for(auto it : crrPDA.nodeList){
                out << crrPDA.hashMap[it] << " ";
            }
            out << "\n";

            out << "Source(hashed) = " << crrPDA.source << "\n";
            out << "Finish nodes(hashed): ";
            for(auto it : crrPDA.nodeList){
                if(crrPDA.isFinish[it] == true){
                    out << it << " ";
                }
            }
            out << "\n";

            for(int itrNodes = 0; itrNodes < crrPDA.getNrNodes(); itrNodes++){
                int crrNode = crrPDA.hashMap[ crrPDA.nodeList[itrNodes] ];
                out << "Edges from node " << crrNode << ":" << "\n";
                if(crrPDA.edgeList[crrNode].empty()){
                    out << "none!";
                }
                for(int itrEdges = 0; itrEdges < crrPDA.edgeList[crrNode].size(); itrEdges++){
                    Edge &crrEdge = crrPDA.edgeList[crrNode][itrEdges];
                    out << crrEdge << "\n";
                }
                out << "\n";
            }

            return out;
        }

};

int main()
{
    std::ifstream fin ("test.in");
    PDA myPda;
    fin >> myPda;
    std::string messageToVerify;
    fin >> messageToVerify;
    std::cout << messageToVerify << "\n";
    fin.close();

    std::ofstream fout ("test.out");
    std::cout << myPda << "\n";
    fout << myPda << "\n";

    std::cout << "Message " << messageToVerify << " is ";
    fout << "Message " << messageToVerify << " is ";
    if(myPda.admits(messageToVerify)){
        std::cout << "accepted!" << "\n";
        fout << "accepted!" << "\n";
    }
    else{
        std::cout << "NOT accepted!" << "\n";
        fout << "NOT accepted!" << "\n";
    }

    fout.close();


    return 0;
}
