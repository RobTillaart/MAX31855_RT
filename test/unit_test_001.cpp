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


#include "Arduino.h"
#include "MAX31855.h"


unittest_setup()
{
  fprintf(stderr, "MAX31855_VERSION: %s\n", (char *) MAX31855_VERSION);
}


unittest_teardown()
{
}


unittest(test_constants)
{
  assertEqual(0x00, STATUS_OK);
  assertEqual(0x01, STATUS_OPEN_CIRCUIT);
  assertEqual(0x02, STATUS_SHORT_TO_GND);
  assertEqual(0x04, STATUS_SHORT_TO_VCC);
  assertEqual(0x07, STATUS_ERROR);
  assertEqual(0x80, STATUS_NOREAD);
  assertEqual(0x81, STATUS_NO_COMMUNICATION);

  assertEqual(-999, MAX31855_NO_TEMPERATURE);
}


unittest(test_status)
{
  const int doPin = 7;
  const int csPin = 6;
  const int clPin = 5;

  MAX31855 tc;
  tc.begin(clPin, csPin, doPin);

  fprintf(stderr, "Status...\n");
  assertEqual(STATUS_NOREAD, (int)tc.getStatus());
  assertEqual(0, tc.lastRead());
  assertEqual(0, tc.getRawData());
  assertFalse(tc.openCircuit());
  assertFalse(tc.shortToGND());
  assertFalse(tc.shortToVCC());
  assertFalse(tc.genericError());
  assertFalse(tc.noCommunication());
  assertTrue(tc.noRead());
}


unittest(test_temperature)
{
  const int doPin = 7;
  const int csPin = 6;
  const int clPin = 5;

  MAX31855 tc;
  tc.begin(clPin, csPin, doPin);

  fprintf(stderr, "Temperature...\n");
  assertEqualFloat(MAX31855_NO_TEMPERATURE, tc.getInternal(), 0.001);
  assertEqualFloat(MAX31855_NO_TEMPERATURE, tc.getTemperature(), 0.001);

  fprintf(stderr, "\nOffset...\n");
  for (int of = 0; of < 10; of++)
  {
    tc.setOffset(of * 0.1);
    fprintf(stderr, "%f\t", of * 0.1);
    assertEqualFloat(of * 0.1, tc.getOffset(), 0.001);
  }

  fprintf(stderr, "\nSeebeckCoefficient...\n");
  for (float sbc = 9; sbc < 100; sbc += 12.345)    //  non existent still good for test.
  {
    tc.setSeebeckCoefficient(sbc);
    fprintf(stderr, "%f\t", sbc);
    assertEqualFloat(sbc, tc.getSeebeckCoefficient(), 0.001);
  }
}


unittest(test_SPIspeed_SWSPIdelay)
{
  const int doPin = 7;
  const int csPin = 6;
  const int clPin = 5;

  MAX31855 tc;
  tc.begin(clPin, csPin, doPin);

  fprintf(stderr, "SPIspeed...\n");
  for (uint32_t sp = 100000; sp <= 1000000; sp += 100000)
  {
    tc.setSPIspeed(sp);
    fprintf(stderr, "%ld\t", sp);
    assertEqual(sp, tc.getSPIspeed());
  }

  fprintf(stderr, "\nsetSWSPIdelay...\n");
  for (uint16_t del = 0; del < 11; del++)
  {
    tc.setSWSPIdelay(del);
    fprintf(stderr, "%d\t", del);
    assertEqual(del, tc.getSWSPIdelay());
  }
}


unittest_main()


//  -- END OF FILE --
