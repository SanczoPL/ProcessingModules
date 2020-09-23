#include "opencv_gmg.h"
#include <QJsonObject>

constexpr auto INITIALIZATION_FRAMES{ "InitializationFrames" };
constexpr auto DECISION_THRESHOLD{ "DecisionThreshold" };

Subtractors::GMG::GMG(QJsonObject const &a_config)
  : m_initializationFrames{ a_config[INITIALIZATION_FRAMES].toInt() }
  , m_decisionThreshold{ a_config[DECISION_THRESHOLD].toDouble() }

{
  m_backgroundSubtractor = cv::bgsegm::createBackgroundSubtractorGMG(m_initializationFrames, m_decisionThreshold);
}
void Subtractors::GMG::process(std::vector<_data> &_data)
{
  cv::Mat out;
  m_backgroundSubtractor->apply(_data[0].processing, out);
  _data[0].processing = out;
}
