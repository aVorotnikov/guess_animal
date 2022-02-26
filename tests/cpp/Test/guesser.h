#pragma once

#ifndef __GUESSER_H_INCLUDED
#define __GUESSER_H_INCLUDED

#include <string>
#include <memory>

/// @brief ����� ��� ���� "������ ��������".
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
     /// @brief �����������.
     /// @param[in] initialAnimal ��������� ������ ��������, ��������� �������.
     Guesser(const std::string &initialAnimal) : isYesTrace(true), parent(nullptr)
     {
          root = std::make_unique<Node>(Node(initialAnimal));
          curNode = &root;
     }

     /// @brief ����� ��������� �������� ������� �������.
     /// @warning ����� ���� ������ ��������� ��� ������ �� ��������� ������.
     /// @return ���� ���� ("question", <������ � ��������, ��� �� ��� ����� � �������>), ���� ������.
     /// @return ���� ���� ("animal", <������ � ��������, ��� ��� ���� ������� � �������>), ���� ������.
     std::pair<std::string, std::string> Request()
     {
          if (nullptr == (*curNode)->yes)
               return {"animal", (*curNode)->str};
          return {"question", (*curNode)->str};
     }

     /// @brief �� ������� ������ ������� ����� "��".
     /// @warning ���� Request() ���������� ������ � "animal", �� ��������� ������.
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

     /// @brief �� ������� ������ ������� ����� "���".
     void No()
     {
          if (nullptr != (*curNode)->no)
          {
               parent = curNode;
               curNode = &(*curNode)->no;
               isYesTrace = false;
          }
     }

     /// @brief ������ �����������, ���� ������� �� ������� ��������.
     /// @param[in] question ������.
     /// @param[in] animal ��������.
     /// @details ����������� �������� �������� ������� "��" �� ����������� ������, � ������� "���" �������� ��������, ���������� Request().
     /// @warning ��������� ������.
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
