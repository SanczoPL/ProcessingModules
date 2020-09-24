#ifndef FILTER_H
#define FILTER_H

#include <QDebug>
#include <QObject>

#include <opencv2/imgproc.hpp>

#include "../../include/block.h"

class BaseFilter;
class QJsonObject;

class Filter : public Block {
  Q_OBJECT
public:
  explicit Filter(QObject *parent = nullptr);
  void configure(QJsonObject const &a_config);

  void process(std::vector<_data> &_data);
  double getElapsedTime();

private:
  BaseFilter *m_baseFilter{};
  cv::TickMeter m_timer;
};

#endif // FILTER_H