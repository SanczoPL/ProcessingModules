#include "subtractor.h"
#include "subtractorlist.h"

constexpr auto NAME{ "Name" };

Subtractor::Subtractor(QObject *parent)
	: Processing(parent)
{
	m_subtractor = new Subtractors::None();
}

void Subtractor::configure(QJsonObject const &a_config)
{
	//H_logger->trace("Subtractor::configure()");
	delete m_subtractor;
	m_timer.reset();
	auto const NAME_STRING{ a_config[NAME].toString() };
	//H_logger->trace("Subtractor type: {}", NAME_STRING.toStdString());

	if (NAME_STRING == "GSOC")
	{
		m_subtractor = { new Subtractors::GSOC{ a_config } };
	}
	else if (NAME_STRING == "KNN")
	{
		m_subtractor = { new Subtractors::KNN{ a_config } };
	}
	else if (NAME_STRING == "MOG")
	{
		m_subtractor = { new Subtractors::MOG{ a_config } };
	}
	else if (NAME_STRING == "MOG2")
	{
		m_subtractor = { new Subtractors::MOG2{ a_config } };
	}
	else if (NAME_STRING == "GMG")
	{
		m_subtractor = { new Subtractors::GMG{ a_config } };
	}
	else if (NAME_STRING == "CNT")
	{
		m_subtractor = { new Subtractors::CNT{ a_config } };
	}
	else if (NAME_STRING == "LSBP")
	{
		m_subtractor = { new Subtractors::LSBP{ a_config } };
	}
	else if (NAME_STRING == "NONE")
	{
		m_subtractor = { new Subtractors::None{} };
	}
	else if (NAME_STRING == "MEDIAN")
	{
		m_subtractor = { new Subtractors::Median{ a_config } };
	}
	else if (NAME_STRING == "MEDIAN2")
	{
		m_subtractor = { new Subtractors::Median2{ a_config } };
	}
	else if (NAME_STRING == "ViBe")
	{
		m_subtractor = { new Subtractors::ViBe{ a_config } };
	}
	else if (NAME_STRING == "ABL")
	{
		m_subtractor = { new Subtractors::ABL{ a_config } };
	}
	else if (NAME_STRING == "ASBL")
	{
		m_subtractor = { new Subtractors::ASBL{ a_config } };
	}
	else if (NAME_STRING == "LOBSTER")
	{
		m_subtractor = { new Subtractors::LOBSTER{ a_config } };
	}
	else if (NAME_STRING == "WMV")
	{
		m_subtractor = { new Subtractors::WeightedMovingVariance{ a_config } };
	}
	else if (NAME_STRING == "WMM")
	{
		m_subtractor = { new Subtractors::WeightedMovingMean{ a_config } };
	}
	else if (NAME_STRING == "PBAS")
	{
		m_subtractor = { new Subtractors::PixelBasedAdaptiveSegmenter{ a_config } };
	}
	else
	{
		Logger->error("Unsupported subtractor type:{}", NAME_STRING.toStdString());
	}
}

void Subtractor::process(std::vector<_data> &_data)
{
	m_timer.start();

	if (_data[0].processing.empty())
	{
		Logger->error("Subtractor::process() image is empty!");
	}

	m_subtractor->process(_data);
	m_timer.stop();
}

double Subtractor::getElapsedTime()
{
	return m_timer.getTimeMilli();
}
