#include "classControllCenter.h"




bool checkLogOrPas(std::string &arg){
    for(size_t i = 0; i < arg.size(); ++i){
        if(i > 7) return false;
        if(arg[i] == ' ' || std::tolower(arg[i]) < 'a' || std::tolower(arg[i]) > 'z'){
            return false;
        }
    }
    return true;
}



int main(){
    std::string request, arg1,arg2,arg3;
    ControllCenter controllbase;

    while (true)
    {
        request.clear();
        arg1.clear();
        arg2.clear();
        arg3.clear();
        clearinterface();


        std::cout << "Enter your choice: ";
        std::getline(std::cin, request);
        std::stringstream ss(request);
        ss >> arg1 >> arg2 >> arg3;

        if((arg1 == "1" || arg1 == "1vip") && !arg2.empty() && !arg3.empty()){
            if(!checkLogOrPas(arg2) && !checkLogOrPas(arg3)){
                std::cout << "Your username or password does not meet the standards.\n";
                std::cout << "use up to 8 characters inclusive, and do not use characters\n";
                std::cout << "Try again.\n";
                continue;
            }
            if(arg1 == "1vip"){
                controllbase.addAccount(arg2, arg3, "vip");
            } else {
                controllbase.addAccount(arg2, arg3, "def");
            }

        } else if(arg1 == "2" && !arg2.empty() && !arg3.empty()){
            controllbase.deleteAccount(arg2, arg3);

        } else if(arg1 == "3" && !arg2.empty() && !arg3.empty()){
            controllbase.loginAccount(arg2, arg3);

        } else if(arg1 == "admin" && arg2 == "admin"){
            std::cout << "start admin menu:\n";
            controllbase.adminmenu();

        } else if(arg1 == "0"){
            std::cout << "Good bay!\n";
            return 0;
        }
    }
}