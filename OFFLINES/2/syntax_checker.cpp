#include <stack>
#include <string>
using namespace std;

/**
 * Helper function to check if an opening bracket matches a closing bracket
 * @param opening: The opening bracket character
 * @param closing: The closing bracket character
 * @return true if they form a matching pair, false otherwise
 */
bool isMatchingPair(char opening,char closing){
    if(opening=='(' && closing==')') return true;
    if(opening=='{' && closing=='}') return true;
    if(opening=='[' && closing==']') return true;
    return false;
}

/**
 * Checks if brackets in an arithmetic expression are properly matched
 * @param expression: A string containing an arithmetic expression
 * @return true if all brackets are properly matched and balanced, false otherwise
 */
bool isValidExpression(const string& expression){
    stack<char> s;
    for(char c:expression){
        if(c=='(' || c=='{' || c=='['){
            s.push(c);
        } 
        else if(c==')' || c=='}' || c==']'){
            if(s.empty()){
                return false;
            }
            if(!isMatchingPair(s.top(),c)){
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}