# Naive Bayes Classifer
For Udacity Self-driving car nano-degree term 3, [prediction module](https://classroom.udacity.com/nanodegrees/nd013/parts/6047fe34-d93c-4f50-8336-b70ef10cb4b2/modules/27800789-bc8e-4adc-afe0-ec781e82ceae/lessons/a883a337-51c8-471b-a8cf-3911dc429166/concepts/e2ce2c1b-5d5c-4fe4-bc16-19202e37df09).

Usage:
```
mkdir build
cd build
cmake ..
make
./naive-bayes

X_train number of elements 750
X_train element size 4
Y_train number of elements 750
means
  keep: 20.3888 3.69192 10.0303 0.00583049
  left: 19.8067 5.07552 9.96067 -0.971628
  right: 19.5661 2.94745 9.99259 0.958378
stderr
  keep: 131.208 11.6229 1.1466 0.0283561
  left: 151.759 5.59683 0.987353 0.442029
  right: 146.733 5.37123 0.912678 0.420338
X_test number of elements 250
X_test element size 4
Y_test number of elements 250
You got 84.4 percent correct
```
