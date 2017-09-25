#ifndef UTILS_H_
#define	UTILS_H_

//GPIOS TESTADOS
//65	A
//51	B
//49
//47	C
//46	E
//45	F
//44	G
//27	DP
//26 	DISPLAY 1
//23	DISPLAY 2
//22  DISPLAY 3


#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <map>
#include <vector>

class driverDisplay
{
	driverDisplay();
	std::vector<std::string> zero,um,dois,tres,quatro,cinco,seis,sete,oito,nove;
	std::map<std::string,BlackLib::BlackGPIO> displayMap;

	void show(int,int); //recebe numero e display
};

BlackLib::BlackGPIO led(BlackLib::GPIO_51, BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO button(BlackLib::GPIO_49, BlackLib::input, BlackLib::SecureMode);

driverDisplay()
{
	BlackLib::BlackGPIO a(BlackLib::GPIO_65, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO b(BlackLib::GPIO_51, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO c(BlackLib::GPIO_47, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO d(BlackLib::GPIO_46, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO e(BlackLib::GPIO_45, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO f(BlackLib::GPIO_44, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO g(BlackLib::GPIO_27, BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO dp(BlackLib::GPIO_26, BlackLib::output, BlackLib::SecureMode);


	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("a",a));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("b",b));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("c",c));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("d",d));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("e",e));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("f",f));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("g",g));
	displayMap.insert(std::pair<std::string,BlackLib::BlackGPIO>("dp",dp));

	//b,c
	um.push_back("b");
	um.push_back("c");

	//a,b,g,e,d
	dois.push_back("a");//a,b,g,e,d
	dois.push_back("b");
	dois.push_back("g");
	dois.push_back("e");
	dois.push_back("d");

	//a,b,g,c,d
	tres.push_back("a");
	tres.push_back("b");
	tres.push_back("g");
	tres.push_back("c");
	tres.push_back("d");

	//f,g,b,c
	quatro.push_back("f");
	quatro.push_back("g");
	quatro.push_back("b");
	quatro.push_back("c");

	//a,f,g,c,d
	cinco.push_back("a");
	cinco.push_back("f");
	cinco.push_back("g");
	cinco.push_back("c");
	cinco.push_back("d");

	//a,f,g,e,c,d
	seis.push_back("a");
	seis.push_back("f");
	seis.push_back("g");
	seis.push_back("e");
	seis.push_back("c");
	seis.push_back("d");

	//a,b,c
	sete.push_back("a");
	sete.push_back("b");
	sete.push_back("c");

	//a,b,c,e,d,f,g
	oito.push_back("a");
	oito.push_back("b");
	oito.push_back("c");
	oito.push_back("d");
	oito.push_back("e");
	oito.push_back("f");
	oito.push_back("g");

	//a,b,c,f
	nove.push_back("a");
	nove.push_back("b");
	nove.push_back("c");
	nove.push_back("f");

	//a,b,c,d,e,f
	zero.push_back("a");
	zero.push_back("b");
	zero.push_back("c");
	zero.push_back("d");
	zero.push_back("e");
	zero.push_back("f");
}

void show(int num, int display)
{
	std::vector<std::string>::iterator itr;
	switch(num)
	{
		case 0:
			for(itr = zero.begin();itr != zero.end();itr++)
			{
				displayMap.find((*itr)).
			}
			break;
			
	}
}


#endif //UTILS_H_
