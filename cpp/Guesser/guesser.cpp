#include "guesser_realization.h"

#include <iostream>
#include <algorithm>

int main()
{
     std::cout << "Input initial animal: ";
     std::string animal;
     std::getline(std::cin, animal);

     Guesser guesser(animal);
     while (true)
     {
          auto response = guesser.Request();
          std::cout << response.second << "?" << std::endl;
          std::cout << "[Y/N]";

          std::string answer;
          if (!std::getline(std::cin, answer) || answer.empty())
               break;
          std::transform(answer.begin(), answer.end(), answer.begin(),
               [](auto ch) {return static_cast<unsigned char>(std::tolower(ch));});
          if (answer == "yes" || answer == "y")
          {
               guesser.Yes();
               if ("animal" == response.first)
                    std::cout << "Guessed" << std::endl;
          }
          else if (answer == "no" || answer == "n")
          {
               guesser.No();
               if ("animal" == response.first)
               {
                    std::cout << "Input new animal: ";
                    std::string animal;
                    std::getline(std::cin, animal);

                    std::cout << "Input new definition: ";
                    std::string question;
                    std::getline(std::cin, question);

                    guesser.AddDef(question, animal);
               }
          }
          else
               std::cout << "Incorrect input";
     }
}
