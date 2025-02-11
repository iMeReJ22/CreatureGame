//
// Created by Jeremi on 30.05.2022.
//

#ifndef PRO01_VALUES_H
#define PRO01_VALUES_H


class Values {


    int maxValue;
    int currentValue;
public:
    Values();

/*!
 * Ten konstruktor ustawia maxValue, i currentValue
 * na parametr maxValue podany w konstruktorze.
 * @param maxValue
 */
    Values(int maxValue);

/*!
 * Ta metoda dodaje do zmiennej currentValue wartość
 * parametru val.
 * @param val
 */
    void plusCurrent(int val);

    int getMaxValue() const;

    void setMaxValue(int maxValue);

    int getCurrentValue() const;

    void setCurrentValue(int currentValue);

/*!
 * Ta metoda ustawia zmienną currentValue na
 * wartość zmiennej maxValue.
 */
    void resetValue();
/*!
 * Ta metoda zprawdza czy wartość currentValue
 * jest mniejsza od zera.
 * @return true kiedy currentValue jest mniejsze od zera
 * inaczej false.
 */
    bool isZero() const;

};
#endif //PRO01_VALUES_H
