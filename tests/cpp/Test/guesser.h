#pragma once

#ifndef __GUESSER_H_INCLUDED
#define __GUESSER_H_INCLUDED

#include <string>
#include <memory>

/// @brief Класс для игры "угадай животное".
class Guesser
{
private:
     struct Node
     {
          std::unique_ptr<Node> yes;
          std::unique_ptr<Node> no;
          std::string str;

          Node(std::string name, std::unique_ptr<Node> &&yesNode = nullptr, std::unique_ptr<Node> &&noNode = nullptr)
               : str(name), yes(std::move(yesNode)), no(std::move(noNode))
          {
          }
     };

     std::unique_ptr<Node> root;
     std::unique_ptr<Node>* curNode;
     std::unique_ptr<Node>* parent;
     bool isYesTrace;

public:
     /// @brief Конструктор.
     /// @param[in] initialAnimal Принимает первое животное, известное системе.
     Guesser(const std::string &initialAnimal) : isYesTrace(true), parent(nullptr)
     {
          root = std::make_unique<Node>(Node(initialAnimal));
          curNode = &root;
     }

     /// @brief Метод получения текущего вопроса системы.
     /// @warning Может быть вызван несколько раз подряд до получения ответа.
     /// @return Пару вида ("question", <строка с вопросом, как он был введён в систему>), если вопрос.
     /// @return Пару вида ("animal", <строка с животным, как оно было введено в систему>), если вопрос.
     std::pair<std::string, std::string> Request()
     {
          if (nullptr == (*curNode)->yes)
               return {"animal", (*curNode)->str};
          return {"question", (*curNode)->str};
     }

     /// @brief На текущий вопрос системы ответ "Да".
     /// @warning Если Request() возвращает кортеж с "animal", то обновляет сессию.
     void Yes()
     {
          parent = curNode;
          if (nullptr == (*curNode)->yes)
               curNode = &root;
          else
          {
               curNode = &(*curNode)->yes;
               isYesTrace = true;
          }
     }

     /// @brief На текущий вопрос системы ответ "Нет".
     void No()
     {
          if (nullptr != (*curNode)->no)
          {
               parent = curNode;
               curNode = &(*curNode)->no;
               isYesTrace = false;
          }
     }

     /// @brief Ввести определение, если система не угадала животное.
     /// @param[in] question Вопрос.
     /// @param[in] animal Животное.
     /// @details Принимаемое животное является ответом "Да" на принимаемый вопрос, а ответом "Нет" является животное, получаемое Request().
     /// @warning Обновляет сессию.
     void AddDef(const std::string &question, const std::string &animal)
     {
          auto newAnimal = std::make_unique<Node>(animal);
          if (nullptr == root->yes)
          {
               auto newQuestion = std::make_unique<Node>(question, std::move(newAnimal), std::move(root));
               root = std::move(newQuestion);
          }
          else
          {
               auto newQuestion = std::make_unique<Node>(question, std::move(newAnimal), std::move(*curNode));
               if (isYesTrace)
                    (*parent)->yes = std::move(newQuestion);
               else
                    (*parent)->no = std::move(newQuestion);
          }
          parent = curNode;
          curNode = &root;
     }
};

#endif // __GUESSER_H_INCLUDED
