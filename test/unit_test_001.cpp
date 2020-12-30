//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the MAX31855_RT Thermocouple library
//          https://github.com/RobTillaart/MAX31855_RT
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

// #define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
// #define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
// #define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "MAX31855.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", MAX31855_VERSION);
  
  const int doPin = 7;
  const int csPin = 6;
  const int clPin = 5;

  MAX31855 tc(clPin, csPin, doPin);
  tc.begin();
  /*
    float   getInternal(void) const { return _internal; }
  float   getTemperature(void);

  uint8_t getStatus(void) const  { return _status; };
  inline  bool openCircuit()     { return _status == STATUS_OPEN_CIRCUIT; };
  inline  bool shortToGND()      { return _status == STATUS_SHORT_TO_GND; };
  inline  bool shortToVCC()      { return _status == STATUS_SHORT_TO_VCC; };
  inline  bool genericError()    { return _status == STATUS_ERROR; };
  inline  bool noRead()          { return _status == STATUS_NOREAD; };
  inline  bool noCommunication() { return _status == STATUS_NO_COMMUNICATION; };

  // use offset to callibrate the TC.
  void    setOffset(const float  t)   { _offset = t; };
  float   getOffset() const           { return _offset; };

  //  set the above E_TC (etc) Seebrecht Coefficients
  //  one can also set your own optimized values.
  void    setSeebeckCoefficient(const float SC) { _SC = SC; };
  float   getSeebeckCoefficient() const         { return _SC; };

  uint32_t lastRead()            { return _lastRead; };
  uint32_t getRawData()          { return _rawData;};
  
  */
  assertEqual(1, 1);
}

unittest_main()

// --------
