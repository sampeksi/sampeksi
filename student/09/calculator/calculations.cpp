// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double power(double left, double right) {

    double power = 1;
    double calc = right;
    while (calc > 0) {
        power *= left;
        calc -= 1;
    }
    return power;
}
