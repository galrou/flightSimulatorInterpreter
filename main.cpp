#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

/**
 * The main program.
 *
 * @param argc - The number of arguments that we got
 * @param args - The arguments array
 * @return 0 - If all the processes succeeded, 1 - Otherwise
 */
int main(int argc, char* args[]) {

    if (argc < 2) {
        cout<<"Did not get a code-file name."<<endl;
    } else {
        try {
            Lexer lex;
            lex.lexer(args[1]);

            vector<string> ans = lex.getCopyTokensVector();

//    for (unsigned int i=0; i<ans.size(); i++) {
//
//        cout<<ans[i]<<endl;
//    }

            Parser parser1;
            parser1.parse(ans);
        }
        catch (const char *e) {
            cout << e << endl;
        }
    }










    return 0;
}