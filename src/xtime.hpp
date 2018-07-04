/*
* xtime_cpp - Library for work with time.
*
* Copyright (c) 2018 Yaroslav Barabanov. Email: elektroyar@yandex.ru
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef XTIME_HPP_INCLUDED
#define XTIME_HPP_INCLUDED

#include <string>

//functions for working with time
namespace FunctionsForTime {

    /** \brief �������� ����� � ���� ���������� � ���� ������
     * \return ������, ���������� �����
     */
    std::string getStrTime();

    /** \brief �������� Unix-����� ����������
     * \return Unix-�����
     */
    unsigned long long getUnixTime();

    /** \brief �������� Unix-����� �� ���� � ������������ �������
     * \param day ����
     * \param month �����
     * \param year ���
     * \param hour ���
     * \param minutes ������
     * \param seconds �������
     * \return Unix-�����
     */
    unsigned long long getUnixTime(int day, int month, int year, int hour, int minutes, int seconds);

    /** \brief ����� ��� �������� �������
     */
    class cTime {
        public:
        char seconds;   /**< ������� */
        char minutes;   /**< ������ */
        char hour;      /**< ��� */
        char day;       /**< ���� */
        char month;     /**< ����� */
        short year;     /**< ��� */

        /** \brief ����������� ������ ��� ��������� ������������� �������
         */
        cTime();

        /** \brief ������������� � ��������� �������
         * �������, ������ � ��� ����� ���������������� ������� ���������
         * \param day ����
         * \param month �����
         * \param year ���
         */
        cTime(int day, int month, int year);

        /** \brief ������������� � ��������� ������� � ����
         * \param day ����
         * \param month �����
         * \param year ���
         * \param hour ���
         * \param minutes ������
         * \param seconds �������
         */
        cTime(int day, int month, int year, int hour, int minutes, int seconds);

        /** \brief ������������� � ��������� unix-�������
         * \param timestamp unix-�����
         */
        cTime(unsigned long long timestamp);

        /** \brief ������������� � ��������� unix-������� � ������� ISO
         * ������ ������� ISO: 2013-12-06T15:23:01+00:00
         * \param timestamp unix-�����
         */
        cTime(std::string strISOformattedUTCdatetime);

        /** \brief �������� Unix-�����
         * \return Unix-�����
         */
        unsigned long long getUnixTime();

        /** \brief ���������� unix-�����
         * \param timestamp unix-�����
         */
        void setUnixTime(unsigned long long timestamp);

        /** \brief ������� ����� � ���� �� �����
         */
        void print();

        /** \brief �������� ���� � ����� � ���� ������
         * \return ������, ���������� ���� � �����
         */
        std::string getStr();
    };

    /** \brief �������������� ������ � ������� ISO � ������ ������ cTime
     * \param strISOformattedUTCdatetime ������ � ������� ISO, �������� 2013-12-06T15:23:01+00:00
     * \param t ����� ������� � ���� cTime, ������� ����� ��������.
     * \return ������ true
     */
    bool converISO(std::string strISOformattedUTCdatetime, cTime& t);

    /** \brief �������� unix �����
     * \param timedata ����������� �����
     * \return unix �����
     */
    unsigned long long getUnixTime(cTime& timedata);

    /** \brief �������� ����������� �����
     * \param timestamp unix �����
     * \return ����������� �����
     */
    cTime getTime(unsigned long long timestamp);

    enum eWday {
        SUN = 0,    /**< ����������� */
        MON,        /**< ����������� */
        TUS,        /**< ������� */
        WED,        /**< ����� */
        THU,        /**< ������� */
        FRI,        /**< ������� */
        SAT,        /**< ������� */
    };

    /** \brief �������� ���� ������
     * \param day ����
     * \param month �����
     * \param year ���
     * \return ���� ������ (SUN = 0, MON = 1, ... SAT = 6)
     */
    int getWday(int day, int month, int year);

    /** \brief �������� ���� ������
     * \param unix Unix-�����
     * \return ���� ������ (SUN = 0, MON = 1, ... SAT = 6)
     */
    int getWday(unsigned long long unix);

    /** \brief ���������� ���� � �����
     * \param unix ����� � ������� timestamp
     */
    void printDateAndTime(unsigned long long unix);
}

#endif // XTIME_HPP_INCLUDED
