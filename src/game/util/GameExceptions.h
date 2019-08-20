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
};

class InvalidExamineException : public LesserException {
    public:
       virtual const char* what() const throw() {
           return "Error: the only valid 1-word command is \"examine\"";
       }
};

class FatalException : public std::exception {};

class FileLoadError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: error while opening the given game file";
        }
};

class InvalidXMLError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: invalid XML file";
        }
};

class InvalidAreaError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: Invalid file: only Area elements can be children of"
                   "the top XML node";
        }
};

class InvalidItemError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: Invalid file: only Item elements can be children of"
                   "Area elements";
        }
};

class InvalidStateError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: Invalid file: only State elements can be children of"
                   "Item elements";
        }
};

class InvalidCommandError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: Invalid file: only Command elements can be children of"
                   "State elements";
        }
};

class InvalidActionError : public FatalException {
    public:
        virtual const char* what() const throw() {
            return "Error: Invalid file: only Action elements can be children of"
                   "Command elements";
        }
};


#endif //COLINA_ENGINE_GAMEEXCEPTIONS_H

