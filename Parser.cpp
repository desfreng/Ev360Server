//
// Created by gabriel on 13/06/2020.
//

#include "Parser.h"

Parser::Parser(const std::string &token) {
    _t = token;
}

void Parser::addData(std::string data) {
    std::string strAction;
    while (!data.empty()) {
        strAction = nextToken(data);

        if (strAction == "PO") {
            int intData = std::stoi(nextToken(data));
            _data.push(Action(ActionEnum::Power, intData));
        } else if (strAction == "DI") {
            int intData = std::stoi(nextToken(data));
            _data.push(Action(ActionEnum::Direction, intData));
        } else if (strAction == "ST") {
            _data.push(Action(ActionEnum::Stop, 0));
        } else if (strAction == "TL") {
            _data.push(Action(ActionEnum::TurnLeft, 0));
        } else if (strAction == "TR") {
            _data.push(Action(ActionEnum::TurnRight, 0));
        } else if (strAction == "RW") {
            _data.push(Action(ActionEnum::ResetWheels, 0));
        }
    }
}

Parser::Action Parser::lastAction() {
    Action action;

    if (!isEmpty()) {
        action = _data.front();
        _data.pop();
    } else {
        action.action = None;
    }

    return action;
}

bool Parser::isEmpty() const {
    return _data.empty();
}

std::string Parser::nextToken(std::string &data) {
    size_t pos = data.find(_t);
    std::string value;

    if (pos != std::string::npos) {
        value = data.substr(0, pos);
        data.erase(0, pos + _t.size());
    } else {
        value = data;
        data.erase(0, data.size());
    }
    return value;
}

Parser::Action::Action(Parser::ActionEnum anEnum, int i) {
    action = anEnum;
    data = i;
}

Parser::Action::Action() {
    action = None;
    data = 0;
}

std::string Parser::Action::toString() const {
    switch (action) {
        case TurnRight:
            return "TurnRight";
        case TurnLeft:
            return "TurnLeft";
        case Stop:
            return "Stop";
        case ResetWheels:
            return "ResetWheels";
        case Direction:
            return "Direction : " + std::to_string(data);
        case Power:
            return "Power : " + std::to_string(data);
        case None:
            return "None";
    }
}
