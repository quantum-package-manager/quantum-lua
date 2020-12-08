#include <iostream>
#include <string>
#include <unistd.h>
#include "install.hpp"
#include "remove.hpp"
#include "libs/installed.hpp"
#include "libs/getDescription.hpp"

int main(int argc, char *argv[]){
    
    
    if ( argc != 1 ){
	std::string arg=argv[1];
	std::string pkg="";
	if(argc == 3){
		pkg=argv[2];
	}
        if(arg=="install" || arg=="remove"){
            std::string answer;
            std::cout << "Name" << std::endl << pkg << std::endl << std::endl << "Do you want to continue? [Y/n] ";
            std::cin >> answer;

            if(answer == "y"){
                if(arg == "install"){
		            if(argc==3){
                        install_pkg(pkg);
		            } else {
			            install_pkg(pkg, argv[3]);
		            }
                } else if (arg == "remove"){
                    if(argc==3){
                        remove(pkg);
                    } else {
                        remove(pkg, argv[3]);
                    }
                }
            }   
        } else if(arg=="installed"){
            if (installed(pkg)) {
                std::cout << "yes" << std::endl;
            } else {
                std::cout << "no" << std::endl;
            }
        } else if(arg=="description"){
            desc(pkg);
        } else if(arg=="populate"){
            auto myprivs = geteuid();
            std::string install_dir;

            if (myprivs == 0){
                install_dir = "/usr/share/quantum/";
            } else {
                install_dir = std::getenv("HOME");
                install_dir.append("/quantum-lua");
            }

		    std::string cmd="cd ";
            cmd.append(install_dir);
            cmd.append(" && curl -LO https://raw.githubusercontent.com/quantum-package-manager/repo/main/quantum.db");
		    system(cmd.c_str());
    	} /* else if(arg=="update"){

        } */
    } else {
        std::cout << "Quantum Package Manager v2 - 0.1.0a" << std::endl;
    }
}
