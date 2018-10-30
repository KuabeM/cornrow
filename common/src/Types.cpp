#include "Types.h"

namespace common
{

const std::set<int> validSampleRates = {
    44100,
    48000
};

Config::Config(Source source_, int rate_, SampleFormat format_, std::string watchFilename_)
    : source(source_),
      rate(rate_),
      format(format_),
      watchFilename(watchFilename_)
{
}

// Renard R40
const std::vector<float> twelfthOctaveBandsTable = {
    16.0,     17.0,    18.0,    19.0,
    20.0,     21.2,    22.4,    23.6,
    25.0,     26.5,    28.0,    30.0,
    31.5,     33.5,    35.5,    37.5,
    40.0,     42.5,    45.0,    47.5,
    50.0,     53.0,    56.0,    60.0,
    63.0,     67.0,    71.0,    75.0,
    80.0,     85.0,    90.0,    95.0,
    100.0,    106.0,   112.0,   118.0,
    125.0,    132.0,   140.0,   150.0,
    160.0,    170.0,   180.0,   190.0,
    200.0,    212.0,   224.0,   236.0,
    250.0,    265.0,   280.0,   300.0,
    315.0,    335.0,   355.0,   375.0,
    400.0,    425.0,   450.0,   475.0,
    500.0,    530.0,   560.0,   600.0,
    630.0,    670.0,   710.0,   750.0,
    800.0,    850.0,   900.0,   950.0,
    1000.0,  1060.0,  1120.0,  1180.0,
    1250.0,  1320.0,  1400.0,  1500.0,
    1600.0,  1700.0,  1800.0,  1900.0,
    2000.0,  2120.0,  2240.0,  2360.0,
    2500.0,  2650.0,  2800.0,  3000.0,
    3150.0,  3350.0,  3550.0,  3750.0,
    4000.0,  4250.0,  4500.0,  4750.0,
    5000.0,  5300.0,  5600.0,  6000.0,
    6300.0,  6700.0,  7100.0,  7500.0,
    8000.0,  8500.0,  9000.0,  9500.0,
    10000.0, 10600.0, 11200.0, 11800.0,
    12500.0, 13200.0, 14000.0, 15000.0,
    16000.0, 17000.0, 18000.0, 19000.0,
    20000.0, 21200.0
};

// Renard R80
const std::vector<float> twentyFourthOctaveBandsTable {
      16.0,     16.5,    17.0,    17.5,    18.0,    18.5,    19.0,    19.5,

      20.0,     20.6,    21.2,    21.8,    22.4,    23.0,    23.6,    24.3,
      25.0,     25.8,    26.5,    27.2,    28.0,    29.0,    30.0,    30.7,
      31.5,     32.5,    33.5,    34.5,    35.5,    36.5,    37.5,    38.7,
      40.0,     41.2,    42.5,    43.7,    45.0,    46.2,    47.5,    48.7,
      50.0,     51.5,    53.0,    54.5,    56.0,    57.5,    60.0,    61.5,
      63.0,     65.0,    67.0,    69.0,    71.0,    73.0,    75.0,    77.5,
      80.0,     82.5,    85.0,    87.5,    90.0,    92.5,    95.0,    97.5,
     100.0,    103.0,   106.0,   109.0,   112.0,   115.0,   118.0,   122.0,
     125.0,    128.0,   132.0,   136.0,   140.0,   145.0,   150.0,   155.0,
     160.0,    165.0,   170.0,   175.0,   180.0,   185.0,   190.0,   195.0,

     200.0,    206.0,   212.0,   218.0,   224.0,   230.0,   236.0,   243.0,
     250.0,    258.0,   265.0,   272.0,   280.0,   290.0,   300.0,   307.0,
     315.0,    325.0,   335.0,   345.0,   355.0,   365.0,   375.0,   387.0,
     400.0,    412.0,   425.0,   437.0,   450.0,   462.0,   475.0,   487.0,
     500.0,    515.0,   530.0,   545.0,   560.0,   575.0,   600.0,   615.0,
     630.0,    650.0,   670.0,   690.0,   710.0,   730.0,   750.0,   775.0,
     800.0,    825.0,   850.0,   875.0,   900.0,   925.0,   950.0,   975.0,
     1000.0,  1030.0,  1060.0,  1090.0,  1120.0,  1150.0,  1180.0,  1220.0,
     1250.0,  1280.0,  1320.0,  1360.0,  1400.0,  1450.0,  1500.0,  1550.0,
     1600.0,  1650.0,  1700.0,  1750.0,  1800.0,  1850.0,  1900.0,  1950.0,

     2000.0,  2060.0,  2120.0,  2180.0,  2240.0,  2300.0,  2360.0,  2430.0,
     2500.0,  2580.0,  2650.0,  2720.0,  2800.0,  2900.0,  3000.0,  3070.0,
     3150.0,  3250.0,  3350.0,  3450.0,  3550.0,  3650.0,  3750.0,  3870.0,
     4000.0,  4120.0,  4250.0,  4370.0,  4500.0,  4620.0,  4750.0,  4870.0,
     5000.0,  5150.0,  5300.0,  5450.0,  5600.0,  5750.0,  6000.0,  6150.0,
     6300.0,  6500.0,  6700.0,  6900.0,  7100.0,  7300.0,  7500.0,  7750.0,
     8000.0,  8250.0,  8500.0,  8750.0,  9000.0,  9250.0,  9500.0,  9750.0,
    10000.0, 10300.0, 10600.0, 10900.0, 11200.0, 11500.0, 11800.0, 12200.0,
    12500.0, 12800.0, 13200.0, 13600.0, 14000.0, 14500.0, 15000.0, 15500.0,
    16000.0, 16500.0, 17000.0, 17500.0, 18000.0, 18500.0, 19000.0, 19500.0,

    20000.0, 20600.0, 21200.0, 21800.0 //, 22400.0, 23000.0, 23600.0
};

// Renard R20 most rounded
const std::vector<float> qTable {
    0.10,  0.11,
    0.12,  0.14,
    0.16,  0.18,
    0.20,  0.22,
    0.25,  0.28,
    0.30,  0.35,
    0.40,  0.45,
    0.50,  0.55,
    0.60,  0.70,
    0.80,  0.90,
    1.00,  1.10,
    1.20,  1.40,
    1.60,  1.80,
    2.00,  2.20,
    2.50,  2.80,
    3.00,  3.50,
    4.00,  4.50,
    5.00,  5.50,
    6.00,  7.00,
    8.00,  9.00,
    10.00, 11.00,
    12.00, 14.00,
    16.00, 18.00,
    20.00, 22.00,
    25.00, 28.00,
    30.00, 35.00,
    40.00, 45.00,
    50.00
};

} // namespace common
