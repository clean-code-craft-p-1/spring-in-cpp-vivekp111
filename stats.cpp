#include<iostream>
#include "stats.h"
#include<cfloat>
#include <cmath>
using namespace std;
using namespace Statistics;

Stats Statistics::ComputeStatistics(const std::vector<double>& computedStats)
{
    static Stats stData = {0};

    if (computedStats.size() > 0)
    {
        /* Average calcuation */
        for (auto Value : computedStats)
        {
            stData.average = stData.average + Value;
        }
        stData.average = stData.average / computedStats.size();

        /* Max caluclation */
        double max = 0.0;
        for (auto value : computedStats)
        {
            if (value > max)
            {
                max = value;
            }
        }
        stData.max = max;

        /* Min caluclation */
        double min = DBL_MAX;
        for (auto value : computedStats)
        {
            if (value < min)
            {
                min = value;
            }
        }
        stData.min = min;
    }
    else
    {
        stData.average = std::nan("NaN");
        stData.min = std::nan("NaN");
        stData.max = std::nan("NaN");
    }

    return stData;
}

void EmailAlert::SetAlert(void)
{
    emailSent = TRUE;
}

void LEDAlert::SetAlert(void)
{
    ledGlows = TRUE;
}

void StatsAlerter::checkAndAlert(const std::vector<double>& computedStats)
{
    double max = 0.0;
    for (auto value : computedStats)
    {
        if (value > max)
        {
            max = value;
        }
    }
    /* Check for threashold */
    if (max > m_maxThreshold)
    {
        for (auto value : m_vIAlerter)
        {
            value->SetAlert();
        }
    }
}
