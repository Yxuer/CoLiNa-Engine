//
// Created by usuario on 19/8/19.
//

#ifndef COLINA_ENGINE_GAMEEXCEPTIONS_H
#define COLINA_ENGINE_GAMEEXCEPTIONS_H

#include <exception>

class TooManyWordsException : public std::exception {
    public :
      virtual const char* what() const throw() {
          return "Error: too many words given. Write 2-word commands";
      }
} tooManyWordsException;

class InvalidExamineException : public std::exception {
    public:
       virtual const char* what() const throw() {
           return "Error: the only valid 1-word command is \"examine\"";
       }
} invalidExamineException;

#endif //COLINA_ENGINE_GAMEEXCEPTIONS_H

