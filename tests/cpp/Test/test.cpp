#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>

#include "guesser.h"

class Animal
{
public:
     Animal(const std::string& name0, const std::vector<std::string>& attribs0) :
          name(name0), attribs(attribs0)
     {
     }

     bool Match(const std::string& str) const
     {
          std::vector<std::string> question;
          std::istringstream iss(str);
          std::copy(std::istream_iterator<std::string>(iss),
               std::istream_iterator<std::string>(),
               std::back_inserter(question));

          if (question.size() == 0 || question.size() > 2)
               throw std::exception("");
          bool val = std::find(attribs.begin(), attribs.end(), question.back()) != attribs.end();
          return question.size() == 1 ? val : !val;
     }

     std::string GetDiff(const Animal& animal) const
     {
          for (const auto& attr : attribs)
               if (std::find(animal.attribs.begin(), animal.attribs.end(), attr) == animal.attribs.end())
                    return attr;
          for (const auto& attr : animal.attribs)
               if (std::find(attribs.begin(), attribs.end(), attr) == attribs.end())
                    return "Not " + attr;
          return "";
     }

     std::string GetName() const
     {
          return name;
     }

private:
     std::string name;
     std::vector<std::string> attribs;
};

bool AddAnimal(Guesser& guesser, const Animal& animal, const std::vector<Animal>& animals)
{
     while (true)
     {
          auto response = guesser.Request();
          if (response.first == "question")
               if (animal.Match(response.second))
                    guesser.Yes();
               else
                    guesser.No();
          else
               if (response.second == animal.GetName())
               {
                    guesser.Yes();
                    return false;
               }
               else
               {
                    for (const auto& an : animals)
                         if (response.second == an.GetName())
                         {
                              guesser.No();
                              guesser.AddDef(animal.GetDiff(an), animal.GetName());
                              return true;
                         }
                    return false;
               }
     }
}

bool CheckAnimal(Guesser &guesser, const Animal &animal, const std::vector<Animal> &animals)
{
     while (true)
     {
          auto response = guesser.Request();
          if (response.first == "question")
               if (animal.Match(response.second))
                    guesser.Yes();
               else
                    guesser.No();
          else
               if (response.second == animal.GetName())
               {
                    guesser.Yes();
                    return true;
               }
               else
               {
                    for (const auto &an : animals)
                         if (response.second == an.GetName())
                         {
                              guesser.No();
                              guesser.AddDef(animal.GetDiff(an), animal.GetName());
                              return false;
                         }
                    return false;
               }
     }
}

int main()
{
     std::ifstream animalFile("../../../../../animals.txt");
     if (!animalFile.is_open())
          return 0;

     std::string line;
     std::vector<Animal> animals;
     while (std::getline(animalFile, line))
     {
          std::vector<std::string> words;
          std::istringstream iss(line);
          std::copy(std::istream_iterator<std::string>(iss),
               std::istream_iterator<std::string>(),
               std::back_inserter(words));

          if (words.size() == 0)
               continue;

          std::vector<std::string> attribs(words.begin() + 1, words.end());
          animals.push_back(Animal(words[0], attribs));
     }

     int score = 0;
     Guesser guesser(animals[0].GetName());
     score += CheckAnimal(guesser, animals[0], animals);

     for (int i = 1; i < 11; i++)
          AddAnimal(guesser, animals[i], animals);

     score += CheckAnimal(guesser, animals[0], animals);
     score += CheckAnimal(guesser, animals[8], animals);
     score += CheckAnimal(guesser, animals[5], animals);

     for (int i = 11; i < animals.size(); i++)
          AddAnimal(guesser, animals[i], animals);

     score += CheckAnimal(guesser, animals[0], animals);
     score += CheckAnimal(guesser, animals[8], animals);
     score += CheckAnimal(guesser, animals[86], animals);
     score += CheckAnimal(guesser, animals[51], animals);
     score += CheckAnimal(guesser, animals[16], animals);
     score += CheckAnimal(guesser, animals[43], animals);

     std::cout << score;

     return 0;
}
