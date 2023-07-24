#include <vector>

namespace Statistics {

#define TRUE ((bool)(1))

typedef struct
{
    double average;
    double max;
    double min;
}Stats;

class IAlerter
{
public:
    virtual void SetAlert(void) = 0;
    virtual ~IAlerter() {};
};

class EmailAlert:public IAlerter
{
public:
    void SetAlert(void) override;
    ~EmailAlert() {};
    bool emailSent{0};
};

class LEDAlert :public IAlerter
{
public:
    void SetAlert(void) override;
    ~LEDAlert() {};
    bool ledGlows{0};
};

class StatsAlerter
{
private:
    float m_maxThreshold{ 0.0f };
    //std::vector<IAlerter*> *m_pIAlerter{ nullptr }; //TODO
    std::vector<IAlerter*> m_vIAlerter;

public:
    StatsAlerter(float maxThreshold, std::vector<IAlerter*> &IAlrt)
    {
        m_maxThreshold = maxThreshold;
        for (auto value : IAlrt)
        {
            m_vIAlerter.push_back(value);
        }
    }
    ~StatsAlerter() {};

public:
    void checkAndAlert(const std::vector<double>& computedStats);
};

Stats ComputeStatistics(const std::vector<double>& computedStats);
}
