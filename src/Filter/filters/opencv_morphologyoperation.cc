#include "opencv_morphologyoperation.h"
#include <QJsonObject>

constexpr auto MORPH_OPERATOR{ "MorphOperator" }; // MorphTypes
constexpr auto MORPH_SIZE{ "MorphSize" };
constexpr auto MORPH_ELEMENT{ "MorphElement" }; // MorphShapes

Filters::MorphologyOperation::MorphologyOperation(QJsonObject const &a_config)
  : m_morphOperator{ a_config[MORPH_OPERATOR].toInt() }
  , m_morphSize{ a_config[MORPH_SIZE].toInt() }
  , m_morphElement{ a_config[MORPH_ELEMENT].toInt() }
{
}

void Filters::MorphologyOperation::process(std::vector<_data> &_data)
{
  cv::Mat m_Element = cv::getStructuringElement(m_morphElement, cv::Size(2 * m_morphSize + 1, 2 * m_morphSize + 1),
                                                cv::Point(m_morphSize, m_morphSize));
  morphologyEx(_data[0].processing, _data[0].processing, m_morphOperator, m_Element);
}