#include <iostream>
#include <windows.h>
#include "Server.h"
#include "ConsoleController.h"

using namespace std;

int main()
{
    try{
        ConsoleController c1(0);
        ConsoleController c2(1);
        Server server(c1,c2);
        int winner = server.Run();
        system("cls");
        cout << "Player " + to_string(winner + 1) + " win\n";
    }
    catch(const exception& e){
        cout << endl << "An exception happened:"<<endl;
        cout << e.what();
    }
    catch (...){
        cout << endl << "An unknown exception happened" << endl;
    }
    cin.get();
    return 0;
}