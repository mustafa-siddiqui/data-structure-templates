/**
 * @file    node.h
 * @author  Mustafa Siddiqui
 * @brief   Template class for a node.
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _NODE_H_
#define _NODE_H_

/**
 * =====================================================
 * INCLUDES
 * =====================================================
 */

#include <iostream>

#include "interfaces/node-intf.h"
#include "logging/logging.h"

/**
 * =====================================================
 * CLASS DEFINITIONS
 * =====================================================
 */

/**
 * @brief Template class for a node. Inherits from the
 * interface for a node class.
 */
template <typename T>
class NODE : public NODE_INTF<T> {
private:
    uint32_t myId;
    T myVal;
    std::shared_ptr<NODE_INTF<T>> nextNodePtr;
    std::shared_ptr<NODE_INTF<T>> prevNodePtr;

public:
    // delete default constructor
    NODE() = delete;

    // constructor
    // default values of empty string and val=0
    explicit NODE(T value, uint32_t id = 0)
        : NODE_INTF<T>(),
          myId(id),
          myVal(value),
          nextNodePtr(nullptr),
          prevNodePtr(nullptr) {
        LOGGING::logMessage(this->toString() + " created");
    }

    /**
     * =====================================================
     * INTERFACE METHODS DEFINITIONS
     * =====================================================
     */

    // destructor
    ~NODE() override {
        LOGGING::logMessage(this->toString() + " destroyed");
    }

    // set id of object
    void setID(uint32_t newId) override { this->myId = newId; }

    // return id of object
    uint32_t getID() const override { return this->myId; }

    // return value stored in object
    T getValue() const override { return this->myVal; }

    // declaration and definition is split due to
    // template specializations required
    std::string toString() const override;

    // set next node to given node
    void setNextNodePtr(
        std::shared_ptr<NODE_INTF<T>>& nodePtr) override {
        this->nextNodePtr = nodePtr;
    }

    // get pointer to the next node
    std::shared_ptr<NODE_INTF<T>> getNextNodePtr() const override {
        return this->nextNodePtr;
    }

    // set previous node to given node
    void setPrevNodePtr(
        std::shared_ptr<NODE_INTF<T>>& nodePtr) override {
        this->prevNodePtr = nodePtr;
    }

    // get pointer to the previous node
    std::shared_ptr<NODE_INTF<T>> getPrevNodePtr() const override {
        return this->prevNodePtr;
    }

    // '<<' operator overload
    friend std::ostream& operator<<(std::ostream& os,
                                    const NODE<T>& nodeObj) {
        os << nodeObj.toString();
        return os;
    }

    // '==' operator overload
    friend bool operator==(const NODE_INTF<T>& lhs, const NODE_INTF<T>& rhs) {
        LOGGING::logMessage("NODE == operator used");
        return (lhs.getID() == rhs.getID() && lhs.getValue() == rhs.getValue());
    }
};

// template method
template <typename T>
std::string NODE<T>::toString(void) const {
    return "[Node Value: " + std::to_string(this->getValue()) +
           ", Node ID: " + std::to_string(this->getID()) + "]";
}

// template specialization when type = char
template <>
std::string NODE<char>::toString(void) const {
    return "[Node Value: " + std::string(1, this->getValue()) +
           ", Node ID: " + std::to_string(this->getID()) + "]";
}

// template specialization when type = string
template <>
std::string NODE<std::string>::toString(void) const {
    return "[Node Value: " + this->getValue() +
           ", Node ID: " + std::to_string(this->getID()) + "]";
}

#endif /* _NODE_H_ */
