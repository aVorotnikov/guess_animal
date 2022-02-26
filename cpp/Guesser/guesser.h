#pragma once

#ifndef __GUESSER_H_INCLUDED
#define __GUESSER_H_INCLUDED

#include <string>

/// @brief Класс для игры "угадай животное".
class Guesser
{
public:
     /// @brief Конструктор.
     /// @param[in] initialAnimal Принимает первое животное, известное системе.
     Guesser(const std::string &initialAnimal)
     {
          (void)initialAnimal;
     }

     /// @brief Метод получения текущего вопроса системы.
     /// @warning Может быть вызван несколько раз подряд до получения ответа.
     /// @return Пару вида ("question", <строка с вопросом, как он был введён в систему>), если вопрос.
     /// @return Пару вида ("animal", <строка с животным, как оно было введено в систему>), если вопрос.
     std::pair<std::string, std::string> Request()
     {
          return {};
     }

     /// @brief На текущий вопрос системы ответ "Да".
     /// @warning Если Request() возвращает кортеж с "animal", то обновляет сессию.
     void Yes()
     {
     }

     /// @brief На текущий вопрос системы ответ "Нет".
     void No()
     {
     }

     /// @brief Ввести определение, если система не угадала животное.
     /// @param[in] question Вопрос.
     /// @param[in] animal Животное.
     /// @details Принимаемое животное является ответом "Да" на принимаемый вопрос, а ответом "Нет" является животное, получаемое Request().
     /// @warning Обновляет сессию.
     void AddDef(const std::string &question, const std::string &animal)
     {
          (void)question;
          (void)animal;
     }
};

#endif // __GUESSER_H_INCLUDED
