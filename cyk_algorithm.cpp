#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <assert.h>
#include <set>

std::set<char> dp[100][100];

class Cyk{
    private:
        std::set<char>symbolList;
        std::map<char, std::set<char> >parentsOfCharacter;
        std::map<std::string, std::set<char> >parentsOfString;

        void outputSet(std::set<char> X){
            if(X.empty()){
                std::cout << "-";
                return;
            }

            std::cout << "(";
            std::set<char>::iterator it = X.begin();
            while(it != X.end()){
                std::cout << (*it);

                it++;
                if(it != X.end()){
                    std::cout << ",";
                }
            }
            std::cout << ")";
        }

    public:
        ~Cyk() = default;

        bool admits(std::string message){
            ///compute for dim = 1
            for(int itr = 0; itr < message.size(); itr++){
                for(auto it : parentsOfCharacter[ message[itr] ]){
                    dp[1][itr] = parentsOfCharacter[ message[itr] ];
                    ///check if deepCopy or shallowCopy -- update: it's a deepCopy
                    ///also works even if right operand is empty()
                }
                ///dp[1][itr] = [lista simbolurilor in care se termina message[itr]]
            }

            for(int dim = 2; dim <= message.size(); dim++){
                for (int leftItr = 0; leftItr + dim - 1 < message.size(); leftItr++){
                    int rightItr = leftItr + dim - 1;

                    ///substring [leftItr, rightItr]
                    for(int commaPosition = leftItr; commaPosition <= rightItr - 1; commaPosition++){
                        ///combine [leftItr, commaPosition] with [commaPosition + 1, rightItr]
                        int leftDim = commaPosition - leftItr + 1;
                        int rightDim = rightItr - commaPosition;
                        int wholeDim = rightItr - leftItr + 1;

                        ///combine dp[leftDim][leftItr] and dp[rightDim][commaPosition + 1]
                        ///in dp[wholeDim][leftItr]

                        ///iau fiecare litera mare din dp[leftDim][leftItr] cu fiecare
                        ///litera mare din dp[rightDim][commaPosition + 1]
                        for(auto leftLetter : dp[leftDim][leftItr]){
                            for(auto rightLetter : dp[rightDim][commaPosition + 1]){
                                ///std::cout << leftLetter << rightLetter << "\n";
                                std::string tmpString;
                                tmpString = leftLetter;
                                tmpString += rightLetter;

                                parentsOfString[tmpString];
                                ///add every element of the vector<char> (parentsOfString[tmpString])
                                ///to dp[wholeDim][leftItr]
                                for(auto parentChar : parentsOfString[tmpString]){
                                    dp[wholeDim][leftItr].insert(parentChar);
                                }
                            }
                        }

                    }
                }
            }

            for(int dim = message.size(); dim >= 1; dim--){
                for(int i = 0; i <= message.size() - dim + 1 - 1; i++){
                    outputSet(dp[dim][i]); std::cout << " ";
                }
                std::cout << "\n";
                ///dp[dim][pos];
            }

            for(auto letter : dp[message.size()][0]){
                if(letter == 'S'){
                    return true;
                }
            }

            return false;
        }

        friend std::istream& operator >> (std::istream& in, Cyk &X){
            X.symbolList.clear();
            X.parentsOfCharacter.clear();
            X.parentsOfString.clear();


            int numberOfSymbols;
            in >> numberOfSymbols;
            X.symbolList.clear();

            for(int itr = 0; itr < numberOfSymbols; itr++){
                char crrSymbol;
                in >> crrSymbol;

                X.symbolList.insert(crrSymbol);

                int numberOfChildren;
                in >> numberOfChildren;
                for(int itrChildren = 0; itrChildren < numberOfChildren; itrChildren++){
                    int type;
                    in >> type; assert(type == 0 || type == 1);

                    if(type == 0){
                        ///nonterminal symbol
                        std::string nonTerminalString;
                        in >> nonTerminalString;
                        X.parentsOfString[nonTerminalString].insert(crrSymbol); ///works even if vector is not initialized
                    }
                    else if(type == 1){
                        ///terminal symbol
                        char terminalSymbol;
                        in >> terminalSymbol;
                        X.parentsOfCharacter[terminalSymbol].insert(crrSymbol);
                    }
                }
            }

            return in;
        }

};

int main()
{
    std::ifstream fin ("test.in");
    Cyk X;
    fin >> X;
    fin.close();

    std::string inputMessage;
    std::cout << "Input message = ";
    std::cin >> inputMessage;

    if(X.admits(inputMessage)){
        std::cout << "Message is accepted!" << "\n";
    }
    else {
        std::cout << "Message is NOT accepted!" << "\n";
    }

    return 0;
}
