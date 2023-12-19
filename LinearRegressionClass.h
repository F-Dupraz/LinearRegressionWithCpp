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
    std::vector<num> coefficients;  /**< Coefficients of the linear regression model. */
    num intercept;  /**< Intercept of the linear regression model. */
    num R2;  /**< Coefficient of determination (R^2) for the linear regression model. */

    ~LinearRegression();

    /**
     * @brief Fit a linear regression model to the given data.
     *
     * @param xValues Matrix of independent variable values.
     * @param yValues Vector of dependent variable values.
     * @return The coefficient of determination (R^2) for the fitted model.
     */
    num fit(const std::vector<std::vector<num>>& xValues, const std::vector<num>& yValues);

    /**
     * @brief Predict the dependent variable value for a given independent variable value.
     *
     * @param xValues The independent variable value for prediction.
     * @return The predicted dependent variable value.
     */
    num predict(const std::vector<num>& xValues) const;

    /**
     * @brief Get the slope (coefficient) of the linear regression model.
     *
     * @return The slope of the linear regression model.
     */
    num getSlope() const;

    /**
     * @brief Get the intercept of the linear regression model.
     *
     * @return The intercept of the linear regression model.
     */
    num getIntercept() const;

private:
    /**
     * @brief Calculates the mean (average) of a vector of numeric values.
     *
     * @param findMean The vector for which to calculate the mean.
     * @return The mean of the vector.
     */
    num meanFinder(const std::vector<num>& findMean) const;

    /**
     * @brief Calculates the means of each column in a matrix.
     *
     * @param xValues Matrix of numeric values.
     * @param means Vector to store the means of each column.
     */
    void calculateMeans(const std::vector<std::vector<num>>& xValues, std::vector<num>& means) const;

    /**
     * @brief Calculates the intercept of a linear regression model.
     *
     * @param xMeans Vector of mean values for each independent variable.
     */
    void calculateIntercept(const std::vector<num>& xMeans, const num& yMeans);
};

#endif // LINEAR_REGRESSION_CLASS_H
