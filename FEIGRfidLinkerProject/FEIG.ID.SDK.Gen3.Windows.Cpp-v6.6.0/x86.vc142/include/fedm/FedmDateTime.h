/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_DATE_TIME_H
#define FEDM_DATE_TIME_H

#include <string>

#include "FedmBase.h"



namespace FEDM
{

/// @brief DATA class with date and time settings
class FEDM_CLASS_DEF DateTime
{
	friend class FedmFriend;

public:
	DateTime();

	DateTime(int hour, int minute, int second, int milliSecond);

	DateTime(int year, int month, int day, int hour, int minute, int second, int milliSecond);

	~DateTime() { }

	void clear(void);

	/// @return True, if date or time values are valid
	bool isValid() const;

	/// @return True, if all time values are valid
	bool isValidTime() const;

	/// @return True, if all date values are valid
	bool isValidDate() const;

	/// @return Date and/or time string according to ISO 8601
	std::string toString(void) const;

	bool operator== (const DateTime & other) const;

	/// @return A DateTime object holding the current local date and time form the host system
	static DateTime currentDateTime(void);

	int year() const { return m_year; }
	void setYear(int year) { m_year = year; }

	int month() const { return m_month; }
	void setMonth(int month) { m_month = month; }

	int day() const { return m_day; }
	void setDay(int day) { m_day = day; }

	int hour() const { return m_hour; }
	void setHour(int hour) { m_hour = hour; }

	int minute() const { return m_minute; }
	void setMinute(int minute) { m_minute = minute; }

	int second() const { return m_second; }
	void setSecond(int second) { m_second = second; }

	int milliSecond() const { return m_milliSecond; }
	void setMilliSecond(int milliSecond) { m_milliSecond = milliSecond; }

private:
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
	int m_milliSecond;

}; // end of class DateTime

}; // end of namespace FEDM

#endif // FEDM_DATE_TIME_H
