//
// Created by gabriel on 13/06/2020.
//

#ifndef EV360MOVER_PARSER_H
#define EV360MOVER_PARSER_H

#include <string>
#include <queue>

class Parser {
public:
    enum ActionEnum {
        TurnLeft,
        TurnRight,
        ResetWheels,
        Direction,
        Power,
        Stop,
        None
    };

    struct Action {
        Action();
        Action(ActionEnum anEnum, int i);
        std::string toString() const;

        ActionEnum action;
        int data;
    };

    explicit Parser(const std::string &token);

    void addData(std::string data);

    Action lastAction();

    bool isEmpty() const;

private:
    std::string nextToken(std::string &data);

    std::string _t;
    std::queue<Action> _data;
};


#endif //EV360MOVER_PARSER_H
