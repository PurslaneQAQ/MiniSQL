#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Config.h"
#include "Catalog.h"
#include "API.h"
#if DEBUG
#include "MiniSQL_ABC.h"
#endif

class INTERPRETER
{
public:
    INTERPRETER();
    QString& Interpret(const QString &input) const;  // Its functions are as below:
                                                     // contact interface(DBMS_UI) and get input
                                                     // recognize different oprations and call API accordingly
                                                     // also deal with spript with multiple statements(execfile) and exit
                                                     // build the CONDITION_TREE (defined by Data_Struct) if necessary
                                                     // catch all the errors from below and throw them to interface
                                                     // also deal with invalid input statement
                                                     // divided into smaller functions is encouraged
};

#endif // INTERPRETER_H
