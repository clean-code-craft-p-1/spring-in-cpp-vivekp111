#include "stats.h"
#include "gtest/gtest.h"
#include <cmath>
#include <cfloat>

using namespace Statistics;

TEST(Statistics, ReportsAverageMinMax) {
    auto computedStats = Statistics::ComputeStatistics({1.5, 8.9, 3.2, 4.5});
    float epsilon = 0.001f;
    EXPECT_LT(std::abs(computedStats.average - 4.525), epsilon);
    EXPECT_LT(std::abs(computedStats.max - 8.9), epsilon);
    EXPECT_LT(std::abs(computedStats.min - 1.5), epsilon);
}

TEST(Statistics, AverageNaNForEmpty) {
    auto computedStats = Statistics::ComputeStatistics({});
    //All fields of computedStats (average, max, min) must be
    //NAN (not-a-number), as defined in math.h

    //Design the REQUIRE statement here.
    //Use http://www.cplusplus.com/reference/cmath/isnan/
    EXPECT_EQ(TRUE, isnan(computedStats.average));
    EXPECT_EQ(TRUE, isnan(computedStats.max));
    EXPECT_EQ(TRUE, isnan(computedStats.min));
}

TEST(Alert, AlertsWhenMaxExceeds) {
    Statistics::EmailAlert emailAlert;
    Statistics::LEDAlert ledAlert;
    std::vector<IAlerter*> alerters = {&emailAlert, &ledAlert};
    
    const float maxThreshold = 10.2f;
    
    Statistics::StatsAlerter statsAlerter(maxThreshold, alerters);
    statsAlerter.checkAndAlert({99.8, 34.2, 4.5, 6.7});

    EXPECT_TRUE(emailAlert.emailSent);
    EXPECT_TRUE(ledAlert.ledGlows);
}

//Google test main entry point
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}
