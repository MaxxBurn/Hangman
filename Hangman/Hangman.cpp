#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <Windows.h>

using vecS = std::vector<std::string>;
using vecC = std::vector<char>;
vecS List;
vecC currString;
vecC CurrWordStored;
vecC InputingWord;
std::string category;

struct Player
{
	int hp = 5;
	std::string name;
	int score = 0;
}player;

void Play();

void Color(int color);

void render(int HP)
{
	//Generating the number of _ that user will see on screen

	std::cout << "\n\n";

	//Rendering the Hangman stickman
	switch (HP)
	{
	case 5:
		std::cout << "\n\n";
		break;
	case 4:
		std::cout << "  /\n";
		std::cout << " /\n";
		std::cout << "/\n";
		break;
	case 3:
		std::cout << "     /\n";
		std::cout << "    /\n";
		std::cout << "   /\n";
		std::cout << "  /\n";
		std::cout << " /\n";
		std::cout << "/\n";
		break;
	case 2:
		std::cout << "      ____________\n";
		std::cout << "     /\n";
		std::cout << "    /\n";
		std::cout << "   /\n";
		std::cout << "  /\n";
		std::cout << " /\n";
		std::cout << "/\n";
		break;

	case 1:
		std::cout << "      ____________\n";
		std::cout << "     /       \\ \n";
		std::cout << "    /         \\ \n";
		std::cout << "   /           \\ \n";
		std::cout << "  /\n";
		std::cout << " /\n";
		std::cout << "/\n";
		break;
	case 0:
		std::cout << "      ____________\n";
		std::cout << "     /       \\ \n";
		std::cout << "    /         \\ \n";
		std::cout << "   /           \\ \n";
		std::cout << "  /             O \n";
		std::cout << " /            / | \\ \n";
		std::cout << "/            /  | \\ \n";
		std::cout << "                |     \n";
		std::cout << "              /   \\   \n";
		std::cout << "             /     \\   \n";
		break;
	}
	std::cout << "\t\t\t\tWord :";

	for (int x = 0; x < InputingWord.size(); x++)
	{
		std::cout << InputingWord.at(x) << " ";
	}

	std::cout << "\t";
	//Here deleted
	
	std::cout << "\t\t\t Score :";
	std::cout << player.score;
	std::cout<<"\n\n\nInput letters for the word : ";

	std::cout << "\n\n\n";
}

void WordGenerator()
{
	for (char CurrWord : currString)	
	{
		CurrWordStored.push_back(CurrWord);
		InputingWord.push_back('_');
	}
	render(player.hp);
}

void Initialize(std::string* category)
{
	//Lists of stuff user has to guess
	if (*category == "Clothes" || *category == "1")
		List = { "Shirt","Trousers","Jeans","Bra","Socks","Crop top","Skirt","Dress","Shoes","Underwear","Hoodie",
					"Hat","Gloves","Pants","Suit","Jacksdet","Coat","Sweater","Slippers","Waistcoats","Belt","Jumper",
					"Kimono","Leggings","Tracksuit" };
	else if (*category == "Food" || *category == "2")
		List = { "Spaghetti","Spinach","Soup","Potatoe","Tomatoe","Rice","Bread","Croissant","Bacon","Egg","Ramen" 
					"Broccoli","Cabbage","Pumpkin","Curry","Risotto","Salad","Pizza","Sandwich","Carrot","Meatball"
					"Muffins","Beef","Burger","Cookie"};

	//Generating random thingy
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type>random(0, 24);
	int randomNumber = random(rng);

	std::copy(List[randomNumber].begin(), List[randomNumber].end(), std::back_inserter(currString));

	WordGenerator();
}
auto Information()
{
	
	std::cout << "Enter your stickman name: \t\n\n";
	std::cin >> player.name;
	std::cout << "\n\nChoose a category \n\n 1. Clothes \n\n 2. Food\n\n";
	std::cin >> category;
	
	//Bad Input
	while (category != "Clothes" && category!="Food" && category!="1" && category!="2")
	{std::cout << "\n\nCorrect category please.\n\n"; std::cin >> category;}
	std::cout << "\n\n\n";

	return Initialize(&category);
}

int main()
{	
	Information();
	while(player.hp>0)
		Play();
	Color(4);
	std::cout << "\n\nYour stickman got lynched :( !\n\n\n";	
	Color(7);
}

void Play()
{
//User Input
	char temp;
		//Iterating through the currently stored vector
	auto foundLine = std::find(InputingWord.begin(), InputingWord.end(), ('_'));
	bool in_array = foundLine != InputingWord.end();
		while (in_array)
		{
			int x;
			std::cin >> temp;
			auto foundLine = std::find(CurrWordStored.begin(), CurrWordStored.end(), temp);
			auto found = std::find(CurrWordStored.begin(), CurrWordStored.end(), temp); //toupper maybe isnt needed
			x = std::distance(CurrWordStored.begin(), found);
			if (found != CurrWordStored.end())
			{
				InputingWord.at(x) = temp;
				player.score++;
				render(player.hp);
			}
			else {
				player.hp--;
				render(player.hp);
			}
			foundLine = std::find(InputingWord.begin(), InputingWord.end(), ('_'));
			in_array = foundLine != InputingWord.end();
			if (player.hp <= 0)
				break;
		}
		if (player.hp > 0) {
			CurrWordStored.clear();
			InputingWord.clear();
			Initialize(&category);
		}
}
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
