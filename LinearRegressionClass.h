#ifndef LINEAR_REGRESSION_CLASS_H
#define LINEAR_REGRESSION_CLASS_H

#include <vector>

/**
 * @brief A class representing linear regression analysis.
 *
 * @tparam num The numeric type for calculations.
 */
template <typename num>
class LinearRegression {
public:
    /**
     * @brief Calculates the mean (average) of a vector of numeric values.
     *
     * @param findMean The vector for which to calculate the mean.
     * @return The mean of the vector.
     */
    num meanFinder(const std::vector<num>& findMean);

    /**
     * @brief Calculates the slope of a linear regression model.
     *
     * @param xValues The vector of X values.
     * @param yValues The vector of Y values.
     * @return The slope of the linear regression model.
     */
    num calculateSlope(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& xMean, const num& yMean);

    /**
     * @brief Calculates the intercept of a linear regression model.
     *
     * @param xValues The vector of X values.
     * @param yValues The vector of Y values.
     * @return The intercept of the linear regression model.
     */
    num calculateIntercept(const num& xMean, const num& yMean, const num& slope);

    /**
     * @brief Calculates the coefficient of determination (R^2) for a linear regression model.
     *
     * @param xValues The vector of X values.
     * @param yValues The vector of Y values.
     * @return The coefficient of determination (R^2).
     */
    num calculateR2(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& slope, const num& intercept);

};

#endif // LINEAR_REGRESSION_CLASS_H
