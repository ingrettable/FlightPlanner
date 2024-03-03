#pragma once
/**
 * Based on Num.java
 *
 * This class serves as the data class that our transactions will manipulate.
 * It's just an integer wrapper class.
 *
 * @author THE McKilla Gorilla (accept no imposters)
 * @version 2.0
 */
class Num {

private:
    // THE NUMBER THIS CLASS MANAGES
    int num = 0;

public:
    /**
     * Mutator method for the num instance variable.
     *
     * @param initNum The value to set num to.
     */
    void setNum(int initNum) {
        num = initNum;
    }

    /**
     * Accessor method for num.
     *
     * @return The num instance variable value.
     */
    int getNum() {
        return num;
    }

    void andMask(int mask) {
        num = num & mask;
    }

    void orMask(int mask) {
        num = num | mask;
    }
};