//
// Created by usuario on 19/8/19.
//

#ifndef COLINA_ENGINE_GAMEEXCEPTIONS_H
#define COLINA_ENGINE_GAMEEXCEPTIONS_H

#include <exception>

class LesserException : public std::exception {};

class TooManyWordsException : public LesserException {
    public :
      virtual const char* what() const throw() {
          return "Error: too many words given. Write 2-word commands";
      }
} tooManyWordsException;

class InvalidExamineException : public LesserException {
    public:
       virtual const char* what() const throw() {
           return "Error: the only valid 1-word command is \"examine\"";
       }
} invalidExamineException;

class FatalException : public std::exception {};

#endif //COLINA_ENGINE_GAMEEXCEPTIONS_H

